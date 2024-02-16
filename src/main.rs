use std::ptr::null;

fn main() {
    let x: i32 = aux(); // expression
    let y = { // block
        let x_square = x * x;
        let x_cube = x_square * x;

        x_cube + x_square + x // --> this line works as a return
    };

    let mut instance = MyClass::new(x);
    print!("Value: {} \n", instance.rectangle.get_area());
}

fn aux() -> i32 {
    3
}

struct Rectangle(i32, i32 );

impl Rectangle {
    fn get_area(&self) -> i32 {
        self.0 * self.1
    }
}

struct MyClass {
    i: i32,
    rectangle: Rectangle,
}

impl MyClass {
    fn new(len: i32)-> MyClass{ // Similar to a constructor method
        MyClass {i: len, rectangle: Rectangle(len, len*2)}
    }
}