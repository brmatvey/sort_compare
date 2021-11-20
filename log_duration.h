#pragma once

#include <chrono>

class LogDuration {
public:
    // заменим имя типа std::chrono::steady_clock
    // с помощью using для удобства
    using Clock = std::chrono::steady_clock;

    LogDuration() = default;

    ~LogDuration() {
    }

    const double getDuration() const {
        auto l = std::chrono::duration_cast<std::chrono::microseconds>(Clock::now() - start_time_);
        return static_cast<double>(l.count()) / 1000.0;
    }

private:
    const Clock::time_point start_time_ = Clock::now();
};
