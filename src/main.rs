// >> Project modules "imports" <<
mod modules{
    pub mod rust{
        pub mod test;

        pub mod client;
    }
}

use modules::rust::client::Client as Client;

fn main() {
    let msg_to_send = b"Hello from Rust!!";
    let socket = Client::deploy("127.0.0.1".to_owned(), 7676);
    socket.say_something(msg_to_send);
}