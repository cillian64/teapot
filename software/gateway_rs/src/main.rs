use std::io::BufRead;
use std::io::BufReader;
use std::time::Duration;

extern crate serialport;
extern crate ureq;

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

/// Check whether this thing looks like a valid ukhasnet packet
///
/// # Arguments
///
/// * `packet` - Trimmed string received from the gateway hardware
///
/// # Returns
///
/// * true if this looks like a packet, false otherwise.
fn check_packet(packet: &str) -> bool {
    if packet.chars().count() < 2 {
        // Must have at least a hop and sequence-number
        return false;
    }
    let mut chars = packet.chars();
    let hop = chars.next().unwrap();
    let seq = chars.next().unwrap();
    if !hop.is_ascii_digit() {
        // Hop must be a single numerical digit
        return false;
    }
    if !seq.is_ascii_lowercase() {
        // Sequence number must be a single lower-case character
        return false;
    }
    // Could check more things but this is enough to filter out complete
    // garbage, such as accidentally getting the wrong serial port.
    true
}

/// Try to upload a packet to ukhas.net.  No action is taken if the upload
/// fails.
///
/// # Arguments
///
/// * `packet` - Trimmed string received from the gateway hardware
fn upload_packet(packet: &str) {
    let url = "http://www.ukhas.net/api/upload";
    let origin = "TEA0";
    let resp = ureq::post(url).send_form(&[("origin", origin), ("data", packet)]);
    // If upload fails then print a warning and discard the packet.  We can't
    // indicate a timestamp for old packets so storing and uploading packets
    // later would corrupt the time series data.
    if let Err(why) = resp {
        println!("Failed to upload packet: {}", why);
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
        let line_trimmed = line.trim();
        println!("Received: {}", line_trimmed);

        if check_packet(&line_trimmed) {
            upload_packet(&line_trimmed);
        }
    }
}
