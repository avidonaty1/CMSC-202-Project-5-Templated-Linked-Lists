#include "Bar.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {

    cout << "Welcome to UMBC Grid of Bar Charts" << endl;
    char choice;
    string filename;

    do {
        cout << "Which file would you like to use? (Choose 1, 2, or 3)" << endl;
        cin >> choice;
    } while (choice != '1' && choice != '2' && choice != '3');

    switch(choice) {
        case '1':
            filename = "proj5_test1.txt";
            break;
        
        case '2':
            filename = "proj5_test2.txt";
            break;
        
        case '3':
            filename = "proj5_test3.txt";
            break;;

        default:
            cout << "There was an error with the choice" << endl;
    }

    
    Bar myBar(filename); // creates bar charts by passing the filename
    myBar.Start();
    return 0;
}