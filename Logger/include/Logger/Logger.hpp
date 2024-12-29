#pragma once

#include <fmt/core.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <memory>
#include <string>

#define LOG_TRACE(logger, ...) logger->log(Logger::LogLevel::Trace, __VA_ARGS__)
#define LOG_DEBUG(logger, ...) logger->log(Logger::LogLevel::Debug, __VA_ARGS__)
#define LOG_INFO(logger, ...) logger->log(Logger::LogLevel::Info, __VA_ARGS__)
#define LOG_WARN(logger, ...) logger->log(Logger::LogLevel::Warn, __VA_ARGS__)
#define LOG_ERROR(logger, ...) logger->log(Logger::LogLevel::Error, __VA_ARGS__)
#define LOG_CRITICAL(logger, ...) \
    logger->log(Logger::LogLevel::Critical, __VA_ARGS__)

class Logger {
   public:
    enum class LogLevel { Trace, Debug, Info, Warn, Error, Critical };

    Logger(const std::string& pattern = "%^[%T] [%l] %v%$",
           LogLevel log_level = LogLevel::Info);

    template <typename... Args>
    void log(LogLevel level, const char* fmt, Args&&... args);

   private:
    std::shared_ptr<spdlog::logger> m_logger;

    spdlog::level::level_enum mapToSpdLogLevel(LogLevel level);
};

template <typename... Args>
void Logger::log(LogLevel level, const char* fmt, Args&&... args) {
    std::string formatted;

    if constexpr (sizeof...(args) > 0) {
        formatted = fmt::format(fmt::runtime(fmt), std::forward<Args>(args)...);
    } else {
        formatted = fmt;
    }

    switch (level) {
        case LogLevel::Trace:
            m_logger->trace(formatted);
            break;
        case LogLevel::Debug:
            m_logger->debug(formatted);
            break;
        case LogLevel::Info:
            m_logger->info(formatted);
            break;
        case LogLevel::Warn:
            m_logger->warn(formatted);
            break;
        case LogLevel::Error:
            m_logger->error(formatted);
            break;
        case LogLevel::Critical:
            m_logger->critical(formatted);
            break;
    }
}
