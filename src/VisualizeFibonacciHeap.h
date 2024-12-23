// VisualizeFibonacciHeap.h
#pragma once

#include "imgui.h"
#include "FibHeap.h"
#include "Node.h"
#include "NodeArray.h"
#include <string>

class ImDrawList; // Forward declaration
struct ImVec2;

void VisualizeFibonacciHeap(FibHeap<std::string>& heap);

// Helper functions:
void DrawNode(ImDrawList* drawList, ImVec2 center, int key, bool isMin, bool isMarked, ImU32 color);
void DrawLinks(ImDrawList* drawList, Node<std::string>* node, NodePositionPair* nodePositions, int numPositions);
void CalculateNodePositions(Node<std::string>* node, NodePositionPair* nodePositions, int& numPositions, ImVec2 parentPos, float canvasWidth);

NodeArray getRoots(const FibHeap<std::string>& heap);
NodeArray getChildren(Node<std::string>* node);