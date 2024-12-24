#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <functional>
#include <iostream>
#include "DoublyCircularLinkedList.h"

// Forward declarations
template<typename T>
class Node;

class VisualizeFibonacciHeap;

/**
 * @class FibHeap
 * @brief Represents a Fibonacci Heap data structure.
 *
 * This class provides the implementation of a Fibonacci Heap, including
 * operations such as insertion, merging, extracting the minimum, and
 * decreasing or increasing keys.
 *
 * @tparam T The type of data stored in the heap nodes.
 */
template<typename T>
class FibHeap {
private:
    Node<T> *min; ///< Pointer to the node with the minimum key.
    int size; ///< Number of nodes in the heap.
    DoublyCircularLinkedList<T> rootList; ///< Root linked list.

    void link(Node<T> *y, Node<T> *x);
    void consolidate();
    void cut(Node<T> *x, Node<T> *y);
    void cascadingCut(Node<T> *y);
    Node<T> *search(Node<T> *root, int key) const;

public:
    friend class VisualizeFibonacciHeap;

    FibHeap();
    void insert(Node<T> *x);
    Node<T> *extractMin();
    Node<T> *displayMinimum();
    void modifyKey(int k, int new_k);
    void deleteNode(int k);
    void display();
    Node<T> *find(int key) const;
    bool isEmpty();
    int getSize();
};

// Implementation of the FibHeap template class

template<typename T>
FibHeap<T>::FibHeap() : min(nullptr), size(0) {}

template<typename T>
void FibHeap<T>::insert(Node<T> *x) {
    x->deg = 0;
    x->parent = nullptr;
    x->child = nullptr;
    x->mark = false;
    rootList.insert(x);
    if (min == nullptr || x->key < min->key)
        min = x;
    ++size;
}

template<typename T>
Node<T> *FibHeap<T>::extractMin() {
    Node<T> *minptr = min;
    if (minptr == nullptr) {
        return nullptr;
    }
    if (minptr->child != nullptr) {
        int numChildren = minptr->child->size;
        for (int i = 0; i < numChildren; i++) {
            Node<T> *child = minptr->child->head;
            minptr->child->remove(child);
            rootList.insert(child);
            child->parent = nullptr;
        }
    }
    minptr->left->right = minptr->right;
    minptr->right->left = minptr->left;
    if (minptr == minptr->right) {
        min = nullptr;
        if (minptr->child == nullptr)
            rootList.remove(minptr);
    } else {
        min = minptr->right;
        consolidate();
    }
    size--;

    return minptr;
}

template<typename T>
bool FibHeap<T>::isEmpty() {
    return size == 0;
}

template<typename T>
void FibHeap<T>::consolidate() {
    const int fibsize = 45;
    Node<T> *A[fibsize];
    Node<T> *x = min;
    for (int i = 0; i < fibsize; i++)
        A[i] = nullptr;
    int iterations = rootList.size;
    for (int i = 0; i < iterations - 1; i++) {
        int d = x->deg;
        while (A[d] != nullptr) {
            Node<T> *y = A[d];
            if (x->key > y->key){
                Node <T> *temp = x;
                x = y;
                y = temp;
            }
            link(y, x);
            A[d] = nullptr;
            ++d;
        }
        A[d] = x;
        x->deg = d;
        x = x->right;
    }
    min = nullptr;
    rootList = DoublyCircularLinkedList<T>();
    for (int i = 0; i < fibsize; i++) {
        if (A[i] != nullptr){
            rootList.insert(A[i]);
            if (min == nullptr || A[i]->key < min->key)
                min = A[i];
        }
    }
}

template<typename T>
void FibHeap<T>::link(Node<T> *y, Node<T> *x) {
    rootList.remove(y);
    if (x->child == nullptr)
        x->child = new DoublyCircularLinkedList<T>();
    x->child->insert(y);
    y->parent = x;
    y->mark = false;
}

template<typename T>
Node<T> *FibHeap<T>::search(Node<T> *current, int key) const {
    if (current == nullptr)
        return nullptr;
    Node<T> *start = current;
    do {
        if (current->key == key) {
            return current;
        }
        if (current->child != nullptr) {
            return search(current->child->head, key);
        }
        current = current->right;
    } while (current != start);
    return nullptr;
}

template<typename T>
Node<T> *FibHeap<T>::find(int key) const {
    return search(this->rootList.head, key);
}

template<typename T>
void FibHeap<T>::modifyKey(int currentNodeKey, int new_k) {
    Node<T> *x = find(currentNodeKey);
    if (x == nullptr) {
        std::cerr << "Node with key " << currentNodeKey << " not found." << std::endl;
        return;
    }
    if (x != nullptr && new_k > x->key) {
        modifyKey(x->key, -1);
        Node<T>* mini = extractMin();
        mini->key = new_k;
        insert(mini);
        return;
    }

    x->key = new_k;
    Node<T> *y = x->parent;
    if (y != nullptr && x->key < y->key) {
        cut(x, y);
        cascadingCut(y);
    }
    if (x->key < min->key) {
        min = x;
    }
}

template<typename T>
void FibHeap<T>::cut(Node<T> *x, Node<T> *y) {
    y->child->remove(x);
    rootList.insert(x);
    x->parent = nullptr;
    x->mark = false;
}

template<typename T>
void FibHeap<T>::cascadingCut(Node<T> *y) {
    Node<T> *z = y->parent;
    if (z != nullptr) {
        if (y->mark == false) {
            y->mark == true;
        } else {
            cut(y, z);
            cascadingCut(z);
        }
    }
}

template<typename T>
void FibHeap<T>::deleteNode(int key) {
    Node<T> *x = find(key);
    if (x == nullptr) {
        std::cerr << "Node with key " << key << " not found." << std::endl;
        return;
    }
    modifyKey(key, min->key - 1);
    extractMin();
    std::cout << "Deleted node with key " << key << std::endl;
}

template<typename T>
Node<T> *FibHeap<T>::displayMinimum() {
    return this->min;
}

template<typename T>
void FibHeap<T>::display() {
    if (!rootList.head) {
        std::cout << "The Fibonacci heap is empty." << std::endl;
        return;
    }

    std::function<void(Node<T>*, int)> displayNode = [&](Node<T>* node, int level) {
        if (!node) return;
        Node<T>* start = node;
        do {
            for (int i = 0; i < level; ++i) std::cout << "  ";
            std::cout << "Key: " << node->getKey() << ", Name: " << node->getName() << ", Degree: " << node->getDeg() << std::endl;
            if (node->child) {
                displayNode(node->child->head, level + 1);
            }
            node = node->right;
        } while (node != start);
    };

    displayNode(rootList.head, 0);
}

template<typename T>
int FibHeap<T>::getSize() {
    return size;
}

#endif // FIBHEAP_H