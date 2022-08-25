//! Parse a ukhasnet packet and turn the measurements into something suitable
//! for InfluxDB
//!
//! This code is heavily based on Adam Greig's
//! https://github.com/adamgreig/ukhasnet-influxdb

use anyhow::{Result, bail};
use std::collections::HashMap;
use ukhasnet_parser::{Packet, DataField};
use std::time::{UNIX_EPOCH, SystemTime};

/// Append a numeric field to the line.
fn numeric_field(
    field_name: &'static str,
    data_points: &[f32],
    field_counts: &mut HashMap<&'static str, usize>,
    line_fields: &mut Vec<String>,
) {
    // How many times we have seen a data field of this type, including
    // this one.
    let field_count = field_counts.entry(field_name).or_default();
    *field_count += 1;

    for (i, data_point) in data_points.iter().enumerate() {
        line_fields.push(format!("{}_{}_{}={}", field_name, field_count, i, data_point));
    }
}

/// Convert a ukhasnet packet to a string ready for posting to InfluxDB.  May
/// fail if the ukhasnet packet is particularly malformed.
pub fn packet_to_influx(packet_raw: &str, p: &Packet) -> Result<String> {
    let node = match p.path.get(0) {
        Some(s) => s,
        None => bail!("No origin node name in path"),
    };
    let pathend = match p.path.last() {
        Some(s) => s,
        None => bail!("No node at end of path"),
    };

    // The number of data fields of each type we have seen
    let mut field_counts: HashMap<&'static str, usize> = HashMap::new();

    let mut line_fields: Vec<String> = Vec::new();

    for df in &p.data {
        match df {
            DataField::Temperature(t) => {
                numeric_field("temperature", t, &mut field_counts, &mut line_fields);
            },
            DataField::Voltage(v) => {
                numeric_field("voltage", v, &mut field_counts, &mut line_fields);
            },
            DataField::Current(i) => {
                numeric_field("current", i, &mut field_counts, &mut line_fields);
            },
            DataField::Humidity(h) => {
                numeric_field("humidity", h, &mut field_counts, &mut line_fields);
            },
            DataField::Pressure(p) => {
                numeric_field("pressure", p, &mut field_counts, &mut line_fields);
            },
            DataField::Sun(s) => {
                numeric_field("sun", s, &mut field_counts, &mut line_fields);
            },
            DataField::Rssi(r) => {
                numeric_field("rssi", r, &mut field_counts, &mut line_fields);
            },
            DataField::Count(c) => {
                numeric_field("count", c, &mut field_counts, &mut line_fields);
            },
            DataField::Custom(c) => {
                numeric_field("custom", c, &mut field_counts, &mut line_fields);
            },
            DataField::Location(l) => {
                let field_count = field_counts.entry("location").or_default();
                *field_count += 1;
                match l.latlng {
                    Some((latitude, longitude)) => {
                        line_fields.push(format!("location_{}_latitude={}",
                                                  field_count, latitude));
                        line_fields.push(format!("location_{}_longitude={}",
                                                  field_count, longitude));
                    },
                    None => ()
                }
                match l.alt {
                    Some(alt) => line_fields.push(
                        format!("location_{}_altitude={}",
                                field_count, alt)),
                    None => ()
                }
            },
            DataField::WindSpeed(w) => {
                let field_count = field_counts.entry("windspeed").or_default();
                *field_count += 1;
                match w.speed {
                    Some(speed) => {
                        line_fields.push(format!("windspeed_{}_speed={}",
                                              field_count, speed));
                    },
                    None => ()
                }
                match w.bearing {
                    Some(b) => line_fields.push(
                        format!("windspeeed_{}_bearing={}",
                                field_count, b)),
                    None => ()
                }
            },
            DataField::Zombie(z) => {
                let field_count = field_counts.entry("zombie").or_default();
                *field_count += 1;
                line_fields.push(format!("zombie_{}={}i", field_count, z));
            },
        }
    }

    if let Some(comment) = &p.comment {
        line_fields.push(format!("message=\"{}\"", comment));
    }

    // Append the raw packet for reference
    line_fields.push(format!("sentence=\"{}\"", packet_raw));

    // Get the current time in unix epoch nanoseconds
    let epoch_ns = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .expect("System time is before unix epoch?")
        .as_nanos();

    Ok(format!(
        "packet,node={},pathend={} {} {}",
        node,
        pathend,
        line_fields.join(","),
        epoch_ns,
    ))
}
