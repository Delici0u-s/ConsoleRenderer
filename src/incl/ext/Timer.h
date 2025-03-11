#ifndef TIMER_H
#define TIMER_H

#include <chrono> // for std::chrono functions

class Timer {
private:
  // Type aliases to make accessing nested type easier
  using Clock = std::chrono::steady_clock;
  using Second = std::chrono::duration<double, std::ratio<1>>;

  std::chrono::time_point<Clock> m_beg{Clock::now()};

public:
  // reset Timer
  void reset() { m_beg = Clock::now(); }

  // return the elapsed time in Seconds
  // defaults to templae type std::chrono::seconds
  template <typename Duration = std::chrono::seconds> double elapsed() const {
    return std::chrono::duration_cast<Duration>(Clock::now() - m_beg).count();
  }

  double delapsed() const {
    return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
  }
};

#endif // !TIMER_H
