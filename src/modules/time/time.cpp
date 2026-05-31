#include "vida2d/time/time.hpp"
#include "vida2d.hpp"

namespace Vida2D {
namespace Time {
double GetDelta() { return Context::GetInstance().dt; }

bool Timer::Done() {
  t += GetDelta();
  if (t >= duration) {
    t -= duration;
    return true;
  }
  return false;
}

double Timer::Left() { return duration - t; }
double Timer::Elapsed() { return t; }
} // namespace Time
} // namespace Vida2D
