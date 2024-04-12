// >> Crate and external libs imports <<

// >> Project modules "imports" <<
pub mod modules{
    pub mod rust{
        pub mod client;
    }
}

pub mod app{
    pub mod rust;
}

// >> Modules access abbreviations <<
use app::rust::client_gui::VotingWindow as VotingWindow;

fn main() {
    let window = VotingWindow::new();
        window.run();
}