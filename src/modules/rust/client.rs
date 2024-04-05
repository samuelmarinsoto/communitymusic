use core::time;

// Socket related libraries
use std::net::{TcpStream, Shutdown};
use std::io::{Error, Read, Write};
use std::{str, thread};

// Thread related libraries
use std::sync::{Mutex, Arc}; 

// JSON library
use serde_json::{json, Value}; // ---> library for json parsing


pub enum Cmds {
    Idling,
    Request,
    UpVote,
    DownVote,
    Exit
}
pub struct Client{
    socket: Mutex<TcpStream>, //TcpStream,
    status: Mutex<bool>, // Arc< Mutex <bool> >,
    petition: Mutex <String>, // String,
    response: Mutex<String> // String
}

impl Client{

    /* Creates an instance of Client wrapped in a Result<Client, Error> for */
    #[allow(dead_code)]
    pub fn new(ip:&str, port:i32)-> Result < Client, Error > {
        // Create a bind with ip and port
        let addr_binding = format!("{}:{}", ip, port);
        // Try connecting the TCPstream through the binding
            // On success socket will connect
            // On error the socket will fail to bind
        let stream = TcpStream::connect(addr_binding);

        // Access the Result<...> of the TCPstream and determine the return type of instance
        match stream{
            Ok(s) => { // Connection success !
                return Ok(Client{socket:Mutex::new(s), status:Mutex::new(true),
                        petition:Mutex::new("{\"cmd\":\"idling\"}".to_owned()), response:Mutex::new("None".to_owned())})
            },
            Err(e) => { // Connection failed :(
                return Err(e);
            }
        };
    }

    // Starts communicating with server every few ticks on separate listener thread
    #[allow(dead_code)]
    pub fn start_com(&self) -> (){
        // Starts communication using a loop for constant messaging
        while self.access_condition() {
            // Access(LOCK) the current petition on mutex-petition attribute
                let msg_buffer = self.petition.lock().unwrap();
            // Access(LOCK) the socket, or TCPstream
                let mut connection = self.socket.lock().unwrap();
                connection.write(msg_buffer.as_bytes()).unwrap(); // Send a petition
            // Drop the buffer to unlock
                drop(msg_buffer);
            // Set petition to default
                self.set_petition(Cmds::Idling,&[]);
                //-------------{Obtain response(bytes) from Server}--------------//
                let mut response_buffer = [0 as u8; 5000];
                connection.read(&mut response_buffer).unwrap();
                let mut server_response = match str::from_utf8(&response_buffer) {
                    Ok(rp_slice) => rp_slice,
                    Err(e) => panic!("ERROR: {}", e)
                };
                let new_response = &server_response.replace("\u{0000}", " ");
                server_response = new_response.trim();
                //----------------------{Analyze received json}----------------------//
                let json_response: Value = match serde_json::from_str(server_response){
                    Ok(r) => r,
                    Err(e) => panic!("ERROR: {}", e)
                };
                if json_response["cmd"] == "send-songs" {
                    // save response to client instance
                    let mut mutex_response = self.response.lock().unwrap();
                    *mutex_response = server_response.to_owned();
                    drop(mutex_response);
                }
                if (json_response["cmd"] == "up-vote" || json_response["cmd"] == "down-vote") && json_response["status"] == "OK" {
                    self.set_petition(Cmds::Request, &[]);
                }
                if json_response["cmd"] == "exiting" && json_response["status"] == "OK" {
                    self.stop_communication();
                }
            }
    }

    #[allow(dead_code)]
    fn access_condition(&self) -> bool {
        let value = self.status.lock().unwrap();
        *value
    }

    #[allow(dead_code)]
    pub fn stop_communication(&self) -> (){
        let mut ptr_status = self.status.lock().unwrap();
        *ptr_status = false;
    }

    #[allow(dead_code)]
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

    // Returns the received response of Server at recent times 
    #[allow(dead_code)]
    pub fn get_current_response(&self) -> String{
        let copy_response = self.response.lock().unwrap();
        copy_response.clone()
    }
}