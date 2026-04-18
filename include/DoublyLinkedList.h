//
// Created by iraan on 21.03.2026.
//

// Szablon listy dwukierunkowej
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H


template<class T>
class DoublyLinkedList {
    public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T d) {
            data = d;
            next = nullptr;
            prev = nullptr;
        };
    };
    Node* head;
    Node* tail;
    int size;

    //konstruktor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    };

    //destruktor
    ~DoublyLinkedList() {
        Node *current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        size = 0;
    };

    DoublyLinkedList(const DoublyLinkedList &other) {
        head = nullptr;
        tail = nullptr;
        size = 0;

        Node *current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    DoublyLinkedList& operator=(const DoublyLinkedList &other) {
        if (this == &other) return *this;

        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;

        Node* temp = other.head;
        while (temp != nullptr) {
            push_back(temp->data);
            temp = temp->next;
        }

        return *this;
    }

    T& operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; ++i) {
            current = current->next;
        }
        return current->data;
    }


    void push_back(T d) {
        Node *newNode = new Node(d);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void read() {
        cout << "DoublyLinkedList::read()" << endl;
        Node *current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
            cout << endl;
        }
    }

    int getSize () {
        return size;
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }

    void setHead(Node* newHead) {
        head = newHead;
    }

    void setTail(Node* newTail) {
        tail = newTail;
    }

    bool isSorted() {
        Node* current = head;

        while (current != nullptr && current->next != nullptr) {
            if (current->data > current->next->data) {
                return false;
            }
            current = current->next;
        }

        return true;
    }
    T findMin() {
        if (head == nullptr) {
            cout << "The list is empty" << endl;
            return T();
        }
        T min = head->data;
        Node *current = head->next;
        while (current != nullptr) {
            if ((current->data) < min) {
                min = current->data;
            }
            current = current->next;
        }
        return min;
    }

    T findMax() {
        if (head == nullptr) {
            cout << "The list is empty" << endl;
            return T();
        }
        T max = head->data;
        Node *current = head->next;
        while (current != nullptr) {
            if (current->data> max) {
                max = current->data;
            }
            current = current->next;
        }
        return max;
    }

    void push(T d) {
        Node* newNode = new Node(d);

        if (!head){
            head = tail = newNode;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void clear() {
        Node* current = head;

        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        size = 0;
    }
};
#endif //DOUBLYLINKEDLIST_H
