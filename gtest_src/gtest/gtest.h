// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines the public API for Google Test.  It should be
// included by any test program that uses Google Test.
//
// IMPORTANT NOTE: Due to limitation of the C++ language, we have to
// leave some internal implementation details in this header file.
// They are clearly marked by comments like this:
//
//   // INTERNAL IMPLEMENTATION - DO NOT USE IN A USER PROGRAM.
//
// Such code is NOT meant to be used by a user directly, and is subject
// to CHANGE WITHOUT NOTICE.  Therefore DO NOT DEPEND ON IT in a user
// program!
//
// Acknowledgment: Google Test borrowed the idea of automatic test
// registration from Barthelemy Dagenais' (barthelemy@prologique.com)
// easyUnit framework.

#ifndef GTEST_INCLUDE_GTEST_GTEST_H_
#define GTEST_INCLUDE_GTEST_GTEST_H_

#include <limits>
#include <ostream>
#include <vector>

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan), eefacm@gmail.com (Sean Mcafee)
//
// The Google C++ Testing Framework (Google Test)
//
// This header file declares functions and macros used internally by
// Google Test.  They are subject to change without notice.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_INTERNAL_H_

// Copyright 2005, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Authors: wan@google.com (Zhanyong Wan)
//
// Low-level types and utilities for porting Google Test to various
// platforms.  All macros ending with _ and symbols defined in an
// internal namespace are subject to change without notice.  Code
// outside Google Test MUST NOT USE THEM DIRECTLY.  Macros that don't
// end with _ are part of Google Test's public API and can be used by
// code outside Google Test.
//
// This file is fundamental to Google Test.  All other Google Test source
// files are expected to #include this.  Therefore, it cannot #include
// any other Google Test header.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_H_

// Environment-describing macros
// -----------------------------
//
// Google Test can be used in many different environments.  Macros in
// this section tell Google Test what kind of environment it is being
// used in, such that Google Test can provide environment-specific
// features and implementations.
//
// Google Test tries to automatically detect the properties of its
// environment, so users usually don't need to worry about these
// macros.  However, the automatic detection is not perfect.
// Sometimes it's necessary for a user to define some of the following
// macros in the build script to override Google Test's decisions.
//
// If the user doesn't define a macro in the list, Google Test will
// provide a default definition.  After this header is #included, all
// macros in this list will be defined to either 1 or 0.
//
// Notes to maintainers:
//   - Each macro here is a user-tweakable knob; do not grow the list
//     lightly.
//   - Use #if to key off these macros.  Don't use #ifdef or "#if
//     defined(...)", which will not work as these macros are ALWAYS
//     defined.
//
//   GTEST_HAS_CLONE          - Define it to 1/0 to indicate that clone(2)
//                              is/isn't available.
//   GTEST_HAS_EXCEPTIONS     - Define it to 1/0 to indicate that exceptions
//                              are enabled.
//   GTEST_HAS_GLOBAL_STRING  - Define it to 1/0 to indicate that ::string
//                              is/isn't available (some systems define
//                              ::string, which is different to std::string).
//   GTEST_HAS_GLOBAL_WSTRING - Define it to 1/0 to indicate that ::string
//                              is/isn't available (some systems define
//                              ::wstring, which is different to std::wstring).
//   GTEST_HAS_POSIX_RE       - Define it to 1/0 to indicate that POSIX regular
//                              expressions are/aren't available.
//   GTEST_HAS_PTHREAD        - Define it to 1/0 to indicate that <pthread.h>
//                              is/isn't available.
//   GTEST_HAS_RTTI           - Define it to 1/0 to indicate that RTTI is/isn't
//                              enabled.
//   GTEST_HAS_STD_WSTRING    - Define it to 1/0 to indicate that
//                              std::wstring does/doesn't work (Google Test can
//                              be used where std::wstring is unavailable).
//   GTEST_HAS_TR1_TUPLE      - Define it to 1/0 to indicate tr1::tuple
//                              is/isn't available.
//   GTEST_HAS_SEH            - Define it to 1/0 to indicate whether the
//                              compiler supports Microsoft's "Structured
//                              Exception Handling".
//   GTEST_HAS_STREAM_REDIRECTION
//                            - Define it to 1/0 to indicate whether the
//                              platform supports I/O stream redirection using
//                              dup() and dup2().
//   GTEST_USE_OWN_TR1_TUPLE  - Define it to 1/0 to indicate whether Google
//                              Test's own tr1 tuple implementation should be
//                              used.  Unused when the user sets
//                              GTEST_HAS_TR1_TUPLE to 0.
//   GTEST_LANG_CXX11         - Define it to 1/0 to indicate that Google Test
//                              is building in C++11/C++98 mode.
//   GTEST_LINKED_AS_SHARED_LIBRARY
//                            - Define to 1 when compiling tests that use
//                              Google Test as a shared library (known as
//                              DLL on Windows).
//   GTEST_CREATE_SHARED_LIBRARY
//                            - Define to 1 when compiling Google Test itself
//                              as a shared library.

// Platform-indicating macros
// --------------------------
//
// Macros indicating the platform on which Google Test is being used
// (a macro is defined to 1 if compiled on the given platform;
// otherwise UNDEFINED -- it's never defined to 0.).  Google Test
// defines these macros automatically.  Code outside Google Test MUST
// NOT define them.
//
//   GTEST_OS_AIX      - IBM AIX
//   GTEST_OS_CYGWIN   - Cygwin
//   GTEST_OS_FREEBSD  - FreeBSD
//   GTEST_OS_HPUX     - HP-UX
//   GTEST_OS_LINUX    - Linux
//     GTEST_OS_LINUX_ANDROID - Google Android
//   GTEST_OS_MAC      - Mac OS X
//     GTEST_OS_IOS    - iOS
//   GTEST_OS_NACL     - Google Native Client (NaCl)
//   GTEST_OS_OPENBSD  - OpenBSD
//   GTEST_OS_QNX      - QNX
//   GTEST_OS_SOLARIS  - Sun Solaris
//   GTEST_OS_SYMBIAN  - Symbian
//   GTEST_OS_WINDOWS  - Windows (Desktop, MinGW, or Mobile)
//     GTEST_OS_WINDOWS_DESKTOP  - Windows Desktop
//     GTEST_OS_WINDOWS_MINGW    - MinGW
//     GTEST_OS_WINDOWS_MOBILE   - Windows Mobile
//     GTEST_OS_WINDOWS_PHONE    - Windows Phone
//     GTEST_OS_WINDOWS_RT       - Windows Store App/WinRT
//   GTEST_OS_ZOS      - z/OS
//
// Among the platforms, Cygwin, Linux, Max OS X, and Windows have the
// most stable support.  Since core members of the Google Test project
// don't have access to other platforms, support for them may be less
// stable.  If you notice any problems on your platform, please notify
// googletestframework@googlegroups.com (patches for fixing them are
// even more welcome!).
//
// It is possible that none of the GTEST_OS_* macros are defined.

// Feature-indicating macros
// -------------------------
//
// Macros indicating which Google Test features are available (a macro
// is defined to 1 if the corresponding feature is supported;
// otherwise UNDEFINED -- it's never defined to 0.).  Google Test
// defines these macros automatically.  Code outside Google Test MUST
// NOT define them.
//
// These macros are public so that portable tests can be written.
// Such tests typically surround code using a feature with an #if
// which controls that code.  For example:
//
// #if GTEST_HAS_DEATH_TEST
//   EXPECT_DEATH(DoSomethingDeadly());
// #endif
//
//   GTEST_HAS_COMBINE      - the Combine() function (for value-parameterized
//                            tests)
//   GTEST_HAS_DEATH_TEST   - death tests
//   GTEST_HAS_PARAM_TEST   - value-parameterized tests
//   GTEST_HAS_TYPED_TEST   - typed tests
//   GTEST_HAS_TYPED_TEST_P - type-parameterized tests
//   GTEST_IS_THREADSAFE    - Google Test is thread-safe.
//   GTEST_USES_POSIX_RE    - enhanced POSIX regex is used. Do not confuse with
//                            GTEST_HAS_POSIX_RE (see above) which users can
//                            define themselves.
//   GTEST_USES_SIMPLE_RE   - our own simple regex is used;
//                            the above two are mutually exclusive.
//   GTEST_CAN_COMPARE_NULL - accepts untyped NULL in EXPECT_EQ().

// Misc public macros
// ------------------
//
//   GTEST_FLAG(flag_name)  - references the variable corresponding to
//                            the given Google Test flag.

// Internal utilities
// ------------------
//
// The following macros and utilities are for Google Test's INTERNAL
// use only.  Code outside Google Test MUST NOT USE THEM DIRECTLY.
//
// Macros for basic C++ coding:
//   GTEST_AMBIGUOUS_ELSE_BLOCKER_ - for disabling a gcc warning.
//   GTEST_ATTRIBUTE_UNUSED_  - declares that a class' instances or a
//                              variable don't have to be used.
//   GTEST_DISALLOW_ASSIGN_   - disables operator=.
//   GTEST_DISALLOW_COPY_AND_ASSIGN_ - disables copy ctor and operator=.
//   GTEST_MUST_USE_RESULT_   - declares that a function's result must be used.
//   GTEST_INTENTIONAL_CONST_COND_PUSH_ - start code section where MSVC C4127 is
//                                        suppressed (constant conditional).
//   GTEST_INTENTIONAL_CONST_COND_POP_  - finish code section where MSVC C4127
//                                        is suppressed.
//
// C++11 feature wrappers:
//
//   testing::internal::move  - portability wrapper for std::move.
//
// Synchronization:
//   Mutex, MutexLock, ThreadLocal, GetThreadCount()
//                            - synchronization primitives.
//
// Template meta programming:
//   is_pointer     - as in TR1; needed on Symbian and IBM XL C/C++ only.
//   IteratorTraits - partial implementation of std::iterator_traits, which
//                    is not available in libCstd when compiled with Sun C++.
//
// Smart pointers:
//   scoped_ptr     - as in TR2.
//
// Regular expressions:
//   RE             - a simple regular expression class using the POSIX
//                    Extended Regular Expression syntax on UNIX-like
//                    platforms, or a reduced regular exception syntax on
//                    other platforms, including Windows.
//
// Logging:
//   GTEST_LOG_()   - logs messages at the specified severity level.
//   LogToStderr()  - directs all log messages to stderr.
//   FlushInfoLog() - flushes informational log messages.
//
// Stdout and stderr capturing:
//   CaptureStdout()     - starts capturing stdout.
//   GetCapturedStdout() - stops capturing stdout and returns the captured
//                         string.
//   CaptureStderr()     - starts capturing stderr.
//   GetCapturedStderr() - stops capturing stderr and returns the captured
//                         string.
//
// Integer types:
//   TypeWithSize   - maps an integer to a int type.
//   Int32, UInt32, Int64, UInt64, TimeInMillis
//                  - integers of known sizes.
//   BiggestInt     - the biggest signed integer type.
//
// Command-line utilities:
//   GTEST_DECLARE_*()  - declares a flag.
//   GTEST_DEFINE_*()   - defines a flag.
//   GetInjectableArgvs() - returns the command line as a vector of strings.
//
// Environment variable utilities:
//   GetEnv()             - gets the value of an environment variable.
//   BoolFromGTestEnv()   - parses a bool environment variable.
//   Int32FromGTestEnv()  - parses an Int32 environment variable.
//   StringFromGTestEnv() - parses a string environment variable.

#include <ctype.h>   // for isspace, etc
#include <stddef.h>  // for ptrdiff_t
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifndef _WIN32_WCE
# include <sys/types.h>
# include <sys/stat.h>
#endif  // !_WIN32_WCE

#if defined __APPLE__
# include <AvailabilityMacros.h>
# include <TargetConditionals.h>
#endif

#include <algorithm>  // NOLINT
#include <iostream>  // NOLINT
#include <sstream>  // NOLINT
#include <string>  // NOLINT
#include <utility>
#include <vector>  // NOLINT

// Copyright 2015, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The Google C++ Testing Framework (Google Test)
//
// This header file defines the GTEST_OS_* macro.
// It is separate from gtest-port.h so that custom/gtest-port.h can include it.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_ARCH_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_ARCH_H_

// Determines the platform on which Google Test is compiled.
#ifdef __CYGWIN__
# define GTEST_OS_CYGWIN 1
#elif defined __SYMBIAN32__
# define GTEST_OS_SYMBIAN 1
#elif defined _WIN32
# define GTEST_OS_WINDOWS 1
# ifdef _WIN32_WCE
#  define GTEST_OS_WINDOWS_MOBILE 1
# elif defined(__MINGW__) || defined(__MINGW32__)
#  define GTEST_OS_WINDOWS_MINGW 1
# elif defined(WINAPI_FAMILY)
#  include <winapifamily.h>
#  if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#   define GTEST_OS_WINDOWS_DESKTOP 1
#  elif WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_PHONE_APP)
#   define GTEST_OS_WINDOWS_PHONE 1
#  elif WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_APP)
#   define GTEST_OS_WINDOWS_RT 1
#  else
    // WINAPI_FAMILY defined but no known partition matched.
    // Default to desktop.
#   define GTEST_OS_WINDOWS_DESKTOP 1
#  endif
# else
#  define GTEST_OS_WINDOWS_DESKTOP 1
# endif  // _WIN32_WCE
#elif defined __APPLE__
# define GTEST_OS_MAC 1
# if TARGET_OS_IPHONE
#  define GTEST_OS_IOS 1
# endif
#elif defined __FreeBSD__
# define GTEST_OS_FREEBSD 1
#elif defined __linux__
# define GTEST_OS_LINUX 1
# if defined __ANDROID__
#  define GTEST_OS_LINUX_ANDROID 1
# endif
#elif defined __MVS__
# define GTEST_OS_ZOS 1
#elif defined(__sun) && defined(__SVR4)
# define GTEST_OS_SOLARIS 1
#elif defined(_AIX)
# define GTEST_OS_AIX 1
#elif defined(__hpux)
# define GTEST_OS_HPUX 1
#elif defined __native_client__
# define GTEST_OS_NACL 1
#elif defined __OpenBSD__
# define GTEST_OS_OPENBSD 1
#elif defined __QNX__
# define GTEST_OS_QNX 1
#endif  // __CYGWIN__

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_PORT_ARCH_H_
// Copyright 2015, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Injection point for custom user configurations.
// The following macros can be defined:
//
//   Flag related macros:
//     GTEST_FLAG(flag_name)
//     GTEST_USE_OWN_FLAGFILE_FLAG_  - Define to 0 when the system provides its
//                                     own flagfile flag parsing.
//     GTEST_DECLARE_bool_(name)
//     GTEST_DECLARE_int32_(name)
//     GTEST_DECLARE_string_(name)
//     GTEST_DEFINE_bool_(name, default_val, doc)
//     GTEST_DEFINE_int32_(name, default_val, doc)
//     GTEST_DEFINE_string_(name, default_val, doc)
//
//   Test filtering:
//     GTEST_TEST_FILTER_ENV_VAR_ - The name of an environment variable that
//                                  will be used if --GTEST_FLAG(test_filter)
//                                  is not provided.
//
//   Logging:
//     GTEST_LOG_(severity)
//     GTEST_CHECK_(condition)
//     Functions LogToStderr() and FlushInfoLog() have to be provided too.
//
//   Threading:
//     GTEST_HAS_NOTIFICATION_ - Enabled if Notification is already provided.
//     GTEST_HAS_MUTEX_AND_THREAD_LOCAL_ - Enabled if Mutex and ThreadLocal are
//                                         already provided.
//     Must also provide GTEST_DECLARE_STATIC_MUTEX_(mutex) and
//     GTEST_DEFINE_STATIC_MUTEX_(mutex)
//
//     GTEST_EXCLUSIVE_LOCK_REQUIRED_(locks)
//     GTEST_LOCK_EXCLUDED_(locks)
//
// ** Custom implementation starts here **

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_CUSTOM_GTEST_PORT_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_CUSTOM_GTEST_PORT_H_

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_CUSTOM_GTEST_PORT_H_

#if !defined(GTEST_DEV_EMAIL_)
# define GTEST_DEV_EMAIL_ "googletestframework@@googlegroups.com"
# define GTEST_FLAG_PREFIX_ "gtest_"
# define GTEST_FLAG_PREFIX_DASH_ "gtest-"
# define GTEST_FLAG_PREFIX_UPPER_ "GTEST_"
# define GTEST_NAME_ "Google Test"
# define GTEST_PROJECT_URL_ "https://github.com/google/googletest/"
#endif  // !defined(GTEST_DEV_EMAIL_)

#if !defined(GTEST_INIT_GOOGLE_TEST_NAME_)
# define GTEST_INIT_GOOGLE_TEST_NAME_ "testing::InitGoogleTest"
#endif  // !defined(GTEST_INIT_GOOGLE_TEST_NAME_)

// Determines the version of gcc that is used to compile this.
#ifdef __GNUC__
// 40302 means version 4.3.2.
# define GTEST_GCC_VER_ \
    (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__)
#endif  // __GNUC__

// Macros for disabling Microsoft Visual C++ warnings.
//
//   GTEST_DISABLE_MSC_WARNINGS_PUSH_(4800 4385)
//   /* code that triggers warnings C4800 and C4385 */
//   GTEST_DISABLE_MSC_WARNINGS_POP_()
#if _MSC_VER >= 1500
# define GTEST_DISABLE_MSC_WARNINGS_PUSH_(warnings) \
    __pragma(warning(push))                        \
    __pragma(warning(disable: warnings))
# define GTEST_DISABLE_MSC_WARNINGS_POP_()          \
    __pragma(warning(pop))
#else
// Older versions of MSVC don't have __pragma.
# define GTEST_DISABLE_MSC_WARNINGS_PUSH_(warnings)
# define GTEST_DISABLE_MSC_WARNINGS_POP_()
#endif

#ifndef GTEST_LANG_CXX11
// gcc and clang define __GXX_EXPERIMENTAL_CXX0X__ when
// -std={c,gnu}++{0x,11} is passed.  The C++11 standard specifies a
// value for __cplusplus, and recent versions of clang, gcc, and
// probably other compilers set that too in C++11 mode.
# if __GXX_EXPERIMENTAL_CXX0X__ || __cplusplus >= 201103L
// Compiling in at least C++11 mode.
#  define GTEST_LANG_CXX11 1
# else
#  define GTEST_LANG_CXX11 0
# endif
#endif

// Distinct from C++11 language support, some environments don't provide
// proper C++11 library support. Notably, it's possible to build in
// C++11 mode when targeting Mac OS X 10.6, which has an old libstdc++
// with no C++11 support.
//
// libstdc++ has sufficient C++11 support as of GCC 4.6.0, __GLIBCXX__
// 20110325, but maintenance releases in the 4.4 and 4.5 series followed
// this date, so check for those versions by their date stamps.
// https://gcc.gnu.org/onlinedocs/libstdc++/manual/abi.html#abi.versioning
#if GTEST_LANG_CXX11 && \
    (!defined(__GLIBCXX__) || ( \
        __GLIBCXX__ >= 20110325ul &&  /* GCC >= 4.6.0 */ \
        /* Blacklist of patch releases of older branches: */ \
        __GLIBCXX__ != 20110416ul &&  /* GCC 4.4.6 */ \
        __GLIBCXX__ != 20120313ul &&  /* GCC 4.4.7 */ \
        __GLIBCXX__ != 20110428ul &&  /* GCC 4.5.3 */ \
        __GLIBCXX__ != 20120702ul))   /* GCC 4.5.4 */
# define GTEST_STDLIB_CXX11 1
#endif

// Only use C++11 library features if the library provides them.
#if GTEST_STDLIB_CXX11
# define GTEST_HAS_STD_BEGIN_AND_END_ 1
# define GTEST_HAS_STD_FORWARD_LIST_ 1
# define GTEST_HAS_STD_FUNCTION_ 1
# define GTEST_HAS_STD_INITIALIZER_LIST_ 1
# define GTEST_HAS_STD_MOVE_ 1
# define GTEST_HAS_STD_SHARED_PTR_ 1
# define GTEST_HAS_STD_TYPE_TRAITS_ 1
# define GTEST_HAS_STD_UNIQUE_PTR_ 1
#endif

// C++11 specifies that <tuple> provides std::tuple.
// Some platforms still might not have it, however.
#if GTEST_LANG_CXX11
# define GTEST_HAS_STD_TUPLE_ 1
# if defined(__clang__)
// Inspired by http://clang.llvm.org/docs/LanguageExtensions.html#__has_include
#  if defined(__has_include) && !__has_include(<tuple>)
#   undef GTEST_HAS_STD_TUPLE_
#  endif
# elif defined(_MSC_VER)
// Inspired by boost/config/stdlib/dinkumware.hpp
#  if defined(_CPPLIB_VER) && _CPPLIB_VER < 520
#   undef GTEST_HAS_STD_TUPLE_
#  endif
# elif defined(__GLIBCXX__)
// Inspired by boost/config/stdlib/libstdcpp3.hpp,
// http://gcc.gnu.org/gcc-4.2/changes.html and
// http://gcc.gnu.org/onlinedocs/libstdc++/manual/bk01pt01ch01.html#manual.intro.status.standard.200x
#  if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 2)
#   undef GTEST_HAS_STD_TUPLE_
#  endif
# endif
#endif

// Brings in definitions for functions used in the testing::internal::posix
// namespace (read, write, close, chdir, isatty, stat). We do not currently
// use them on Windows Mobile.
#if GTEST_OS_WINDOWS
# if !GTEST_OS_WINDOWS_MOBILE
#  include <direct.h>
#  include <io.h>
# endif
// In order to avoid having to include <windows.h>, use forward declaration
// assuming CRITICAL_SECTION is a typedef of _RTL_CRITICAL_SECTION.
// This assumption is verified by
// WindowsTypesTest.CRITICAL_SECTIONIs_RTL_CRITICAL_SECTION.
struct _RTL_CRITICAL_SECTION;
#else
// This assumes that non-Windows OSes provide unistd.h. For OSes where this
// is not the case, we need to include headers that provide the functions
// mentioned above.
# include <unistd.h>
# include <strings.h>
#endif  // GTEST_OS_WINDOWS

#if GTEST_OS_LINUX_ANDROID
// Used to define __ANDROID_API__ matching the target NDK API level.
#  include <android/api-level.h>  // NOLINT
#endif

// Defines this to true iff Google Test can use POSIX regular expressions.
#ifndef GTEST_HAS_POSIX_RE
# if GTEST_OS_LINUX_ANDROID
// On Android, <regex.h> is only available starting with Gingerbread.
#  define GTEST_HAS_POSIX_RE (__ANDROID_API__ >= 9)
# else
#  define GTEST_HAS_POSIX_RE (!GTEST_OS_WINDOWS)
# endif
#endif

#if GTEST_USES_PCRE
// The appropriate headers have already been included.

#elif GTEST_HAS_POSIX_RE

// On some platforms, <regex.h> needs someone to define size_t, and
// won't compile otherwise.  We can #include it here as we already
// included <stdlib.h>, which is guaranteed to define size_t through
// <stddef.h>.
# include <regex.h>  // NOLINT

# define GTEST_USES_POSIX_RE 1

#elif GTEST_OS_WINDOWS

// <regex.h> is not available on Windows.  Use our own simple regex
// implementation instead.
# define GTEST_USES_SIMPLE_RE 1

#else

// <regex.h> may not be available on this platform.  Use our own
// simple regex implementation instead.
# define GTEST_USES_SIMPLE_RE 1

#endif  // GTEST_USES_PCRE

#ifndef GTEST_HAS_EXCEPTIONS
// The user didn't tell us whether exceptions are enabled, so we need
// to figure it out.
# if defined(_MSC_VER) || defined(__BORLANDC__)
// MSVC's and C++Builder's implementations of the STL use the _HAS_EXCEPTIONS
// macro to enable exceptions, so we'll do the same.
// Assumes that exceptions are enabled by default.
#  ifndef _HAS_EXCEPTIONS
#   define _HAS_EXCEPTIONS 1
#  endif  // _HAS_EXCEPTIONS
#  define GTEST_HAS_EXCEPTIONS _HAS_EXCEPTIONS
# elif defined(__clang__)
// clang defines __EXCEPTIONS iff exceptions are enabled before clang 220714,
// but iff cleanups are enabled after that. In Obj-C++ files, there can be
// cleanups for ObjC exceptions which also need cleanups, even if C++ exceptions
// are disabled. clang has __has_feature(cxx_exceptions) which checks for C++
// exceptions starting at clang r206352, but which checked for cleanups prior to
// that. To reliably check for C++ exception availability with clang, check for
// __EXCEPTIONS && __has_feature(cxx_exceptions).
#  define GTEST_HAS_EXCEPTIONS (__EXCEPTIONS && __has_feature(cxx_exceptions))
# elif defined(__GNUC__) && __EXCEPTIONS
// gcc defines __EXCEPTIONS to 1 iff exceptions are enabled.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__SUNPRO_CC)
// Sun Pro CC supports exceptions.  However, there is no compile-time way of
// detecting whether they are enabled or not.  Therefore, we assume that
// they are enabled unless the user tells us otherwise.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__IBMCPP__) && __EXCEPTIONS
// xlC defines __EXCEPTIONS to 1 iff exceptions are enabled.
#  define GTEST_HAS_EXCEPTIONS 1
# elif defined(__HP_aCC)
// Exception handling is in effect by default in HP aCC compiler. It has to
// be turned of by +noeh compiler option if desired.
#  define GTEST_HAS_EXCEPTIONS 1
# else
// For other compilers, we assume exceptions are disabled to be
// conservative.
#  define GTEST_HAS_EXCEPTIONS 0
# endif  // defined(_MSC_VER) || defined(__BORLANDC__)
#endif  // GTEST_HAS_EXCEPTIONS

#if !defined(GTEST_HAS_STD_STRING)
// Even though we don't use this macro any longer, we keep it in case
// some clients still depend on it.
# define GTEST_HAS_STD_STRING 1
#elif !GTEST_HAS_STD_STRING
// The user told us that ::std::string isn't available.
# error "Google Test cannot be used where ::std::string isn't available."
#endif  // !defined(GTEST_HAS_STD_STRING)

#ifndef GTEST_HAS_GLOBAL_STRING
// The user didn't tell us whether ::string is available, so we need
// to figure it out.

# define GTEST_HAS_GLOBAL_STRING 0

#endif  // GTEST_HAS_GLOBAL_STRING

#ifndef GTEST_HAS_STD_WSTRING
// The user didn't tell us whether ::std::wstring is available, so we need
// to figure it out.
// TODO(wan@google.com): uses autoconf to detect whether ::std::wstring
//   is available.

// Cygwin 1.7 and below doesn't support ::std::wstring.
// Solaris' libc++ doesn't support it either.  Android has
// no support for it at least as recent as Froyo (2.2).
# define GTEST_HAS_STD_WSTRING \
    (!(GTEST_OS_LINUX_ANDROID || GTEST_OS_CYGWIN || GTEST_OS_SOLARIS))

#endif  // GTEST_HAS_STD_WSTRING

#ifndef GTEST_HAS_GLOBAL_WSTRING
// The user didn't tell us whether ::wstring is available, so we need
// to figure it out.
# define GTEST_HAS_GLOBAL_WSTRING \
    (GTEST_HAS_STD_WSTRING && GTEST_HAS_GLOBAL_STRING)
#endif  // GTEST_HAS_GLOBAL_WSTRING

// Determines whether RTTI is available.
#ifndef GTEST_HAS_RTTI
// The user didn't tell us whether RTTI is enabled, so we need to
// figure it out.

# ifdef _MSC_VER

#  ifdef _CPPRTTI  // MSVC defines this macro iff RTTI is enabled.
#   define GTEST_HAS_RTTI 1
#  else
#   define GTEST_HAS_RTTI 0
#  endif

// Starting with version 4.3.2, gcc defines __GXX_RTTI iff RTTI is enabled.
# elif defined(__GNUC__) && (GTEST_GCC_VER_ >= 40302)

#  ifdef __GXX_RTTI
// When building against STLport with the Android NDK and with
// -frtti -fno-exceptions, the build fails at link time with undefined
// references to __cxa_bad_typeid. Note sure if STL or toolchain bug,
// so disable RTTI when detected.
#   if GTEST_OS_LINUX_ANDROID && defined(_STLPORT_MAJOR) && \
       !defined(__EXCEPTIONS)
#    define GTEST_HAS_RTTI 0
#   else
#    define GTEST_HAS_RTTI 1
#   endif  // GTEST_OS_LINUX_ANDROID && __STLPORT_MAJOR && !__EXCEPTIONS
#  else
#   define GTEST_HAS_RTTI 0
#  endif  // __GXX_RTTI

// Clang defines __GXX_RTTI starting with version 3.0, but its manual recommends
// using has_feature instead. has_feature(cxx_rtti) is supported since 2.7, the
// first version with C++ support.
# elif defined(__clang__)

#  define GTEST_HAS_RTTI __has_feature(cxx_rtti)

// Starting with version 9.0 IBM Visual Age defines __RTTI_ALL__ to 1 if
// both the typeid and dynamic_cast features are present.
# elif defined(__IBMCPP__) && (__IBMCPP__ >= 900)

#  ifdef __RTTI_ALL__
#   define GTEST_HAS_RTTI 1
#  else
#   define GTEST_HAS_RTTI 0
#  endif

# else

// For all other compilers, we assume RTTI is enabled.
#  define GTEST_HAS_RTTI 1

# endif  // _MSC_VER

#endif  // GTEST_HAS_RTTI

// It's this header's responsibility to #include <typeinfo> when RTTI
// is enabled.
#if GTEST_HAS_RTTI
# include <typeinfo>
#endif

// Determines whether Google Test can use the pthreads library.
#ifndef GTEST_HAS_PTHREAD
// The user didn't tell us explicitly, so we make reasonable assumptions about
// which platforms have pthreads support.
//
// To disable threading support in Google Test, add -DGTEST_HAS_PTHREAD=0
// to your compiler flags.
# define GTEST_HAS_PTHREAD (GTEST_OS_LINUX || GTEST_OS_MAC || GTEST_OS_HPUX \
    || GTEST_OS_QNX || GTEST_OS_FREEBSD || GTEST_OS_NACL)
#endif  // GTEST_HAS_PTHREAD

#if GTEST_HAS_PTHREAD
// gtest-port.h guarantees to #include <pthread.h> when GTEST_HAS_PTHREAD is
// true.
# include <pthread.h>  // NOLINT

// For timespec and nanosleep, used below.
# include <time.h>  // NOLINT
#endif

// Determines if hash_map/hash_set are available.
// Only used for testing against those containers.
#if !defined(GTEST_HAS_HASH_MAP_)
# if _MSC_VER
#  define GTEST_HAS_HASH_MAP_ 1  // Indicates that hash_map is available.
#  define GTEST_HAS_HASH_SET_ 1  // Indicates that hash_set is available.
# endif  // _MSC_VER
#endif  // !defined(GTEST_HAS_HASH_MAP_)

// Determines whether Google Test can use tr1/tuple.  You can define
// this macro to 0 to prevent Google Test from using tuple (any
// feature depending on tuple with be disabled in this mode).
#ifndef GTEST_HAS_TR1_TUPLE
# if GTEST_OS_LINUX_ANDROID && defined(_STLPORT_MAJOR)
// STLport, provided with the Android NDK, has neither <tr1/tuple> or <tuple>.
#  define GTEST_HAS_TR1_TUPLE 0
# else
// The user didn't tell us not to do it, so we assume it's OK.
#  define GTEST_HAS_TR1_TUPLE 1
# endif
#endif  // GTEST_HAS_TR1_TUPLE

// Determines whether Google Test's own tr1 tuple implementation
// should be used.
#ifndef GTEST_USE_OWN_TR1_TUPLE
// The user didn't tell us, so we need to figure it out.

// We use our own TR1 tuple if we aren't sure the user has an
// implementation of it already.  At this time, libstdc++ 4.0.0+ and
// MSVC 2010 are the only mainstream standard libraries that come
// with a TR1 tuple implementation.  NVIDIA's CUDA NVCC compiler
// pretends to be GCC by defining __GNUC__ and friends, but cannot
// compile GCC's tuple implementation.  MSVC 2008 (9.0) provides TR1
// tuple in a 323 MB Feature Pack download, which we cannot assume the
// user has.  QNX's QCC compiler is a modified GCC but it doesn't
// support TR1 tuple.  libc++ only provides std::tuple, in C++11 mode,
// and it can be used with some compilers that define __GNUC__.
# if (defined(__GNUC__) && !defined(__CUDACC__) && (GTEST_GCC_VER_ >= 40000) \
      && !GTEST_OS_QNX && !defined(_LIBCPP_VERSION)) || _MSC_VER >= 1600
#  define GTEST_ENV_HAS_TR1_TUPLE_ 1
# endif

// C++11 specifies that <tuple> provides std::tuple. Use that if gtest is used
// in C++11 mode and libstdc++ isn't very old (binaries targeting OS X 10.6
// can build with clang but need to use gcc4.2's libstdc++).
# if GTEST_LANG_CXX11 && (!defined(__GLIBCXX__) || __GLIBCXX__ > 20110325)
#  define GTEST_ENV_HAS_STD_TUPLE_ 1
# endif

# if GTEST_ENV_HAS_TR1_TUPLE_ || GTEST_ENV_HAS_STD_TUPLE_
#  define GTEST_USE_OWN_TR1_TUPLE 0
# else
#  define GTEST_USE_OWN_TR1_TUPLE 1
# endif

#endif  // GTEST_USE_OWN_TR1_TUPLE

// To avoid conditional compilation everywhere, we make it
// gtest-port.h's responsibility to #include the header implementing
// tuple.
#if GTEST_HAS_STD_TUPLE_
# include <tuple>  // IWYU pragma: export
# define GTEST_TUPLE_NAMESPACE_ ::std
#endif  // GTEST_HAS_STD_TUPLE_

// We include tr1::tuple even if std::tuple is available to define printers for
// them.
#if GTEST_HAS_TR1_TUPLE
# ifndef GTEST_TUPLE_NAMESPACE_
#  define GTEST_TUPLE_NAMESPACE_ ::std::tr1
# endif  // GTEST_TUPLE_NAMESPACE_

# if GTEST_USE_OWN_TR1_TUPLE
// This file was GENERATED by command:
//     pump.py gtest-tuple.h.pump
// DO NOT EDIT BY HAND!!!

// Copyright 2009 Google Inc.
// All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: wan@google.com (Zhanyong Wan)

// Implements a subset of TR1 tuple needed by Google Test and Google Mock.

#ifndef GTEST_INCLUDE_GTEST_INTERNAL_GTEST_TUPLE_H_
#define GTEST_INCLUDE_GTEST_INTERNAL_GTEST_TUPLE_H_

#include <utility>  // For ::std::pair.

// The compiler used in Symbian has a bug that prevents us from declaring the
// tuple template as a friend (it complains that tuple is redefined).  This
// hack bypasses the bug by declaring the members that should otherwise be
// private as public.
// Sun Studio versions < 12 also have the above bug.
#if defined(__SYMBIAN32__) || (defined(__SUNPRO_CC) && __SUNPRO_CC < 0x590)
# define GTEST_DECLARE_TUPLE_AS_FRIEND_ public:
#else
# define GTEST_DECLARE_TUPLE_AS_FRIEND_ \
    template <GTEST_10_TYPENAMES_(U)> friend class tuple; \
   private:
#endif

// Visual Studio 2010, 2012, and 2013 define symbols in std::tr1 that conflict
// with our own definitions. Therefore using our own tuple does not work on
// those compilers.
#if defined(_MSC_VER) && _MSC_VER >= 1600  /* 1600 is Visual Studio 2010 */
# error "gtest's tuple doesn't compile on Visual Studio 2010 or later. \
GTEST_USE_OWN_TR1_TUPLE must be set to 0 on those compilers."
#endif

// GTEST_n_TUPLE_(T) is the type of an n-tuple.
#define GTEST_0_TUPLE_(T) tuple<>
#define GTEST_1_TUPLE_(T) tuple<T##0, void, void, void, void, void, void, \
    void, void, void>
#define GTEST_2_TUPLE_(T) tuple<T##0, T##1, void, void, void, void, void, \
    void, void, void>
#define GTEST_3_TUPLE_(T) tuple<T##0, T##1, T##2, void, void, void, void, \
    void, void, void>
#define GTEST_4_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, void, void, void, \
    void, void, void>
#define GTEST_5_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, void, void, \
    void, void, void>
#define GTEST_6_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, void, \
    void, void, void>
#define GTEST_7_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    void, void, void>
#define GTEST_8_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    T##7, void, void>
#define GTEST_9_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    T##7, T##8, void>
#define GTEST_10_TUPLE_(T) tuple<T##0, T##1, T##2, T##3, T##4, T##5, T##6, \
    T##7, T##8, T##9>

// GTEST_n_TYPENAMES_(T) declares a list of n typenames.
#define GTEST_0_TYPENAMES_(T)
#define GTEST_1_TYPENAMES_(T) typename T##0
#define GTEST_2_TYPENAMES_(T) typename T##0, typename T##1
#define GTEST_3_TYPENAMES_(T) typename T##0, typename T##1, typename T##2
#define GTEST_4_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3
#define GTEST_5_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4
#define GTEST_6_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5
#define GTEST_7_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6
#define GTEST_8_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6, typename T##7
#define GTEST_9_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6, \
    typename T##7, typename T##8
#define GTEST_10_TYPENAMES_(T) typename T##0, typename T##1, typename T##2, \
    typename T##3, typename T##4, typename T##5, typename T##6, \
    typename T##7, typename T##8, typename T##9

// In theory, defining stuff in the ::std namespace is undefined
// behavior.  We can do this as we are playing the role of a standard
// library vendor.
namespace std {
namespace tr1 {

template <typename T0 = void, typename T1 = void, typename T2 = void,
    typename T3 = void, typename T4 = void, typename T5 = void,
    typename T6 = void, typename T7 = void, typename T8 = void,
    typename T9 = void>
class tuple;

// Anything in namespace gtest_internal is Google Test's INTERNAL
// IMPLEMENTATION DETAIL and MUST NOT BE USED DIRECTLY in user code.
namespace gtest_internal {

// ByRef<T>::type is T if T is a reference; otherwise it's const T&.
template <typename T>
struct ByRef { typedef const T& type; };  // NOLINT
template <typename T>
struct ByRef<T&> { typedef T& type; };  // NOLINT

// A handy wrapper for ByRef.
#define GTEST_BY_REF_(T) typename ::std::tr1::gtest_internal::ByRef<T>::type

// AddRef<T>::type is T if T is a reference; otherwise it's T&.  This
// is the same as tr1::add_reference<T>::type.
template <typename T>
struct AddRef { typedef T& type; };  // NOLINT
template <typename T>
struct AddRef<T&> { typedef T& type; };  // NOLINT

// A handy wrapper for AddRef.
#define GTEST_ADD_REF_(T) typename ::std::tr1::gtest_internal::AddRef<T>::type

// A helper for implementing get<k>().
template <int k> class Get;

// A helper for implementing tuple_element<k, T>.  kIndexValid is true
// iff k < the number of fields in tuple type T.
template <bool kIndexValid, int kIndex, class Tuple>
struct TupleElement;

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 0, GTEST_10_TUPLE_(T) > {
  typedef T0 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 1, GTEST_10_TUPLE_(T) > {
  typedef T1 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 2, GTEST_10_TUPLE_(T) > {
  typedef T2 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 3, GTEST_10_TUPLE_(T) > {
  typedef T3 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 4, GTEST_10_TUPLE_(T) > {
  typedef T4 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 5, GTEST_10_TUPLE_(T) > {
  typedef T5 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 6, GTEST_10_TUPLE_(T) > {
  typedef T6 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 7, GTEST_10_TUPLE_(T) > {
  typedef T7 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 8, GTEST_10_TUPLE_(T) > {
  typedef T8 type;
};

template <GTEST_10_TYPENAMES_(T)>
struct TupleElement<true, 9, GTEST_10_TUPLE_(T) > {
  typedef T9 type;
};

}  // namespace gtest_internal

template <>
class tuple<> {
 public:
  tuple() {}
  tuple(const tuple& /* t */)  {}
  tuple& operator=(const tuple& /* t */) { return *this; }
};

template <GTEST_1_TYPENAMES_(T)>
class GTEST_1_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0) : f0_(f0) {}

  tuple(const tuple& t) : f0_(t.f0_) {}

  template <GTEST_1_TYPENAMES_(U)>
  tuple(const GTEST_1_TUPLE_(U)& t) : f0_(t.f0_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_1_TYPENAMES_(U)>
  tuple& operator=(const GTEST_1_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_1_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_1_TUPLE_(U)& t) {
    f0_ = t.f0_;
    return *this;
  }

  T0 f0_;
};

template <GTEST_2_TYPENAMES_(T)>
class GTEST_2_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1) : f0_(f0),
      f1_(f1) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_) {}

  template <GTEST_2_TYPENAMES_(U)>
  tuple(const GTEST_2_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_) {}
  template <typename U0, typename U1>
  tuple(const ::std::pair<U0, U1>& p) : f0_(p.first), f1_(p.second) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_2_TYPENAMES_(U)>
  tuple& operator=(const GTEST_2_TUPLE_(U)& t) {
    return CopyFrom(t);
  }
  template <typename U0, typename U1>
  tuple& operator=(const ::std::pair<U0, U1>& p) {
    f0_ = p.first;
    f1_ = p.second;
    return *this;
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_2_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_2_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
};

template <GTEST_3_TYPENAMES_(T)>
class GTEST_3_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2) : f0_(f0), f1_(f1), f2_(f2) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_) {}

  template <GTEST_3_TYPENAMES_(U)>
  tuple(const GTEST_3_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_3_TYPENAMES_(U)>
  tuple& operator=(const GTEST_3_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_3_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_3_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
};

template <GTEST_4_TYPENAMES_(T)>
class GTEST_4_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3) : f0_(f0), f1_(f1), f2_(f2),
      f3_(f3) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_) {}

  template <GTEST_4_TYPENAMES_(U)>
  tuple(const GTEST_4_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_4_TYPENAMES_(U)>
  tuple& operator=(const GTEST_4_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_4_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_4_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
};

template <GTEST_5_TYPENAMES_(T)>
class GTEST_5_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3,
      GTEST_BY_REF_(T4) f4) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_) {}

  template <GTEST_5_TYPENAMES_(U)>
  tuple(const GTEST_5_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_5_TYPENAMES_(U)>
  tuple& operator=(const GTEST_5_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_5_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_5_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
};

template <GTEST_6_TYPENAMES_(T)>
class GTEST_6_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4),
      f5_(f5) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_) {}

  template <GTEST_6_TYPENAMES_(U)>
  tuple(const GTEST_6_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_6_TYPENAMES_(U)>
  tuple& operator=(const GTEST_6_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_6_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_6_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
};

template <GTEST_7_TYPENAMES_(T)>
class GTEST_7_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6) : f0_(f0), f1_(f1), f2_(f2),
      f3_(f3), f4_(f4), f5_(f5), f6_(f6) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_) {}

  template <GTEST_7_TYPENAMES_(U)>
  tuple(const GTEST_7_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_7_TYPENAMES_(U)>
  tuple& operator=(const GTEST_7_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_7_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_7_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
};

template <GTEST_8_TYPENAMES_(T)>
class GTEST_8_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_(), f7_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6,
      GTEST_BY_REF_(T7) f7) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4),
      f5_(f5), f6_(f6), f7_(f7) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_) {}

  template <GTEST_8_TYPENAMES_(U)>
  tuple(const GTEST_8_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_8_TYPENAMES_(U)>
  tuple& operator=(const GTEST_8_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_8_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_8_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    f7_ = t.f7_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
  T7 f7_;
};

template <GTEST_9_TYPENAMES_(T)>
class GTEST_9_TUPLE_(T) {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_(), f7_(), f8_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6, GTEST_BY_REF_(T7) f7,
      GTEST_BY_REF_(T8) f8) : f0_(f0), f1_(f1), f2_(f2), f3_(f3), f4_(f4),
      f5_(f5), f6_(f6), f7_(f7), f8_(f8) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_) {}

  template <GTEST_9_TYPENAMES_(U)>
  tuple(const GTEST_9_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_9_TYPENAMES_(U)>
  tuple& operator=(const GTEST_9_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_9_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_9_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    f7_ = t.f7_;
    f8_ = t.f8_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
  T7 f7_;
  T8 f8_;
};

template <GTEST_10_TYPENAMES_(T)>
class tuple {
 public:
  template <int k> friend class gtest_internal::Get;

  tuple() : f0_(), f1_(), f2_(), f3_(), f4_(), f5_(), f6_(), f7_(), f8_(),
      f9_() {}

  explicit tuple(GTEST_BY_REF_(T0) f0, GTEST_BY_REF_(T1) f1,
      GTEST_BY_REF_(T2) f2, GTEST_BY_REF_(T3) f3, GTEST_BY_REF_(T4) f4,
      GTEST_BY_REF_(T5) f5, GTEST_BY_REF_(T6) f6, GTEST_BY_REF_(T7) f7,
      GTEST_BY_REF_(T8) f8, GTEST_BY_REF_(T9) f9) : f0_(f0), f1_(f1), f2_(f2),
      f3_(f3), f4_(f4), f5_(f5), f6_(f6), f7_(f7), f8_(f8), f9_(f9) {}

  tuple(const tuple& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_), f3_(t.f3_),
      f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_), f9_(t.f9_) {}

  template <GTEST_10_TYPENAMES_(U)>
  tuple(const GTEST_10_TUPLE_(U)& t) : f0_(t.f0_), f1_(t.f1_), f2_(t.f2_),
      f3_(t.f3_), f4_(t.f4_), f5_(t.f5_), f6_(t.f6_), f7_(t.f7_), f8_(t.f8_),
      f9_(t.f9_) {}

  tuple& operator=(const tuple& t) { return CopyFrom(t); }

  template <GTEST_10_TYPENAMES_(U)>
  tuple& operator=(const GTEST_10_TUPLE_(U)& t) {
    return CopyFrom(t);
  }

  GTEST_DECLARE_TUPLE_AS_FRIEND_

  template <GTEST_10_TYPENAMES_(U)>
  tuple& CopyFrom(const GTEST_10_TUPLE_(U)& t) {
    f0_ = t.f0_;
    f1_ = t.f1_;
    f2_ = t.f2_;
    f3_ = t.f3_;
    f4_ = t.f4_;
    f5_ = t.f5_;
    f6_ = t.f6_;
    f7_ = t.f7_;
    f8_ = t.f8_;
    f9_ = t.f9_;
    return *this;
  }

  T0 f0_;
  T1 f1_;
  T2 f2_;
  T3 f3_;
  T4 f4_;
  T5 f5_;
  T6 f6_;
  T7 f7_;
  T8 f8_;
  T9 f9_;
};

// 6.1.3.2 Tuple creation functions.

// Known limitations: we don't support passing an
// std::tr1::reference_wrapper<T> to make_tuple().  And we don't
// implement tie().

inline tuple<> make_tuple() { return tuple<>(); }

template <GTEST_1_TYPENAMES_(T)>
inline GTEST_1_TUPLE_(T) make_tuple(const T0& f0) {
  return GTEST_1_TUPLE_(T)(f0);
}

template <GTEST_2_TYPENAMES_(T)>
inline GTEST_2_TUPLE_(T) make_tuple(const T0& f0, const T1& f1) {
  return GTEST_2_TUPLE_(T)(f0, f1);
}

template <GTEST_3_TYPENAMES_(T)>
inline GTEST_3_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2) {
  return GTEST_3_TUPLE_(T)(f0, f1, f2);
}

template <GTEST_4_TYPENAMES_(T)>
inline GTEST_4_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3) {
  return GTEST_4_TUPLE_(T)(f0, f1, f2, f3);
}

template <GTEST_5_TYPENAMES_(T)>
inline GTEST_5_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4) {
  return GTEST_5_TUPLE_(T)(f0, f1, f2, f3, f4);
}

template <GTEST_6_TYPENAMES_(T)>
inline GTEST_6_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5) {
  return GTEST_6_TUPLE_(T)(f0, f1, f2, f3, f4, f5);
}

template <GTEST_7_TYPENAMES_(T)>
inline GTEST_7_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6) {
  return GTEST_7_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6);
}

template <GTEST_8_TYPENAMES_(T)>
inline GTEST_8_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6, const T7& f7) {
  return GTEST_8_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6, f7);
}

template <GTEST_9_TYPENAMES_(T)>
inline GTEST_9_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6, const T7& f7,
    const T8& f8) {
  return GTEST_9_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6, f7, f8);
}

template <GTEST_10_TYPENAMES_(T)>
inline GTEST_10_TUPLE_(T) make_tuple(const T0& f0, const T1& f1, const T2& f2,
    const T3& f3, const T4& f4, const T5& f5, const T6& f6, const T7& f7,
    const T8& f8, const T9& f9) {
  return GTEST_10_TUPLE_(T)(f0, f1, f2, f3, f4, f5, f6, f7, f8, f9);
}

// 6.1.3.3 Tuple helper classes.

template <typename Tuple> struct tuple_size;

template <GTEST_0_TYPENAMES_(T)>
struct tuple_size<GTEST_0_TUPLE_(T) > {
  static const int value = 0;
};

template <GTEST_1_TYPENAMES_(T)>
struct tuple_size<GTEST_1_TUPLE_(T) > {
  static const int value = 1;
};

template <GTEST_2_TYPENAMES_(T)>
struct tuple_size<GTEST_2_TUPLE_(T) > {
  static const int value = 2;
};

template <GTEST_3_TYPENAMES_(T)>
struct tuple_size<GTEST_3_TUPLE_(T) > {
  static const int value = 3;
};

template <GTEST_4_TYPENAMES_(T)>
struct tuple_size<GTEST_4_TUPLE_(T) > {
  static const int value = 4;
};

template <GTEST_5_TYPENAMES_(T)>
struct tuple_size<GTEST_5_TUPLE_(T) > {
  static const int value = 5;
};

template <GTEST_6_TYPENAMES_(T)>
struct tuple_size<GTEST_6_TUPLE_(T) > {
  static const int value = 6;
};

template <GTEST_7_TYPENAMES_(T)>
struct tuple_size<GTEST_7_TUPLE_(T) > {
  static const int value = 7;
};

template <GTEST_8_TYPENAMES_(T)>
struct tuple_size<GTEST_8_TUPLE_(T) > {
  static const int value = 8;
};

template <GTEST_9_TYPENAMES_(T)>
struct tuple_size<GTEST_9_TUPLE_(T) > {
  static const int value = 9;
};

template <GTEST_10_TYPENAMES_(T)>
struct tuple_size<GTEST_10_TUPLE_(T) > {
  static const int value = 10;
};

template <int k, class Tuple>
struct tuple_element {
  typedef typename gtest_internal::TupleElement<
      k < (tuple_size<Tuple>::value), k, Tuple>::type type;
};

#define GTEST_TUPLE_ELEMENT_(k, Tuple) typename tuple_element<k, Tuple >::type

// 6.1.3.4 Element access.

namespace gtest_internal {

template <>
class Get<0> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(0, Tuple))
  Field(Tuple& t) { return t.f0_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(0, Tuple))
  ConstField(const Tuple& t) { return t.f0_; }
};

template <>
class Get<1> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(1, Tuple))
  Field(Tuple& t) { return t.f1_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(1, Tuple))
  ConstField(const Tuple& t) { return t.f1_; }
};

template <>
class Get<2> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(2, Tuple))
  Field(Tuple& t) { return t.f2_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(2, Tuple))
  ConstField(const Tuple& t) { return t.f2_; }
};

template <>
class Get<3> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(3, Tuple))
  Field(Tuple& t) { return t.f3_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(3, Tuple))
  ConstField(const Tuple& t) { return t.f3_; }
};

template <>
class Get<4> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(4, Tuple))
  Field(Tuple& t) { return t.f4_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(4, Tuple))
  ConstField(const Tuple& t) { return t.f4_; }
};

template <>
class Get<5> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(5, Tuple))
  Field(Tuple& t) { return t.f5_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(5, Tuple))
  ConstField(const Tuple& t) { return t.f5_; }
};

template <>
class Get<6> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(6, Tuple))
  Field(Tuple& t) { return t.f6_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(6, Tuple))
  ConstField(const Tuple& t) { return t.f6_; }
};

template <>
class Get<7> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(7, Tuple))
  Field(Tuple& t) { return t.f7_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(7, Tuple))
  ConstField(const Tuple& t) { return t.f7_; }
};

template <>
class Get<8> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(8, Tuple))
  Field(Tuple& t) { return t.f8_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(8, Tuple))
  ConstField(const Tuple& t) { return t.f8_; }
};

template <>
class Get<9> {
 public:
  template <class Tuple>
  static GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(9, Tuple))
  Field(Tuple& t) { return t.f9_; }  // NOLINT

  template <class Tuple>
  static GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(9, Tuple))
  ConstField(const Tuple& t) { return t.f9_; }
};

}  // namespace gtest_internal

template <int k, GTEST_10_TYPENAMES_(T)>
GTEST_ADD_REF_(GTEST_TUPLE_ELEMENT_(k, GTEST_10_TUPLE_(T)))
get(GTEST_10_TUPLE_(T)& t) {
  return gtest_internal::Get<k>::Field(t);
}

template <int k, GTEST_10_TYPENAMES_(T)>
GTEST_BY_REF_(GTEST_TUPLE_ELEMENT_(k,  GTEST_10_TUPLE_(T)))
get(const GTEST_10_TUPLE_(T)& t) {
  return gtest_internal::Get<k>::ConstField(t);
}

// 6.1.3.5 Relational operators

// We only implement == and !=, as we don't have a need for the rest yet.

namespace gtest_internal {

// SameSizeTuplePrefixComparator<k, k>::Eq(t1, t2) returns true if the
// first k fields of t1 equals the first k fields of t2.
// SameSizeTuplePrefixComparator(k1, k2) would be a compiler error if
// k1 != k2.
template <int kSize1, int kSize2>
struct SameSizeTuplePrefixComparator;

template <>
struct SameSizeTuplePrefixComparator<0, 0> {
  template <class Tuple1, class Tuple2>
  static bool Eq(const Tuple1& /* t1 */, const Tuple2& /* t2 */) {
    return true;
  }
};

template <int k>
struct SameSizeTuplePrefixComparator<k, k> {
  template <class Tuple1, class Tuple2>
  static bool Eq(const Tuple1& t1, const Tuple2& t2) {
    return SameSizeTuplePrefixComparator<k - 1, k - 1>::Eq(t1, t2) &&
        ::std::tr1::get<k - 1>(t1) == ::std::tr1::get<k - 1>(t2);
  }
};

}  // namespace gtest_internal

template <GTEST_10_TYPENAMES_(T), GTEST_10_TYPENAMES_(U)>
inline bool operator==(const GTEST_10_TUPLE_(T)& t,
                       const GTEST_10_TUPLE_(U)& u) {
  return gtest_internal::SameSizeTuplePrefixComparator<
      tuple_size<GTEST_10_TUPLE_(T) >::value,
      tuple_size<GTEST_10_TUPLE_(U) >::value>::Eq(t, u);
}

template <GTEST_10_TYPENAMES_(T), GTEST_10_TYPENAMES_(U)>
inline bool operator!=(const GTEST_10_TUPLE_(T)& t,
                       const GTEST_10_TUPLE_(U)& u) { return !(t == u); }

// 6.1.4 Pairs.
// Unimplemented.

}  // namespace tr1
}  // namespace std

#undef GTEST_0_TUPLE_
#undef GTEST_1_TUPLE_
#undef GTEST_2_TUPLE_
#undef GTEST_3_TUPLE_
#undef GTEST_4_TUPLE_
#undef GTEST_5_TUPLE_
#undef GTEST_6_TUPLE_
#undef GTEST_7_TUPLE_
#undef GTEST_8_TUPLE_
#undef GTEST_9_TUPLE_
#undef GTEST_10_TUPLE_

#undef GTEST_0_TYPENAMES_
#undef GTEST_1_TYPENAMES_
#undef GTEST_2_TYPENAMES_
#undef GTEST_3_TYPENAMES_
#undef GTEST_4_TYPENAMES_
#undef GTEST_5_TYPENAMES_
#undef GTEST_6_TYPENAMES_
#undef GTEST_7_TYPENAMES_
#undef GTEST_8_TYPENAMES_
#undef GTEST_9_TYPENAMES_
#undef GTEST_10_TYPENAMES_

#undef GTEST_DECLARE_TUPLE_AS_FRIEND_
#undef GTEST_BY_REF_
#undef GTEST_ADD_REF_
#undef GTEST_TUPLE_ELEMENT_

#endif  // GTEST_INCLUDE_GTEST_INTERNAL_GTEST_TUPLE_H_
# elif GTEST_ENV_HAS_STD_TUPLE_
#  include <tuple>
// C++11 puts its tuple into the ::std namespace rather than
// ::std::tr1.  gtest expects tuple to live in ::std::tr1, so put it there.
// This causes undefined behavior, but supported compilers react in
// the way we intend.
namespace std {
namespace tr1 {
using ::std::get;
using ::std::make_tuple;
using ::std::tuple;
using ::std::tuple_element;
using ::std::tuple_size;
}
}

# elif GTEST_OS_SYMBIAN

// On Symbian, BOOST_HAS_TR1_TUPLE causes Boost's TR1 tuple library to
// use STLport's tuple implementation, which unfortunately doesn't
// work as the copy of STLport distributed with Symbian is incomplete.
// By making sure BOOST_HAS_TR1_TUPLE is undefined, we force Boost to
// use its own tuple implementation.
#  ifdef BOOST_HAS_TR1_TUPLE
#   undef BOOST_HAS_TR1_TUPLE
#  endif  // BOOST_HAS_TR1_TUPLE

// This prevents <boost/tr1/detail/config.hpp>, which defines
// BOOST_HAS_TR1_TUPLE, from being #included by Boost's <tuple>.
#  define BOOST_TR1_DETAIL_CONFIG_HPP_INCLUDED
#  include <tuple>  // IWYU pragma: export  // NOLINT

# elif defined(__GNUC__) && (GTEST_GCC_VER_ >= 40000)
// GCC 4.0+ implements tr1/tuple in the <tr1/tuple> header.  This does
// not conform to the TR1 spec, which requires the header to be <tuple>.

#  if !GTEST_HAS_RTTI && GTEST_GCC_VER_ < 40302
// Until version 4.3.2, gcc has a bug that causes <tr1/functional>,
// which is #included by <tr1/tuple>, to not compile when RTTI is
// disabled.  _TR1_FUNCTIONAL is the header guard for
// <tr1/functional>.  Hence the following #define is a hack to prevent
// <tr1/functional> from being included.
#   define _TR1_FUNCTIONAL 1
#   include <tr1/tuple>
#   undef _TR1_FUNCTIONAL  // Allows the user to #include
                        // <tr1/functional> if he chooses to.
#  else
#   include <tr1/tuple>  // NOLINT
#  endif  // !GTEST_HAS_RTTI && GTEST_GCC_VER_ < 40302

# else
// If the compiler is not GCC 4.0+, we assume the user is using a
// spec-conforming TR1 implementation.
#  include <tuple>  // IWYU pragma: export  // NOLINT
# endif  // GTEST_USE_OWN_TR1_TUPLE

#endif  // GTEST_HAS_TR1_TUPLE

// Determines whether clone(2) is supported.
// Usually it will only be available on Linux, excluding
// Linux on the Itanium architecture.
// Also see http://linux.die.net/man/2/clone.
#ifndef GTEST_HAS_CLONE
// The user didn't tell us, so we need to figure it out.

# if GTEST_OS_LINUX && !defined(__ia64__)
#  if GTEST_OS_LINUX_ANDROID
// On Android, clone() is only available on ARM starting with Gingerbread.
#    if defined(__arm__) && __ANDROID_API__ >= 9
#     define GTEST_HAS_CLONE 1
#    else
#     define GTEST_HAS_CLONE 0
#    endif
#  else
#   define GTEST_HAS_CLONE 1
#  endif
# else
#  define GTEST_HAS_CLONE 0
# endif  // GTEST_OS_LINUX && !defined(__ia64__)

#endif  // GTEST_HAS_CLONE

// Determines whether to support stream redirection. This is used to test
// output correctness and to implement death tests.
#ifndef GTEST_HAS_STREAM_REDIRECTION
// By default, we assume that stream redirection is supported on all
// platforms except known mobile ones.
# if GTEST_OS_WINDOWS_MOBILE || GTEST_OS_SYMBIAN || \
    GTEST_OS_WINDOWS_PHONE || GTEST_OS_WINDOWS_RT
#  define GTEST_HAS_STREAM_REDIRECTION 0
# else
#  define GTEST_HAS_STREAM_REDIRECTION 1
# endif  // !GTEST_OS_WINDOWS_MOBILE && !GTEST_OS_SYMBIAN
#endif  // GTEST_HAS_STREAM_REDIRECTION

// Determines whether to support death tests.
// Google Test does not support death tests for VC 7.1 and earlier as
// abort() in a VC 7.1 application compiled as GUI in debug config
// pops up a dialog window that cannot be suppressed programmatically.
#if (GTEST_OS_LINUX || GTEST_OS_CYGWIN || GTEST_OS_SOLARIS || \
     (GTEST_OS_MAC && !GTEST_OS_IOS) || \
     (GTEST_OS_WINDOWS_DESKTOP && _MSC_VER >= 1400) || \
     GTEST_OS_WINDOWS_MINGW || GTEST_OS_AIX || GTEST_OS_HPUX || \
     GTEST_OS_OPENBSD || GTEST_OS_QNX || GTEST_OS_FREEBSD)
# define GTEST_HAS_DEATH_TEST 1
#endif

// We don't support MSVC 7.1 with exceptions disabled now.  Therefore
// all the compilers we care about are adequate for supporting
// value-parameterized tests.
#define GTEST_HAS_PARAM_TEST 1

// Determines whether to support type-driven tests.

// Typed tests need <typeinfo> and variadic macros, which GCC, VC++ 8.0,
// Sun Pro CC, IBM Visual Age, and HP aCC support.
#if defined(__GNUC__) || (_MSC_VER >= 1400) || defined(__SUNPRO_CC) || \
    defined(__IBMCPP__) || defined(__HP_aCC)
# define GTEST_HAS_TYPED_TEST 1
# define GTEST_HAS_TYPED_TEST_P 1
#endif

// Determines whether to support Combine(). This only makes sense when
// value-parameterized tests are enabled.  The implementation doesn't
// work on Sun Studio since it doesn't understand templated conversion
// operators.
#if GTEST_HAS_PARAM_TEST && GTEST_HAS_TR1_TUPLE && !defined(__SUNPRO_CC)
# define GTEST_HAS_COMBINE 1
#endif

// Determines whether the system compiler uses UTF-16 for encoding wide strings.
#define GTEST_WIDE_STRING_USES_UTF16_ \
    (GTEST_OS_WINDOWS || GTEST_OS_CYGWIN || GTEST_OS_SYMBIAN || GTEST_OS_AIX)

// Determines whether test results can be streamed to a socket.
#if GTEST_OS_LINUX
# define GTEST_CAN_STREAM_RESULTS_ 1
#endif

// Defines some utility macros.

// The GNU compiler emits a warning if nested "if" statements are followed by
// an "else" statement and braces are not used to explicitly disambiguate the
// "else" binding.  This leads to problems with code like:
//
//   if (gate)
//     ASSERT_*(condition) << "Some message";
//
// The "switch (0) case 0:" idiom is used to suppress this.
#ifdef __INTEL_COMPILER
# define GTEST_AMBIGUOUS_ELSE_BLOCKER_
#else
# define GTEST_AMBIGUOUS_ELSE_BLOCKER_ switch (0) case 0: default:  // NOLINT
#endif

// Use this annotation at the end of a struct/class definition to
// prevent the compiler from optimizing away instances that are never
// used.  This is useful when all interesting logic happens inside the
// c'tor and / or d'tor.  Example:
//
//   struct Foo {
//     Foo() { ... }
//   } GTEST_ATTRIBUTE_UNUSED_;
//
// Also use it after a variable or parameter declaration to tell the
// compiler the variable/parameter does not have to be used.
#if defined(__GNUC__) && !defined(COMPILER_ICC)
# define GTEST_ATTRIBUTE_UNUSED_ __attribute__ ((unused))
#elif defined(__clang__)
# if __has_attribute(unused)
#  define GTEST_ATTRIBUTE_UNUSED_ __attribute__ ((unused))
# endif
#endif
#ifndef GTEST_ATTRIBUTE_UNUSED_
# define GTEST_ATTRIBUTE_UNUSED_
#endif

// A macro to disallow operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_ASSIGN_(type)\
  void operator=(type const &)

// A macro to disallow copy constructor and operator=
// This should be used in the private: declarations for a class.
#define GTEST_DISALLOW_COPY_AND_ASSIGN_(type)\
  type(type const &);\
  GTEST_DISALLOW_ASSIGN_(type)

// Tell the compiler to warn about unused return values for functions declared
// with this macro.  The macro should be used on function declarations
// following the argument list:
//
//   Sprocket* AllocateSprocket() GTEST_MUST_USE_RESULT_;
#if defined(__GNUC__) && (GTEST_GCC_VER_ >= 30400) && !defined(COMPILER_ICC)
# define GTEST_MUST_USE_RESULT_ __attribute__ ((warn_unused_result))
#else
# define GTEST_MUST_USE_RESULT_
#endif  // __GNUC__ && (GTEST_GCC_VER_ >= 30400) && !COMPILER_ICC

// MS C++ compiler emits warning when a conditional expression is compile time
// constant. In some contexts this warning is false positive and needs to be
// suppressed. Use the following two macros in such cases:
//
// GTEST_INTENTIONAL_CONST_COND_PUSH_()
// while (true) {
// GTEST_INTENTIONAL_CONST_COND_POP_()
// }
# define GTEST_INTENTIONAL_CONST_COND_PUSH_() \
    GTEST_DISABLE_MSC_WARNINGS_PUSH_(4127)
# define GTEST_INTENTIONAL_CONST_COND_POP_() \
    GTEST_DISABLE_MSC_WARNINGS_POP_()

// Determine whether the compiler supports Microsoft's Structured Exception
// Handling.  This is supported by several Windows compilers but generally
// does not exist on any other system.
#ifndef GTEST_HAS_SEH
// The user didn't tell us, so we need to figure it out.

# if defined(_MSC_VER) || defined(__BORLANDC__)
// These two compilers are known to support SEH.
#  define GTEST_HAS_SEH 1
# else
// Assume no SEH.
#  define GTEST_HAS_SEH 0
# endif

#define GTEST_IS_THREADSAFE \
    (GTEST_HAS_MUTEX_AND_THREAD_LOCAL_ \
     || (GTEST_OS_WINDOWS && !GTEST_OS_WINDOWS_PHONE && !GTEST_OS_WINDOWS_RT) \
     || GTEST_HAS_PTHREAD)

#endif  // GTEST_HAS_SEH

#ifdef _MSC_VER
# if GTEST_LINKED_AS_SHARED_LIBRARY
#  define GTEST_API_ __declspec(dllimport)
# elif GTEST_CREATE_SHARED_LIBRARY
#  define GTEST_API_ __declspec(dllexport)
# endif
#elif __GNUC__ >= 4 || defined(__clang__)
# define GTEST_API_ __attribute__((visibility ("default")))
#endif // _MSC_VER

#ifndef GTEST_API_
# define GTEST_API_
#endif

#ifdef __GNUC__
// Ask the compiler to never inline a given function.
# define GTEST_NO_INLINE_ __attribute__((noinline))
#else
# define GTEST_NO_INLINE_
#endif

// _LIBCPP_VERSION is defined by the libc++ library from the LLVM project.
#if defined(__GLIBCXX__) || defined(_LIBCPP_VERSION)
# define GTEST_HAS_CXXABI_H_ 1
#else
# define GTEST_HAS_CXXABI_H_ 0
#endif

// A function level attribute to disable checking for use of uninitialized
// memory when built with MemorySanitizer.
#if defined(__clang__)
# if __has_feature(memory_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_ \
       __attribute__((no_sanitize_memory))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_
# endif  // __has_feature(memory_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_MEMORY_
#endif  // __clang__

// A function level attribute to disable AddressSanitizer instrumentation.
#if defined(__clang__)
# if __has_feature(address_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_ \
       __attribute__((no_sanitize_address))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_
# endif  // __has_feature(address_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_ADDRESS_
#endif  // __clang__

// A function level attribute to disable ThreadSanitizer instrumentation.
#if defined(__clang__)
# if __has_feature(thread_sanitizer)
#  define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_ \
       __attribute__((no_sanitize_thread))
# else
#  define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_
# endif  // __has_feature(thread_sanitizer)
#else
# define GTEST_ATTRIBUTE_NO_SANITIZE_THREAD_
#endif  // __clang__

namespace testing {

class Message;

#if defined(GTEST_TUPLE_NAMESPACE_)
// Import tuple and friends into the ::testing namespace.
// It is part of our interface, having them in ::testing allows us to change
// their types as needed.
using GTEST_TUPLE_NAMESPACE_::get;
using GTEST_TUPLE_NAMESPACE_::make_tuple;
using GTEST_TUPLE_NAMESPACE_::tuple;
using GTEST_TUPLE_NAMESPACE_::tuple_size;
using GTEST_TUPLE_NAMESPACE_::tuple_element;
#endif  // defined(GTEST_TUPLE_NAMESPACE_)

namespace internal {

// A secret type that Google Test users don't know about.  It has no
// definition on purpose.  Therefore it's impossible to create a
// Secret object, which is what we want.
class Secret;

// The GTEST_COMPILE_ASSERT_ macro can be used to verify that a compile time
// expression is true. For example, you could use it to verify the
// size of a static array:
//
//   GTEST_COMPILE_ASSERT_(GTEST_ARRAY_SIZE_(names) == NUM_NAMES,
//                         names_incorrect_size);
//
// or to make sure a struct is smaller than a certain size:
//
//   GTEST_COMPILE_ASSERT_(sizeof(foo) < 128, foo_too_large);
//
// The second argument to the macro is the name of the variable. If
// the expression is false, most compilers will issue a warning/error
// containing the name of the variable.

#if GTEST_LANG_CXX11
# define GTEST_COMPILE_ASSERT_(expr, msg) static_assert(expr, #msg)
#else  // !GTEST_LANG_CXX11
template <bool>
  struct CompileAssert {
};

# define GTEST_COMPILE_ASSERT_(expr, msg) \
  typedef ::testing::internal::CompileAssert<(static_cast<bool>(expr))> \
      msg[static_cast<bool>(expr) ? 1 : -1] GTEST_ATTRIBUTE_UNUSED_
#endif  // !GTEST_LANG_CXX11

// Implementation details of GTEST_COMPILE_ASSERT_:
//
// (In C++11, we simply use static_assert instead of the following)
//
// - GTEST_COMPILE_ASSERT_ works by defining an array type that has -1
//   elements (and thus is invalid) when the expression is false.
//
// - The simpler definition
//
//    #define GTEST_COMPILE_ASSERT_(expr, msg) typedef char msg[(expr) ? 1 : -1]
//
//   does not work, as gcc supports variable-length arrays whose sizes
//   are determined at run-time (this is gcc's extension and not part
//   of the C++ standard).  As a result, gcc fails to reject the
//   following code with the simple definition:
//
//     int foo;
//     GTEST_COMPILE_ASSERT_(foo, msg); // not supposed to compile as foo is
//                                      // not a compile-time constant.
//
// - By using the type CompileAssert<(bool(expr))>, we ensures that
//   expr is a compile-time constant.  (Template arguments must be
//   determined at compile-time.)
//
// - The outter parentheses in CompileAssert<(bool(expr))> are necessary
//   to work around a bug in gcc 3.4.4 and 4.0.1.  If we had written
//
//     CompileAssert<bool(expr)>
//
//   instead, these compilers will refuse to compile
//
//     GTEST_COMPILE_ASSERT_(5 > 0, some_message);
//
//   (They seem to think the ">" in "5 > 0" marks the end of the
//   template argument list.)
//
// - The array size is (bool(expr) ? 1 : -1), instead of simply
//
//     ((expr) ? 1 : -1).
//
//   This is to avoid running into a bug in MS VC 7.1, which
//   causes ((0.0) ? 1 : -1) to incorrectly evaluate to 1.

// StaticAssertTypeEqHelper is used by StaticAssertTypeEq defined in gtest.h.
//
// This template is declared, but intentionally undefined.
template <typename T1, typename T2>
struct StaticAssertTypeEqHelper;

template <typename T>
struct StaticAssertTypeEqHelper<T, T> {
  enum { value = true };
};

// Evaluates to the number of elements in 'array'.
#define GTEST_ARRAY_SIZE_(array) (sizeof(array) / sizeof(array[0]))

#if GTEST_HAS_GLOBAL_STRING
typedef ::string string;
#else
typedef ::std::string string;
#endif  // GTEST_HAS_GLOBAL_STRING

#if GTEST_HAS_GLOBAL_WSTRING
typedef ::wstring wstring;
#elif GTEST_HAS_STD_WSTRING
typedef ::std::wstring wstring;
#endif  // GTEST_HAS_GLOBAL_WSTRING

// A helper for suppressing warnings on constant condition.  It just
// returns 'condition'.
GTEST_API_ bool IsTrue(bool condition);

// Defines scoped_ptr.

// This implementation of scoped_ptr is PARTIAL - it only contains
// enough stuff to satisfy Google Test's need.
template <typename T>
class scoped_ptr {
 public:
  typedef T element_type;

  explicit scoped_ptr(T* p = NULL) : ptr_(p) {}
  ~scoped_ptr() { reset(); }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }
  T* get() const { return ptr_; }

  T* release() {
    T* const ptr = ptr_;
    ptr_ = NULL;
    return ptr;
  }

  void reset(T* p = NULL) {
    if (p != ptr_) {
      if (IsTrue(sizeof(T) > 0)) {  // Makes sure T is a complete type.
        delete ptr_;
      }
      ptr_ = p;
    }
  }

  friend void swap(scoped_ptr& a, scoped_ptr& b) {
    using std::swap;
    swap(a.ptr_, b.ptr_);
  }

 private:
  T* ptr_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(scoped_ptr);
};

// Defines RE.

// A simple C++ wrapper for <regex.h>.  It uses the POSIX Extended
// Regular Expression syntax.
class GTEST_API_ RE {
 public:
  // A copy constructor is required by the Standard to initialize object
  // references from r-values.
  RE(const RE& other) { Init(other.pattern()); }

  // Constructs an RE from a string.
  RE(const ::std::string& regex) { Init(regex.c_str()); }  // NOLINT

#if GTEST_HAS_GLOBAL_STRING

  RE(const ::string& regex) { Init(regex.c_str()); }  // NOLINT

#endif  // GTEST_HAS_GLOBAL_STRING

  RE(const char* regex) { Init(regex); }  // NOLINT
  ~RE();

  // Returns the string representation of the regex.
  const char* pattern() const { return pattern_; }

  // FullMatch(str, re) returns true iff regular expression re matches
  // the entire str.
  // PartialMatch(str, re) returns true iff regular expression re
  // matches a substring of str (including str itself).
  //
  // TODO(wan@google.com): make FullMatch() and PartialMatch() work
  // when str contains NUL characters.
  static bool FullMatch(const ::std::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::std::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }

#if GTEST_HAS_GLOBAL_STRING

  static bool FullMatch(const ::string& str, const RE& re) {
    return FullMatch(str.c_str(), re);
  }
  static bool PartialMatch(const ::string& str, const RE& re) {
    return PartialMatch(str.c_str(), re);
  }

#endif  // GTEST_HAS_GLOBAL_STRING

  static bool FullMatch(const char* str, const RE& re);
  static bool PartialMatch(const char* str, const RE& re);

 private:
  void Init(const char* regex);

  // We use a const char* instead of an std::string, as Google Test used to be
  // used where std::string is not available.  TODO(wan@google.com): change to
  // std::string.
  const char* pattern_;
  bool is_valid_;

#if GTEST_USES_POSIX_RE

  regex_t full_regex_;     // For FullMatch().
  regex_t partial_regex_;  // For PartialMatch().

#else  // GTEST_USES_SIMPLE_RE

  const char* full_pattern_;  // For FullMatch();

#endif

  GTEST_DISALLOW_ASSIGN_(RE);
};

// Formats a source file path and a line number as they would appear
// in an error message from the compiler used to compile this code.
GTEST_API_ ::std::string FormatFileLocation(const char* file, int line);

// Formats a file location for compiler-independent XML output.
// Although this function is not platform dependent, we put it next to
// FormatFileLocation in order to contrast the two functions.
GTEST_API_ ::std::string FormatCompilerIndependentFileLocation(const char* file,
                                                               int line);

// Defines logging utilities:
//   GTEST_LOG_(severity) - logs messages at the specified severity level. The
//                          message itself is streamed into the macro.
//   LogToStderr()  - directs all log messages to stderr.
//   FlushInfoLog() - flushes informational log messages.

enum GTestLogSeverity {
  GTEST_INFO,
  GTEST_WARNING,
  GTEST_ERROR,
  GTEST_FATAL
};

// Formats log entry severity, provides a stream object for streaming the
// log message, and terminates the message with a newline when going out of
// scope.
class GTEST_API_ GTestLog {
 public:
  GTestLog(GTestLogSeverity severity, const char* file, int line);

  // Flushes the buffers and, if severity is GTEST_FATAL, aborts the program.
  ~GTestLog();

  ::std::ostream& GetStream() { return ::std::cerr; }

 private:
  const GTestLogSeverity severity_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestLog);
};

#if !defined(GTEST_LOG_)

# define GTEST_LOG_(severity) \
    ::testing::internal::GTestLog(::testing::internal::GTEST_##severity, \
                                  __FILE__, __LINE__).GetStream()

inline void LogToStderr() {}
inline void FlushInfoLog() { fflush(NULL); }

#endif  // !defined(GTEST_LOG_)

#if !defined(GTEST_CHECK_)
// INTERNAL IMPLEMENTATION - DO NOT USE.
//
// GTEST_CHECK_ is an all-mode assert. It aborts the program if the condition
// is not satisfied.
//  Synopsys:
//    GTEST_CHECK_(boolean_condition);
//     or
//    GTEST_CHECK_(boolean_condition) << "Additional message";
//
//    This checks the condition and if the condition is not satisfied
//    it prints message about the condition violation, including the
//    condition itself, plus additional message streamed into it, if any,
//    and then it aborts the program. It aborts the program irrespective of
//    whether it is built in the debug mode or not.
# define GTEST_CHECK_(condition) \
    GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
    if (::testing::internal::IsTrue(condition)) \
      ; \
    else \
      GTEST_LOG_(FATAL) << "Condition " #condition " failed. "
#endif  // !defined(GTEST_CHECK_)

// An all-mode assert to verify that the given POSIX-style function
// call returns 0 (indicating success).  Known limitation: this
// doesn't expand to a balanced 'if' statement, so enclose the macro
// in {} if you need to use it as the only statement in an 'if'
// branch.
#define GTEST_CHECK_POSIX_SUCCESS_(posix_call) \
  if (const int gtest_error = (posix_call)) \
    GTEST_LOG_(FATAL) << #posix_call << "failed with error " \
                      << gtest_error

#if GTEST_HAS_STD_MOVE_
using std::move;
#else  // GTEST_HAS_STD_MOVE_
template <typename T>
const T& move(const T& t) {
  return t;
}
#endif  // GTEST_HAS_STD_MOVE_

// INTERNAL IMPLEMENTATION - DO NOT USE IN USER CODE.
//
// Use ImplicitCast_ as a safe version of static_cast for upcasting in
// the type hierarchy (e.g. casting a Foo* to a SuperclassOfFoo* or a
// const Foo*).  When you use ImplicitCast_, the compiler checks that
// the cast is safe.  Such explicit ImplicitCast_s are necessary in
// surprisingly many situations where C++ demands an exact type match
// instead of an argument type convertable to a target type.
//
// The syntax for using ImplicitCast_ is the same as for static_cast:
//
//   ImplicitCast_<ToType>(expr)
//
// ImplicitCast_ would have been part of the C++ standard library,
// but the proposal was submitted too late.  It will probably make
// its way into the language in the future.
//
// This relatively ugly name is intentional. It prevents clashes with
// similar functions users may have (e.g., implicit_cast). The internal
// namespace alone is not enough because the function can be found by ADL.
template<typename To>
inline To ImplicitCast_(To x) { return x; }

// When you upcast (that is, cast a pointer from type Foo to type
// SuperclassOfFoo), it's fine to use ImplicitCast_<>, since upcasts
// always succeed.  When you downcast (that is, cast a pointer from
// type Foo to type SubclassOfFoo), static_cast<> isn't safe, because
// how do you know the pointer is really of type SubclassOfFoo?  It
// could be a bare Foo, or of type DifferentSubclassOfFoo.  Thus,
// when you downcast, you should use this macro.  In debug mode, we
// use dynamic_cast<> to double-check the downcast is legal (we die
// if it's not).  In normal mode, we do the efficient static_cast<>
// instead.  Thus, it's important to test in debug mode to make sure
// the cast is legal!
//    This is the only place in the code we should use dynamic_cast<>.
// In particular, you SHOULDN'T be using dynamic_cast<> in order to
// do RTTI (eg code like this:
//    if (dynamic_cast<Subclass1>(foo)) HandleASubclass1Object(foo);
//    if (dynamic_cast<Subclass2>(foo)) HandleASubclass2Object(foo);
// You should design the code some other way not to need this.
//
// This relatively ugly name is intentional. It prevents clashes with
// similar functions users may have (e.g., down_cast). The internal
// namespace alone is not enough because the function can be found by ADL.
template<typename To, typename From>  // use like this: DownCast_<T*>(foo);
inline To DownCast_(From* f) {  // so we only accept pointers
  // Ensures that To is a sub-type of From *.  This test is here only
  // for compile-time type checking, and has no overhead in an
  // optimized build at run-time, as it will be optimized away
  // completely.
  GTEST_INTENTIONAL_CONST_COND_PUSH_()
  if (false) {
  GTEST_INTENTIONAL_CONST_COND_POP_()
    const To to = NULL;
    ::testing::internal::ImplicitCast_<From*>(to);
  }

#if GTEST_HAS_RTTI
  // RTTI: debug mode only!
  GTEST_CHECK_(f == NULL || dynamic_cast<To>(f) != NULL);
#endif
  return static_cast<To>(f);
}

// Downcasts the pointer of type Base to Derived.
// Derived must be a subclass of Base. The parameter MUST
// point to a class of type Derived, not any subclass of it.
// When RTTI is available, the function performs a runtime
// check to enforce this.
template <class Derived, class Base>
Derived* CheckedDowncastToActualType(Base* base) {
#if GTEST_HAS_RTTI
  GTEST_CHECK_(typeid(*base) == typeid(Derived));
#endif

#if GTEST_HAS_DOWNCAST_
  return ::down_cast<Derived*>(base);
#elif GTEST_HAS_RTTI
  return dynamic_cast<Derived*>(base);  // NOLINT
#else
  return static_cast<Derived*>(base);  // Poor man's downcast.
#endif
}

#if GTEST_HAS_STREAM_REDIRECTION

// Defines the stderr capturer:
//   CaptureStdout     - starts capturing stdout.
//   GetCapturedStdout - stops capturing stdout and returns the captured string.
//   CaptureStderr     - starts capturing stderr.
//   GetCapturedStderr - stops capturing stderr and returns the captured string.
//
GTEST_API_ void CaptureStdout();
GTEST_API_ std::string GetCapturedStdout();
GTEST_API_ void CaptureStderr();
GTEST_API_ std::string GetCapturedStderr();

#endif  // GTEST_HAS_STREAM_REDIRECTION

// Returns a path to temporary directory.
GTEST_API_ std::string TempDir();

// Returns the size (in bytes) of a file.
GTEST_API_ size_t GetFileSize(FILE* file);

// Reads the entire content of a file as a string.
GTEST_API_ std::string ReadEntireFile(FILE* file);

// All command line arguments.
GTEST_API_ const ::std::vector<testing::internal::string>& GetArgvs();

#if GTEST_HAS_DEATH_TEST

const ::std::vector<testing::internal::string>& GetInjectableArgvs();
void SetInjectableArgvs(const ::std::vector<testing::internal::string>*
                             new_argvs);


#endif  // GTEST_HAS_DEATH_TEST

// Defines synchronization primitives.
#if GTEST_IS_THREADSAFE
# if GTEST_HAS_PTHREAD
// Sleeps for (roughly) n milliseconds.  This function is only for testing
// Google Test's own constructs.  Don't use it in user tests, either
// directly or indirectly.
inline void SleepMilliseconds(int n) {
  const timespec time = {
    0,                  // 0 seconds.
    n * 1000L * 1000L,  // And n ms.
  };
  nanosleep(&time, NULL);
}
# endif  // GTEST_HAS_PTHREAD

# if GTEST_HAS_NOTIFICATION_
// Notification has already been imported into the namespace.
// Nothing to do here.

# elif GTEST_HAS_PTHREAD
// Allows a controller thread to pause execution of newly created
// threads until notified.  Instances of this class must be created
// and destroyed in the controller thread.
//
// This class is only for testing Google Test's own constructs. Do not
// use it in user tests, either directly or indirectly.
class Notification {
 public:
  Notification() : notified_(false) {
    GTEST_CHECK_POSIX_SUCCESS_(pthread_mutex_init(&mutex_, NULL));
  }
  ~Notification() {
    pthread_mutex_destroy(&mutex_);
  }

  // Notifies all threads created with this notification to start. Must
  // be called from the controller thread.
  void Notify() {
    pthread_mutex_lock(&mutex_);
    notified_ = true;
    pthread_mutex_unlock(&mutex_);
  }

  // Blocks until the controller thread notifies. Must be called from a test
  // thread.
  void WaitForNotification() {
    for (;;) {
      pthread_mutex_lock(&mutex_);
      const bool notified = notified_;
      pthread_mutex_unlock(&mutex_);
      if (notified)
        break;
      SleepMilliseconds(10);
    }
  }

 private:
  pthread_mutex_t mutex_;
  bool notified_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(Notification);
};

# elif GTEST_OS_WINDOWS && !GTEST_OS_WINDOWS_PHONE && !GTEST_OS_WINDOWS_RT

GTEST_API_ void SleepMilliseconds(int n);

// Provides leak-safe Windows kernel handle ownership.
// Used in death tests and in threading support.
class GTEST_API_ AutoHandle {
 public:
  // Assume that Win32 HANDLE type is equivalent to void*. Doing so allows us to
  // avoid including <windows.h> in this header file. Including <windows.h> is
  // undesirable because it defines a lot of symbols and macros that tend to
  // conflict with client code. This assumption is verified by
  // WindowsTypesTest.HANDLEIsVoidStar.
  typedef void* Handle;
  AutoHandle();
  explicit AutoHandle(Handle handle);

  ~AutoHandle();

  Handle Get() const;
  void Reset();
  void Reset(Handle handle);

 private:
  // Returns true iff the handle is a valid handle object that can be closed.
  bool IsCloseable() const;

  Handle handle_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(AutoHandle);
};

// Allows a controller thread to pause execution of newly created
// threads until notified.  Instances of this class must be created
// and destroyed in the controller thread.
//
// This class is only for testing Google Test's own constructs. Do not
// use it in user tests, either directly or indirectly.
class GTEST_API_ Notification {
 public:
  Notification();
  void Notify();
  void WaitForNotification();

 private:
  AutoHandle event_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(Notification);
};
# endif  // GTEST_HAS_NOTIFICATION_

// On MinGW, we can have both GTEST_OS_WINDOWS and GTEST_HAS_PTHREAD
// defined, but we don't want to use MinGW's pthreads implementation, which
// has conformance problems with some versions of the POSIX standard.
# if GTEST_HAS_PTHREAD && !GTEST_OS_WINDOWS_MINGW

// As a C-function, ThreadFuncWithCLinkage cannot be templated itself.
// Consequently, it cannot select a correct instantiation of ThreadWithParam
// in order to call its Run(). Introducing ThreadWithParamBase as a
// non-templated base class for ThreadWithParam allows us to bypass this
// problem.
class ThreadWithParamBase {
 public:
  virtual ~ThreadWithParamBase() {}
  virtual void Run() = 0;
};

// pthread_create() accepts a pointer to a function type with the C linkage.
// According to the Standard (7.5/1), function types with different linkages
// are different even if they are otherwise identical.  Some compilers (for
// example, SunStudio) treat them as different types.  Since class methods
// cannot be defined with C-linkage we need to define a free C-function to
// pass into pthread_create().
extern "C" inline void* ThreadFuncWithCLinkage(void* thread) {
  static_cast<ThreadWithParamBase*>(thread)->Run();
  return NULL;
}

// Helper class for testing Google Test's multi-threading constructs.
// To use it, write:
//
//   void ThreadFunc(int param) { /* Do things with param */ }
//   Notification thread_can_start;
//   ...
//   // The thread_can_start parameter is optional; you can supply NULL.
//   ThreadWithParam<int> thread(&ThreadFunc, 5, &thread_can_start);
//   thread_can_start.Notify();
//
// These classes are only for testing Google Test's own constructs. Do
// not use them in user tests, either directly or indirectly.
template <typename T>
class ThreadWithParam : public ThreadWithParamBase {
 public:
  typedef void UserThreadFunc(T);

  ThreadWithParam(UserThreadFunc* func, T param, Notification* thread_can_start)
      : func_(func),
        param_(param),
        thread_can_start_(thread_can_start),
        finished_(false) {
    ThreadWithParamBase* const base = this;
    // The thread can be created only after all fields except thread_
    // have been initialized.
    GTEST_CHECK_POSIX_SUCCESS_(
        pthread_create(&thread_, 0, &ThreadFuncWithCLinkage, base));
  }
  ~ThreadWithParam() { Join(); }

  void Join() {
    if (!finished_) {
      GTEST_CHECK_POSIX_SUCCESS_(pthread_join(thread_, 0));
      finished_ = true;
    }
  }

  virtual void Run() {
    if (thread_can_start_ != NULL)
      thread_can_start_->WaitForNotification();
    func_(param_);
  }

 private:
  UserThreadFunc* const func_;  // User-supplied thread function.
  const T param_;  // User-supplied parameter to the thread function.
  // When non-NULL, used to block execution until the controller thread
  // notifies.
  Notification* const thread_can_start_;
  bool finished_;  // true iff we know that the thread function has finished.
  pthread_t thread_;  // The native thread object.

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ThreadWithParam);
};
# endif  // !GTEST_OS_WINDOWS && GTEST_HAS_PTHREAD ||
         // GTEST_HAS_MUTEX_AND_THREAD_LOCAL_

# if GTEST_HAS_MUTEX_AND_THREAD_LOCAL_
// Mutex and ThreadLocal have already been imported into the namespace.
// Nothing to do here.

# elif GTEST_OS_WINDOWS && !GTEST_OS_WINDOWS_PHONE && !GTEST_OS_WINDOWS_RT

// Mutex implements mutex on Windows platforms.  It is used in conjunction
// with class MutexLock:
//
//   Mutex mutex;
//   ...
//   MutexLock lock(&mutex);  // Acquires the mutex and releases it at the
//                            // end of the current scope.
//
// A static Mutex *must* be defined or declared using one of the following
// macros:
//   GTEST_DEFINE_STATIC_MUTEX_(g_some_mutex);
//   GTEST_DECLARE_STATIC_MUTEX_(g_some_mutex);
//
// (A non-static Mutex is defined/declared in the usual way).
class GTEST_API_ Mutex {
 public:
  enum MutexType { kStatic = 0, kDynamic = 1 };
  // We rely on kStaticMutex being 0 as it is to what the linker initializes
  // type_ in static mutexes.  critical_section_ will be initialized lazily
  // in ThreadSafeLazyInit().
  enum StaticConstructorSelector { kStaticMutex = 0 };

  // This constructor intentionally does nothing.  It relies on type_ being
  // statically initialized to 0 (effectively setting it to kStatic) and on
  // ThreadSafeLazyInit() to lazily initialize the rest of the members.
  explicit Mutex(StaticConstructorSelector /*dummy*/) {}

  Mutex();
  ~Mutex();

  void Lock();

  void Unlock();

  // Does nothing if the current thread holds the mutex. Otherwise, crashes
  // with high probability.
  void AssertHeld();

 private:
  // Initializes owner_thread_id_ and critical_section_ in static mutexes.
  void ThreadSafeLazyInit();

  // Per http://blogs.msdn.com/b/oldnewthing/archive/2004/02/23/78395.aspx,
  // we assume that 0 is an invalid value for thread IDs.
  unsigned int owner_thread_id_;

  // For static mutexes, we rely on these members being initialized to zeros
  // by the linker.
  MutexType type_;
  long critical_section_init_phase_;  // NOLINT
  _RTL_CRITICAL_SECTION* critical_section_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(Mutex);
};

# define GTEST_DECLARE_STATIC_MUTEX_(mutex) \
    extern ::testing::internal::Mutex mutex

# define GTEST_DEFINE_STATIC_MUTEX_(mutex) \
    ::testing::internal::Mutex mutex(::testing::internal::Mutex::kStaticMutex)

// We cannot name this class MutexLock because the ctor declaration would
// conflict with a macro named MutexLock, which is defined on some
// platforms. That macro is used as a defensive measure to prevent against
// inadvertent misuses of MutexLock like "MutexLock(&mu)" rather than
// "MutexLock l(&mu)".  Hence the typedef trick below.
class GTestMutexLock {
 public:
  explicit GTestMutexLock(Mutex* mutex)
      : mutex_(mutex) { mutex_->Lock(); }

  ~GTestMutexLock() { mutex_->Unlock(); }

 private:
  Mutex* const mutex_;

  GTEST_DISALLOW_COPY_AND_ASSIGN_(GTestMutexLock);
};

typedef GTestMutexLock MutexLock;

// Base class for ValueHolder<T>.  Allows a caller to hold and delete a value
// without knowing its type.
class ThreadLocalValueHolderBase {
 public:
  virtual ~ThreadLocalValueHolderBase() {}
};

// Provides a way for a thread to send notifications to a ThreadLocal
// regardless of its parameter type.
class ThreadLocalBase {
 public:
  // Creates a new ValueHolder<T> object holding a default value passed to
  // this ThreadLocal<T>'s constructor and returns it.  It is the caller's
  // responsibility not to call this when the ThreadLocal<T> instance already
  // has a value on the current thread.
  virtual ThreadLocalValueHolderBase* NewValueForCurrentThread() const = 0;

 protected:
  ThreadLocalBase() {}
  virtual ~ThreadLocalBase() {}

 private:
  GTEST_DISALLOW_COPY_AND_ASSIGN_(ThreadLocalBase);
};

// Maps a thread to a set of ThreadLocals that have values instantiated on that
// thread and notifies them when the thread exits.  A ThreadLocal instance is
// expected to persist until all threads it has values on have terminated.
class GTEST_API_ ThreadLocalRegistry {
 public:
  // Registers thread_local_instance as having value on the current thread.
  // Returns a value that can be used to identify the thread from other threads.
  static ThreadLocalValueHolderBase* GetValueOnCurrentThread(
      const ThreadLocalBase* thread_local_instance);

  // Invoked when a ThreadLocal instance is destroyed.
  static void OnThreadLocalDestroyed(
      const ThreadLocalBase* thread_local_instance);
};

class GTEST_API_ ThreadWithParamBase {
 public:
  void Join();

 protected:
  class Runnable {
   public:
    virtual ~Runnable() {}
    virtual void Run() = 0;
  };

  ThreadWithParamBase(Runnable *runnable, Notification* thread_can_start);
  virtual ~ThreadWithParamBase();

 private:
  AutoHandle thread_;
};

// Helper class for testing Google Test's multi-threading constructs.
template <typename T>
class ThreadWithParam : public ThreadWithParamBase {
 public:
  typedef void UserThreadFunc(T);

  ThreadWithParam(UserThreadFunc* func, T param, Notification* thread_can_start)
      : ThreadWithParamBase(new RunnableImpl(func, param), thread_can_start) {
  }
  virtual ~ThreadWithParam() {}

 private:
  class RunnableImpl : public Runnable {
   public:
    RunnableImpl(UserThreadFunc* func, T param)
        : func_(func),
          param_(param) {
    }
    virtual ~RunnableImpl() {}
    virtual void Run() {
      func_(param_);
    }

   private:
    UserThreadFunc* const func_;
    const T param_;

    GTEST_DISALLOW_COPY_AND_ASSIGN_(RunnableImpl);
  };

  GTEST_DISALLOW_COPY_AND_ASSIGN_(ThreadWithParam);
};

// Implements thread-local storage on Windows systems.
//
//   // Thread 1
//   ThreadLocal<int> tl(100);  // 100 is the default value for each thread.
//
//   // Thread 2
//   tl.set(150);  // Changes the value for thread 2 only.
//   EXPECT_EQ(150, tl.get());
//
//   // Thread 1
//   EXPECT_EQ(100, tl.get());  // In thread 1, tl has the original value.
//   tl.set(200);
//   EXPECT_EQ(200, tl.get());
//
// The template type argument T must have a public copy constructor.
// In addition, the default ThreadLocal constructor requires T to have
// a public default constructor.
//
// The users of a TheadLocal instance have to make sure that all but one
// threads (including the main one) using that instance have exited before
// destroying it. Otherwise, the per-thread objects managed for them by the
// ThreadLocal instance are not guaranteed to be destroyed on all platforms.
//
// Google Test only uses global ThreadLocal objects.  That means they
// will die after main() has returned.  Therefore, no per-thread
// object managed by Google Test will be leaked as long as all threads
// using Google Test have exited when main() returns.
template <typename T>
class ThreadLocal : public ThreadLocalBase {
 public:
  ThreadLocal() : default_factory_(new DefaultValueHolderFactory()) {}
  explicit ThreadLocal(const T& value)
      : default_factory_(new InstanceValueHolderFactory(value)) {}

  ~ThreadLocal() { ThreadLocalRegistry::OnThreadLocalDestroyed(this); }

  T* pointer() { return GetOrCreateValue(); }
  const T* pointer() const { return GetOrCreateValue(); }
  const T& get