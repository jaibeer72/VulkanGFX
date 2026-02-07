#pragma once

#include "IInputController.hpp"
#include "ActionMap.hpp"
#include <deque>

#include <unordered_map>
#include <string>

namespace Input {

class InputManager : public IInputController {
public:
    InputManager() = default;
    ~InputManager() override = default;

    void initialize(GLFWwindow* window) override;
    void update() override;

    bool isActionPressed(const std::string& action) const override;
    bool isActionDown(const std::string& action) const override;
    float getAxis(const std::string& axis) const override;

    // Binding helpers
    void bindAction(const std::string& action, int key);
    void bindAxis(const std::string& axis, int positiveKey, int negativeKey);

private:
    GLFWwindow* window_{nullptr};
    ActionMap map_;

    // Event queue for raw events (diagnostics / future use)
    struct KeyEvent { int key; int scancode; int action; int mods; };
    std::deque<KeyEvent> eventQueue_;

    // Internal handler and callback for GLFW
    void onKeyEvent(int key, int scancode, int action, int mods);
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    // State
    std::unordered_map<std::string,bool> currentState_;
    std::unordered_map<std::string,bool> previousState_;
    std::unordered_map<std::string,float> axisState_;
};

} // namespace Input