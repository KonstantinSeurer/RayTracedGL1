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

layout( location = 0 ) in vec4 in_color;
layout( location = 1 ) in vec2 in_texCoord;
layout( location = 2 ) flat in uint in_textureIndex;
layout( location = 3 ) flat in uint in_emissiveTextureIndex;
layout( location = 4 ) flat in float in_emissiveMult;

layout( location = 0 ) out vec4 out_color;
layout( location = 1 ) out vec3 out_screenEmission;
layout( location = 2 ) out float out_reactivity;

#define DESC_SET_TEXTURES 0
#include "ShaderCommonGLSLFunc.h"

layout( constant_id = 0 ) const uint alphaTest = 0;

#define ALPHA_THRESHOLD 0.5

void main()
{
    vec4 ldrColor = in_color * getTextureSample( in_textureIndex, in_texCoord );

    out_reactivity = 0.9 * ldrColor.a;
    out_color      = ldrColor;

    {
        vec3 ldrEmis;
        if( in_emissiveTextureIndex != MATERIAL_NO_TEXTURE )
        {
            ldrEmis = in_color.rgb * getTextureSample( in_emissiveTextureIndex, in_texCoord ).rgb;
        }
        else
        {
            ldrEmis = ldrColor.rgb;
        }
        ldrEmis *= in_emissiveMult;

        out_screenEmission = ldrEmis;
    }

    if( alphaTest != 0 )
    {
        if( out_color.a < ALPHA_THRESHOLD )
        {
            discard;
        }
    }
}
