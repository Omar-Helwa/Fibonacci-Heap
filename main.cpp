#include <iostream>
#include "DoublyCircularLinkedList.h"
#include "FibHeap.h"

int main() {
    FibHeap<int> fibHeap{};
    auto *node1 = new Node<int>(5, 5);
    auto *node2 = new Node<int>(3, 3);
    auto *node3 = new Node<int>(7, 7);

    fibHeap.insert(node1);
    fibHeap.insert(node2);
    fibHeap.insert(node3);

    std::cout << "Fibonacci Heap before extracting min:" << std::endl;
    fibHeap.display();

    Node<int> *minNode = fibHeap.extractMin();
    if (minNode) {
        std::cout << "Extracted min node: Key = " << minNode->getKey() << ", Name = " << minNode->getName() <<
                std::endl;
    }



    std::cout << "Fibonacci Heap after extracting min:" << std::endl;
    fibHeap.display();

    Node<int> *minNode2 = fibHeap.extractMin();
    if (minNode) {
        std::cout << "Extracted min node: Key = " << minNode->getKey() << ", Name = " << minNode->getName() <<
                std::endl;
    }




    std::cout << "Fibonacci Heap after extracting min:" << std::endl;
    fibHeap.display();

    delete minNode; // Clean up the extracted node
    delete minNode2;
    return 0;
}
