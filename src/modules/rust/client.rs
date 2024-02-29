use core::time;
use std::fmt::format;
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use std::thread::sleep;
use std::time::Duration;
use serde_json::{json, Value, Result}; // ---> library for json parsing


pub struct Client{
    IP: String,
    port: i32,
    socket: TcpStream,
    status: bool,
    petition: String,
    response: String
}

impl Client{
    pub fn deploy(ip:String, port_num:i32)-> Client{
        let binding = format!("{}:{}", ip, port_num);
        let stream = TcpStream::connect(binding).unwrap();
        print!("Connected to: {}:{}", ip, port_num);

        Client {IP:ip, port:port_num, socket:stream, status:true, 
                petition:"{ \"cmd\":\"idling\"}".to_owned(), response: "null".to_owned()}
    }

    pub fn start_com(&mut self) -> (){
        while self.status{
            self.socket.write(self.petition.as_bytes()).unwrap();
            self.set_petition(&["idling"]);
            sleep(time::Duration::from_secs(5));
        }
    }

    pub fn stop_communication(&mut self) -> (){
        self.status = false;
    }

    pub fn set_petition(&mut self, args: &[&str]) -> () {
        if args[0] == "up-vote" {
            let mut json = json!({
                "cmd" : "up-vote",
                "id": "0"
            });
            json["id"] = json!(args[1]);

            self.petition = json.to_string();
        } else if args[0] == "down-vote" {
            let mut json = json!({
                "cmd" : "down-vote",
                "id": "0"
            });
            json["id"] = json!(args[1]);

            self.petition = json.to_string();
        } else if args[0] == "ask" {
            let json = json!({
                "cmd": "send-songs"
            });

            self.petition = json.to_string();
        } else if args[0] == "exit" {
            let json = json!({
                "cmd": "exiting"
            });

            self.petition = json.to_string();
        } else if args[0] == "idling" {
            let json = json!({
                "cmd": "idling"
            });

            self.petition = json.to_string();
        }
    }
}