#pragma once

#include <GLAD/glad.h>

#include "Utils/Types.hpp"

namespace GLHelpers {
    inline s32 getMaxTextureUnits()
    {
        s32 result = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &result);
        return result;
    }
}  // namespace GLHelpers
