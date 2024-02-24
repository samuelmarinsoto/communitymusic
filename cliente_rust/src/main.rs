use gtk::prelude::*;
use gtk::{glib, Application, ApplicationWindow};

const APP_ID: &str = "org.gtk_rs.HelloWorld2";

fn main() -> glib::ExitCode {
    // Create a new application
    let app = Application::builder().application_id(APP_ID).build();

    // Connect to "activate" signal of `app`
    app.connect_activate(build_ui);

    // Run the application
    app.run()
}

fn build_ui(app: &Application) {
    let window = ApplicationWindow::builder()
        .application(app)
        .title("Community Playlist")
        .default_width(400) 
        .default_height(300) 
        .build();
    let button = gtk::Button::with_label("Click me!"); 
    button.connect_clicked(|_| {
        println!("Button clicked!");
    });
    window.set_child(Some(&button));
    window.present();
}




// use gtk::prelude::*;
// use gtk::{Application, ApplicationWindow, Button};

// const APP_ID: &str = "org.gtk_rs.HelloWorld2";

// fn main() -> Result<(), Box<dyn std::error::Error>> {
//     // Crea una nueva aplicación
//     let app = Application::builder().application_id(APP_ID).build();

//     // Conecta la señal "activate" de la aplicación a la función build_ui
//     app.connect_activate(build_ui);

//     // Ejecuta la aplicación
//     app.run();

//     Ok(())
// }

// fn build_ui(app: &Application) {
//     // Crea una ventana con la aplicación
//     let window = ApplicationWindow::builder()
//         .application(app)
//         .title("Community Playlist")
//         .default_width(400) // Establece el ancho de la ventana
//         .default_height(300) // Establece la altura de la ventana
//         .build();

//     // Crea un botón
//     let button = Button::with_label("Click me!");

//     // Conecta la señal "clicked" del botón a una función
//     button.connect_clicked(|_| {
//         println!("Button clicked!");
//     });

//     // Agrega el botón a la ventana
//     window.set_child(Some(&button));

//     // Muestra la ventana
//     window.present();
// }
