#include <iostream>
#include "Set.hpp"
#include <random>
#include "set_operations.hpp"
#include <vector>
using namespace std;

void clearScreen() {
    #ifdef __linux__
        system("clear");
    #elif _WIN32
        system("cls");
    #else
        std::cout << "\033[H\033[2J\033[3J"; // ANSI escape codes for clearing the screen
    #endif
    
}




int main(){
    // We'll use a vector to store the sets
    vector<Set*>sets;
    // we'll implement a interface to use the set operations and to insert elements in the sets
    sets.push_back(new Set()); // Create the first set
    sets.push_back(new Set()); // Create the second set
    sets.push_back(new Set()); // Create the third set
    while (true){
        cout << "Choose an option:" << endl;
        cout << "1. Insert x numbers in one of the sets" << endl;
        cout << "2. Erase x numbers in one of the sets" << endl;
        cout << "3. Show one of the sets" << endl;
        cout << "4. Difference of sets" << endl;
        cout << "5. Union of sets" << endl;
        cout << "6. Intersection of sets" << endl;
        cout << "7. Create a new Set" << endl;
        cout << "8. Minimum value of a set" << endl;
        cout << "9. Maximum value of a set" << endl;
        cout << "10. Predecessor of a value in a set" << endl;
        cout << "11. Sucessor of a value in a set" << endl;
        cout << "0. Exit" << endl;
        int expression;
        int temp1,temp2;
        cin >> expression;
        if (expression == 0) break;
        int value;
        Set* result = nullptr;
        switch (expression){
            case 1:
                cout << "Remember the sets indexes start at 1" << endl;
                cout << "You have " << sets.size() << " sets" << endl;
                cout << "Choose a set to insert numbers into: ";
                cin >> temp1;
                // Check if the set number is valid
                temp1--; // To start at 1
                if (temp1 < 0 || temp1 >= sets.size()) {
                    cout << "Invalid set number. Please try again." << endl;
                    clearScreen(); // Clear the screen after each operation
                    break; // Break out of the switch case to avoid fall-through
                }
                cout << "How many numbers do you wish to insert : ";
                cin >> temp2;
                cout << "Insert the numbers: \nExample: 1 2 3 4 5" << endl;
                 // Read the numbers into the set
                for (int i = 0; i < temp2; i++){
                    cin >> value;
                    sets[temp1]->insert(value); // Insert the value into the set
                }
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through

            case 2:
                cout << "Choose a set to erase numbers from: ";
                cin >> temp1;
                temp1--; // To start at 1
                if (temp1 < 0 || temp1 >= sets.size()) {
                    cout << "Invalid set number. Please try again." << endl;
                    cout << "Press enter to continue..." << endl;
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    cin.get(); // Wait for user input
                    clearScreen(); // Clear the screen after each operation
                    break; // Break out of the switch case to avoid fall-through
                }
                cout << "How many numbers do you wish to erase : ";
                cin >> temp2;
                cout << "Insert the numbers: \nExample: 1 2 3 4 5" << endl;
                 // Read the numbers into the set
                for (int i = 0; i < temp2; i++){
                    cin >> value;
                    cout << "Erasing: " << value << endl;
                    // Check if the value exists in the set before erasing
                    if (!sets[temp1]->contains(value)) {
                        cout << "Value " << value << " not found in set " << temp1 << endl;
                        continue; // Skip to the next iteration if the value is not found
                    }
                    sets[temp1]->erase(value); // Erase the value from the set
                }
                cout << "Set " << temp1 + 1 << " after erasing: " << endl;
                sets[temp1]->show(); // Show the set after erasing
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through
            case 3:
                cout << "Choose a set to show:" << endl;
                cin >> temp1;
                temp1--; // To start at 1
                cout << "Set " << temp1 + 1 << ": " << endl;
                sets[temp1]->show();
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break;
            case 4:
                cout << "Remember that the difference of two sets A and B is A - B" << endl;
                cout << "Choose two sets to find the difference:" << endl;
                cin >> temp1 >> temp2;
                temp1--; temp2--; // To start at 1
                cout << "Difference of the sets: " << endl;
                result = new Set (setDifference(*sets[temp1], *sets[temp2]));
                result->show();
                delete result;
                break; // Break out of the switch case to avoid fall-through
            case 5:
                cout << "Choose two sets to find the union:" << endl;
                cin >> temp1 >> temp2;
                temp1--; temp2--; // To start at 1
                cout << "Union of the sets: " << endl;
                result = new Set(setUnion(*sets[temp1], *sets[temp2]));
                result->show();
                delete result;
                break; // Break out of the switch case to avoid fall-through
            case 6:
                cout << "Choose two sets to find the intersection:" << endl;
                cin >> temp1 >> temp2;
                temp1--; temp2--; // To start at 1
                cout << "Intersection of the sets: ";
                result = new Set(setIntersection(*sets[temp1], *sets[temp2]));
                result->show();
                delete result;
                break; // Break out of the switch case to avoid fall-through
            case 7:
                cout << "Creating a new set..." << endl;
                sets.push_back(new Set()); // Create a new set and add it to the vector
                cout << "New set created. Total sets: " << sets.size() << endl;
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through

            case 8:
                cout << "Choose a set to find the minimum value:" << endl;
                cin >> temp1;
                temp1--; // To start at 1
                if (temp1 < 0 || temp1 >= sets.size()) {
                    cout << "Invalid set number. Please try again." << endl;
                    cout << "Press enter to continue..." << endl;
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    cin.get(); // Wait for user input
                    clearScreen(); // Clear the screen after each operation
                    break; // Break out of the switch case to avoid fall-through
                }
                cout << "Minimum value of set " << temp1 + 1 << ": " << sets[temp1]->minimum() << endl;
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through
            
            case 9:
                cout << "Choose a set to find the maximum value:" << endl;
                cin >> temp1;
                temp1--; // To start at 1
                if (temp1 < 0 || temp1 >= sets.size()) {
                    cout << "Invalid set number. Please try again." << endl;
                    cout << "Press enter to continue..." << endl;
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    cin.get(); // Wait for user input
                    clearScreen(); // Clear the screen after each operation
                    break; // Break out of the switch case to avoid fall-through
                }
                cout << "Maximum value of set " << temp1 + 1 << ": " << sets[temp1]->maximum() << endl;
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through
            
            case 10:
                cout << "Choose a set to find the predecessor of a value:" << endl;
                cin >> temp1;
                temp1--; // To start at 1
                if (temp1 < 0 || temp1 >= sets.size()) {
                    cout << "Invalid set number. Please try again." << endl;
                    cout << "Press enter to continue..." << endl;
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    cin.get(); // Wait for user input
                    clearScreen(); // Clear the screen after each operation
                    break; // Break out of the switch case to avoid fall-through
                }
                cout << "Insert the value: ";
                cin >> value;
                
                if (!(sets[temp1]->predecessor(value) == nullopt)) {
                    cout << "Predecessor of " << value << ": " << sets[temp1]->predecessor(value).value() << endl;
                }
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through
            
            case 11:
                cout << "Choose a set to find the sucessor of a value:" << endl;
                cin >> temp1;
                temp1--; // To start at 1
                if (temp1 < 0 || temp1 >= sets.size()) {
                    cout << "Invalid set number. Please try again." << endl;
                    cout << "Press enter to continue..." << endl;
                    cin.ignore(); // Ignore the newline character left in the input buffer
                    cin.get(); // Wait for user input
                    clearScreen(); // Clear the screen after each operation
                    break; // Break out of the switch case to avoid fall-through
                }
                cout << "Insert the value: ";
                cin >> value;
                cout << "Sucessor of " << value << " in set " << temp1 + 1 << ": " << sets[temp1]->sucessor(value) << endl;
                cout << "Press enter to continue..." << endl;
                cin.ignore(); // Ignore the newline character left in the input buffer
                cin.get(); // Wait for user input
                clearScreen(); // Clear the screen after each operation
                break; // Break out of the switch case to avoid fall-through

            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }
    std::cout << std::endl;
    std::cout << "Exiting the program." << std::endl;
    // Free dynamically allocated memory for each set
    for (Set* set : sets) {
        delete set; // Free the memory allocated for each set
    }
    sets.clear(); // Clear the vector of sets
    return 0;
}