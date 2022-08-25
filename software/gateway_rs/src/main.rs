use std::io::BufRead;
use std::io::BufReader;
use std::time::Duration;

mod ukhn_to_influx;

/// Gateway name
const ORIGIN: &str = "TEA0";

/// Open a serial port at the specified path.  Keeps trying (and blocks) until
/// we can successfully open one.
///
/// # Arguments
///
/// * `path` - OS-dependent path to the serial port to open
///
/// # Returns
///
/// * Some sort of serial port (which type depends on the OS).
fn open_serial_port(path: &str) -> Box<dyn serialport::SerialPort> {
    let timeout = Duration::new(1, 0); // one second
    loop {
        let maybe_port = serialport::new(path, 115_200).timeout(timeout).open();
        if let Ok(port) = maybe_port {
            return port;
        }
    }
}

/// Try to upload a packet to InfluxDB.  No action is taken if the upload
/// fails.
///
/// # Arguments
///
/// * `packet` - Trimmed string received from the gateway hardware
fn upload_to_influx(line: &str) {
    let url = "http://localhost:8086/write?db=ukhasnet";

    eprintln!("line: {}", line);

    if let Err(e) = ureq::post(url)
        .set("Content-Type", "text/plain; charset=utf-8")
        .set("Accept", "application/json")
        .send_string(line)
    {
        // If upload fails then print a warning and discard the packet.  We
        // could buffer packets which don't upload.
        match e {
            ureq::Error::Status(_code, response) => {
                eprintln!("Influx POST returned response {:?}", response);
                eprintln!("Influx response body {}", response.into_string().unwrap());
            }
            ureq::Error::Transport(t) => {
                eprintln!("Transport error posting to influx: {:?}", t);
            }
        }
    }
}

fn main() {
    let path = "/dev/ttyACM0";
    println!("Opening serial port");
    let port = open_serial_port(path);
    println!("Making new bufreader");
    let b = BufReader::new(port);
    println!("Waiting for lines....");

    for line in b.lines().into_iter().flatten() {
        // Trim off whitespace
        let line = line.trim();

        println!("Received: {}", line);

        // Ignore any malformed packets
        match ukhasnet_parser::parse(&line.to_owned()) {
            Ok(mut packet) => {
                // Add this gateway to the packet's path
                packet.path.push(ORIGIN.to_owned());

                // Ignore any packets which can't be made into an influx string
                if let Ok(influx_str) = ukhn_to_influx::packet_to_influx(line, &packet) {
                    upload_to_influx(&influx_str);
                }
            },
            Err(e) => eprintln!("Parse failed: '{}' {}", line, e),
        }
    }
}
