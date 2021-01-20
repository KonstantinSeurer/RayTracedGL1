// Copyright (c) 2020-2021 Sultim Tsyrendashiev
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

#pragma once

#include <RTGL1/RTGL1.h>

#include <memory>

#include "CommandBufferManager.h"
#include "Common.h"
#include "PhysicalDevice.h"
#include "Scene.h"
#include "Swapchain.h"
#include "Queues.h"
#include "GlobalUniform.h"
#include "PathTracer.h"
#include "Rasterizer.h"
#include "BasicStorageImage.h"
#include "MemoryAllocator.h"
#include "TextureManager.h"

class VulkanDevice
{
public:
    explicit VulkanDevice(const RgInstanceCreateInfo *info);
    ~VulkanDevice();

    VulkanDevice(const VulkanDevice& other) = delete;
    VulkanDevice(VulkanDevice&& other) noexcept = delete;
    VulkanDevice& operator=(const VulkanDevice& other) = delete;
    VulkanDevice& operator=(VulkanDevice&& other) noexcept = delete;

    RgResult UploadGeometry(const RgGeometryUploadInfo *uploadInfo, RgGeometry *result);
    RgResult UpdateGeometryTransform(const RgUpdateTransformInfo *updateInfo);

    RgResult UploadRasterizedGeometry(const RgRasterizedGeometryUploadInfo *uploadInfo);

    RgResult SubmitStaticGeometries();
    RgResult StartNewStaticScene();

    // TODO: empty (white) texture 1x1 with index 0 (RG_NO_MATERIAL)
    RgResult CreateStaticMaterial(const RgStaticMaterialCreateInfo *createInfo, RgMaterial *result);
    RgResult CreateAnimatedMaterial(const RgAnimatedMaterialCreateInfo *createInfo, RgMaterial *result);
    RgResult ChangeAnimatedMaterialFrame(RgMaterial animatedMaterial, uint32_t frameIndex);
    RgResult CreateDynamicMaterial(const RgDynamicMaterialCreateInfo *createInfo, RgMaterial *result);
    RgResult UpdateDynamicMaterial(RgMaterial dynamicMaterial, const RgDynamicMaterialUpdateInfo *updateInfo);
    RgResult DestroyMaterial(RgMaterial material);


    RgResult StartFrame(uint32_t surfaceWidth, uint32_t surfaceHeight);
    RgResult DrawFrame(const RgDrawFrameInfo *frameInfo);

private:
    void CreateInstance(const char **ppWindowExtensions, uint32_t extensionCount);
    void CreateDevice();
    void CreateSyncPrimitives();
    static VkSurfaceKHR GetSurfaceFromUser(VkInstance instance, const RgInstanceCreateInfo &info);

    void DestroyInstance();
    void DestroyDevice();
    void DestroySyncPrimitives();

    void FillUniform(ShGlobalUniform *gu, const RgDrawFrameInfo *frameInfo);

    VkCommandBuffer BeginFrame(uint32_t surfaceWidth, uint32_t surfaceHeight);
    void Render(VkCommandBuffer cmd, uint32_t renderWidth, uint32_t renderHeight);
    void EndFrame(VkCommandBuffer cmd);

private:
    VkInstance          instance;
    VkDevice            device;
    VkSurfaceKHR        surface;

    // [0..MAX_FRAMES_IN_FLIGHT-1]
    uint32_t            currentFrameIndex;
    VkCommandBuffer     currentFrameCmd;

    VkFence             frameFences[MAX_FRAMES_IN_FLIGHT];
    VkSemaphore         imageAvailableSemaphores[MAX_FRAMES_IN_FLIGHT];
    VkSemaphore         renderFinishedSemaphores[MAX_FRAMES_IN_FLIGHT];

    std::shared_ptr<PhysicalDevice>         physDevice;
    std::shared_ptr<Queues>                 queues;
    std::shared_ptr<Swapchain>              swapchain;

    std::shared_ptr<MemoryAllocator>        memAllocator;

    std::shared_ptr<CommandBufferManager>   cmdManager;

    // TODO: this storage image is only for debugging in the beginning
    std::shared_ptr<BasicStorageImage>      storageImage;

    std::shared_ptr<GlobalUniform>          uniform;
    std::shared_ptr<Scene>                  scene;

    std::shared_ptr<ShaderManager>          shaderManager;
    std::shared_ptr<RayTracingPipeline>     rtPipeline;
    std::shared_ptr<PathTracer>             pathTracer;
    std::shared_ptr<Rasterizer>             rasterizer;

    std::shared_ptr<TextureManager>         textureManager;

    bool                                    enableValidationLayer;
    VkDebugUtilsMessengerEXT                debugMessenger;
    PFN_rgPrint                             debugPrint;

    VertexBufferProperties                  vbProperties;
};
