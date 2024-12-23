//
// Created by Sigma on 23/12/2024.
//

#ifndef HOSPITALTASKMANAGER_H
#define HOSPITALTASKMANAGER_H

#include "FibHeap.h"
#include "Node.h"
#include <iostream>
#include <string>

class HospitalTaskManager {
private:
    FibHeap<std::string> taskHeap;

public:
    void addTask(const std::string& description, int priority) {
        Node<std::string>* newNode = new Node<std::string>(description, priority);
        taskHeap.insert(newNode);
        std::cout << "Task added: " << description << " (Priority: " << priority << ")\n";
    }

    void completeHighestPriorityTask() {
        if (taskHeap.isEmpty()) {
            std::cout << "No tasks in the queue.\n";
            return;
        }

        Node<std::string>* highestPriorityTask = taskHeap.extractMin();
        std::cout << "Completed task: " << highestPriorityTask->getName() << " (Priority: " << highestPriorityTask->getKey() << ")\n";
        delete highestPriorityTask;
    }

    void updateTaskPriority(int oldPriority, int newPriority) {
        Node<std::string>* taskNode = taskHeap.find(oldPriority);
        if (taskNode == nullptr) {
            std::cout << "Task not found.\n";
            return;
        }

        taskHeap.modifyKey(taskNode->getKey(), newPriority);
        std::cout << "Task priority updated: " << taskNode->getName() << " (New Priority: " << newPriority << ")\n";
    }
};

#endif // HOSPITALTASKMANAGER_H