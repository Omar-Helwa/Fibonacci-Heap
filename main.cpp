#include <iostream>
#include "DoublyCircularLinkedList.h"
#include "FibHeap.h"
#include "HospitalTaskManager.h"

int main() {
    // FibHeap<int> fibHeap{};
    // auto *node5 = new Node<int>(23, 23);
    // auto *node6 = new Node<int>(7, 7);
    // auto *node7 = new Node<int>(21, 21);
    // auto *node8 = new Node<int>(3, 3);
    // auto *node9 = new Node<int>(52, 52);
    // auto *node10 = new Node<int>(18, 18);
    // auto *node11 = new Node<int>(39, 39);
    // auto *node12 = new Node<int>(38, 38);
    // auto *node13 = new Node<int>(41, 41);
    // auto *node14 = new Node<int>(17, 17);
    // auto *node15 = new Node<int>(26, 26);
    // auto *node16 = new Node<int>(35, 35);
    // auto *node17 = new Node<int>(24, 24);
    // auto *node18 = new Node<int>(46, 46);
    //
    //
    // fibHeap.insert(node5);
    // fibHeap.insert(node6);
    // fibHeap.insert(node7);
    // fibHeap.insert(node8);
    // fibHeap.insert(node9);
    // fibHeap.insert(node10);
    // fibHeap.insert(node11);
    // fibHeap.insert(node12);
    // fibHeap.insert(node13);
    // fibHeap.insert(node14);
    // fibHeap.insert(node15);
    // fibHeap.insert(node16);
    // fibHeap.insert(node17);
    // fibHeap.insert(node18);
    //
    //
    // std::cout << "Fibonacci Heap before extracting min:" << std::endl;
    // fibHeap.display();
    //
    // Node<int> *minNode = fibHeap.extractMin();
    // if (minNode) {
    //     std::cout << "Extracted min node: Key = " << minNode->getKey() << ", Name = " << minNode->getName() <<
    //             std::endl;
    // }
    //
    //
    //
    // std::cout << "Fibonacci Heap after extracting min:" << std::endl;
    // fibHeap.display();
    // Node<int> *minNode2 = fibHeap.extractMin();
    // if (minNode2) {
    //     std::cout << "Extracted min node: Key = " << minNode2->getKey() << ", Name = " << minNode2->getName() <<
    //         std::endl;
    // }
    //
    // std::cout << "Fibonacci Heap after extracting min:" << std::endl;
    // fibHeap.display();
    // delete minNode; // Clean up the extracted node
    // delete minNode2;
    //
    //
    // FibHeap<int> fibHeap{};
    // auto *node1 = new Node<int>(5, 5);
    // auto *node2 = new Node<int>(3, 3);
    // auto *node3 = new Node<int>(7, 7);
    // auto *node4 = new Node<int>(10, 10);
    //
    // fibHeap.insert(node1);
    // fibHeap.insert(node2);
    // fibHeap.insert(node3);
    // fibHeap.insert(node4);
    //
    // std::cout << "Fibonacci Heap before deleting a node:" << std::endl;
    // fibHeap.display();
    //
    // // Display the minimum node
    // Node<int> *minNode = fibHeap.displayMinimum();
    // if (minNode) {
    //     std::cout << "Minimum node: Key = " << minNode->getKey() << ", Name = " << minNode->getName() << std::endl;
    // }
    //
    // // Delete a node with key 3
    // fibHeap.deleteNode(3);
    //
    // std::cout << "Fibonacci Heap after deleting the node with key 3:" << std::endl;
    // fibHeap.display();
    //
    // // Display the minimum node again
    // minNode = fibHeap.displayMinimum();
    // if (minNode) {
    //     std::cout << "Minimum node: Key = " << minNode->getKey() << ", Name = " << minNode->getName() << std::endl;
    // }
    // return 0;

        HospitalTaskManager manager;

        // Add tasks
        manager.addTask("Check patient vitals", 5);
        manager.addTask("Administer medication", 2);
        manager.addTask("Schedule surgery", 1);

        // Complete the highest priority task
        manager.completeHighestPriorityTask();

        // Update task priority
        manager.updateTaskPriority(5, 3);

        // Complete the highest priority task again
        manager.completeHighestPriorityTask();

        // Complete the remaining tasks
        manager.completeHighestPriorityTask();
        manager.completeHighestPriorityTask();

        return 0;
}
