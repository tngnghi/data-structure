#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;
    
    Node* insertHelper(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else {
            node->right = insertHelper(node->right, value);
        }
        
        return node;
    }
    
    void inorderHelper(ostream &o, Node* node) {
        if (node == nullptr) return;
        
        inorderHelper(o, node->left);
        o << node->data << " ";
        inorderHelper(o, node->right);
    }
    
    int heightHelper(Node* node) {
        if (node == nullptr) {
            return -1; 
        }
        
        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);
        
        return max(leftHeight, rightHeight) + 1;
    }
    
public:
    BST() {
        root = nullptr;
    }
    
    // Public methods
    void insert(int value) {
        root = insertHelper(root, value);
    }
    
    void inorder(ostream &o, Node* root) {
        inorderHelper(o, root);
    }
    
    int height(Node* root) {
        return heightHelper(root);
    }
    
    // Getter for root
    Node* getRoot() {
        return root;
    }
};

int main() {
    BST tree;
    
    int sequence[] = {25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90};
    int n = sizeof(sequence) / sizeof(sequence[0]);
    
    for (int i = 0; i < n; i++) {
        tree.insert(sequence[i]);
    }
    
    ofstream outFile("bst_output.txt");
    if (!outFile) {
        cerr << "Error opening output file!" << endl;
        return 1;
    }
    
    cout << "In-order Traversal (Console and File): ";
    tree.inorder(cout, tree.getRoot());
    cout << endl;
    
    tree.inorder(outFile, tree.getRoot());
    outFile.close();
    
    int treeHeight = tree.height(tree.getRoot());
    cout << "Tree Height: " << treeHeight << endl;
    
    return 0;
}