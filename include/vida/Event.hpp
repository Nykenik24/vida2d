#pragma once

namespace Vida {
enum class EventType {
  LoopEnter,
  LoopExit,
  DrawEnter,
  DrawExit,
};

union Event {
  EventType type;
};
} // namespace Vida
