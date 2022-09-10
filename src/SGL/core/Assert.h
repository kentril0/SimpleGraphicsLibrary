/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_CORE_ASSERT_H_
#define SGL_CORE_ASSERT_H_

#include <spdlog/spdlog.h>

#include "SGL/core/Base.h"
#include "SGL/core/Log.h"

#ifdef SGL_ENABLE_ASSERTS

    // TODO other platforms, like windows: __debugbreak()
    #include <signal.h>
    #define SGL_DEXIT() raise(SIGTRAP)

    /**
     * @brief Assert macro. Prints default message
     *  when 'check' does NOT hold
     */
    #define SGL_ASSERT(check) { if(!(check)) {                                \
        SPDLOG_LOGGER_CRITICAL(SGL_ASSERT_LOGGER(), "Assertion '{0}' failed", \
                               SGL_STRINGIFY(check));                         \
        SGL_DEXIT(); } }

    /**
     * @brief Assert macro 
     * @param check If does NOT hold then exits the program
     * @param msg Log message printed if assert triggered
     */
    #define SGL_ASSERT_MSG(check, ...) { if(!(check)) {            \
        SPDLOG_LOGGER_CRITICAL(SGL_ASSERT_LOGGER(), __VA_ARGS__);  \
        SGL_DEXIT(); } }

#else
    #define SGL_DEXIT()
    #define SGL_ASSERT(...)
    #define SGL_ASSERT_MSG(...)
#endif // SGL_ENABLE_ASSERTS

#endif // SGL_CORE_ASSERT_H_
