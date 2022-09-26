#pragma once

#include <GLFW/glfw3.h>
#include <STB/stb_image.h>

#include <memory>

#include "Utils/Types.hpp"

namespace Graphics {
    struct Deleter {
        void operator()(u8* pixelData) const
        {
            if (pixelData) {
                stbi_image_free(pixelData);
            }
        }
        void operator()(GLFWwindow* window) const
        {
            if (window) {
                glfwDestroyWindow(window);
            }
        }
    };
}  // namespace Graphics

using PixelData = std::unique_ptr<u8, Graphics::Deleter>;
using Window    = std::unique_ptr<GLFWwindow, Graphics::Deleter>;
