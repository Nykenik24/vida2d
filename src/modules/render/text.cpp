#include "vida2d/render/text.hpp"

namespace Vida2D {
namespace Render {

bool Font::SetSize(float size) {
  return ttf_font && TTF_SetFontSize(ttf_font, size);
}

Text::Text(Text &&o) noexcept : text_obj(o.text_obj) { o.text_obj = nullptr; }
Text &Text::operator=(Text &&o) noexcept {
  if (this != &o) {
    TTF_DestroyText(text_obj);
    text_obj = o.text_obj;
    o.text_obj = nullptr;
  }
  return *this;
}

bool Text::SetString(const std::string &str) {
  return text_obj && TTF_SetTextString(text_obj, str.c_str(), str.length());
}

bool Text::Draw(Vector2 pos) {
  return text_obj && TTF_DrawRendererText(text_obj, pos.x, pos.y);
}

bool Text::SetColor(Color color) {
  return text_obj &&
         TTF_SetTextColor(text_obj, color.r, color.g, color.b, color.a);
}

} // namespace Render
} // namespace Vida2D
