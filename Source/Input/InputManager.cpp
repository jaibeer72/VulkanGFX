#include "InputManager.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Input {

void InputManager::initialize(GLFWwindow* window) {
    window_ = window;
    if (window_) {
        glfwSetWindowUserPointer(window_, this);
        glfwSetKeyCallback(window_, InputManager::keyCallback);
        std::cout << "[Input] GLFW key callback installed\n";
    }
}

void InputManager::onKeyEvent(int key, int scancode, int action, int mods) {
    eventQueue_.push_back({key, scancode, action, mods});
    std::cout << "[Input] Raw key event: key=" << key << " scancode=" << scancode << " action=" << action << " mods=" << mods << "\n";

    // Update action states immediately for responsiveness
    if (action == GLFW_PRESS) {
        for (auto &a : map_.actions()) {
            if (map_.getActionKey(a) == key) {
                previousState_[a] = currentState_[a];
                currentState_[a] = true;
            }
        }
    } else if (action == GLFW_RELEASE) {
        for (auto &a : map_.actions()) {
            if (map_.getActionKey(a) == key) {
                previousState_[a] = currentState_[a];
                currentState_[a] = false;
            }
        }
    }
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto *inst = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    if (inst) inst->onKeyEvent(key, scancode, action, mods);
} 

void InputManager::update() {
    if (!window_) return;

    // Actions
    for (auto &action : map_.actions()) {
        int key = map_.getActionKey(action);
        if (key == -1) continue;
        int state = glfwGetKey(window_, key);
        previousState_[action] = currentState_[action];
        currentState_[action] = (state == GLFW_PRESS || state == GLFW_REPEAT);
        if (currentState_[action] && !previousState_[action]) {
            std::cout << "[Input] Action pressed: " << action << " (key=" << key << ")\n";
        }
    }

    // Axes (simple keyboard axes)
    for (auto &axis : map_.axes()) {
        auto keys = map_.getAxisKeys(axis);
        int pos = keys.first;
        int neg = keys.second;
        float value = 0.f;
        if (pos != -1) {
            int s = glfwGetKey(window_, pos);
            if (s == GLFW_PRESS || s == GLFW_REPEAT) value += 1.f;
        }
        if (neg != -1) {
            int s = glfwGetKey(window_, neg);
            if (s == GLFW_PRESS || s == GLFW_REPEAT) value -= 1.f;
        }
        if (axisState_[axis] != value) {
            std::cout << "[Input] Axis " << axis << " changed: " << value << "\n";
        }
        axisState_[axis] = value;
    }
}

bool InputManager::isActionPressed(const std::string& action) const {
    bool cur = false, prev = false;
    auto itCur = currentState_.find(action);
    if (itCur != currentState_.end()) cur = itCur->second;
    auto itPrev = previousState_.find(action);
    if (itPrev != previousState_.end()) prev = itPrev->second;
    return cur && !prev;
}

bool InputManager::isActionDown(const std::string& action) const {
    auto it = currentState_.find(action);
    return it != currentState_.end() ? it->second : false;
}

float InputManager::getAxis(const std::string& axis) const {
    auto it = axisState_.find(axis);
    return it != axisState_.end() ? it->second : 0.f;
}

void InputManager::bindAction(const std::string& action, int key) {
    map_.bindAction(action, key);
    currentState_.try_emplace(action, false);
    previousState_.try_emplace(action, false);
}

void InputManager::bindAxis(const std::string& axis, int positiveKey, int negativeKey) {
    map_.bindAxis(axis, positiveKey, negativeKey);
    axisState_.try_emplace(axis, 0.f);
}

} // namespace Input