// ---------------------------------- GTK dependencies
extern crate gtk;

use gtk::prelude::*;
use gtk::{Button, Grid, Label, Window, WindowType};

// ---------------------------------- Project things
use crate::modules::rust::client::{Client as Client, Cmds};
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
    client: Arc<Client>, // This should save the client during the execution of the program
    songs: Arc< Mutex<String> >
}

impl VotingWindow {
    pub fn new() -> VotingWindow {
    // ----------------------------- All this client processes for the window could be changed into function
    	// Start glog
    	glog::new().init(Flags::default()).unwrap();

        // The client should try to connect to the designated server address (TODO: as such the IP and port fields should be changed for the ones from INI)
        /* HOW SHOULD IT WORK 
            SUCCESS: The voting window opens normally
            FAIL: The voting window does not open up and instead goes back to start window
        */
        let mut songs_json = Arc::new( Mutex::new("".to_owned()));

        let client = match Client::new("127.0.0.1", 49094){
            Ok(c) => { // Create an arc of the connected client and
                let arc_guard = Arc::new(c);
                // ----------------
                    // >>> Communication thread 
                    let cli_copy = Arc::clone(&arc_guard);
                    thread::spawn(move || {
                       cli_copy.start_com();
                    });
                    // >>> List of songs retrieval
                    let other_cli_copy = Arc::clone(&arc_guard);
                    let mut json_lock = Arc::clone(&songs_json);
                    thread::spawn(move || {
                        loop {
                            sleep(Duration::from_millis(1800));
                            let mut songs_ref = json_lock.lock().unwrap();
                            *songs_ref = other_cli_copy.get_current_response();
                        }
                    });
                // ----------------
                arc_guard
            },
            Err(e) => {
            	info!("ERROR: Rust client socket failed to connect {}", e);
            	panic!("ERROR: {}", e);  // TODO: set a behavior to disregard this code an open another window
            }
        };
        sleep(Duration::from_millis(3600));
    // ----------------------------- All this client processes for the window could be changed into function
        // Initialize GTK
        info!("Initializing GTK window");
        gtk::init().expect("Couldn't initialize GTK library binaries");

        // Create a new window
        let window = Window::new(WindowType::Toplevel);
        window.set_title("CommunityMusic Client");
        window.set_default_size(600, 200);
        
        // Define actions for each "UpVote" button
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

        // Create a grid container for objects
        let grid = Grid::new();
        grid.set_column_homogeneous(true);
        grid.set_row_homogeneous(true);


		let clientcopy = Arc::clone(&client);
        let jsoncopy= Arc::clone(&songs_json);
            let json_lockguard = jsoncopy.lock().unwrap();
            let parsed_json: Value = serde_json::from_str(json_lockguard.as_str()).unwrap();
        // Create buttons for upvote

        for i in 0..( parsed_json["attach"].as_array().unwrap().len()) {
            // Retrieve the song on the iterator
            let song: Value = parsed_json["attach"][i].to_owned();
                let mut song_id = song["id"].as_str().unwrap().to_owned();
                let song_title = song["title"].as_str().unwrap().to_owned();
                let song_artist = song["artist"].as_str().unwrap().to_owned();
            // ----------------- Create button 1
            let client_guard1 = Arc::clone(&clientcopy);
            let up_button = Button::with_label(&format!("Up Vote"));
            up_button.connect_clicked(move |_| {
                client_guard1.set_petition(Cmds::UpVote, &[song_id.as_str()]);
            });
            grid.attach(&up_button, 0, i as i32, 1, 1);
            song_id = song["id"].as_str().unwrap().to_owned(); // Reset the song_id
            // ----------------- Create song tags
            let label = Label::new(Some(&format!("{} - {}", song_title, song_artist)));
            grid.attach(&label, 1, i as i32, 1, 1);
            // ----------------- Create button 2
            let client_guard2 = Arc::clone(&clientcopy);
            let down_button = Button::with_label(&format!("Down Vote"));
            down_button.connect_clicked(move |_| {
                client_guard2.set_petition(Cmds::DownVote, &[song_id.as_str()]);
            });
            grid.attach(&down_button, 2, i as i32, 1, 1);
        }
        // for (i, action) in vote_up_actions.into_iter().enumerate() {
        //     let songs_lockguard = jsoncopy.lock().unwrap();

        //     let parsed_json: Value = serde_json::from_str(songs_lockguard.as_str()).unwrap();
        //     let song_id = parsed_json["attach"][i]["id"].as_str().unwrap().to_owned();

        //     let button = Button::with_label(&format!("Up Vote"));
        //     // Obtain a copy of the client to use in the action
        //     let client_guard = Arc::clone(&clientcopy);
        //     button.connect_clicked(move |_| {
        //         // Send petition to server on request
        //         client_guard.set_petition(Cmds::UpVote, &[song_id.as_str()]);
        //     });

        //     grid.attach(&button, 0, i as i32, 1, 1);
        // }

        // // Create tags for each song
        // for i in 0..10 {
        // 	let songs_lock = jsoncopy.lock().unwrap();
        // 	let songs_json: Value = serde_json::from_str(songs_lock.as_str()).unwrap();
        // 	let song_title = songs_json["attach"][i]["title"].as_str().unwrap().to_owned();
        // 	let song_artist = songs_json["attach"][i]["artist"].as_str().unwrap().to_owned();
        //     let label = Label::new(Some(&format!("{} - {}", song_title, song_artist)));
        //     grid.attach(&label, 1, i as i32, 1, 1);
        // }

        // // Crear botones "Vote Down" con acciones
        // // Cambiar i para que sea cantidad de canciones cargadas por el
        // // servidor, y no solo 10
        // for (i, action) in vote_down_actions.into_iter().enumerate() {
        //     let button = Button::with_label(&format!("Vote Down {}", i + 1));
        //     button.connect_clicked(move |_| action());
        //     grid.attach(&button, 2, i as i32, 1, 1);
        // }

        // Agregar el grid a la ventana
        window.add(&grid);

        VotingWindow { window: window, client: client, songs: songs_json}
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
