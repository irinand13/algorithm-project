//
// Created by iraan on 18.04.2026.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H
template<typename T>
class BinaryTree {
public:
    struct Node {
        T data;
        Node *left, *right;
        Node(T d) : data(d), left(nullptr), right(nullptr) {}
    };

private:
    Node* root = nullptr;
    int size = 0;

    Node* insert(Node* node, T data) {
        if (node == nullptr) return new Node(data);
        if (data < node->data) node->left = insert(node->left, data);
        else node->right = insert(node->right, data);
        return node;
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr), size(0) {}

    ~BinaryTree() {
        clear(root);
    }

    void add(T data) {
        root = insert(root, data);
        size++;
    }

    int getSize() { return size; }

    void fillArrayInOrder(Node* node, T* arr, int& index) {
        if (node == nullptr) return;
        fillArrayInOrder(node->left, arr, index);
        arr[index++] = node->data;
        fillArrayInOrder(node->right, arr, index);
    }
};
#endif //BINARYTREE_H
