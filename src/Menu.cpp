#include <iostream>
#include <string>

int mode=0;
std::string source;
std::string dest;
std::string avoidNodes;
std::string avoidEdges;
std::string includeNode;
std::string test;

void menu() {

    std::cout<<"0.Mode"<<std::endl<<"1.source"<<std::endl<<
    "2.destination"<<std::endl<<"3.Avoid Nodes"<<std::endl<<
    "4.Avoid Segments"<<std::endl<<"5.Include Node"<<std::endl<<"6.Read From File"
    <<std::endl<<"7.execute \n"<<"8.Exit Menu"<<std::endl;
}
void modedisplay() {
    std::cout<<"Enter Mode \n"<<"1.Driving \n"<<"2.Walking \n"<<"3.Driving-walking \n";
}

void read() {
    std::cout<<"Enter path to Locations file: \n"<<"Enter path to distance file: \n";
}


int main() {
    int choice;

    while (true){
        menu();
        std::cin>>choice;
        if (choice == 8) break;
        switch (choice) {
            case 0:
                modedisplay();
            std::cin>>mode;
            break;
            case 1:
                std::cin>>source;
            case 2:
                std::cin>>dest;
            break;
            case 3:
                std::cin>>avoidNodes;
            break;
            case 4:
                std::cin>>avoidEdges;
            break;
            case 5:
                std::cin>>includeNode;
            break;
            case 6:
                read();
            std::cin >> test;
            readfromfile(test);
            break;
            case 7:
                if (mode!=0 && !source.empty() && !dest.empty() && !avoidNodes.empty() && !avoidEdges.empty()&& !includeNode.empty()) {
                    switch (mode) {
                        case 1:
                            break;
                        case 2:
                            break;
                        case 3:
                            break;
                    }
                }
            std::cout<<"One of the necessary fields was not filled \n";
            default:
                std::cout << "Invalid choice, please try again. \n";
            break;

        }
    }
    return 0;
}