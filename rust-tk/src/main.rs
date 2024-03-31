use rstk::*;

fn main() {
    let root = rstk::start_with("wish8.6").unwrap();

    // Set the window size 
    root.geometry(800,600,0,0);

    // // Set the window background color to purple
    // root.configure("background", "#2596BE");
    
    let hello = rstk::make_label(&root);
    hello.text("Comunity Playlist");
    hello.grid().layout();

    // Create buttons and labels for each song
    let button1 = rstk::make_button(&root);
    button1.text("Song 1");  // Emoji
    button1.grid().row(5).column(5).layout();  

    let label1 = rstk::make_label(&root);
    label1.text("c1");
    label1.grid().row(5).column(6).layout();

    let button2 = rstk::make_button(&root);
    button2.text("Song 2");
    button2.grid().row(7).column(5).layout();  

    let label2 = rstk::make_label(&root);
    label2.text("c2");
    label2.grid().row(7).column(6).layout();  

    let button3 = rstk::make_button(&root);
    button3.text("Song 3");
    button3.grid().row(9).column(5).layout();  

    let label3 = rstk::make_label(&root);
    label3.text("c3");
    label3.grid().row(9).column(6).layout();  

    let button4 = rstk::make_button(&root);
    button4.text("Song 4");
    button4.grid().row(11).column(5).layout();  

    let label4 = rstk::make_label(&root);
    label4.text("c4");
    label4.grid().row(11).column(6).layout();  

    let button5 = rstk::make_button(&root);
    button5.text("Song 5");
    button5.grid().row(13).column(5).layout();  

    let label5 = rstk::make_label(&root);
    label5.text("c5");
    label5.grid().row(13).column(6).layout();  

    let button6 = rstk::make_button(&root);
    button6.text("Song 6");
    button6.grid().row(15).column(5).layout();  

    let label6 = rstk::make_label(&root);
    label6.text("c6");
    label6.grid().row(15).column(6).layout();  

    let button7 = rstk::make_button(&root);
    button7.text("Song 7");
    button7.grid().row(17).column(5).layout();  

    let label7 = rstk::make_label(&root);
    label7.text("c7");
    label7.grid().row(17).column(6).layout();  

    let button8 = rstk::make_button(&root);
    button8.text("Song 8");
    button8.grid().row(19).column(5).layout();  
    let label8 = rstk::make_label(&root);
    label8.text("c8");
    label8.grid().row(19).column(6).layout();  

    let button9 = rstk::make_button(&root);
    button9.text("Song 9");
    button9.grid().row(21).column(5).layout(); 
    let label9 = rstk::make_label(&root);
    label9.text("c9");
    label9.grid().row(21).column(6).layout();  

    let button10 = rstk::make_button(&root);
    button10.text("Song 10");
    button10.grid().row(23).column(5).layout();  

    let label10 = rstk::make_label(&root);
    label10.text("c10");
    label10.grid().row(23).column(6).layout();  

    rstk::mainloop();
}
