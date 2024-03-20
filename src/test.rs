// ---------- Standard imports

use core::time;
// ---------- Threading imports
use std::thread;
use std::thread::sleep;
use std::time::Duration;
use std::sync::{Mutex, Arc};

//--------------------{CLASS}--------------------//
enum Container{
    Exec,
    Copy,
}
struct MyClass{
    name: String,
    container: Container,
    shared: Mutex<bool>
}

impl MyClass{
    fn create(arg: &str) -> MyClass{
        MyClass{name:arg.to_owned(),container: Container::Exec,
             shared:Mutex::new(true)}
    }

    fn access_condition(&self, thread_id:&str) -> bool{
        print!("Thread ({}) is accessing data \n", thread_id);
        let result = self.shared.lock().unwrap();
        *result
    }

    fn looping(&self, id:&str) -> (){
        let mut counter = 0;
        while self.access_condition(id) {
            if counter == 18 {
                break;
            } else if counter==7 && id=="0x007"{
                let mut condition = self.shared.lock().unwrap();
                *condition = false;
            }
            counter += 1;
            print!("Thread {} is counting at {} \n", id, counter);
            sleep(time::Duration::from_secs(2));
        }
    }
}

//--------------------{CLASS}--------------------//
pub fn execute() -> (){
    let instance = Arc::new(MyClass::create("Carlos"));

    let copy_instance = Arc::clone(&instance);
    let t1 = thread::spawn(move || {
        copy_instance.looping("0x018");
    });

    let copy_instance2 = Arc::clone(&instance);
    let t2 = thread::spawn(move || {
        copy_instance2.looping("0x007");
    });

    t2.join().unwrap();
    t1.join().unwrap();

}