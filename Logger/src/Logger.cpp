#include "../include/Logger/Logger.hpp"

Logger::Logger(const std::string& pattern, LogLevel log_level) {
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_pattern(pattern);

    m_logger = std::make_shared<spdlog::logger>("console", console_sink);
    m_logger->set_level(mapToSpdLogLevel(log_level));
}

spdlog::level::level_enum Logger::mapToSpdLogLevel(LogLevel level) {
    switch (level) {
        case LogLevel::Trace:
            return spdlog::level::trace;
        case LogLevel::Debug:
            return spdlog::level::debug;
        case LogLevel::Info:
            return spdlog::level::info;
        case LogLevel::Warn:
            return spdlog::level::warn;
        case LogLevel::Error:
            return spdlog::level::err;
        case LogLevel::Critical:
            return spdlog::level::critical;
        default:
            return spdlog::level::info;
    }
}
