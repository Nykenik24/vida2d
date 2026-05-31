#pragma once

namespace Vida2D {
namespace Time {
double GetDelta();

class Timer {
public:
  Timer(double duration);
  Timer(Timer &&) = default;
  Timer(const Timer &) = default;
  Timer &operator=(Timer &&) = default;
  Timer &operator=(const Timer &) = default;
  ~Timer() = default;

  bool Done();
  void SetDuration(double duration);
  double GetDuration() const;
  double Left();
  double Elapsed();

private:
  double duration;
  double t;
};

inline Timer::Timer(double duration) : duration(duration), t(0) {}
inline void Timer::SetDuration(double duration) { this->duration = duration; }
inline double Timer::GetDuration() const { return duration; }
} // namespace Time
} // namespace Vida2D
