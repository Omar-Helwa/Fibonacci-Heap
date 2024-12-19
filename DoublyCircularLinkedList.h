#pragma once
#include "Node.h"
#include "FibHeap.h"

template<typename T>
class DoublyCircularLinkedList {
private:
    Node<T>* head;
    int size;
    void insert(Node<T>* newNode); // Private insert function

public:
    DoublyCircularLinkedList();
    ~DoublyCircularLinkedList();

    void insert(T Name, int key);
    void deleteNode(Node<T>* curr);
    void display() const; // Ensure display function is declared as const
    int getSize() const; // Ensure getSize function is declared as const
    Node<T> *remove(Node<T> *x);

    friend class FibHeap<T>;
};

template<typename T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList() : head(nullptr), size(0) {}

template<typename T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
    if (head) {
        Node<T>* current = head;
        do {
            Node<T>* next = current->right;
            delete current;
            current = next;
        } while (current != head);
    }
}

template<typename T>
void DoublyCircularLinkedList<T>::insert(Node<T>* newNode) {
    if (!head) {
        head = newNode;
    } else {
        Node<T>* tail = head->left;
        newNode->right = head;
        newNode->left = tail;
        tail->right = newNode;
        head->left = newNode;
    }
    size++;
}

template<typename T>
void DoublyCircularLinkedList<T>::insert(T Name, int key) {
    Node<T>* newNode = new Node<T>(Name, key);
    insert(newNode); // Call the private insert function
}

template<typename T>
void DoublyCircularLinkedList<T>::deleteNode(Node<T>* curr) {
    if (!head || !curr) return;

    if (curr->right == curr) {
        head = nullptr;
    } else {
        Node<T>* prev = curr->left;
        Node<T>* next = curr->right;
        prev->right = next;
        next->left = prev;
        if (curr == head) {
            head = next;
        }
    }
    delete curr;
    size--;
}

template<typename T>
void DoublyCircularLinkedList<T>::display() const {
    if (!head) return;

    Node<T>* current = head;
    do {
        std::cout << "Name: " << current->getName() << ", Key: " << current->getKey() << std::endl;
        current = current->right;
    } while (current != head);
}

template<typename T>
int DoublyCircularLinkedList<T>::getSize() const {
    return size;
}

template<typename T>
Node<T>* DoublyCircularLinkedList<T>::remove(Node<T>* x)
{
    if (!head || !x) return nullptr;

    if (x->right == x) {
        head = nullptr;
    } else {
        Node<T>* prev = x->left;
        Node<T>* next = x->right;
        prev->right = next;
        next->left = prev;
        if (x == head) {
            head = next;
        }
    }
    x->left = x->right = x; // Isolate the node
    --this->size;
    return x;
}