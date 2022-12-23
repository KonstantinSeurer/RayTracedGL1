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

#include "RTGL1/RTGL1.h"

namespace RTGL1
{

class UserPrint
{
public:
    UserPrint( PFN_rgPrint _printFunc, void* _pUserData )
        : printFunc( _printFunc ), pUserData( _pUserData )
    {
    }
    ~UserPrint() = default;

    UserPrint( const UserPrint& other )                = delete;
    UserPrint( UserPrint&& other ) noexcept            = delete;
    UserPrint& operator=( const UserPrint& other )     = delete;
    UserPrint& operator=( UserPrint&& other ) noexcept = delete;

    void Print( const char* pMessage, RgMessageSeverityFlags severity ) const
    {
        if( printFunc != nullptr )
        {
            printFunc( pMessage, severity, pUserData );
        }
    }

private:
    PFN_rgPrint printFunc;
    void*       pUserData;
};

}
