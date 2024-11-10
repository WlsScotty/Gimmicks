// Simple sorting visualizer
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>

#define Sleep(t) std::this_thread::sleep_for(std::chrono::milliseconds(t))

int array[10] = {10,2,9,8,6,5,7,4,3,1}; // Array to sort


class ScreenDim{
    
    int MaxEntrySize(){
        int temp = 0;
    
        for(int i = 0; i <= sizeof(array) / sizeof(int) - 2; i++){
            if(temp < array[i+1]){
                temp = array[i+1];
            }
        }
    return temp;
    } 

public:
    int x = sizeof(array) / sizeof(int) - 1; // Max "x" value
    int y; // Max "y" value; defined later

    ScreenDim(){
    y = MaxEntrySize();

    }
    

};

bool BubbleSort(){ // The bubble sorting algorithm
    for(int i = 0; i <= sizeof(array) / sizeof(int) - 2; i++){
        if(array[i] > array[i+1]){
        int temp;
            
        temp = array[i+1];
        array[i+1] = array[i];
        array[i] = temp;
        
        return true;
        }
    }
    return false;    
}

int main(){
    int c = 0;
    ScreenDim scrn;
    
    while (c <= sizeof(array) / sizeof(int)){
        if(BubbleSort() == true){
        c = 0;
              
        for(int y = 0; y <= scrn.y; y++){
            for(int x = scrn.x; x >= 0; x-=1){
                if(array[x] <= y){                 
                    std::cout << "#";
                }
                else{
                    std::cout << " ";
                }
            }
        std::cout << "\n";
        }
        Sleep(100);    
        continue;
    }
    c++;   

    }
    for(int i = 0; i <= sizeof(array) / sizeof(int) - 1; i++){
    std::cout << array[i];    
        
    }
}
