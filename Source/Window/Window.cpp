//
//  Window.cpp
//  VulkanGFX
//
//  Created by Jaibeer Dugal on 08/09/2023.
//

#include "Window.hpp"
#include <iostream>

Window::Window(uint32_t width, uint32_t height, const std::string& title) : width_(width), height_(height), title_(title) {
}

Window::~Window() {
	destroy();
}

void Window::InitializeModule() {
	initialize();
}

void Window::UpdateModule() {
	pollEvents();
}

void Window::CleanUpModule() {
	destroy();
}

bool Window::initialize() {
	if (window_)
		return true; // already initialized

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW.\n";
		return false;
	}

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
	if (!window_) {
		std::cerr << "Failed to create GLFW window.\n";
		glfwTerminate();
		return false;
	}

	return true;
}

void Window::destroy() {
	if (window_) {
		glfwDestroyWindow(window_);
		window_ = nullptr;
	}

	// Terminate only when no windows are left; glfwTerminate is safe to call from here
	glfwTerminate();
}

void Window::pollEvents() {
	if (window_)
		glfwPollEvents();
}

bool Window::shouldClose() const {
	return window_ ? glfwWindowShouldClose(window_) : true;
}
