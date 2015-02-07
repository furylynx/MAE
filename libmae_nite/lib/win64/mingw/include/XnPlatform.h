/*****************************************************************************
*                                                                            *
*  OpenNI 1.x Alpha                                                          *
*  Copyright (C) 2012 PrimeSense Ltd.                                        *
*                                                                            *
*  This file is part of OpenNI.                                              *
*                                                                            *
*  Licensed under the Apache License, Version 2.0 (the "License");           *
*  you may not use this file except in compliance with the License.          *
*  You may obtain a copy of the License at                                   *
*                                                                            *
*      http://www.apache.org/licenses/LICENSE-2.0                            *
*                                                                            *
*  Unless required by applicable law or agreed to in writing, software       *
*  distributed under the License is distributed on an "AS IS" BASIS,         *
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
*  See the License for the specific language governing permissions and       *
*  limitations under the License.                                            *
*                                                                            *
*****************************************************************************/
#ifndef __XN_PLATFORM_H__
#define __XN_PLATFORM_H__

//---------------------------------------------------------------------------
// Platform Defines
//---------------------------------------------------------------------------
#define XN_PLATFORM_WIN32 1
#define XN_PLATFORM_XBOX360 2
#define XN_PLATFORM_PS3 3
#define XN_PLATFORM_WII 4
#define XN_PLATFORM_LINUX_X86 5
#define XN_PLATFORM_FILES_ONLY 6
#define XN_PLATFORM_ARC 6
#define XN_PLATFORM_LINUX_ARM 7
#define XN_PLATFORM_MACOSX 8
#define XN_PLATFORM_ANDROID_ARM 9
#define XN_PLATFORM_WIN32MINGW 10

#define XN_PLATFORM_IS_LITTLE_ENDIAN 1
#define XN_PLATFORM_IS_BIG_ENDIAN    2

#define XN_PLATFORM_USE_NO_VAARGS 1
#define XN_PLATFORM_USE_WIN32_VAARGS_STYLE 2
#define XN_PLATFORM_USE_GCC_VAARGS_STYLE   3
#define XN_PLATFORM_USE_ARC_VAARGS_STYLE   4

//---------------------------------------------------------------------------
// Platform Identifier 
//---------------------------------------------------------------------------

#if defined(_WIN32) // Microsoft Visual Studio

#ifdef __MINGW32__
	#include "Win32MinGW/XnPlatformWin32MinGW.h"
#else
	#ifndef RC_INVOKED
		#if _MSC_VER < 1300 // Before MSVC7 (2003)
			#error Xiron Platform Abstraction Layer - Win32 - Microsoft Visual Studio versions below 2003 (7.0) are not supported!
		#endif

		#if _MSC_VER > 1600 // After MSVC8 (2010)
			#error Xiron Platform Abstraction Layer - Win32 - Microsoft Visual Studio versions above 2010 (10.0) are not supported!
		#endif
	#endif

	#include "Win32/XnPlatformWin32.h"
#endif

#elif defined(ANDROID) && defined(__arm__)
	#include "Android-Arm/XnPlatformAndroid-Arm.h"
#elif (linux && (i386 || __x86_64__))
	#include "Linux-x86/XnPlatformLinux-x86.h"
#elif (linux && __arm__)
	#include "Linux-Arm/XnPlatformLinux-Arm.h"
#elif _ARC
	#include "ARC/XnPlatformARC.h"
#elif (__APPLE__)
	#include "MacOSX/XnPlatformMacOSX.h"
#else
	#error OpenNI Platform Abstraction Layer - Unsupported Platform!
#endif

//---------------------------------------------------------------------------
// Basic Common Macros
//---------------------------------------------------------------------------
#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE
	#define FALSE 0
#endif

#define XN_MIN(a,b)            (((a) < (b)) ? (a) : (b))

#define XN_MAX(a,b)            (((a) > (b)) ? (a) : (b))

typedef void (*XnFuncPtr)();

#define XN_COMPILER_ASSERT(x) typedef int compileAssert[x ? 1 : -1]

struct XnRegistrationHandleImpl;
typedef struct XnRegistrationHandleImpl* XnRegistrationHandle;

//---------------------------------------------------------------------------
// API Export/Import Macros
//---------------------------------------------------------------------------

#ifdef __cplusplus
	#define XN_C_API_EXPORT extern "C" XN_API_EXPORT
	#define XN_C_API_IMPORT extern "C" XN_API_IMPORT
	#define XN_CPP_API_EXPORT XN_API_EXPORT
	#define XN_CPP_API_IMPORT XN_API_IMPORT
#else
	#define XN_C_API_EXPORT XN_API_EXPORT
	#define XN_C_API_IMPORT XN_API_IMPORT
#endif

#ifdef XN_EXPORTS
	#define XN_C_API XN_C_API_EXPORT
	#define XN_CPP_API XN_CPP_API_EXPORT
#else
	#define XN_C_API XN_C_API_IMPORT
	#define XN_CPP_API XN_CPP_API_IMPORT
#endif

#endif //__XN_PLATFORM_H__

