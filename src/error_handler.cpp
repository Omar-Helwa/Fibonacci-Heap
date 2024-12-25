#include "../include/error_handler.h"
#include "imgui.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "_env.h"


void error_handler::e_log(int id) {
    int classID = id / 10;
    int errorID = id % 10;
    std::cerr << std::endl << errorClass[classID] + errorMessages[errorID];
    addErrorMessage(errorClass[classID] + errorMessages[errorID], 4000);
}

void error_handler::verbose_log(int classID, std::string msg) {
    if (FLAG_VERBOSE) {
        std::cout << std::endl << errorClass[classID] + msg;
    }
}

void error_handler::addErrorMessage(const std::string &message, int durationMS) {
    TimedMessage timedMessage;
    timedMessage.message = message;
    timedMessage.endTime = std::chrono::steady_clock::now() + std::chrono::milliseconds(durationMS);
    activeMessages.push_back(timedMessage); // Add the message to the activeMessages vector
}


void error_handler::renderErrorMessages() {
    auto now = std::chrono::steady_clock::now();
    for (auto it = activeMessages.begin(); it != activeMessages.end(); ) {
        if (now > it->endTime) {
            it = activeMessages.erase(it);
        } else {
            ++it;
        }
    }

    // Set the font color to red for error messages
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));

    for (const auto& msg : activeMessages) {
        ImGui::Text("%s", msg.message.c_str());
    }

    // Revert to the previous font color
    ImGui::PopStyleColor();
}

