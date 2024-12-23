// NodeArray.h
#pragma once

#include "Node.h"
#include <string>
#include "imgui.h"

#ifndef MAX_NODES
#define MAX_NODES 100
#endif


typedef struct {
    Node<std::string>* first; // Using std::string for name
    ImVec2 second;
} NodePositionPair;

typedef struct {
    Node<std::string>* nodes[MAX_NODES]; // Using std::string for name
    int count;
} NodeArray;