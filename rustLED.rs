use std::fs;
use std::thread;
use std::time;

fn main() {
    let gpio_path: &str = "/sys/class/gpio/gpio";
    let mut trafficLight1Ports: [String; 3] = [gpio_path.to_owned()+"44", gpio_path.to_owned()+"68", gpio_path.to_owned()+"67"];
    let mut trafficLight2Ports: [String; 3] = [gpio_path.to_owned()+"26", gpio_path.to_owned()+"46", gpio_path.to_owned()+"65"];
    for index in 0..trafficLight1Ports.len() {
        writeLED("/direction".to_string(), trafficLight1Ports[index].clone(), "out".to_string());
        writeLED("/direction".to_string(), trafficLight2Ports[index].clone(), "out".to_string());
    }

    while(true) {
        cycleLights(trafficLight1Ports[0].clone(), trafficLight1Ports[1].clone(), trafficLight1Ports[2].clone(), trafficLight2Ports[0].clone(), trafficLight2Ports[1].clone(), trafficLight2Ports[2].clone());
    }
}

fn cycleLights(greenPort1:String, yellowPort1:String, redPort1:String, greenPort2:String, yellowPort2:String, redPort2:String) {
    writeLED("/value".to_string(), greenPort1.clone(), "1".to_string());
    writeLED("/value".to_string(), redPort2.clone(), "1".to_string());

    thread::sleep(time::Duration::from_secs(10));

    writeLED("/value".to_string(), greenPort1.clone(), "0".to_string());
    writeLED("/value".to_string(), yellowPort1.clone(), "1".to_string());

    thread::sleep(time::Duration::from_secs(5));

    writeLED("/value".to_string(), yellowPort1.clone(), "0".to_string());
    writeLED("/value".to_string(), redPort1.clone(), "1".to_string());
    writeLED("/value".to_string(), greenPort2.clone(), "1".to_string());
    writeLED("/value".to_string(), redPort2.clone(), "0".to_string());

    thread::sleep(time::Duration::from_secs(10));

    writeLED("/value".to_string(), greenPort2.clone(), "0".to_string());
    writeLED("/value".to_string(), yellowPort2.clone(), "1".to_string());

    thread::sleep(time::Duration::from_secs(5));

    writeLED("/value".to_string(), yellowPort2.clone(), "0".to_string());
    writeLED("/value".to_string(), redPort1.clone(), "0".to_string());
}

fn writeLED(filename:String, port:String, value:String) {
    fs::write(port+&filename,value);
}
