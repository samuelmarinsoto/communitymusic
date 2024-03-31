use gtk::prelude::*;
use gtk::{Application, ApplicationWindow, Button, Label};
use glib::signal::Inhibit; // Import Inhibit

const APP_ID: &str = "org.gtk_rs.HelloWorld2";

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
        .build();

    window.set_app_paintable(true);
    window.connect_draw(move |window, ctx| {
        ctx.set_source_rgba(220.0/255.0, 239.0/255.0, 250.0/255.0, 1.0);
        let _ = ctx.paint();
        false.into()
    });


    // Create a vertical box layout to hold buttons and labels
    let vbox = gtk::Box::new(gtk::Orientation::Vertical, 5);
    window.set_child(Some(&vbox));

    // Create labels and buttons for each song
    for i in 1..=10 {
        let button = Button::new();
        button.set_label(&format!("Song {}", i));
        vbox.pack_start(&button, false, false, 0);

        let label = Label::new(None);
        label.set_text(&format!("c{}", i));
        vbox.pack_start(&label, false, false, 0);

        // Set size request for button to make it smaller
        button.set_size_request(100, 30);
        label.set_size_request(100, -1); // Set width same as button, height auto
    }

    // Show all widgets
    window.show_all();
}
