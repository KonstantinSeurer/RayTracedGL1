// Copyright (c) 2021 Sultim Tsyrendashiev
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

#include "Common.h"
#include "DepthCopying.h"
#include "Framebuffers.h"
#include "RasterizerPipelines.h"

namespace RTGL1
{
    class RasterPass : public IShaderDependency
    {
    public:
        RasterPass( VkDevice                                device,
                    VkPhysicalDevice                        physDevice,
                    VkPipelineLayout                        pipelineLayout,
                    const std::shared_ptr< ShaderManager >& shaderManager,
                    const std::shared_ptr< Framebuffers >&  storageFramebuffers,
                    const RgInstanceCreateInfo&             instanceInfo );
        ~RasterPass() override;

        RasterPass( const RasterPass& other )     = delete;
        RasterPass( RasterPass&& other ) noexcept = delete;
        RasterPass& operator=( const RasterPass& other ) = delete;
        RasterPass& operator=( RasterPass&& other ) noexcept = delete;

        void PrepareForFinal( VkCommandBuffer                        cmd,
                              uint32_t                               frameIndex,
                              const std::shared_ptr< Framebuffers >& storageFramebuffers,
                              uint32_t                               renderWidth,
                              uint32_t                               renderHeight );

        void CreateFramebuffers( uint32_t                                       renderWidth,
                                 uint32_t                                       renderHeight,
                                 const std::shared_ptr< Framebuffers >&         storageFramebuffers,
                                 const std::shared_ptr< MemoryAllocator >&      allocator,
                                 const std::shared_ptr< CommandBufferManager >& cmdManager );
        void DestroyFramebuffers();

        void OnShaderReload( const ShaderManager* shaderManager ) override;

        VkRenderPass                                  GetWorldRenderPass() const;
        VkRenderPass                                  GetSkyRenderPass() const;
        const std::shared_ptr< RasterizerPipelines >& GetRasterPipelines() const;
        const std::shared_ptr< RasterizerPipelines >& GetSkyRasterPipelines() const;

        VkFramebuffer                                 GetWorldFramebuffer( uint32_t frameIndex ) const;
        VkFramebuffer GetSkyFramebuffer( uint32_t frameIndex ) const;

    private:
        VkRenderPass CreateWorldRenderPass( VkFormat finalImageFormat,
                                            VkFormat screenEmisionFormat,
                                            VkFormat depthImageFormat ) const;
        VkRenderPass CreateSkyRenderPass( VkFormat skyFinalImageFormat,
                                          VkFormat depthImageFormat ) const;

        void CreateDepthBuffers( uint32_t                                       width,
                                 uint32_t                                       height,
                                 const std::shared_ptr< MemoryAllocator >&      allocator,
                                 const std::shared_ptr< CommandBufferManager >& cmdManager );
        void DestroyDepthBuffers();

    private:
        VkDevice device = VK_NULL_HANDLE;

        VkRenderPass worldRenderPass = VK_NULL_HANDLE;
        VkRenderPass skyRenderPass   = VK_NULL_HANDLE;

        std::shared_ptr< RasterizerPipelines > worldPipelines;
        std::shared_ptr< RasterizerPipelines > skyPipelines;

        VkFramebuffer worldFramebuffers[ MAX_FRAMES_IN_FLIGHT ] = {};
        VkFramebuffer skyFramebuffers[ MAX_FRAMES_IN_FLIGHT ]   = {};

        std::shared_ptr< DepthCopying > depthCopying;

        VkImage        depthImages[ MAX_FRAMES_IN_FLIGHT ] = {};
        VkImageView    depthViews[ MAX_FRAMES_IN_FLIGHT ]  = {};
        VkDeviceMemory depthMemory[ MAX_FRAMES_IN_FLIGHT ] = {};
    };

}
