#pragma once

#include "imgui.h"

namespace Vida {
namespace UI {
extern ImFont *FontUI;
extern ImFont *FontUIBold;
extern ImFont *FontMono;

void InitStyle();
void InitFonts();

void DrawUI(/*ImTextureID viewport_texture, */ bool viewport_focused,
            bool viewport_hovered);
} // namespace UI
} // namespace Vida
