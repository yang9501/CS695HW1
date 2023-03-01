use std::fs;
use std::thread;
use std::time;

fn main() {
    let gpio_path: &str = "/sys/class/gpio/gpio";
    let traffic_light1_ports: [String; 3] = [gpio_path.to_owned()+"44", gpio_path.to_owned()+"68", gpio_path.to_owned()+"67"];
    let traffic_light2_ports: [String; 3] = [gpio_path.to_owned()+"26", gpio_path.to_owned()+"46", gpio_path.to_owned()+"65"];
    for index in 0..traffic_light1_ports.len() {
        write_led("/direction".to_string(), traffic_light1_ports[index].clone(), "out".to_string());
        write_led("/direction".to_string(), traffic_light2_ports[index].clone(), "out".to_string());
    }

    loop {
        cycle_lights(traffic_light1_ports[0].clone(), traffic_light1_ports[1].clone(), traffic_light1_ports[2].clone(), traffic_light2_ports[0].clone(), traffic_light2_ports[1].clone(), traffic_light2_ports[2].clone());
    }
}

fn cycle_lights(green_port1:String, yellow_port1:String, red_port1:String, green_port2:String, yellow_port2:String, red_port2:String) {
    write_led("/value".to_string(), green_port1.clone(), "1".to_string());
    write_led("/value".to_string(), red_port2.clone(), "1".to_string());

    thread::sleep(time::Duration::from_secs(10));

    write_led("/value".to_string(), green_port1.clone(), "0".to_string());
    write_led("/value".to_string(), yellow_port1.clone(), "1".to_string());

    thread::sleep(time::Duration::from_secs(5));

    write_led("/value".to_string(), yellow_port1.clone(), "0".to_string());
    write_led("/value".to_string(), red_port1.clone(), "1".to_string());
    write_led("/value".to_string(), green_port2.clone(), "1".to_string());
    write_led("/value".to_string(), red_port2.clone(), "0".to_string());

    thread::sleep(time::Duration::from_secs(10));

    write_led("/value".to_string(), green_port2.clone(), "0".to_string());
    write_led("/value".to_string(), yellow_port2.clone(), "1".to_string());

    thread::sleep(time::Duration::from_secs(5));

    write_led("/value".to_string(), yellow_port2.clone(), "0".to_string());
    write_led("/value".to_string(), red_port1.clone(), "0".to_string());
}

fn write_led(filename:String, port:String, value:String) {
    fs::write(port+&filename,value).expect("Unable to write file");
}
