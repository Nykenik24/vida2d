#pragma once

#include "vida/input/Key.hpp"
#include "vida/render/Renderer.hpp"
namespace Vida {
enum class EventType {
  LoopFirstEnter,
  LoopEnter,
  LoopExit,
  DrawFirstEnter,
  DrawEnter,
  DrawExit,
  KeyboardDown,
  KeyboardUp,
};

struct Event {
  EventType type;
  Renderer *render = nullptr;
  Key key = Key::None;

  Event(EventType type) : type(type) {};
  Event(EventType type, Renderer *render) : type(type), render(render) {};
  Event(EventType type, Key key) : type(type), key(key) {};
};
} // namespace Vida
