#pragma once

#include <GLFW/glfw3.h>

#include <memory>

namespace Graphics {
	struct Deleter {
		void operator()(GLFWwindow* window) const {
			if (window) { glfwDestroyWindow(window); }
		}
	};
}

using Window = std::unique_ptr<GLFWwindow, Graphics::Deleter>;
