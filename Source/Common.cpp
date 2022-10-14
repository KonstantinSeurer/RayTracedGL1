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

#include "Common.h"


namespace RTGL1
{
// extension functions' definitions
#define VK_EXTENSION_FUNCTION( fname ) PFN_##fname s##fname;
VK_INSTANCE_DEBUG_UTILS_FUNCTION_LIST
VK_DEVICE_FUNCTION_LIST
VK_DEVICE_DEBUG_UTILS_FUNCTION_LIST
#undef VK_EXTENSION_FUNCTION
}

void RTGL1::InitInstanceExtensionFunctions_DebugUtils( VkInstance instance )
{
#define VK_EXTENSION_FUNCTION( fname )                                   \
    s##fname = ( PFN_##fname )vkGetInstanceProcAddr( instance, #fname ); \
    assert( s##fname != nullptr );

    VK_INSTANCE_DEBUG_UTILS_FUNCTION_LIST
#undef VK_EXTENSION_FUNCTION
}

void RTGL1::InitDeviceExtensionFunctions( VkDevice device )
{
#define VK_EXTENSION_FUNCTION( fname )                               \
    s##fname = ( PFN_##fname )vkGetDeviceProcAddr( device, #fname ); \
    assert( s##fname != nullptr );

    VK_DEVICE_FUNCTION_LIST
#undef VK_EXTENSION_FUNCTION
}

void RTGL1::InitDeviceExtensionFunctions_DebugUtils( VkDevice device )
{
#define VK_EXTENSION_FUNCTION( fname )                               \
    s##fname = ( PFN_##fname )vkGetDeviceProcAddr( device, #fname ); \
    assert( s##fname != nullptr );

    VK_DEVICE_DEBUG_UTILS_FUNCTION_LIST
#undef VK_EXTENSION_FUNCTION
}

void RTGL1::AddDebugName( VkDevice device, uint64_t obj, VkObjectType type, const char* pName )
{
    if( svkSetDebugUtilsObjectNameEXT == nullptr || pName == nullptr )
    {
        return;
    }

    VkDebugUtilsObjectNameInfoEXT nameInfo = {
        .sType        = VK_STRUCTURE_TYPE_DEBUG_UTILS_OBJECT_NAME_INFO_EXT,
        .objectType   = type,
        .objectHandle = obj,
        .pObjectName  = pName,
    };

    VkResult r = svkSetDebugUtilsObjectNameEXT( device, &nameInfo );
    VK_CHECKERROR( r );
}

void RTGL1::BeginCmdLabel( VkCommandBuffer cmd, const char* pName, const float pColor[ 4 ] )
{
    if( svkCmdBeginDebugUtilsLabelEXT == nullptr || pName == nullptr )
    {
        return;
    }

    VkDebugUtilsLabelEXT labelInfo = {
        .sType      = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT,
        .pLabelName = pName,
    };

    if( pColor != nullptr )
    {
        memcpy( labelInfo.color, pColor, sizeof( float ) * 4 );
    }

    svkCmdBeginDebugUtilsLabelEXT( cmd, &labelInfo );
}

void RTGL1::EndCmdLabel( VkCommandBuffer cmd )
{
    if( svkCmdEndDebugUtilsLabelEXT == nullptr )
    {
        return;
    }

    svkCmdEndDebugUtilsLabelEXT( cmd );
}
