#include "vida2d/time/time.hpp"
#include "vida2d.hpp"

namespace Vida2D {
namespace Time {
double GetDelta() { return Context::GetInstance().GetDT(); }
} // namespace Time
} // namespace Vida2D
