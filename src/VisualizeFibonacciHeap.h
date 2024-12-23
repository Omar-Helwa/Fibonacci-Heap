// VisualizeFibonacciHeap.h
#pragma once

#include "imgui.h"
#include "FibHeap.h"
#include "Node.h"
#include <string>
#include <iostream>

class ImDrawList; // Forward declaration
struct ImVec2;

class VisualizeFibonacciHeap {
private:
    // Constants
    static const int MAX_NODES = 100;

    // Structures to store node positions and an array of nodes
    typedef struct {
        Node<std::string>* first;
        ImVec2 second;
    } NodePositionPair;

    typedef struct {
        Node<std::string>* nodes[MAX_NODES];
        int count;
    } NodeArray;

    // Helper functions (now private members of the class):
    void drawNode(ImDrawList* drawList, ImVec2 center, int key, bool isMin, bool isMarked, ImU32 color) {
        const float nodeRadius = 20.0f;
        drawList->AddCircleFilled(center, nodeRadius, color);

        // Highlight the minimum node if specified
        if (isMin) {
            drawList->AddCircle(center, nodeRadius + 5.0f, IM_COL32(255, 255, 0, 255), 0, 2.5f);
        }

        // Convert the key to a string and display it
        char keyStr[16];
        snprintf(keyStr, sizeof(keyStr), "%d", key);
        ImVec2 textSize = ImGui::CalcTextSize(keyStr);
        drawList->AddText(ImVec2(center.x - textSize.x * 0.5f, center.y - textSize.y * 0.5f), IM_COL32(0, 0, 0, 255), keyStr);

        // Display a mark if the node is marked
        if (isMarked) {
            drawList->AddText(ImVec2(center.x + nodeRadius * 0.5f, center.y - nodeRadius * 0.5f), IM_COL32(255, 0, 0, 255), "M");
        }
    }

    void drawLinks(ImDrawList* drawList, Node<std::string>* node, NodePositionPair* nodePositions, int numPositions) {
        if (node == nullptr) return;

        // Find the position of the current node
        ImVec2 parentPos;
        for (int i = 0; i < numPositions; i++) {
            if (nodePositions[i].first == node) {
                parentPos = nodePositions[i].second;
            }
        }

        // Draw links to children if they exist
        if (node->child) {
            NodeArray children = getChildren(node);
            for (int i = 0; i < children.count; i++) {
                Node<std::string>* child = children.nodes[i];
                ImVec2 childPos;
                for (int j = 0; j < numPositions; j++) {
                    if (nodePositions[j].first == child) {
                        childPos = nodePositions[j].second;
                    }
                }

                drawList->AddLine(parentPos, childPos, IM_COL32(0, 0, 0, 255), 2.0f);
                drawLinks(drawList, child, nodePositions, numPositions);
            }
        }
    }

    void calculateNodePositions(Node<std::string>* node, NodePositionPair* nodePositions, int& numPositions, ImVec2 parentPos, float canvasWidth) {
        if (node == nullptr || node->child == nullptr) return;

        NodeArray children = getChildren(node);

        float childSpacing = canvasWidth / (4 * (children.count + 1));

        for (size_t i = 0; i < children.count; ++i) {
            if (numPositions < MAX_NODES) {
                ImVec2 childPos = ImVec2(parentPos.x + (i * childSpacing), parentPos.y + 100);
                nodePositions[numPositions++] = { children.nodes[i], childPos };
                calculateNodePositions(children.nodes[i], nodePositions, numPositions, childPos, canvasWidth);
            }
            else {
                std::cerr << "Error: Maximum number of nodes reached in CalculateNodePositions." << std::endl;
                return;
            }
        }
    }

    NodeArray getRoots(const FibHeap<std::string>& heap) {
        NodeArray roots = { {}, 0 }; // Initialize NodeArray
        if (heap.min == nullptr) return roots;

        Node<std::string>* current = heap.min;
        do {
            if (roots.count < MAX_NODES) {
                roots.nodes[roots.count++] = current;
                current = current->right;
            }
            else {
                std::cerr << "Error: Maximum number of nodes reached in getRoots." << std::endl;
                break;
            }
        } while (current != heap.min);
        return roots;
    }

    NodeArray getChildren(Node<std::string>* node) {
        NodeArray children = { {}, 0 }; // Initialize NodeArray
        if (node == nullptr || node->child == nullptr || node->child->head == nullptr) return children;

        Node<std::string>* current = node->child->head;
        do {
            if (children.count < MAX_NODES) {
                children.nodes[children.count++] = current;
                current = current->right;
            }
            else {
                std::cerr << "Error: Maximum number of nodes reached in getChildren." << std::endl;
                break;
            }
        } while (current != node->child->head);
        return children;
    }

public:
    VisualizeFibonacciHeap() {} // default constructor

    void visualize(FibHeap<std::string>& heap) {
        ImGui::Begin("Fibonacci Heap Visualization");

        // --- Control Panel ---
        ImGui::Text("Controls");

        // Input controls for inserting a node
        static int insertValue = 0;
        static char insertName[128] = "";
        ImGui::InputText("Name", insertName, IM_ARRAYSIZE(insertName));
        ImGui::InputInt("Key", &insertValue);

        // Button to trigger insertion
        if (ImGui::Button("Insert")) {
            std::string nameStr(insertName);
            Node<std::string>* node = new Node<std::string>(nameStr, insertValue);
            heap.insert(node);
        }

        // Button to extract the minimum node
        ImGui::SameLine();
        if (ImGui::Button("Extract-Min")) {
            heap.extractMin();
        }

        // Input controls for modifying a key
        static int modifyKey = 0;
        static int newValue = 0;
        ImGui::InputInt("Key to Modify", &modifyKey);
        ImGui::InputInt("New Key Value", &newValue);

        // Button to trigger key modification
        if (ImGui::Button("Modify Key")) {
            heap.modifyKey(modifyKey, newValue);
        }

        // Input control for deleting a node
        ImGui::SameLine();
        static int deleteKey = 0;
        ImGui::InputInt("Delete Key", &deleteKey);

        // Button to trigger deletion
        if (ImGui::Button("Delete")) {
            heap.deleteNode(deleteKey);
        }

        ImGui::Separator();

        // --- Visualization Area ---
        ImGui::Text("Fibonacci Heap");

        // Get ImGui's draw list
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImVec2 canvasPos = ImGui::GetCursorScreenPos(); // Top-left of the drawing area
        ImVec2 canvasSize = ImGui::GetContentRegionAvail();

        // Get the roots of the heap
        NodeArray roots = getRoots(heap);
        // Initialize an array to store node positions
        NodePositionPair nodePositions[MAX_NODES];
        int numPositions = 0;

        // Calculate positions for the root nodes
        float rootSpacing = canvasSize.x / (roots.count + 1);
        for (size_t i = 0; i < roots.count; ++i) {
            ImVec2 rootPos = ImVec2(canvasPos.x + rootSpacing * (i + 1), canvasPos.y + 50); // Adjust vertical position as needed
            nodePositions[numPositions++] = { roots.nodes[i], rootPos };

            // Recursively calculate positions of children
            calculateNodePositions(roots.nodes[i], nodePositions, numPositions, rootPos, canvasSize.x);
        }

        // Draw the nodes
        for (int i = 0; i < numPositions; i++) {
            Node<std::string>* node = nodePositions[i].first;
            ImVec2 position = nodePositions[i].second;

            drawNode(drawList, position, node->getKey(), node == heap.min, node->mark, IM_COL32(255, 255, 255, 255));
        }

        // Draw links between nodes
        if (roots.count > 0) {
            for (int i = 0; i < roots.count; i++) {
                drawLinks(drawList, roots.nodes[i], nodePositions, numPositions);
            }
        }

        ImGui::End();
    }
};