// This file was generated by GenerateShaderCommon.py

#pragma once

#include "../Common.h"

namespace RTGL1
{

#define FB_SAMPLER_INVALID_BINDING 0xFFFFFFFF

enum FramebufferImageIndex
{
    FB_IMAGE_INDEX_ALBEDO = 0,
    FB_IMAGE_INDEX_NORMAL = 1,
    FB_IMAGE_INDEX_NORMAL_PREV = 2,
    FB_IMAGE_INDEX_NORMAL_GEOMETRY = 3,
    FB_IMAGE_INDEX_NORMAL_GEOMETRY_PREV = 4,
    FB_IMAGE_INDEX_METALLIC_ROUGHNESS = 5,
    FB_IMAGE_INDEX_METALLIC_ROUGHNESS_PREV = 6,
    FB_IMAGE_INDEX_DEPTH_WORLD = 7,
    FB_IMAGE_INDEX_DEPTH_WORLD_PREV = 8,
    FB_IMAGE_INDEX_DEPTH_GRAD = 9,
    FB_IMAGE_INDEX_DEPTH_NDC = 10,
    FB_IMAGE_INDEX_MOTION = 11,
    FB_IMAGE_INDEX_UNFILTERED_DIRECT = 12,
    FB_IMAGE_INDEX_UNFILTERED_SPECULAR = 13,
    FB_IMAGE_INDEX_UNFILTERED_INDIRECT_S_H_R = 14,
    FB_IMAGE_INDEX_UNFILTERED_INDIRECT_S_H_G = 15,
    FB_IMAGE_INDEX_UNFILTERED_INDIRECT_S_H_B = 16,
    FB_IMAGE_INDEX_SURFACE_POSITION = 17,
    FB_IMAGE_INDEX_SURFACE_POSITION_PREV = 18,
    FB_IMAGE_INDEX_VISIBILITY_BUFFER = 19,
    FB_IMAGE_INDEX_VISIBILITY_BUFFER_PREV = 20,
    FB_IMAGE_INDEX_VIEW_DIRECTION = 21,
    FB_IMAGE_INDEX_VIEW_DIRECTION_PREV = 22,
    FB_IMAGE_INDEX_PRIMARY_TO_REFL_REFR = 23,
    FB_IMAGE_INDEX_THROUGHPUT = 24,
    FB_IMAGE_INDEX_PRE_FINAL = 25,
    FB_IMAGE_INDEX_FINAL = 26,
    FB_IMAGE_INDEX_UPSCALED_PING = 27,
    FB_IMAGE_INDEX_UPSCALED_PONG = 28,
    FB_IMAGE_INDEX_UPSCALED_HISTORY = 29,
    FB_IMAGE_INDEX_UPSCALED_HISTORY_PREV = 30,
    FB_IMAGE_INDEX_MOTION_DLSS = 31,
    FB_IMAGE_INDEX_ACCUM_HISTORY_LENGTH = 32,
    FB_IMAGE_INDEX_ACCUM_HISTORY_LENGTH_PREV = 33,
    FB_IMAGE_INDEX_DIFF_ACCUM_COLOR = 34,
    FB_IMAGE_INDEX_DIFF_ACCUM_COLOR_PREV = 35,
    FB_IMAGE_INDEX_DIFF_ACCUM_MOMENTS = 36,
    FB_IMAGE_INDEX_DIFF_ACCUM_MOMENTS_PREV = 37,
    FB_IMAGE_INDEX_DIFF_COLOR_HISTORY = 38,
    FB_IMAGE_INDEX_DIFF_PING_COLOR_AND_VARIANCE = 39,
    FB_IMAGE_INDEX_DIFF_PONG_COLOR_AND_VARIANCE = 40,
    FB_IMAGE_INDEX_SPEC_ACCUM_COLOR = 41,
    FB_IMAGE_INDEX_SPEC_ACCUM_COLOR_PREV = 42,
    FB_IMAGE_INDEX_SPEC_PING_COLOR = 43,
    FB_IMAGE_INDEX_SPEC_PONG_COLOR = 44,
    FB_IMAGE_INDEX_INDIR_ACCUM_S_H_R = 45,
    FB_IMAGE_INDEX_INDIR_ACCUM_S_H_R_PREV = 46,
    FB_IMAGE_INDEX_INDIR_ACCUM_S_H_G = 47,
    FB_IMAGE_INDEX_INDIR_ACCUM_S_H_G_PREV = 48,
    FB_IMAGE_INDEX_INDIR_ACCUM_S_H_B = 49,
    FB_IMAGE_INDEX_INDIR_ACCUM_S_H_B_PREV = 50,
    FB_IMAGE_INDEX_INDIR_PING_S_H_R = 51,
    FB_IMAGE_INDEX_INDIR_PING_S_H_G = 52,
    FB_IMAGE_INDEX_INDIR_PING_S_H_B = 53,
    FB_IMAGE_INDEX_INDIR_PONG_S_H_R = 54,
    FB_IMAGE_INDEX_INDIR_PONG_S_H_G = 55,
    FB_IMAGE_INDEX_INDIR_PONG_S_H_B = 56,
    FB_IMAGE_INDEX_ATROUS_FILTERED_VARIANCE = 57,
    FB_IMAGE_INDEX_BLOOM_MIP1 = 58,
    FB_IMAGE_INDEX_BLOOM_MIP2 = 59,
    FB_IMAGE_INDEX_BLOOM_MIP3 = 60,
    FB_IMAGE_INDEX_BLOOM_MIP4 = 61,
    FB_IMAGE_INDEX_BLOOM_MIP5 = 62,
    FB_IMAGE_INDEX_BLOOM_RESULT = 63,
    FB_IMAGE_INDEX_WIPE_EFFECT_SOURCE = 64,
    FB_IMAGE_INDEX_RESERVOIRS = 65,
    FB_IMAGE_INDEX_RESERVOIRS_PREV = 66,
    FB_IMAGE_INDEX_RESERVOIRS_INITIAL = 67,
    FB_IMAGE_INDEX_GRADIENT_INPUTS = 68,
    FB_IMAGE_INDEX_GRADIENT_INPUTS_PREV = 69,
    FB_IMAGE_INDEX_D_I_S_PING_GRADIENT = 70,
    FB_IMAGE_INDEX_D_I_S_PONG_GRADIENT = 71,
    FB_IMAGE_INDEX_D_I_S_GRADIENT_HISTORY = 72,
    FB_IMAGE_INDEX_GRADIENT_PREV_PIX = 73,
};

enum FramebufferImageFlagBits
{
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_IS_ATTACHMENT = 4,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_FORCE_SIZE_1_2 = 8,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_FORCE_SIZE_1_3 = 16,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_FORCE_SIZE_1_4 = 32,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_FORCE_SIZE_1_8 = 64,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_FORCE_SIZE_1_16 = 128,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_FORCE_SIZE_1_32 = 256,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_BILINEAR_SAMPLER = 512,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_UPSCALED_SIZE = 1024,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_SINGLE_PIXEL_SIZE = 2048,
    FB_IMAGE_FLAGS_FRAMEBUF_FLAGS_USAGE_TRANSFER = 4096,
};
typedef uint32_t FramebufferImageFlags;

extern const uint32_t ShFramebuffers_Count;
extern const VkFormat ShFramebuffers_Formats[];
extern const FramebufferImageFlags ShFramebuffers_Flags[];
extern const uint32_t ShFramebuffers_Bindings[];
extern const uint32_t ShFramebuffers_BindingsSwapped[];
extern const uint32_t ShFramebuffers_Sampler_Bindings[];
extern const uint32_t ShFramebuffers_Sampler_BindingsSwapped[];
extern const char *const ShFramebuffers_DebugNames[];

}