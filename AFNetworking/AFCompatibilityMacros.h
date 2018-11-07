// AFCompatibilityMacros.h
// Copyright (c) 2011–2016 Alamofire Software Foundation ( http://alamofire.org/ )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef AFCompatibilityMacros_h
#define AFCompatibilityMacros_h
/*
 
 #ifndef
 #define
 这个主要是防止发生 include时候头文件的重复包含，
 
 假设 a.h ,b.h,b.c,ac.c;
 b.h include a.h
 b.c include b.h
 ac.c inluce a.h b.h
 
 我们可以从gcc -E ac.c -o test1.i
 
 在test1.i中看看 加和不加该宏 所产生文件内容的不同
 
 ------>R-AFCompatibilityMacros_h
 */

#ifdef API_UNAVAILABLE
    #define AF_API_UNAVAILABLE(x) API_UNAVAILABLE(x)
#else
    #define AF_API_UNAVAILABLE(x)
#endif // API_UNAVAILABLE

/*
 这个宏没有啥好说的，
 iOS10开始提供的新的unavailable宏API_UNAVAILABLE:
 所以这里是为了系统适配
 API_UNAVAILABLE(macos)
 API_UNAVAILABLE(watchos, tvos)
 */

#if __has_warning("-Wunguarded-availability-new")
    #define AF_CAN_USE_AT_AVAILABLE 1
#else
    #define AF_CAN_USE_AT_AVAILABLE 0
#endif

/*
 此宏传入一个字符串作为参数，该字符串表示一种警告类型，如果该警告有效返回true
 -Wunguarded-availability-new
 这个字符串的警告可以看下边含义
 This patch adds a new warning flag called -Wunguarded-availability-new. If -Wunguarded-availability is off, this warning only warns about uses of APIs that have been introduced in macOS >= 10.13, iOS >= 11, watchOS >= 4 and tvOS >= 11. This warning is on by default. We decided to use this kind of solution as we didn't want to turn on -Wunguarded-availability by default, as we didn't want our users to get warnings about uses of old APIs in their existing projects.

  https://reviews.llvm.org/D34264
 */

#if ((__IPHONE_OS_VERSION_MAX_ALLOWED && __IPHONE_OS_VERSION_MAX_ALLOWED < 100000) || (__MAC_OS_VERSION_MAX_ALLOWED && __MAC_OS_VERSION_MAX_ALLOWED < 101200) ||(__WATCH_OS_MAX_VERSION_ALLOWED && __WATCH_OS_MAX_VERSION_ALLOWED < 30000) ||(__TV_OS_MAX_VERSION_ALLOWED && __TV_OS_MAX_VERSION_ALLOWED < 100000))
    #define AF_CAN_INCLUDE_SESSION_TASK_METRICS 0
#else
    #define AF_CAN_INCLUDE_SESSION_TASK_METRICS 1
#endif

/*
 这个宏不说了 很长 主要是系统判断 支不支持使用sessiontask api
 */

#endif /* AFCompatibilityMacros_h */
