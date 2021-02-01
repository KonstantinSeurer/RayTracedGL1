// This file was generated by GenerateShaderCommon.py

#include "ShaderCommonC.h"
uint32_t ShFramebuffers_Count = 7;

VkFormat ShFramebuffers_Formats[] = 
{
    VK_FORMAT_R32G32B32A32_SFLOAT,
    VK_FORMAT_R32G32B32A32_SFLOAT,
    VK_FORMAT_R32G32B32A32_SFLOAT,
    VK_FORMAT_R32G32B32A32_SFLOAT,
    VK_FORMAT_R32G32B32A32_SFLOAT,
    VK_FORMAT_R32G32B32A32_SFLOAT,
    VK_FORMAT_R32G32B32A32_SFLOAT,
};

uint32_t ShFramebuffers_Bindings[] = 
{
    0,
    1,
    2,
    3,
    4,
    5,
    6,
};

const char *ShFramebuffers_DebugNames[] = 
{
    "Framebuf Albedo",
    "Framebuf Normal",
    "Framebuf NormalPrev",
    "Framebuf NormalGeometry",
    "Framebuf NormalGeometryPrev",
    "Framebuf Metallic",
    "Framebuf MetallicPrev",
};
