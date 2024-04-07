use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Button, Box, Label};

const APP_ID: &str = "org.gtk_rs.HelloWorld2";
const WINDOW_WIDTH: i32 = 500;
const WINDOW_HEIGHT: i32 = 300;
const BUTTON_WIDTH: i32 = 30; // Reduced button width
const BUTTON_HEIGHT: i32 = 15; // Reduced button height

fn main() {
    // Create a new application
    let app = Application::builder()
        .application_id(APP_ID)
        .build();

    // Connect to "activate" signal of `app`
    app.connect_activate(build_ui);

    // Run the application
    app.run();
}

fn build_ui(app: &Application) {
    // Create the application window
    let window = ApplicationWindow::builder()
        .application(app)
        .title("Hello, World!")
        .default_width(WINDOW_WIDTH)
        .default_height(WINDOW_HEIGHT)
        .build();

    window.set_app_paintable(true);
    window.connect_draw(move |window, ctx| {
        ctx.set_source_rgba(220.0/255.0, 239.0/255.0, 250.0/255.0, 1.0);
        let _ = ctx.paint();
        false.into()
    });

    // Create a new box container with horizontal orientation
    let main_container = Box::new(gtk::Orientation::Horizontal, 0);

    // Create a sub-container for Vote Up buttons with vertical orientation
    let vote_up_button_container = Box::new(gtk::Orientation::Vertical, 0);

    // Create a vector of actions for Vote Up buttons
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

    // Create Vote Up buttons and labels using a for loop
    for (i, action) in vote_up_actions.into_iter().enumerate() {
        // Create a horizontal container for each pair of button and label
        let hbox = Box::new(gtk::Orientation::Horizontal, 0);

        // Create Vote Up button
        let button = Button::with_label(&format!("Vote Up {}", i + 1));
        button.set_size_request(BUTTON_WIDTH, BUTTON_HEIGHT);
        // Connect button to its corresponding action
        button.connect_clicked(move |_| action());
        hbox.pack_start(&button, false, false, 0);


        // Pack the horizontal container into Vote Up button container
        vote_up_button_container.pack_start(&hbox, false, false, 0);
    }

    // Pack the Vote Up button container into the main container
    main_container.pack_start(&vote_up_button_container, false, false, 0);

    // Create a sub-container for Vote Down buttons with vertical orientation
    let vote_down_button_container = Box::new(gtk::Orientation::Vertical, 0);

    // Create a vector of actions for Vote Down buttons
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

    // Create Vote Down buttons and labels using a for loop
    for (i, action) in vote_down_actions.into_iter().enumerate() {
        // Create a horizontal container for each pair of button and label
        let hbox = Box::new(gtk::Orientation::Horizontal, 0);

        // Create Vote Down button
        let button = Button::with_label(&format!("Vote Down {}", i + 1));
        button.set_size_request(BUTTON_WIDTH, BUTTON_HEIGHT);
        // Connect button to its corresponding action
        button.connect_clicked(move |_| action());
        hbox.pack_start(&button, false, false, 0);

        // Create label for song
        let label = Label::new(Some(&format!("Canción {}", i + 1)));
        hbox.pack_start(&label, false, false, 0);

        // Pack the horizontal container into Vote Down button container
        vote_down_button_container.pack_start(&hbox, false, false, 0);
    }

    // Pack the Vote Down button container into the main container
    main_container.pack_start(&vote_down_button_container, false, false, 0);

    // Add the main container to the window
    window.add(&main_container);

    // Show all widgets
    window.show_all();
}
