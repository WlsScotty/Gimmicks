#include <fcntl.h> // Used for future memory manipulation
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Xlib.h>   //Ignore my poor library selection, this is just supposed to be a simple fun little utility
#include <X11/Xutil.h>
#include <X11/Xatom.h>

#define true 1

const char* procName = "/home/scottywilson/example.txt";
int sleepTime = 30; // Time between each individual input


ssize_t handle; // Assigning it later



int main(int argc, char *argv[]){


    if (access(procName, R_OK) != 0){ // Execption for if it fails
        printf("Error! Couldn't access specified file!");
        return 1;
    }
    handle = open(procName,O_RDONLY); // Read permission is only required

    Display* display = XOpenDisplay(NULL);
    Window w = 0x9000009;
    XRaiseWindow(display, w); // This was my test for if the window didnt work itself, which it did.
    XSetInputFocus(display, w, RevertToNone, CurrentTime);

    // Defining the Xevent class
     XKeyEvent event;
     event.display = display;
     event.window = w;
     event.root = w;
     event.x = 0;
     event.y = 0;
     event.x_root = 0;
     event.y_root = 0;
     event.type = KeyPress;
     event.same_screen = true;
     event.keycode = XKeysymToKeycode(display, XStringToKeysym("t")); // Filler key, will get replaced late
     event.state = 0;
    // Done Defining

    struct stat file;
    stat(procName,&file);
    char* bytes = (char*)malloc((size_t)file.st_size);

    ssize_t bytes_read = read(handle, bytes, (int)file.st_size);

    for(int i = 0; i <= file.st_size - 1; i++){ // Main loop for individual Keya presses
    usleep(sleepTime); // time elapsed before next input

    event.keycode = XKeysymToKeycode(display, XStringToKeysym((const char[]){bytes[i], '\0'})); // C is terrifying for this one piece of code I had to learn. Godness, why c, and why not bytes[0]? I get you expect the indiviual datatype, but holy, you are terrifying.

    XSendEvent(display, w, True, KeyPressMask, (XEvent *)&event);
    }

    XFlush(display);
    XCloseDisplay(display);

    free(bytes);

  return 0;
}
