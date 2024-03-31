use rstk::*;

fn main() {
  let root = rstk::start_with("wish8.6").unwrap();

  // Set the window size to 800x600
  root.geometry(800,600,0,0);

  let hello = rstk::make_label(&root);
  hello.text("Hello from Rust/Tk");
  hello.grid().layout();
  let button = rstk::make_button(&root);
  button.text("Click me");
  button.grid().layout();
  rstk::mainloop();
}
