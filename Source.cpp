#include <iostream>
#include <fstream>
#include <sstream>
#include "BalancedBST.h"

using namespace std;


// Function to check if a string represents a valid integer
bool isValidInteger(const string str) {
    try {
        // Attempt to convert the string to an integer
        stoi(str);
        return true;
    }
    catch (const invalid_argument& ia) {
        return false;
    }
    catch (const out_of_range& oor) {
        return false;
    }
}

int main() {


    int operationAmounts[4] = { 0, 0, 0, 0 };

    string inputFileName, operationFileName, outputFileName;

    std::cout << "Enter the name of the input file: ";
    cin >> inputFileName;

    /*std::cout << "Enter the name of the operation file: ";
    cin >> operationFileName;*/

    std::cout << "Enter the name of the output file: ";
    cin >> outputFileName;

    ifstream inputFile(inputFileName);

    if (!inputFile) {
        cerr << "Error opening input file!" << endl;
        return 1;
    }


    ofstream outputFile(outputFileName);

    if (!outputFile) {
        cerr << "Error opening output file!" << endl;
        inputFile.close();
        return 1;
    }


    BalancedBST bst;

    int value;
    string line;

    std::cout << "\n\n\n";



    while (getline(inputFile, line)) {

        if (isValidInteger(line)) {
            // Convert the string to an integer and insert into the BST
            value = stoi(line);
            bst.insert(value);
            operationAmounts[0] += bst.getNumOperations() + 1;
            // Print the BST to the console and the output file after each insertion
            bst.printTree(outputFile);
            bst.print2DConsole();
            bst.print2DToFile(outputFile);
        }
        else {
            cerr << "Error: Invalid integer - skipping line: " << line << endl;
        }
    }

    if (bst.getRoot() == nullptr) {
        outputFile << "\nTree is empty after creation.\n";
        std::cout << "\nTree is empty after creation.\n";
    }


    std::cout << "\nCreation of BST complete " << operationAmounts[0] << " operations completed" << endl;
    std::cout << "\n\n\n";


    /*
    // Check if the operation file is empty and valid and perform operations
    ifstream operationFile(operationFileName);
    if (operationFile.peek() == ifstream::traits_type::eof()) {
        std::cout << "Empty Operation File - No Operations Performed" << endl;
    }
    else {
        // Perform operations from the operation file
        while (getline(operationFile, line)) {
            char actionCode;
            int numOperations;


            istringstream iss(line);
            // Checks if each line is in the correct format then proceeds with the operations
            if (iss >> actionCode >> numOperations) {
                switch (actionCode) {
                case 'I':

                    value = numOperations;
                    // Insert value into BST
                    bst.insert(value);
                    operationAmounts[3] += (bst.getNumOperations() + 1);
                    // Print the BST to the console and the output file after each insertion
                    bst.printTree(outputFile);
                    bst.print2DConsole();
                    bst.print2DToFile(outputFile);
                    std::cout << bst.getNumOperations() + 1 << " operations completed" << endl;
                    outputFile << bst.getNumOperations() + 1 << " operations completed" << endl;

                    break;

                case 'D':

                    value = numOperations;
                    // Check if the value is in the tree before attempting deletion
                    if (bst.search(value)) {
                        // Delete the value from the BST
                        operationAmounts[2] += (bst.getNumOperations() + 1);
                        bst.deleteNode(value);
                        operationAmounts[2] += (bst.getNumOperations() + 1);
                        // Print the BST to the console and the output file after each deletion
                        bst.printTree(outputFile);
                        bst.print2DConsole();
                        bst.print2DToFile(outputFile);
                        std::cout << bst.getNumOperations() + 1 << " operations completed" << endl;
                    }
                    else {
                        std::cout << "Value " << value << " not found in the tree - skipping deletion." << endl;
                        outputFile << "Value " << value << " not found in the tree - skipping deletion." << endl;
                        operationAmounts[2] += (bst.getNumOperations() + 1); // Accounts for the search even if the value is not found
                    }

                    break;

                case 'S':

                    value = numOperations;
                    // Search for the value in the BST
                    if (bst.search(value)) {
                        std::cout << "Value " << value << " found in the tree." << endl;
                        std::cout << bst.getNumOperations() + 1 << " operations completed" << endl;
                        operationAmounts[1] += (bst.getNumOperations() + 1);
                    }
                    else {
                        std::cout << "Value " << value << " not found in the tree." << endl;
                        outputFile << "Value " << value << " not found in the tree." << endl;
                        operationAmounts[1] += (bst.getNumOperations() + 1);  // Accounts for the search even if the value is not found
                    }

                    break;

                default:
                    cerr << "Error: Invalid Action Code - skipping line: " << line << endl;
                    break;
                }
            }
            else {
                cerr << "Error: Invalid format for operation - skipping line: " << line << endl;
            }
        }
    }

    */

    int creation = operationAmounts[0];
    int search = operationAmounts[1];
    int deletion = operationAmounts[2];
    int insert = operationAmounts[3];

    // Print analysis data
    std::cout << "\n              BST";
    std::cout << "\nCreation      " << creation;
    std::cout << "\nSearch        " << search;
    std::cout << "\nInsert        " << insert;
    std::cout << "\nDelete        " << deletion;
    std::cout << "\n         -------------";
    std::cout << "\nTotal         " << (creation + search + insert + deletion);



    outputFile << "\n              BST";
    outputFile << "\nCreation      " << creation;
    outputFile << "\nSearch        " << search;
    outputFile << "\nInsert        " << insert;
    outputFile << "\nDelete        " << deletion;
    outputFile << "\n         -------------";
    outputFile << "\nTotal         " << (creation + search + insert + deletion);



    // Close the files
    inputFile.close();
    outputFile.close();
    //operationFile.close();



    return 0;
}