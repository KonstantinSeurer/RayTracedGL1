// Copyright (c) 2022 Sultim Tsyrendashiev
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#version 460

#if 0

layout (location = 0) in vec4 vertColor;
layout (location = 1) in vec2 vertTexCoord;
layout (location = 2) flat in uint textureIndex;

layout (location = 0) out vec4 outColor;
layout (location = 1) out vec3 outScreenEmission;

#define DESC_SET_TEXTURES 1
#include "ShaderCommonGLSLFunc.h"

layout (constant_id = 0) const uint alphaTest = 0;

#define ALPHA_THRESHOLD 0.5

void main()
{
    outColor = vertColor * getTextureSample(textureIndex, vertTexCoord);
    outScreenEmission = vec3(0);

    if (alphaTest != 0)
    {
        if (outColor.a < ALPHA_THRESHOLD)
        {
            discard;
        }
    }
}

#else
void main() {}
#endif
