#include "BalancedBST.h"





// Print the BST using 2D representation
void BalancedBST::print2D(Node* root, int space, ostream& out) {
    if (root == nullptr) {
        return;
    }
    // Increase distance between levels of BST
    space += COUNT;

    print2D(root->right, space, out);

    // Print current node after space count is correct
    out << endl;
    for (int i = COUNT; i < space; i++)
        out << " ";

    // Check for twin chain and print the node value along with the number of twins
    if (root->next != nullptr) {
        int twinCount = countTwins(root);
        out << root->data << "-" << twinCount << "\n";
    }
    else {
        out << root->data << "\n";
    }

    print2D(root->left, space, out);
}



// Counts the number of twins in a twin chain
int BalancedBST::countTwins(Node* node) {
    int count = 0;
    while (node != nullptr) {
        count++;
        node = node->next;
    }
    return count;
}



// Deletes node from BST
void BalancedBST::deleteNode(int value) {
    if (root == nullptr) {
        std::cout << "Tree is empty. Cannot delete value: " << value << endl;
        return;
    }
    operations = 0;
    root = deleteNodeRecursive(root, value);
    std::cout << "Deleted value: " << value << ", Tree Height: " << height(root) << endl;
}



// Recursive delete function
Node* BalancedBST::deleteNodeRecursive(Node* current, int value) {
    operations++;
    if (current == nullptr) {
        return current;
    }

    if (value < current->data) {
        current->left = deleteNodeRecursive(current->left, value);
    }
    else if (value > current->data) {
        current->right = deleteNodeRecursive(current->right, value);
    }
    else {
        // Handle twin chaining
        if (current->next != nullptr) {
            // Subtract one from the twin chain
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        else {
            // If not a twin chain, perform regular deletion
            if (current->left == nullptr) {
                Node* temp = current->right;
                delete current;
                return temp;
            }
            else if (current->right == nullptr) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            // Node with two children, get the inorder successor
            Node* temp = minValueNode(current->right);

            // Copy the inorder successor's data to this node
            current->data = temp->data;

            // Delete the inorder successor
            current->right = deleteNodeRecursive(current->right, temp->data);
        }
    }

    return current;
}



// Inserts a new node into the BST
void BalancedBST::insert(int value) {
    operations = 0;
    root = insertRecursive(root, value);
    std::cout << "Inserted value: " << value << ", Tree Height: " << height(root) << endl;
}



// Finds node of minimum value in any specified subtree
Node* BalancedBST::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}



// Recursive insertion
Node* BalancedBST::insertRecursive(Node* current, int value) {
    operations++;
    if (current == nullptr) {
        return new Node(value);
    }

    if (value < current->data) {
        current->left = insertRecursive(current->left, value);
    }
    else if (value > current->data) {
        current->right = insertRecursive(current->right, value);
    }
    else {
        // Twin chaining handling
        Node* newNode = new Node(value);
        newNode->next = current->next;
        current->next = newNode;
    }

    balanceByPath(current);

    return current;
}



// Calculates the height of the tree
int BalancedBST::height(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    }
}



// Searches for value in the tree
bool BalancedBST::search(int value) {
    operations = 0;
    return searchRecursive(root, value);
}



// Iterative search function
bool BalancedBST::searchRecursive(Node* current, int value) {
    while (current != nullptr) {
        operations++;
        if (value == current->data) {
            return true;
        }
        else if (value < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return false;
}



// Prints the BST to a file and the console
void BalancedBST::printTree(ofstream& outputFile) {
    std::cout << "BST elements: ";
    printTreeRecursive(root);
    std::cout << ", Tree Height: " << height(root) << endl;

    outputFile << "BST elements: ";
    printTreeRecursiveToFile(root, outputFile);
    outputFile << ", Tree Height: " << height(root) << endl;
}



// Printing with inorder traversal
void BalancedBST::printTreeRecursive(Node* current) {
    if (current != nullptr) {
        printTreeRecursive(current->left);
        printTwinChain(current);
        printTreeRecursive(current->right);
    }
}



// Printing twin chain duplicates
void BalancedBST::printTwinChain(Node* node) {
    while (node != nullptr) {
        std::cout << node->data << " ";
        node = node->next;
    }
}



// Inorder traversal to print to file
void BalancedBST::printTreeRecursiveToFile(Node* current, ofstream& outputFile) {
    if (current != nullptr) {
        printTreeRecursiveToFile(current->left, outputFile);
        printTwinChainToFile(current, outputFile);
        printTreeRecursiveToFile(current->right, outputFile);
    }
}



// Prints twin chain values to file
void BalancedBST::printTwinChainToFile(Node* node, ofstream& outputFile) {
    while (node != nullptr) {
        outputFile << node->data << " ";
        node = node->next;
    }
}



// Prints the BST using 2D representation to the console
void BalancedBST::print2DConsole() {
    std::cout << "Printing BST using 2D representation:" << endl;
    print2D(root, 0, std::cout);
}



// Prints the BST using 2D representation to a specified output stream
void BalancedBST::print2DToFile(ofstream& outputFile) {
    outputFile << "Printing BST using 2D representation:" << endl;
    print2D(root, 0, outputFile);
}



// Calls balanceTree from the root node
void BalancedBST::balance() {
    balanceTree(root);
}



// Ensures every part of the tree is in balance
void BalancedBST::balanceTree(Node*& current) {
    int balanceFactor = getBalanceFactor(current);

    if (current != nullptr) {
        balanceTree(current->left);

        // Left-Left Case
        if (balanceFactor > 1 && getBalanceFactor(current->left) >= 0)
            current = rotateRight(current);

        // Left-Right Case
        if (balanceFactor > 1 && getBalanceFactor(current->left) < 0) {
            current->left = rotateLeft(current->left);
            current = rotateRight(current);
        }

        // Right-Right Case
        if (balanceFactor < -1 && getBalanceFactor(current->right) <= 0)
            current = rotateLeft(current);

        // Right-Left Case
        if (balanceFactor < -1 && getBalanceFactor(current->right) > 0) {
            current->right = rotateRight(current->right);
            current = rotateLeft(current);
        }

        balanceTree(current->right);
    }
}



void BalancedBST::balanceByPath(Node*& current)
{
    int balanceFactor = getBalanceFactor(current);
    
    // Left-Left Case
    if (balanceFactor > 1 && getBalanceFactor(current->left) >= 0)
        current = rotateRight(current);

    // Left-Right Case
    if (balanceFactor > 1 && getBalanceFactor(current->left) < 0) {
        current->left = rotateLeft(current->left);
        current = rotateRight(current);
    }

    // Right-Right Case
    if (balanceFactor < -1 && getBalanceFactor(current->right) <= 0)
        current = rotateLeft(current);

    // Right-Left Case
    if (balanceFactor < -1 && getBalanceFactor(current->right) > 0) {
        current->right = rotateRight(current->right);
        current = rotateLeft(current);
    }
}


// Gets value of the balance factor for each node
int BalancedBST::getBalanceFactor(Node* current){
    if (current == nullptr)
        return 0;
    return height(current->left) - height(current->right);
}



// Rotates tree to the left
Node* BalancedBST::rotateLeft(Node* node){
    Node* rNode = node->right;
    Node* temp = rNode->left;

    rNode->left = node;
    node->right = temp;

    return rNode;

}



// Rotates tree to the right
Node* BalancedBST::rotateRight(Node* node){
    Node* lNode = node->left;
    Node* temp = lNode->right;

    lNode->right = node;
    node->left = temp;

    return lNode;
}