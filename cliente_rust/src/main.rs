extern crate gtk;

use gtk::prelude::*;
use gtk::{Button, Grid, Label, Window, WindowType};

pub struct VotingWindow {
    window: Window,
}

impl VotingWindow {
    pub fn new() -> VotingWindow {
        // Inicializar la aplicación GTK
        gtk::init().expect("No se pudo inicializar GTK.");

        // Crear una nueva ventana
        let window = Window::new(WindowType::Toplevel);
        window.set_title("Votación");
        window.set_default_size(600, 200);

        // Definir acciones para cada botón "Vote Up"
        let vote_up_actions = vec![
            || println!("Vote Up 1 clicked!"),
            || println!("Vote Up 2 clicked!"),
            || println!("Vote Up 3 clicked!"),
            || println!("Vote Up 4 clicked!"),
            || println!("Vote Up 5 clicked!"),
            || println!("Vote Up 6 clicked!"),
            || println!("Vote Up 7 clicked!"),
            || println!("Vote Up 8 clicked!"),
            || println!("Vote Up 9 clicked!"),
            || println!("Vote Up 10 clicked!"),
        ];

        // Definir acciones para cada botón "Vote Down"
        let vote_down_actions = vec![
            || println!("Vote Down 1 clicked!"),
            || println!("Vote Down 2 clicked!"),
            || println!("Vote Down 3 clicked!"),
            || println!("Vote Down 4 clicked!"),
            || println!("Vote Down 5 clicked!"),
            || println!("Vote Down 6 clicked!"),
            || println!("Vote Down 7 clicked!"),
            || println!("Vote Down 8 clicked!"),
            || println!("Vote Down 9 clicked!"),
            || println!("Vote Down 10 clicked!"),
        ];

        // Crear un contenedor grid
        let grid = Grid::new();
        grid.set_column_homogeneous(true);
        grid.set_row_homogeneous(true);

        // Crear botones "Vote Up" con acciones
        for (i, action) in vote_up_actions.into_iter().enumerate() {
            let button = Button::with_label(&format!("Vote Up {}", i + 1));
            button.connect_clicked(move |_| action());
            grid.attach(&button, 0, i as i32, 1, 1);
        }

        // Crear etiquetas de canciones
        for i in 0..10 {
            let label = Label::new(Some(&format!("Canción {}", i + 1)));
            grid.attach(&label, 1, i as i32, 1, 1);
        }

        // Crear botones "Vote Down" con acciones
        for (i, action) in vote_down_actions.into_iter().enumerate() {
            let button = Button::with_label(&format!("Vote Down {}", i + 1));
            button.connect_clicked(move |_| action());
            grid.attach(&button, 2, i as i32, 1, 1);
        }

        // Agregar el grid a la ventana
        window.add(&grid);

        VotingWindow { window }
    }

    pub fn run(&self) {
        // Mostrar la ventana
        self.window.show_all();

        // Conectar el evento de eliminación de la ventana
        self.window.connect_delete_event(|_, _| {
            gtk::main_quit();
            false.into()
        });

        // Iniciar el bucle de eventos GTK
        gtk::main();
    }
}

fn main() {
    let voting_window = VotingWindow::new();
    voting_window.run();
}