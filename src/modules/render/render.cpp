#include "vida2d/render/render.hpp"
#include "SDL3/SDL_render.h"
#include "vida2d.hpp"
#include "vida2d/macros.hpp"

namespace Vida2D {
namespace Render {
bool Point(Vector2 pos) {
  return SDL_RenderPoint(Context::GetInstance().GetRenderer(), pos.x, pos.y);
}

bool Line(Vector2 start, Vector2 end) {
  return SDL_RenderLine(Context::GetInstance().GetRenderer(), start.x, start.y,
                        end.x, end.y);
}

bool Rect(Vector2 pos, Vector2 size) {
  auto &ctx = Context::GetInstance();

  SDL_FRect rect;
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = size.x;
  rect.h = size.y;

  return SDL_RenderRect(ctx.GetRenderer(), &rect);
}

bool RectFill(Vector2 pos, Vector2 size) {
  auto &ctx = Context::GetInstance();

  SDL_FRect rect;
  rect.x = pos.x;
  rect.y = pos.y;
  rect.w = size.x;
  rect.h = size.y;

  return SDL_RenderFillRect(ctx.GetRenderer(), &rect);
}

bool Triangle(Vector2 p1, Vector2 p2, Vector2 p3) {
  auto &ctx = Context::GetInstance();

  V2D_CHECK(SDL_RenderLine(ctx.GetRenderer(), p1.x, p1.y, p2.x, p2.y));
  V2D_CHECK(SDL_RenderLine(ctx.GetRenderer(), p2.x, p2.y, p3.x, p3.y));
  V2D_CHECK(SDL_RenderLine(ctx.GetRenderer(), p3.x, p3.y, p1.x, p1.y));
  return true;
}

bool TriangleFill(Vector2 p1, Vector2 p2, Vector2 p3) {
  auto &ctx = Context::GetInstance();
  Color c;
  SDL_GetRenderDrawColor(ctx.GetRenderer(), &c.r, &c.g, &c.b, &c.a);

  SDL_FColor fc = {
      c.r / 255.0f,
      c.g / 255.0f,
      c.b / 255.0f,
      c.a / 255.0f,
  };

  SDL_Vertex verts[3] = {
      {{p1.x, p1.y}, fc, {0, 0}},
      {{p2.x, p2.y}, fc, {0, 0}},
      {{p3.x, p3.y}, fc, {0, 0}},
  };

  return SDL_RenderGeometry(ctx.GetRenderer(), NULL, verts, 3, NULL, 0);
}

bool Circle(Vector2 center, float radius) {
  auto &ctx = Context::GetInstance();

  int x = radius, y = 0, err = 0;
  float cx = center.x;
  float cy = center.y;
  SDL_Renderer *r = ctx.GetRenderer();
  while (x >= y) {
    V2D_CHECK(SDL_RenderPoint(r, cx + x, cy + y));
    V2D_CHECK(SDL_RenderPoint(r, cx + y, cy + x));
    V2D_CHECK(SDL_RenderPoint(r, cx - y, cy + x));
    V2D_CHECK(SDL_RenderPoint(r, cx - x, cy + y));
    V2D_CHECK(SDL_RenderPoint(r, cx - x, cy - y));
    V2D_CHECK(SDL_RenderPoint(r, cx - y, cy - x));
    V2D_CHECK(SDL_RenderPoint(r, cx + y, cy - x));
    V2D_CHECK(SDL_RenderPoint(r, cx + x, cy - y));
    if (err <= 0) {
      y++;
      err += 2 * y + 1;
    }
    if (err > 0) {
      x--;
      err -= 2 * x + 1;
    }
  }
  return true;
}

bool CircleFill(Vector2 center, float radius) {
  auto &ctx = Context::GetInstance();
  for (int dy = -radius; dy <= radius; dy++) {
    int dx = (int)SDL_sqrt(radius * radius - dy * dy);
    V2D_CHECK(SDL_RenderLine(ctx.GetRenderer(), center.x - dx, center.y + dy,
                             center.x + dx, center.y + dy));
  }
  return true;
}

bool SetColor(Color color) {
  return SDL_SetRenderDrawColor(Context::GetInstance().GetRenderer(), color.r,
                                color.g, color.b, color.a);
}

void SetBackgroundColor(Color color) {
  Context::GetInstance().SetClearColor(color);
}

bool Update() {
  auto &ctx = Context::GetInstance();
  return SDL_RenderPresent(ctx.GetRenderer());
}
} // namespace Render
} // namespace Vida2D
