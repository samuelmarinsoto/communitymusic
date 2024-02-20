use std::fmt::format;
use std::net::{TcpStream, Shutdown};
use std::io::{Read, Write};
use std::str::from_utf8;

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

    fn begin_com() -> (){

    }

    pub fn say_something(mut self, msg:&[u8]) -> i32{
        self.socket.write(msg).unwrap();
        return 0;
    }

    pub fn post_request() -> bool {
        true
    }

    pub fn exit(&mut self) -> (){
        self.socket.shutdown(Shutdown::Both);
    }
}