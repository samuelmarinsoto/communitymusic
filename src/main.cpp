#include "modules/c++/Server.hpp"

#include <iostream>
#include <string>


int main(int argc, char *argv[]){
    Server socket(49001 ,"127.0.0.1");
    while (true) {
        string* x = socket.access_event();
        cout << x[0] << " said " << x[1] << endl;
    }
    return 0;
}