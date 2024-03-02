// ----------- Standarad imports
#include <iostream>
#include <string>

// ----------- Threading imports
#include <thread>
#include<mutex>

// -----------

using namespace std;
//------------------------{TEST CLASS}------------------------//
class MyClass{
    public:
        string str;
        bool condition;
        struct container{
            int value;
            char c;
        };
        enum crate{
            terminate,
            halt,
            exec
        };

        mutex shared;

        MyClass(string arg){
            this->str = str;
            this->condition = true;
        }

        bool share_bool(crate param){
            cout << "accessing resource" << endl;
            lock_guard<mutex> guard(this->shared); // locks the mutex
            bool result = this->condition;
            // ^^^^ get the required value
            cout << "releasing resource" << endl;
            return result; // resource is released upon ending;
        }

        void looping(string id){
            int counter = 0;
            while (this->share_bool(exec)){
                if (counter == 18){
                    break;
                }
                cout << "Thread ( " << id << " ) is on:"<<counter << endl;
                counter++;
            }
        }
};


// Executable main() method
int main() {
    MyClass inst("IAmAClass");
    thread subprocess1(&MyClass::looping, &inst, "0x003");
    thread subprocess2(&MyClass::looping, &inst, "0x005");
    subprocess1.join();
    subprocess2.join();
    
    return 0;
};