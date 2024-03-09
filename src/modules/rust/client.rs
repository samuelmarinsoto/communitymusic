use core::time;

// Socket related libraries
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use std::str;

// Thread related libraries
use std::sync::Mutex; 

use serde_json::{json, Value, Result}; // ---> library for json parsing

pub enum Cmds {
    Idling,
    Request,
    UpVote,
    DownVote,
    Exit
}
pub struct Client{
    IP: String,
    port: i32,
    socket: Mutex<TcpStream>, //TcpStream,
    status: Mutex<bool>, // Arc< Mutex <bool> >,
    petition: Mutex <String>, // tring,
    response: Mutex<String> // String
}

impl Client{
    pub fn new(ip:String, port_num:i32)-> Client {
        let binding = format!("{}:{}", ip, port_num);
        let stream = TcpStream::connect(binding).unwrap();
        print!("Connected to: {}:{}\n", ip, port_num);

        Client {IP:ip, port:port_num, socket:Mutex::new(stream), status:Mutex::new(true), 
                petition:Mutex::new("{\"cmd\":\"idling\"}".to_owned()), response: Mutex::new("null".to_owned())}
    }

    pub fn start_com(&self) -> (){
        while self.access_condition() {
            let msg_buffer = self.petition.lock().unwrap();
            // ^^ get petition json string
            let mut connection = self.socket.lock().unwrap();
            connection.write(msg_buffer.as_bytes()).unwrap();
            drop(msg_buffer);
            // ^^ send over socket
            self.set_petition(Cmds::Idling,&[]);
            // ^^ default the petition to the voidless type
            //-------------{Obtain response(bytespetition_type) from Server}--------------//
            let mut response_buffer = [0 as u8; 1024];
            connection.read(&mut response_buffer).unwrap();
            let response = match str::from_utf8(&response_buffer) {
                Ok(rp_slice) => String::from(rp_slice),
                Err(e) => panic!("ERROR: {}", e)
            };
            print!("{}", response);
            //-------------[Break points]-------------//
            /*let json_response: Value = serde_json::from_str(&response).unwrap(); // NOTE: could be changed to manage parsing errors
                // ^^ parse the received string as
            // Responses
            /*if response == "Hello"{ // Proto
                self.set_petition(Cmds::UpVote, &["12712F1213"]);
            }*/
            // TO-DO: manage all responses
            if json_response["cmd"] == "send-songs" {
                // Code here
                self.set_petition(Cmds::UpVote, &["0x008"]);
                //save to response;
            } else if json_response["cmd"] == "up-vote" {
                // Code here
                self.set_petition(Cmds::DownVote, &["0x107"])
            } else if json_response["cmd"] == "down-vote" {
                // Code here
                self.set_petition(Cmds::Request, &[]);
            }
            */
        }
    }

    fn access_condition(&self) -> bool {
        let value = self.status.lock().unwrap();
        *value
    }

    pub fn stop_communication(&self) -> (){
        let mut ptr_status = self.status.lock().unwrap();
        *ptr_status = false;
    }

    pub fn set_petition(&self, petition_type: Cmds,args: &[&str]) -> () {
        let mut json_string = self.petition.lock().unwrap();
        match petition_type {
            Cmds::Idling => {
                let json = json!({
                    "cmd": "idling"
                });

                *json_string = json.to_string();
            },
            Cmds::Request => {
                let json = json!({
                    "cmd": "send-songs"
                });
    
                *json_string = json.to_string();
            },
            Cmds::DownVote => {
                let mut json = json!({
                    "cmd" : "down-vote",
                    "id": "0"
                });
                json["id"] = json!(args[0]);
    
                *json_string = json.to_string();
            },
            Cmds::UpVote => {
                let mut json = json!({
                    "cmd" : "up-vote",
                    "id": "0"
                });
                json["id"] = json!(args[0]);
    
                *json_string = json.to_string();
            },
            Cmds::Exit => {
                let json = json!({
                    "cmd": "exiting"
                });
    
                *json_string = json.to_string();
            }
        }
    }
}