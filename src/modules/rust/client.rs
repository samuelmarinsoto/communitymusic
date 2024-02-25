use std::fmt::format;
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use serde_json::{Value}; // ---> library for json parsing

pub struct Client{
    IP: String,
    port: i32,
    socket: TcpStream
}

impl Client{
    pub fn deploy(ip:String, port_num:i32)-> Client{
        let binding = format!("{}:{}", ip, port_num);
        let stream = TcpStream::connect(binding).unwrap();
        print!("Connected to: {}:{}", ip, port_num);


        Client {IP:ip, port:port_num, socket:stream}
    }

    fn start_com() -> (){

    }

    pub fn say_something(mut self, msg:&[u8]) -> i32{
        self.socket.write(msg).unwrap();
        return 0;
    }

    pub fn set_petition(brief: &str) -> &str {
        if brief == "up-vote" {

        }

        if brief == "down-vote" {

        }

        if brief == "ask" {
            
        }
        r#"{"pow": null}"# // TODO: change for generic petition
    }

    pub fn exit(&mut self) -> (){
        self.socket.shutdown(Shutdown::Both);
    }
}