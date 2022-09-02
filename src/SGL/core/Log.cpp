#include "SGL/core/Log.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>


namespace sgl
{
    std::shared_ptr<spdlog::logger> Log::s_Logger;
    std::shared_ptr<spdlog::logger> Log::s_AssertLogger;

    void Log::Init()
    {
        spdlog::set_level(spdlog::level::trace);

        s_Logger = spdlog::stdout_color_mt("SGL");
        // TODO expose level later
        s_Logger->set_level(spdlog::level::trace);
        s_Logger->set_pattern("%^[%T]: %v%$");

        // TODO to file also
        s_AssertLogger = spdlog::stdout_color_mt("SGLA");
        s_AssertLogger->set_level(spdlog::level::trace);
        s_AssertLogger->set_pattern("%^[%T]: %s:%#:%!() %v%$");
    }    

} // namespace sgl
