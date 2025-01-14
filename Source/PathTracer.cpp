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

#include "PathTracer.h"
#include "Generated/ShaderCommonC.h"
#include "CmdLabel.h"

using namespace RTGL1;

PathTracer::PathTracer(VkDevice _device, std::shared_ptr<RayTracingPipeline> _rtPipeline)
    : rtPipeline(std::move(_rtPipeline))
{}

PathTracer::TraceParams PathTracer::Bind( VkCommandBuffer                  cmd,
                                          uint32_t                         frameIndex,
                                          uint32_t                         width,
                                          uint32_t                         height,
                                          Scene*                           scene,
                                          const GlobalUniform*             uniform,
                                          const TextureManager*            textureManager,
                                          std::shared_ptr< Framebuffers >  framebuffers,
                                          std::shared_ptr< RestirBuffers > restirBuffers,
                                          const BlueNoise*                 blueNoise,
                                          const CubemapManager*            cubemapManager,
                                          const RenderCubemap*             renderCubemap,
                                          const PortalList*                portalList,
                                          const Volumetric*                volumetric )
{
    rtPipeline->Bind(cmd);

    VkDescriptorSet sets[] = {
        // ray tracing acceleration structures
        scene->GetASManager()->GetTLASDescSet(frameIndex),
        // storage images
        framebuffers->GetDescSet(frameIndex),
        // uniform
        uniform->GetDescSet(frameIndex),
        // vertex data
        scene->GetASManager()->GetBuffersDescSet(frameIndex),
        // textures
        textureManager->GetDescSet(frameIndex),
        // uniform random
        blueNoise->GetDescSet(),
        // light sources
        scene->GetLightManager()->GetDescSet(frameIndex),
        // cubemaps
        cubemapManager->GetDescSet(frameIndex),
        // dynamic cubemaps
        renderCubemap->GetDescSet(),
        // portals
        portalList->GetDescSet(frameIndex),
        // device local buffers for restir
        restirBuffers->GetDescSet(frameIndex),
        // device local buffers for volumetrics
        volumetric->GetDescSet(frameIndex),
    };

    vkCmdBindDescriptorSets( cmd,
                             VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR,
                             rtPipeline->GetLayout(),
                             0,
                             std::size( sets ),
                             sets,
                             0,
                             nullptr );

    TraceParams p = {};
    p.cmd = cmd;
    p.frameIndex = frameIndex;
    p.width = width;
    p.height = height;
    p.framebuffers = std::move( framebuffers );
    p.restirBuffers = std::move( restirBuffers );

    return p;
}

void PathTracer::TraceRays(VkCommandBuffer cmd, uint32_t sbtRayGenIndex, uint32_t width, uint32_t height, uint32_t depth)
{
    VkStridedDeviceAddressRegionKHR raygenEntry, missEntry, hitEntry, callableEntry;
    rtPipeline->GetEntries(sbtRayGenIndex, raygenEntry, missEntry, hitEntry, callableEntry);

    svkCmdTraceRaysKHR(
        cmd,
        &raygenEntry, &missEntry, &hitEntry, &callableEntry,
        width, height, depth);
}

void PathTracer::TracePrimaryRays(const TraceParams &params)
{
    CmdLabel label(params.cmd, "Primary rays");

    typedef FramebufferImageIndex FI;
    FI fs[] =
    {
        FI::FB_IMAGE_INDEX_ALBEDO,
        FI::FB_IMAGE_INDEX_NORMAL,
        FI::FB_IMAGE_INDEX_NORMAL_GEOMETRY,
        FI::FB_IMAGE_INDEX_METALLIC_ROUGHNESS,
        FI::FB_IMAGE_INDEX_DEPTH_WORLD,
        FI::FB_IMAGE_INDEX_DEPTH_GRAD,
        FI::FB_IMAGE_INDEX_DEPTH_NDC,
        FI::FB_IMAGE_INDEX_MOTION,
        FI::FB_IMAGE_INDEX_SURFACE_POSITION,
        FI::FB_IMAGE_INDEX_VISIBILITY_BUFFER,
        FI::FB_IMAGE_INDEX_VIEW_DIRECTION,
        FI::FB_IMAGE_INDEX_THROUGHPUT,
        FI::FB_IMAGE_INDEX_PRIMARY_TO_REFL_REFR,
    };
    params.framebuffers->BarrierMultiple(params.cmd, params.frameIndex, fs);


    TraceRays(params.cmd, SBT_INDEX_RAYGEN_PRIMARY, params.width, params.height);
}

void PathTracer::TraceReflectionRefractionRays(const TraceParams &params)
{
    CmdLabel label(params.cmd, "Reflection/refraction rays");

    typedef FramebufferImageIndex FI;
    FI fs[] =
    {
        FI::FB_IMAGE_INDEX_ALBEDO,
        FI::FB_IMAGE_INDEX_NORMAL,
        FI::FB_IMAGE_INDEX_NORMAL_GEOMETRY,
        FI::FB_IMAGE_INDEX_METALLIC_ROUGHNESS,
        FI::FB_IMAGE_INDEX_DEPTH_WORLD,
        FI::FB_IMAGE_INDEX_MOTION,
        FI::FB_IMAGE_INDEX_SURFACE_POSITION,
        FI::FB_IMAGE_INDEX_VISIBILITY_BUFFER,
        FI::FB_IMAGE_INDEX_VIEW_DIRECTION,
        FI::FB_IMAGE_INDEX_THROUGHPUT,
        FI::FB_IMAGE_INDEX_PRIMARY_TO_REFL_REFR,
    };
    params.framebuffers->BarrierMultiple(params.cmd, params.frameIndex, fs);


    TraceRays(params.cmd, SBT_INDEX_RAYGEN_REFL_REFR, params.width, params.height);
}

void PathTracer::CalculateInitialReservoirs(const TraceParams& params)
{
    CmdLabel label(params.cmd, "Initial reservoirs");


    typedef FramebufferImageIndex FI;
    FI fs[] =
    {
        FI::FB_IMAGE_INDEX_ALBEDO,
        FI::FB_IMAGE_INDEX_SURFACE_POSITION,
        FI::FB_IMAGE_INDEX_METALLIC_ROUGHNESS,
        FI::FB_IMAGE_INDEX_NORMAL,
        FI::FB_IMAGE_INDEX_NORMAL_GEOMETRY,
        FI::FB_IMAGE_INDEX_VIEW_DIRECTION,
    };
    params.framebuffers->BarrierMultiple(params.cmd, params.frameIndex, fs);


    TraceRays(params.cmd, SBT_INDEX_RAYGEN_INITIAL_RESERVOIRS, params.width, params.height);
}

void PathTracer::TraceDirectllumination(const TraceParams &params)
{
    CmdLabel label(params.cmd, "Direct illumination");


    typedef FramebufferImageIndex FI;
    FI fs[] =
    {
        FI::FB_IMAGE_INDEX_RESERVOIRS_INITIAL,
        FI::FB_IMAGE_INDEX_ALBEDO,
        FI::FB_IMAGE_INDEX_NORMAL,
        FI::FB_IMAGE_INDEX_NORMAL_GEOMETRY,
        FI::FB_IMAGE_INDEX_METALLIC_ROUGHNESS,
        FI::FB_IMAGE_INDEX_DEPTH_WORLD,
        FI::FB_IMAGE_INDEX_DEPTH_GRAD,
        FI::FB_IMAGE_INDEX_SURFACE_POSITION,
        FI::FB_IMAGE_INDEX_VIEW_DIRECTION,
    };
    params.framebuffers->BarrierMultiple(params.cmd, params.frameIndex, fs);


    TraceRays(params.cmd, SBT_INDEX_RAYGEN_DIRECT, params.width, params.height);
}

void PathTracer::CalculateGradientsSamples(const TraceParams &params)
{
    CmdLabel label(params.cmd, "Gradient samples");


    typedef FramebufferImageIndex FI;
    FI fs[] =
    {
        FI::FB_IMAGE_INDEX_ALBEDO,
        FI::FB_IMAGE_INDEX_GRADIENT_INPUTS,
        FI::FB_IMAGE_INDEX_VIEW_DIRECTION,
        FI::FB_IMAGE_INDEX_RESERVOIRS,
        FI::FB_IMAGE_INDEX_VISIBILITY_BUFFER,
    };
    params.framebuffers->BarrierMultiple(params.cmd, params.frameIndex, fs);


    uint32_t gradWidth  = (params.width  + COMPUTE_ASVGF_STRATA_SIZE - 1) / COMPUTE_ASVGF_STRATA_SIZE;
    uint32_t gradHeight = (params.height + COMPUTE_ASVGF_STRATA_SIZE - 1) / COMPUTE_ASVGF_STRATA_SIZE;


    TraceRays(params.cmd, SBT_INDEX_RAYGEN_GRADIENTS, gradWidth, gradHeight);
}

void PathTracer::TraceIndirectllumination(const TraceParams &params)
{
    using FI = FramebufferImageIndex;

    {
        CmdLabel label(params.cmd, "Indirect illumination - Init");

        FI fs[] = 
        {
            FI::FB_IMAGE_INDEX_UNFILTERED_SPECULAR,
        };
        params.framebuffers->BarrierMultiple( params.cmd, params.frameIndex, fs );


        TraceRays( params.cmd, SBT_INDEX_RAYGEN_INDIRECT_INIT, params.width, params.height );
    }

    {
        CmdLabel label( params.cmd, "Indirect illumination - Final" );

        params.restirBuffers->BarrierInitial( params.cmd );


        TraceRays( params.cmd, SBT_INDEX_RAYGEN_INDIRECT_FINAL, params.width, params.height );
    }
}

void PathTracer::TraceVolumetric( const TraceParams& params )
{
    CmdLabel label( params.cmd, "Volumetric illumination" );

    TraceRays( params.cmd,
               SBT_INDEX_RAYGEN_VOLUMETRIC,
               VOLUMETRIC_SIZE_X,
               VOLUMETRIC_SIZE_Y,
               VOLUMETRIC_SIZE_Z );
}
