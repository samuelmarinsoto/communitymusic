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

//use serde_json::Value;
use std::thread;
use std::thread::sleep;
use std::sync::Arc;

use modules::rust::client::{Client as Client, Cmds as Cmds};

fn main() {
    //execute();
    let socket = Arc::new(Client::new(
        "127.0.0.1".to_owned(), 7676));
    let socket_ref = Arc::clone(&socket);
    let com_thread = thread::spawn(move || {
        socket_ref.start_com();
    });

    com_thread.join().unwrap(); // esta fckin linea afecta la comunicacion

    /*let other_ref = Arc::clone(&socket);
    let timeout_thread =thread::spawn(move || {
        let mut counter = 0;
        while counter<= 20 {
            counter+=1;
            sleep(time::Duration::from_secs(1));
        }
        other_ref.set_petition(Cmds::Exit, &[]);
    });*/

    /*let data = r#"
    {
        "key1" : null,
        "key2" : 777,
        "arr1" : [false, 10, {"x": 80, "y": 170}],
        "key3" : true
    }
    "#;
    let json : Value = serde_json::from_str(&data).unwrap();
    let search_v = "arr1";
    print!("KEY-PAIR ---> ({}) : ({}) \n", search_v ,json[search_v][2]["y"]);
    let value = json[search_v].as_i64().unwrap_or(0);
    print!("JSON int = {}", value);*/
}