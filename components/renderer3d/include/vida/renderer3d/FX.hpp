#pragma once

#include "vida/core/Color.hpp"
#include "vida/core/Math.hpp"

namespace Vida {

enum class FX {
  Unlit,
  Lit,
  Outline,
  Transparent,
  Pulse,
  Dissolve,
  Fog,
};

struct FXParams {
  // Outline
  ColorRGBA outline_color = ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
  float outline_width = 1.05f;

  // Lit
  Vec3 light_dir = Vec3(1.0f, 2.0f, 1.0f);
  Vec3 light_color = Vec3(1.0f, 1.0f, 1.0f);
  float ambient = 0.2f;

  // Transparent
  float alpha = 0.5f;

  // Pulse
  float pulse_speed = 3.0f;

  // Dissolve
  float dissolve_speed = 0.5f;

  // Fog
  ColorRGBA fog_color = ColorRGBA(0.5f, 0.5f, 0.5f, 1.0f);
  float fog_near = 5.0f;
  float fog_far = 50.0f;
};

} // namespace Vida
