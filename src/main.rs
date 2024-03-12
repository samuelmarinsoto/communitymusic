use test::execute;

// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod test;

        pub mod client;
    }
}

pub mod test;

use core::time;
//use std::fmt::format;
    
use serde_json::{json, Value};
use std::thread;
use std::thread::sleep;
use std::sync::Arc;


use modules::rust::client::{Client as Client, Cmds as Cmds};

fn main() {     
    let client = Client::new("172.16.0.1".to_owned(), 49094);
    client.start_com();
    /*let js_data = "{\"x\":147,\"y\":\"hello\"}";
    let pre_js = serde_json::to_value(js_data).unwrap();
    let js: Value = serde_json::from_value(pre_js).unwrap();
    let jsx = json!(js_data);
    print!("{}\t{}\n", js["x"], jsx["x"]);*/
}