//
// Created by iraan on 18.04.2026.
//

#ifndef BINARYTREE_H
#define BINARYTREE_H

//Implementacja drzewa binarnego
//Każdy węzeł ma 2 dzieci
//
template<typename T>
class BinaryTree {
public:
    //Przentuje jeden węzeł drzewa
    struct Node {
        T data;   //wartośćć
        Node *left, *right; //wskażniki na lewe i prawe dziecka
        explicit Node(T d) : data(d), left(nullptr), right(nullptr) {}
    };

private:
    Node* root = nullptr;  //korzeń drzewa
    int size = 0;   //rozmiar

    //Rekurencyjna etoda wtawiania elementu do drzewa
    Node* insert(Node* node, T data) {
        if (node == nullptr) return new Node(data);

        //decyduje gdzie zapisać wartość
        if (data < node->data) node->left = insert(node->left, data); //mniejsze
        else node->right = insert(node->right, data); //większe lub równe
        return node;
    }

    //Rekurencyjne usuwanie drzewa
    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BinaryTree() : root(nullptr), size(0) {}


    //destruktor drzewa
    ~BinaryTree() {
        clear(root);
    }


    //Dodawanie elementu
    void add(T data) {
        root = insert(root, data);
        size++;
    }

    //Zwraca rozmiar drzewa
    int getSize() { return size; }
    //Zwraca korzeń drzewa
    Node* getRoot() { return root; }


    //Przepisywanie elementów z drzewa do tablicy rosnąco
    // lewo->korzeń->prawo
    void fillArrayInOrder(Node* node, T* arr, int& index) {
        if (node == nullptr) return;
        fillArrayInOrder(node->left, arr, index);
        arr[index++] = node->data;
        fillArrayInOrder(node->right, arr, index);
    }

    //Sprawdza czy właściwości BST są zachowane w drzewie
    bool isSorted() {
        if (root == nullptr) return true;

        T* lastValue = nullptr;
        return isSortedRecursive(root, lastValue); //wywołanoe rekurencji
    }

    //Rekurencyjna metoda sprawdzająca poprawność sortowanie dla lewego i prawego poddrzew
    bool isSortedRecursive(Node* node, T*& lastValue) {
        if (node == nullptr) return true;

        if (!isSortedRecursive(node->left, lastValue)) return false;

        if (lastValue != nullptr && (node->data) < *lastValue) return false;
        lastValue = &(node->data);

        return isSortedRecursive(node->right, lastValue);

    }

};
#endif //BINARYTREE_H
