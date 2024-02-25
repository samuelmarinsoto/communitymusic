// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod test;

        pub mod client;
    }
}

use serde_json::Value; 

//use modules::rust::client::Client as Client;

fn main() {
    /*let msg_to_send = b"Hello from Rust!!";
    let socket = Client::deploy("127.0.0.1".to_owned(), 7676);
    socket.say_something(msg_to_send);*/
    let data = r#"
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
    print!("JSON int = {}", value);
}