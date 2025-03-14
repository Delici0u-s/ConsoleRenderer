#ifndef TIMER_H
#define TIMER_H

#include <chrono>

// Uncomment the next line if you want to use high_resolution_clock instead of steady_clock
// #define USE_HIGH_RES_CLOCK

class Timer {
public:
#ifdef USE_HIGH_RES_CLOCK
  using Clock = std::chrono::high_resolution_clock;
#else
  using Clock = std::chrono::steady_clock;
#endif
  using TimePoint = typename Clock::time_point;

  // Constructor: initialize timer start point.
  Timer() noexcept : m_start(Clock::now()) {}

  // Reset the timer without returning the elapsed time.
  void reset() noexcept { m_start = Clock::now(); }

  // Returns the elapsed time since the last reset.
  // The default duration is std::chrono::duration<double> for sub-second precision.
  template <typename Duration = std::chrono::duration<double>>
  double elapsed() const noexcept {
    return std::chrono::duration_cast<Duration>(Clock::now() - m_start).count();
  }

  // Lap: Returns the elapsed time since the last reset and resets the timer.
  double lap() noexcept {
    auto now = Clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(now - m_start).count();
    m_start = now;
    return elapsedTime;
  }

private:
  TimePoint m_start;
};

#endif // TIMER_H
