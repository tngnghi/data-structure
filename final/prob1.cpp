#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value){
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;
    Node* insertHelper(Node* node, int value){
        if(node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        }
        else {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    void preorderHelper(Node* node){
        if (node == nullptr) {
            return;
        }

        cout << node->data <<" ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void inorderHelper(Node* node){
        if (node == nullptr) {
            return;
        }

        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    void postorderHelper(Node* node){
        if (node == nullptr) {
            return;
        }

        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }

public:
    BST() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertHelper(root, value);
    }

    void preorder() {
        cout << "Pre-order: ";
        preorderHelper(root);
        cout << endl;
    }
    
    void inorder() {
        cout << "In-order: ";
        inorderHelper(root);
        cout << endl;
    }
    
    void postorder() {
        cout << "Post-order: ";
        postorderHelper(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int arr[] = {7, 5, 1, 8, 3, 6, 0, 9, 4, 2};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i=0; i<n; i++){
        tree.insert(arr[i]);
    }

    tree.preorder();
    tree.inorder();
    tree.postorder();

    return 0;
}