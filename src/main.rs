use rstk::*;
use std::sync::Arc;
use std::thread::{self, Thread};

// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod client;
    }
}


use modules::rust::client::Client as Client;

fn main() {
    /*let root = rstk::start_wish().unwrap();

    let hello = rstk::make_label(&root);
    hello.text("Hello from Rust/Tk");
  
    hello.grid().layout();
  
    rstk::mainloop();*/

    let client = Client::new("127.0.0.1", 49050);
    match client {
        Ok(cli) => {
            let arc_guard = Arc::new(cli);
            let copy = Arc::clone(&arc_guard);
            thread::spawn(move || {
                copy.start_com();
            });
            loop {
                let response = arc_guard.get_current_response();
                print!("Server said: {}\n", response);
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
