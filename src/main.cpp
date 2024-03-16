#include "modules/c++/fJSON.hpp"
#include "modules/c++/Server.hpp"

#include <iostream>
#include <string>
#include <tk.h>

extern "C" {
    int Tcl_AppInit(Tcl_Interp *interp) {
        if (Tk_Init(interp) == TCL_ERROR) {
            return TCL_ERROR;
        }

        // You can add additional initialization code here

        return TCL_OK;
    }
}

int main(int argc, char *argv[]){
    Tk_Main(argc, argv, Tcl_AppInit);
    //Server socket(49094 ,"172.16.0.1");

    /*std::string jString = json_as_string("settings/file.json");
    JSONObject json(jString);
        json.remove("u");
        json.append("new", 41);
        json.append("a", 9);
    JSONArray arr = json.getArray("f");
        arr.append((float)67.81);
        arr.append(string("hello"));
        arr.remove(1);
    json.append("f",  arr);
    cout << json.content << endl;*/

    return 0;
}