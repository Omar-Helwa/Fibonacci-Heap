#ifndef VISUALIZETASKMANAGER_H
#define VISUALIZETASKMANAGER_H

#include "imgui.h"
#include "HospitalTaskManager.h"
#include "error_handler.h"

class VisualizeTaskManager {
public:
    void visualize(HospitalTaskManager &manager, error_handler * error_handler) {
        // Set global font scale

        // Set a larger window size
        ImGui::Begin("Hospital Task Manager");

        // Get the available content region size
        ImVec2 contentRegion = ImGui::GetContentRegionAvail();

        // Input controls for adding a task
        static int taskPriority = 0;
        static char taskDescription[128] = "";

        ImGui::InputText("Description", taskDescription, IM_ARRAYSIZE(taskDescription));
        ImGui::InputInt("Priority", &taskPriority);

        // Button to add a task
        if (ImGui::Button("Add Task")) {
            // 40% width, 70px height
            std::string descriptionStr(taskDescription);
            manager.addTask(descriptionStr, taskPriority);
        }

        ImGui::SameLine();
        // Button to complete the highest priority task
        if (ImGui::Button("Complete Highest Priority Task")) {
            // 50% width, 70px height
            manager.completeHighestPriorityTask();
        }
        // ImGui::PopStyleVar();

        ImGui::Separator();

        // Input controls for updating a task's priority
        static int oldPriority = 0;
        static int newPriority = 0;
        ImGui::InputInt("Old Priority", &oldPriority);
        ImGui::InputInt("New Priority", &newPriority);

        // Button to update a task's priority
        if (ImGui::Button("Update Task Priority")) {
            // 50% width, 70px height
            manager.updateTaskPriority(oldPriority, newPriority);
        }

        ImGui::Separator();

        error_handler->renderErrorMessages();

        ImGui::Separator();

        // Display the number of tasks
        ImGui::Text("Number of Tasks: %d", manager.countTasks());

            displayTasks(manager);


        ImGui::End();
    }

private:
    void displayTasks(HospitalTaskManager &manager) {
        if (ImGui::BeginTable("TasksTable", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            // Set up the headers
            ImGui::TableSetupColumn("Task Name");
            ImGui::TableSetupColumn("Priority");
            ImGui::TableHeadersRow();

            // Display each task in the table
            traverseHeap(manager.taskHeap->displayMinimum());

            ImGui::EndTable();
        }
    }

    void traverseHeap(Node<std::string> *node) {
        if (!node) return;

        Node<std::string> *start = node;
        do {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("%s", node->getName().c_str());
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("%d", node->getKey());

            if (node->child) {
                traverseHeap(node->child->head);
            }
            node = node->right;
        } while (node != start);
    }
};

#endif
