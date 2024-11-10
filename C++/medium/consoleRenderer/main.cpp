#include <iostream>
#include <cstring> // For memset
#include <unistd.h>
#include <chrono>
#include <thread>
#include <termios.h>
#include <cstdlib>
#include <ctime>

#define sleep(t) std::this_thread::sleep_for(std::chrono::milliseconds(t))

char* input[20]; // Global Classes

class renderer {
    char* render; // This is where everything takes place
    
public:

    const int screenX;
    const int screenY;

    // Constructor definition with proper initialization
    renderer(int max_x, int max_y) : screenX(max_x), screenY(max_y) {
        render = new char[max_x * max_y]; // Allocate memory for render space

        // Initialize render space with blank characters
        std::memset(render, ' ', max_x * max_y * sizeof(char));
        
        // Set newline characters at the end of each row
        for (int i = 0; i < max_y; ++i) {
            render[(i + 1) * max_x - 1] = '\n';
        }
    }

    // Destructor to free allocated memory
    ~renderer() {
        delete[] render;
    }

    // Function to print the rendered screen
    void printScreen() {
        std::system("clear");
        std::cout << render;
    }
    
    // Function to write a character at specific coordinates
    void writeChar(char instance, int x, int y) {
        render[x + y * screenX] = instance;
    }

    char fieldChar(char entry, int offset, int lookPast) { // Very unoptimized way to find an element, wouldn't reccomend this way conventionally, unless there is a memoryleak that needs to be debbuged.
        for(int i = offset; i <= screenX * screenY - 1; i++){
            if(render[i] == entry){
                if(lookPast == 0){
                    return render[i];

                }
                lookPast -= 1;
            }
        }
        return 0;
    }
};

renderer *r; // Define the renderer for use later, as we dont have to define it in stack instantly.

class object{ // iNCOMPLETE
public:
    int x;
    int y;

    object(){
    r->writeChar('P',x, y);

    }
    void moveTo(){
        
    }
};

void defineBorders() { // Now, this is where we get into functions that perform
    for(int i = 0; i <= r->screenY - 2; i++){
        r->writeChar('#',0,i);
        r->writeChar('#',r->screenX - 2,i);
    }
    for(int i = 0; i <= r->screenX - 2; i++){
        r->writeChar('#',i,0);
        r->writeChar('#',i,r->screenY - 2);
    }
}

renderer RENDERER_INIT(int max_x, int max_y){ // Wrapper for instancing the script across there
    renderer rend(max_x, max_y); // We are not really going to reference too much by the original datatype, but rather pointer. This is because we use pretty much all of our functions with the pointer alternative prior.
    r = (renderer*)&rend;
    return rend;
}

int main() {

    renderer rend = RENDERER_INIT(30,20);

    defineBorders();

    rend.printScreen();
}
