// ---------------------------------- GTK dependencies
extern crate gtk;

use gtk::prelude::*;
use gtk::{Button, Grid, Label, Window, WindowType};

// ---------------------------------- Project things
use crate::modules::rust::client::Client as Client;
use serde_json::Value;
use std::str::FromStr;


// ---------------------------------- Mutex and threads
use std::sync::{Arc, Mutex};
use std::thread::{self, sleep, Thread};
use std::time::Duration;
// Glogs
use log::*;
use glog::Flags;

// Rust GTK window to preview playlist songs
pub struct VotingWindow {
    window: Window,
}

impl VotingWindow {
    pub fn new() -> VotingWindow {
    // ----------------------------- All this client processes for the window could be changed into function
    	// start glog
    	glog::new().init(Flags::default()).unwrap();

        // The client should try to connect to the designated server address (TODO: as such the IP and port fields should be changed for the ones from INI)
        /* HOW SHOULD IT WORK 
            SUCCESS: The voting window opens normally
            FAIL: The voting window does not open up and instead goes back to start window
        */
        let client = match Client::new("127.0.0.1", 49094){
            Ok(c) => c,
            Err(e) => {
            	info!("ERROR: cliente rust no pudo conectar socket");
            	panic!("ERROR: {}", e);  // TODO: set a behavior to disregard this code an open another window
            }
        };

        // Create an Arc to thread the client communication processes
        let cli_arc_guard = Arc::new(client);
            // <+> >>> 1st subprocess: Establish a communication channel
            let client_copy_b = Arc::clone(&cli_arc_guard);
            thread::spawn(move || {
                client_copy_b.start_com();
            });

        // Create an auto-updated string which contains the most recent response from server(most cases is the list of songs up-to-date)
        let mut songs = Arc::new(Mutex::new("".to_owned()));
            // <+> >>> 2nd subprocess: Get responses from server every few seconds and save into "songs"
            let client_copy_b = Arc::clone(&cli_arc_guard);
            let songs_copy = Arc::clone(&songs);
            thread::spawn(move || {
                loop { // Get current response from server and copy into current field
                    let mut songs_info = songs_copy.lock().unwrap();
                    *songs_info = client_copy_b.get_current_response();
                    drop(songs_info);
                    sleep(Duration::from_secs(2));
                }
            });
        sleep(Duration::from_secs(4));
        // Create a usable client from within the GTK application
        let usable_client = Arc::clone(&cli_arc_guard);
        let mut json_songs = Value::from_str(songs.lock().unwrap().as_str()).unwrap(); // This has the list of songs inside it
        
    // ----------------------------- All this client processes for the window could be changed into function

        // Initialize GTK
        info!("Inicializando ventana");
        gtk::init().expect("Couldn't initialize GTK library binaries");

        // Create a new window
        let window = Window::new(WindowType::Toplevel);
        window.set_title("Votación");
        window.set_default_size(600, 200);

        // Definir acciones para cada botón "Vote Up"
        let vote_up_actions = vec![
            || info!("Vote Up 1 clicked!"),
            || info!("Vote Up 2 clicked!"),
            || info!("Vote Up 3 clicked!"),
            || info!("Vote Up 4 clicked!"),
            || info!("Vote Up 5 clicked!"),
            || info!("Vote Up 6 clicked!"),
            || info!("Vote Up 7 clicked!"),
            || info!("Vote Up 8 clicked!"),
            || info!("Vote Up 9 clicked!"),
            || info!("Vote Up 10 clicked!"),
        ];

        // Definir acciones para cada botón "Vote Down"
        let vote_down_actions = vec![
            || info!("Vote Down 1 clicked!"),
            || info!("Vote Down 2 clicked!"),
            || info!("Vote Down 3 clicked!"),
            || info!("Vote Down 4 clicked!"),
            || info!("Vote Down 5 clicked!"),
            || info!("Vote Down 6 clicked!"),
            || info!("Vote Down 7 clicked!"),
            || info!("Vote Down 8 clicked!"),
            || info!("Vote Down 9 clicked!"),
            || info!("Vote Down 10 clicked!"),
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
