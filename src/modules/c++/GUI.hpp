#include <iostream>
#include <tk.h>

using namespace std;

class Gui {
    public:
        Gui(){
            // Initialize Tk and Tcl
            if (Tcl_Init(interp.get()) == TCL_ERROR) {
                std::cerr << "Error initializing Tk: " << Tcl_GetStringResult(interp.get()) << std::endl;
                exit(1);
            }
        }

        ~Gui(){
            // 
            Tcl_Finalize();
        }

        void createWindow(){
            // Create the main window
            Tk_Window mainWindow = Tk_CreateMainWindow(interp.get(), NULL, "Hello, C++/Tk!", NULL);

            // Create a button with "Say Hello" text and bind the hello command
            button(".b", mainWindow) -text("Say Hello") -command(hello);
            pack(".b", mainWindow) -padx(20) -pady(6);

            // Start the main event loop
            Tk_MainLoop();
        }

    private:
        // Tcl interpreter handle
        std::unique_ptr<Tcl_Interp, decltype(&Tcl_DeleteInterp)> interp{Tcl_CreateInterp(), Tcl_DeleteInterp};

        // Helper function to create Tk widgets using C++/Tk syntax
        template <typename T>
        T button(const char* name, Tk_Window window = NULL) {
            return T(Tcl_CreateCommand(interp.get(), name, nullptr, nullptr, nullptr));
        }

        template <typename T>
        T pack(const char* name, Tk_Window window = NULL) {
            return T(Tcl_CreateCommand(interp.get(), name, nullptr, nullptr, nullptr));
        }

        // Function called when the button is clicked (could be a member function)
        static void hello(ClientData /*data*/, Tcl_Interp* /*interp*/, int /*argc*/, const char* /*argv*/[]) {
            std::cout << "Hello C++/Tk!" << std::endl;
        }

}