#ifndef VISUALIZETASKMANAGER_H
#define VISUALIZETASKMANAGER_H

#include "imgui.h"
#include "HospitalTaskManager.h"

class VisualizeTaskManager {
public:
    void visualize(HospitalTaskManager &manager) {
        // Create a new ImGui window for HospitalTaskManager
        ImGui::Begin("Hospital Task Manager");

        // Input controls for adding a task
        static int taskPriority = 0;
        static char taskDescription[128] = "";
        ImGui::InputText("Description", taskDescription, IM_ARRAYSIZE(taskDescription));
        ImGui::InputInt("Priority", &taskPriority);

        // Button to add a task
        if (ImGui::Button("Add Task")) {
            std::string descriptionStr(taskDescription);
            manager.addTask(descriptionStr, taskPriority);
        }

        // Button to complete the highest priority task
        if (ImGui::Button("Complete Highest Priority Task")) {
            manager.completeHighestPriorityTask();
        }

        // Input controls for updating a task's priority
        static int oldPriority = 0;
        static int newPriority = 0;
        ImGui::InputInt("Old Priority", &oldPriority);
        ImGui::InputInt("New Priority", &newPriority);

        // Button to update a task's priority
        if (ImGui::Button("Update Task Priority")) {
            manager.updateTaskPriority(oldPriority, newPriority);
        }

        // Display the number of tasks
        ImGui::Text("Number of Tasks: %d", manager.countTasks());

        // Button to display all tasks
        if (ImGui::Button("Display Tasks")) {
            manager.displayTasks();
        }
        ImGui::End();
    }
};

#endif