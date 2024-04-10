// >> Crate and external libs imports <<


// >> Project modules "imports" <<
pub mod modules{
    pub mod rust;
}

pub mod app{
    pub mod rust;
}

// >> Modules access abbreviations <<
use modules::rust::client::Client as Client;
use app::rust::client_gui::VotingWindow as VotingWindow;

fn main() {
    let window = VotingWindow::new();
        window.run();
}