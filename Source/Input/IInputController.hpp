#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Input {

class IInputController {
public:
    virtual ~IInputController() = default;

    // Initialize with a platform window handle (GLFW for now)
    virtual void initialize(GLFWwindow* window) = 0;

    // Called every frame to update internal state
    virtual void update() = 0;

    // Query input
    virtual bool isActionPressed(const std::string& action) const = 0; // pressed this frame
    virtual bool isActionDown(const std::string& action) const = 0;    // currently down
    virtual float getAxis(const std::string& axis) const = 0;         // -1..1
};

} // namespace Input