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
    let client = Client::new("127.0.0.1".to_owned(), 7676);
    client.start_com();
}