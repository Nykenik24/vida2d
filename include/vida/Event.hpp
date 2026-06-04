#pragma once

#include "vida/input/Key.hpp"
#include "vida/input/Mouse.hpp"
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
  MouseDown,
  MouseUp,
  MouseMoved,
  MouseDragged,
};

struct Event {
  EventType type;
  Renderer *render = nullptr;

  Key key = Key::None;
  MouseBttn mouse_bttn = MouseBttn::None;
  int mx = 0, my = 0;

  Event(EventType type) : type(type) {};
  Event(EventType type, Renderer *render) : type(type), render(render) {};
  Event(EventType type, Key key) : type(type), key(key) {};
  Event(EventType type, MouseBttn mbttn, int mx, int my)
      : type(type), mouse_bttn(mbttn), mx(mx), my(my) {};
};
} // namespace Vida
