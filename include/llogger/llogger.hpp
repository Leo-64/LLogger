#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <string_view>
#include <utility>
#include <vector>

namespace LLogger
{

enum class Level
{
    TRACE,
    DEBUG,
    INFO,
    WARNING,
    ERROR
};

class LLogger
{
  public:
    static LLogger &getInstance()
    {
        static LLogger instance;
        return instance;
    }

    LLogger(const LLogger &) = delete;
    LLogger &operator=(const LLogger &) = delete;

    template <typename... Args> void log(Level level, std::string_view message, const Args &...args)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        printTimestamp();
        printLevel(level);

        std::cout << format(message, args...) << "\n";
    }

  private:
    LLogger() = default;
    std::mutex m_mutex;

    void printTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::cout << "[" << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S") << "] ";
    }

    void printLevel(Level level)
    {
        switch (level)
        {
        case Level::TRACE:
            std::cout << "[TRACE] ";
            break;
        case Level::DEBUG:
            std::cout << "[DEBUG] ";
            break;
        case Level::INFO:
            std::cout << "[INFO ] ";
            break;
        case Level::WARNING:
            std::cout << "[WARN ] ";
            break;
        case Level::ERROR:
            std::cout << "[ERROR] ";
            break;
        }
    }

    template <typename T> std::string to_string_kv(const T &val)
    {
        if constexpr (std::is_convertible_v<T, std::string_view>)
        {
            return std::string(val);
        }
        else
        {
            std::ostringstream oss;
            oss << val;
            return oss.str();
        }
    }

    template <typename T> std::string to_string_kv(const std::vector<T> &vec)
    {
        std::ostringstream oss;
        oss << "[";
        for (size_t i = 0; i < vec.size(); ++i)
        {
            oss << vec[i];
            if (i + 1 < vec.size())
                oss << ", ";
        }
        oss << "]";
        return oss.str();
    }

    std::string format_core(std::string_view fmt, const std::vector<std::string> &args)
    {
        std::string result;
        result.reserve(fmt.size() + args.size() * 16);

        size_t i = 0;
        while (i < fmt.size())
        {
            if (fmt[i] == '{')
            {
                if (i + 1 < fmt.size() && fmt[i + 1] == '{')
                {
                    result.push_back('{');
                    i += 2;
                    continue;
                }

                size_t close_pos = fmt.find('}', i);
                if (close_pos == std::string_view::npos)
                {
                    result.append(fmt.substr(i));
                    break;
                }

                size_t idx = 0;
                bool valid_num = true;
                for (size_t k = i + 1; k < close_pos; ++k)
                {
                    if (fmt[k] >= '0' && fmt[k] <= '9')
                    {
                        idx = idx * 10 + (fmt[k] - '0');
                    }
                    else
                    {
                        valid_num = false;
                        break;
                    }
                }

                if (valid_num && idx < args.size())
                {
                    result.append(args[idx]);
                }
                else
                {
                    result.append(fmt.substr(i, close_pos - i + 1));
                }
                i = close_pos + 1;
            }
            else if (fmt[i] == '}' && i + 1 < fmt.size() && fmt[i + 1] == '}')
            {
                result.push_back('}');
                i += 2;
            }
            else
            {
                result.push_back(fmt[i]);
                i++;
            }
        }
        return result;
    }

    template <typename... Args> std::string format(std::string_view fmt, const Args &...args)
    {
        std::vector<std::string> converted_args = {to_string_kv(args)...};
        return format_core(fmt, converted_args);
    }
};

#ifdef NDEBUG
#define LOG_TRACE(msg, ...)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
    } while (0)
#define LOG_DEBUG(msg, ...)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
    } while (0)
#else
#define LOG_TRACE(msg, ...) LLogger::LLogger::getInstance().log(LLogger::Level::TRACE, msg, ##__VA_ARGS__)
#define LOG_DEBUG(msg, ...) LLogger::LLogger::getInstance().log(LLogger::Level::DEBUG, msg, ##__VA_ARGS__)
#endif

#define LOG_INFO(msg, ...) LLogger::LLogger::getInstance().log(LLogger::Level::INFO, msg, ##__VA_ARGS__)
#define LOG_WARNING(msg, ...) LLogger::LLogger::getInstance().log(LLogger::Level::WARNING, msg, ##__VA_ARGS__)
#define LOG_ERROR(msg, ...) LLogger::LLogger::getInstance().log(LLogger::Level::ERROR, msg, ##__VA_ARGS__)

} // namespace LLogger
