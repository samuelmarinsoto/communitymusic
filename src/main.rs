use rstk::*;
use serde_json::Value;
use std::str::FromStr;
use std::sync::Arc;
use std::thread::{self, sleep, Thread};
use std::time::Duration;

// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod client;
    }
}

use modules::rust::client::Client as Client;

fn main() {

    let client = Client::new("127.0.0.1", 49094);
    match client {
        Ok(cli) => {
            let arc_guard = Arc::new(cli);
            let copy = Arc::clone(&arc_guard);
            thread::spawn(move || {
                copy.start_com();
            });
            loop {
                let response: String = arc_guard.get_current_response();
                if response != "None" {
                    let _json: Value = match serde_json::from_str(response.as_str()){
                        Ok(j) => j,
                        Err(e) => panic!("ERROR: {}", e)
                    };
                    print!("Server sent songs: \n{}\n", _json["attach"]);
                } else {
                    print!("Server said: {}\n", response);
                }
                sleep(Duration::from_secs(6));
            }
        },
        Err(e) => {
            eprint!("Client couldnt communicate with server\nError: {}\n", e)
        }
    }

    /*let js_data = "{\"x\":147,\"y\":\"hello\"}";
    let pre_js = serde_json::to_value(js_data).unwrap();
    let js: Value = serde_json::from_value(pre_js).unwrap();
    let jsx = json!(js_data);
    print!("{}\t{}\n", js["x"], jsx["x"]);*/
}