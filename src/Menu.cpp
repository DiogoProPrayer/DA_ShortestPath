#include <iostream>
#include <string>

void menu() {
int choice;
    std::cout<<"0.Mode"<<std::endl<<"1.source"<<std::endl<<
    "2.destination"<<std::endl<<"3.Avoid Nodes"<<std::endl<<
    "4.Avoid Segments"<<std::endl<<"5.Include Node"<<std::endl<<"6.Read From File"
    <<std::endl<<"7.Exit Menu"<<std::endl;
    std::cin>>choice;
    

}

int main() {
    menu();
    return 0;
}