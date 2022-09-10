/**
 *  Copyright (c) 2022 SGL authors Distributed under MIT License 
 * (http://opensource.org/licenses/MIT)
 */

#ifndef SGL_SRC_CORE_LOG_H_
#define SGL_SRC_CORE_LOG_H_

#include <memory>

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
// Ignore any warnings raised inside external headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)


namespace sgl
{
    class Log
    {
    public:
        static void Init();
        
        static std::shared_ptr<spdlog::logger>& GetLogger()
        {
            return s_Logger;
        }
        static std::shared_ptr<spdlog::logger>& GetAssertLogger()
        {
             return s_AssertLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
        static std::shared_ptr<spdlog::logger> s_AssertLogger;
    };

} // namespace sgl


#ifdef SGL_DEBUG
    #define SGL_LOG_TRACE(...) ::sgl::Log::GetLogger()->trace(__VA_ARGS__)
    #define SGL_LOG_INFO(...)  ::sgl::Log::GetLogger()->info(__VA_ARGS__)
    #define SGL_LOG_WARN(...)  ::sgl::Log::GetLogger()->warn(__VA_ARGS__)
    #define SGL_LOG_ERR(...)   ::sgl::Log::GetLogger()->error(__VA_ARGS__)
    #define SGL_LOG_CRIT(...)  ::sgl::Log::GetLogger()->critical(__VA_ARGS__)

    #define SGL_ASSERT_LOGGER() ::sgl::Log::GetAssertLogger()
    
    // @brief Prints that the function has been called, and when
    #define SGL_FUNCTION() { \
        SPDLOG_LOGGER_TRACE(::sgl::Log::GetAssertLogger(), ""); \
    }
#else
    #define SGL_LOG_TRACE(...)
    #define SGL_LOG_INFO(...)
    #define SGL_LOG_WARN(...)
    #define SGL_LOG_ERR(...)
    #define SGL_LOG_CRIT(...)
    #define SGL_FUNCTION()
#endif

#endif // SGL_SRC_CORE_LOG_H_
