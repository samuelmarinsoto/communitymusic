use rstk::*;

fn main() {
/* si no funca, utilizar start_with(<wish>)
donde <wish> es el nombre del comando "wish"
que viene con el paquete de tk */ 
  let root = rstk::start_with("wish8.6").unwrap();

  let hello = rstk::make_label(&root);
  hello.text("Hello from Rust/Tk");

  hello.grid().layout();

  rstk::mainloop();
}
