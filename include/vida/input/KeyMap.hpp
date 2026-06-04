#pragma once

#include "Key.hpp"
#include <GL/glut.h>
#include <optional>

namespace Vida {

inline std::optional<Key> KeyFromGlut(unsigned char k) {
  switch (k) {
  case ' ':
    return Key::Space;
  case '!':
    return Key::Exclamation;
  case '"':
    return Key::DoubleQuote;
  case '#':
    return Key::Hash;
  case '$':
    return Key::Dollar;
  case '%':
    return Key::Percent;
  case '&':
    return Key::Ampersand;
  case '\'':
    return Key::SingleQuote;
  case '(':
    return Key::LeftParen;
  case ')':
    return Key::RightParen;
  case '*':
    return Key::Asterisk;
  case '+':
    return Key::Plus;
  case ',':
    return Key::Comma;
  case '-':
    return Key::Minus;
  case '.':
    return Key::Period;
  case '/':
    return Key::Slash;

  case '0':
    return Key::Num0;
  case '1':
    return Key::Num1;
  case '2':
    return Key::Num2;
  case '3':
    return Key::Num3;
  case '4':
    return Key::Num4;
  case '5':
    return Key::Num5;
  case '6':
    return Key::Num6;
  case '7':
    return Key::Num7;
  case '8':
    return Key::Num8;
  case '9':
    return Key::Num9;

  case ':':
    return Key::Colon;
  case ';':
    return Key::Semicolon;
  case '<':
    return Key::Less;
  case '=':
    return Key::Equal;
  case '>':
    return Key::Greater;
  case '?':
    return Key::Question;
  case '@':
    return Key::At;

  case 'A':
    return Key::A;
  case 'B':
    return Key::B;
  case 'C':
    return Key::C;
  case 'D':
    return Key::D;
  case 'E':
    return Key::E;
  case 'F':
    return Key::F;
  case 'G':
    return Key::G;
  case 'H':
    return Key::H;
  case 'I':
    return Key::I;
  case 'J':
    return Key::J;
  case 'K':
    return Key::K;
  case 'L':
    return Key::L;
  case 'M':
    return Key::M;
  case 'N':
    return Key::N;
  case 'O':
    return Key::O;
  case 'P':
    return Key::P;
  case 'Q':
    return Key::Q;
  case 'R':
    return Key::R;
  case 'S':
    return Key::S;
  case 'T':
    return Key::T;
  case 'U':
    return Key::U;
  case 'V':
    return Key::V;
  case 'W':
    return Key::W;
  case 'X':
    return Key::X;
  case 'Y':
    return Key::Y;
  case 'Z':
    return Key::Z;

  case '[':
    return Key::LeftBracket;
  case '\\':
    return Key::Backslash;
  case ']':
    return Key::RightBracket;
  case '^':
    return Key::Caret;
  case '_':
    return Key::Underscore;
  case '`':
    return Key::Backtick;

  case 'a':
    return Key::a;
  case 'b':
    return Key::b;
  case 'c':
    return Key::c;
  case 'd':
    return Key::d;
  case 'e':
    return Key::e;
  case 'f':
    return Key::f;
  case 'g':
    return Key::g;
  case 'h':
    return Key::h;
  case 'i':
    return Key::i;
  case 'j':
    return Key::j;
  case 'k':
    return Key::k;
  case 'l':
    return Key::l;
  case 'm':
    return Key::m;
  case 'n':
    return Key::n;
  case 'o':
    return Key::o;
  case 'p':
    return Key::p;
  case 'q':
    return Key::q;
  case 'r':
    return Key::r;
  case 's':
    return Key::s;
  case 't':
    return Key::t;
  case 'u':
    return Key::u;
  case 'v':
    return Key::v;
  case 'w':
    return Key::w;
  case 'x':
    return Key::x;
  case 'y':
    return Key::y;
  case 'z':
    return Key::z;

  case '{':
    return Key::LeftBrace;
  case '|':
    return Key::Pipe;
  case '}':
    return Key::RightBrace;
  case '~':
    return Key::Tilde;

  case '\b':
    return Key::Backspace; // 0x08
  case '\t':
    return Key::Tab; // 0x09
  case '\r':
    return Key::Enter; // 0x0D
  case 0x1B:
    return Key::Escape;
  case 0x7F:
    return Key::Delete;

  default:
    return std::nullopt;
  }
}

inline std::optional<Key> KeyFromGlutSpecial(int k) {
  switch (k) {
  case GLUT_KEY_F1:
    return Key::F1;
  case GLUT_KEY_F2:
    return Key::F2;
  case GLUT_KEY_F3:
    return Key::F3;
  case GLUT_KEY_F4:
    return Key::F4;
  case GLUT_KEY_F5:
    return Key::F5;
  case GLUT_KEY_F6:
    return Key::F6;
  case GLUT_KEY_F7:
    return Key::F7;
  case GLUT_KEY_F8:
    return Key::F8;
  case GLUT_KEY_F9:
    return Key::F9;
  case GLUT_KEY_F10:
    return Key::F10;
  case GLUT_KEY_F11:
    return Key::F11;
  case GLUT_KEY_F12:
    return Key::F12;

  case GLUT_KEY_LEFT:
    return Key::Left;
  case GLUT_KEY_RIGHT:
    return Key::Right;
  case GLUT_KEY_UP:
    return Key::Up;
  case GLUT_KEY_DOWN:
    return Key::Down;

  case GLUT_KEY_PAGE_UP:
    return Key::PageUp;
  case GLUT_KEY_PAGE_DOWN:
    return Key::PageDown;
  case GLUT_KEY_HOME:
    return Key::Home;
  case GLUT_KEY_END:
    return Key::End;
  case GLUT_KEY_INSERT:
    return Key::Insert;

  default:
    return std::nullopt;
  }
}

inline void ModifiersFromGlut(int mods, Key *out, int &count) {
  count = 0;
  if (mods & GLUT_ACTIVE_SHIFT)
    out[count++] = Key::Shift;
  if (mods & GLUT_ACTIVE_CTRL)
    out[count++] = Key::Ctrl;
  if (mods & GLUT_ACTIVE_ALT)
    out[count++] = Key::Alt;
}

} // namespace Vida
