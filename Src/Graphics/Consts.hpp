#pragma once

#include "Utils/Types.hpp"

namespace Graphics {
    inline constexpr s32 MaxBuffers = 1;

    inline constexpr const c8* ProjViewUniform = "projView";
    inline constexpr const c8* TextureUniform  = "tex";

    inline constexpr const c8* VSData = R"(
        #version 330 core
        layout (location = 0) in vec2 vOffset;
        layout (location = 1) in vec4 vDst;
        layout (location = 2) in vec4 vSrc;
        layout (location = 3) in uint vTid;
        uniform mat4 projView;
             out vec2 fOffset;
             out vec4 fSrc;
        flat out uint fTid;
        void main() {
            fOffset = vOffset;
            fSrc = vSrc;
            fTid = vTid;
            gl_Position = projView * vec4((vOffset * vDst.zw) + vDst.xy, 0.f, 1.f);
        }
    )";

    inline constexpr const c8* FSData = R"(
        #version 330 core
        in vec2 fOffset;
        in vec4 fSrc;
        flat in uint fTid;
        out vec4 Color;
        uniform sampler2D tex[5];
        void main() {
            Color = texelFetch(tex[fTid], ivec2((fOffset * fSrc.zw) + fSrc.xy), 0);
        }
    )";
}  // namespace Graphics
