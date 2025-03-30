#include <iostream>
#include "menu.h"
#include "readData.h"
#include "batch.h"

using namespace std;

#define COLOR_BLUE_HEADER "\033[1;97;44m"  // Bright white on blue
#define COLOR_GREEN_HEADER "\033[1;97;42m" // Bright white on green
#define COLOR_RED "\033[1;31m"             // Red
#define COLOR_GREEN "\033[1;32m"           // Green
#define COLOR_YELLOW "\033[1;33m"          // Yellow
#define COLOR_CYAN "\033[1;36m"            // Cyan
#define COLOR_MAGENTA "\033[1;35m"         // Magenta
#define COLOR_RESET "\033[0m"              // Reset


/*
 * @brief Main function to run the program
 * @return 0 on success
 */
int main() {
    Graph graph;
    readData(graph);
    int input = -1;
    while(input!=0){
        cout<<"\n\n\n\033[1;33mDo you wish to enter Bash Mode or the Main Menu?\n\033[1;32m1 - Bash Mode\n2 - Menu\n\033[1;31m0 - Quit\n\033[1;33mEnter your choice: \033[0m";
        cin>>input;
        if(input==1){
            system("clear");
            batch(graph);
        }
        else if(input==2){
            system("clear");
            menu(graph);
        } else{
            system("clear");
        }
    }
    
    
    return 0;
}


