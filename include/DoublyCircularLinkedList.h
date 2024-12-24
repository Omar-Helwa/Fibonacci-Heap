#pragma once
#include "Node.h"

/**
 * Forward declaration of FibHeap class template.
 */
template<typename T>
class FibHeap;

/**
 * Forward declaration of VisualizeFibonacciHeap class.
 */
class VisualizeFibonacciHeap;

/**
 * @brief A class representing a doubly circular linked list.
 *
 * This class is used as a part of the Fibonacci Heap implementation.
 * It supports insertion, deletion, and display of nodes.
 *
 * @tparam T The type of data stored in the nodes.
 */
template<typename T>
class DoublyCircularLinkedList {
private:
    Node<T> *head; ///< Pointer to the head node of the list.
    int size; ///< Number of nodes in the list.

    /**
     * @brief Inserts a new node into the list.
     *
     * @param newNode Pointer to the new node to be inserted.
     */
    void insert(Node<T> *newNode); // Private insert function

public:
    /**
     * @brief Constructs an empty doubly circular linked list.
     */
    DoublyCircularLinkedList();

    /**
     * @brief Destroys the doubly circular linked list and deallocates all nodes.
     */
    ~DoublyCircularLinkedList();

    /**
     * @brief Inserts a new node with the specified name and key into the list.
     *
     * @param Name The name associated with the new node.
     * @param key The key associated with the new node.
     */
    void insert(T Name, int key);

    /**
     * @brief Deletes the specified node from the list.
     *
     * @param curr Pointer to the node to be deleted.
     */
    void deleteNode(Node<T> *curr);

    /**
     * @brief Displays the contents of the list.
     */
    void display() const; // Ensure display function is declared as const

    /**
     * @brief Returns the number of nodes in the list.
     *
     * @return The size of the list.
     */
    [[nodiscard]] int getSize() const; // Ensure getSize function is declared as const

    /**
     * @brief Removes the specified node from the list and isolates it.
     *
     * @param x Pointer to the node to be removed.
     * @return Pointer to the removed node.
     */
    Node<T> *remove(Node<T> *x);

    // Friend classes to allow access to private members
    friend class FibHeap<T>;
    friend class VisualizeFibonacciHeap;
};

template<typename T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList() : head(nullptr), size(0) {
}

template<typename T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
    if (head) {
        Node<T> *current = head;
        do {
            Node<T> *next = current->right;
            delete current;
            current = next;
        } while (current != head);
        head = nullptr;
    }
}

template<typename T>
void DoublyCircularLinkedList<T>::insert(Node<T> *newNode) {
    if (!head) {
        head = newNode;
        newNode->right = newNode;
        newNode->left = newNode;
    } else {
        Node<T> *tail = head->left;
        newNode->right = head;
        newNode->left = tail;
        tail->right = newNode;
        head->left = newNode;
    }
    size++;
}

template<typename T>
void DoublyCircularLinkedList<T>::insert(T Name, int key) {
    auto *newNode = new Node<T>(Name, key);
    insert(newNode); // Call the private insert function
}

template<typename T>
void DoublyCircularLinkedList<T>::deleteNode(Node<T> *curr) {
    if (!head || !curr) return;

    if (curr->right == curr) {
        head = nullptr;
    } else {
        Node<T> *prev = curr->left;
        Node<T> *next = curr->right;
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

    Node<T> *current = head;
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
Node<T> *DoublyCircularLinkedList<T>::remove(Node<T> *x) {
    if (!head || !x) return nullptr;

    if (x->right == x) {
        head = nullptr;
    } else {
        Node<T> *prev = x->left;
        Node<T> *next = x->right;
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
