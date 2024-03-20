use test::execute;

// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod test;

        pub mod client;
    }
}

pub mod test;

//use core::time;
//use std::fmt::format;

//use serde_json::Value;
//use std::thread;
//use std::thread::sleep;

//use modules::rust::client::Client as Client;

fn main() {
    execute();
    /*let mut socket = Client::deploy("127.0.0.1".to_owned(), 7676);
    let com_thread = thread::spawn(move || {
        socket.start_com();
    });
    socket.set_petition(&["up-vote", "0x008"]);
    sleep(time::Duration::from_secs(12));
    socket.set_petition(&["down-vote", "0x106"]);*/

    /*let data = r#"
    {
        "key1" : null,
        "key2" : 777,
        "arr1" : [false, 10, {"x": 80, "y": 170}],
        "key3" : true
    }
    "#; 7u89
    let json : Value = serde_json::from_str(&data).unwrap();
    let search_v = "arr1";
    print!("KEY-PAIR ---> ({}) : ({}) \n", search_v ,json[search_v][2]["y"]);
    let value = json[search_v].as_i64().unwrap_or(0);
    print!("JSON int = {}", value);*/
}