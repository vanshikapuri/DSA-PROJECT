#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node* insert(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }

    if (data <= root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }

    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

Node* search(Node* root, int data) {
    if (root == NULL || root->data == data) {
        return root;
    }

    if (data < root->data) {
        return search(root->left, data);
    }

    return search(root->right, data);
}

Node* findMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* deleteNode(Node* root, int data) {
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = deleteNode(root->left, data);
    } else if (data > root->data) {
        root->right = deleteNode(root->right, data);
    } else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

int main() {
    Node* root = NULL;

    int numNodes;
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    for (int i = 0; i < numNodes; i++) {
        int data;
        cout << "Enter node " << i + 1 << " value: ";
        cin >> data;
        root = insert(root, data);
    }

    cout << "\nInorder traversal: ";
    inorder(root);
    cout << endl;

    int newNodeValue;
    cout << "\nEnter a new node value: ";
    cin >> newNodeValue;
    root = insert(root, newNodeValue);

    cout << "Inorder traversal after inserting new node: ";
    inorder(root);
    cout << endl;

    int searchValue;
    cout << "\nEnter a value to search: ";
    cin >> searchValue;
    Node* found = search(root, searchValue);
    if (found) {
        cout << "Found value: " << found->data << endl;
    } else {
        cout << "Not found" << endl;
    }

    int deleteValue;
    cout << "\nEnter a value to delete: ";
    cin >> deleteValue;
    root = deleteNode(root, deleteValue);

    cout << "Inorder traversal after deleting node: ";
    inorder(root);
    cout << endl;

    return 0;
}
