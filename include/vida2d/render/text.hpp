#pragma once
#include "vida2d.hpp"
#include "vida2d/color.hpp"
#include "vida2d/vec.hpp"
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

namespace Vida2D {
namespace Render {
class Font {
public:
  Font() = default;
  explicit Font(const std::string &path, float size);
  ~Font();

  Font(const Font &) = delete;
  Font &operator=(const Font &) = delete;
  Font(Font &&o) noexcept : ttf_font(o.ttf_font) { o.ttf_font = nullptr; }
  Font &operator=(Font &&o) noexcept {
    if (this != &o) {
      TTF_CloseFont(ttf_font);
      ttf_font = o.ttf_font;
      o.ttf_font = nullptr;
    }
    return *this;
  }

  bool SetSize(float size);
  TTF_Font *Raw() const { return ttf_font; }
  bool Valid() const { return ttf_font != nullptr; }

private:
  TTF_Font *ttf_font = nullptr;
};

inline Font::Font(const std::string &path, float size) {
  ttf_font = TTF_OpenFont(path.c_str(), size);
}

inline Font::~Font() { TTF_CloseFont(ttf_font); }

class Text {
public:
  Text() = default;
  Text(Font &font, std::string str);
  Text(Font &font, std::string str, Color color);
  ~Text();

  Text(const Text &) = delete;
  Text &operator=(const Text &) = delete;
  Text(Text &&) noexcept;
  Text &operator=(Text &&) noexcept;

  bool SetString(const std::string &str);
  template <typename... Args> bool SetStringF(const char *fmt, Args &&...args) {
    int size = std::snprintf(nullptr, 0, fmt, std::forward<Args>(args)...);
    if (size < 0)
      return false;
    std::string buf(size + 1, '\0');
    std::snprintf(buf.data(), buf.size(), fmt, std::forward<Args>(args)...);
    buf.resize(size);
    return SetString(buf);
  }
  bool Draw(Vector2 pos);
  bool Valid() const { return text_obj != nullptr; }
  bool SetColor(Color color);

private:
  TTF_Text *text_obj = nullptr;
};

inline Text::Text(Font &font, std::string str) {
  if (!font.Valid())
    return;
  text_obj = TTF_CreateText(Context::GetInstance().text_engine, font.Raw(),
                            str.c_str(), str.length());
}

inline Text::Text(Font &font, std::string str, Color color) {
  if (!font.Valid())
    return;
  text_obj = TTF_CreateText(Context::GetInstance().text_engine, font.Raw(),
                            str.c_str(), str.length());
  if (text_obj)
    SetColor(color);
}

inline Text::~Text() { TTF_DestroyText(text_obj); }
} // namespace Render
} // namespace Vida2D
