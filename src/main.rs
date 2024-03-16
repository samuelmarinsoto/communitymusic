use rstk::*;

// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod client;
    }
}


use modules::rust::client::Client as Client;

fn main() {
    let root = rstk::start_wish().unwrap();

    let hello = rstk::make_label(&root);
    hello.text("Hello from Rust/Tk");
  
    hello.grid().layout();
  
    rstk::mainloop();

    /*let client = Client::new("172.16.0.1".to_owned(), 49094);
    client.start_com();*/

    /*let js_data = "{\"x\":147,\"y\":\"hello\"}";
    let pre_js = serde_json::to_value(js_data).unwrap();
    let js: Value = serde_json::from_value(pre_js).unwrap();
    let jsx = json!(js_data);
    print!("{}\t{}\n", js["x"], jsx["x"]);*/
}