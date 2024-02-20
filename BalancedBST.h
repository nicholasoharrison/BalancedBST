#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int COUNT = 5; // For 2D tree printing spacing

struct Node {
    int data;
    Node* left;
    Node* right;
    Node* next; // Pointer for twin chaining

    Node(int value) : data(value), left(nullptr), right(nullptr), next(nullptr) {}
};



class BalancedBST {

private:

    Node* root;

    // Print the BST using 2D representation
    void print2D(Node* root, int space, ostream& out);

    int operations;

    // Counts the number of twins in a twin chain
    int countTwins(Node* node);

public:
    BalancedBST() : root(nullptr) { operations = 0; } //Constructor sets the root node to null

    Node* getRoot() { return root; }

    int getNumOperations() { return operations; }

    // Inserts a new node into the BST
    void insert(int value);

    // Delete node with specific value from BST
    void deleteNode(int value);

    // Recursive deletion function
    Node* deleteNodeRecursive(Node* current, int value);

    // Finds the smallest node in a specified subtree
    Node* minValueNode(Node* node);

    // Recursive insertion
    Node* insertRecursive(Node* current, int value);

    // Calculates the height of the tree
    int height(Node* node);

    // Searches for specific value in the tree
    bool search(int value);

    // Perform iterative search
    bool searchRecursive(Node* current, int value);

    // Prints the BST to a file and the console
    void printTree(ofstream& outputFile);

    // Printing with inorder traversal
    void printTreeRecursive(Node* current);

    // Printing twin chain duplicates
    void printTwinChain(Node* node);

    // Inorder traversal to print to file
    void printTreeRecursiveToFile(Node* current, ofstream& outputFile);

    // Prints twin chain values to file
    void printTwinChainToFile(Node* node, ofstream& outputFile);

    // Prints the BST using 2D representation to the console
    void print2DConsole();

    // Prints the BST using 2D representation to a specified output stream
    void print2DToFile(ofstream& outputFile);

    // Ensures every node of the tree is in balance
    void balanceTree(Node*& current);

    // Balances by a specific path (recursive stack)
    void balanceByPath(Node*& current);

    // Returns the balance factor of a specified node
    int getBalanceFactor(Node* current);

    // Rotates subtree to the left
    Node* rotateLeft(Node* node);

    // Rotates subtree to the right
    Node* rotateRight(Node* node);

    // Calls the balance tree function from the root node
    void balance();



};

