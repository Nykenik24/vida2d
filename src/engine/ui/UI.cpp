#include "vida/engine/ui/UI.hpp"
#include "imgui.h"
#include "imgui_internal.h"

namespace Vida {
namespace UI {
ImFont *FontUI = nullptr;
ImFont *FontUIBold = nullptr;
ImFont *FontMono = nullptr;

void InitStyle() {
  ImGuiStyle &style = ImGui::GetStyle();
  ImVec4 *colors = style.Colors;

  // ###########
  // # Palette #
  // ###########

  // Background family
  const ImVec4 bg_deep = ImVec4(0.10f, 0.08f, 0.09f, 1.00f);   // #191416
  const ImVec4 bg_base = ImVec4(0.14f, 0.11f, 0.12f, 1.00f);   // #241D1F
  const ImVec4 bg_raised = ImVec4(0.19f, 0.15f, 0.17f, 1.00f); // #30262B
  const ImVec4 bg_hover = ImVec4(0.25f, 0.20f, 0.22f, 1.00f);  // #403338

  // Surface / border
  const ImVec4 border = ImVec4(0.31f, 0.24f, 0.27f, 1.00f); // #4F3D45
  const ImVec4 separator = ImVec4(0.25f, 0.20f, 0.22f, 1.00f);

  // Accent (warm rose)
  const ImVec4 accent = ImVec4(0.83f, 0.39f, 0.55f, 1.00f);        // #D4638C
  const ImVec4 accent_hover = ImVec4(0.91f, 0.48f, 0.64f, 1.00f);  // #E87AA3
  const ImVec4 accent_active = ImVec4(0.70f, 0.31f, 0.46f, 1.00f); // #B35075
  const ImVec4 accent_dim = ImVec4(0.83f, 0.39f, 0.55f, 0.28f);
  const ImVec4 accent_subtle = ImVec4(0.83f, 0.39f, 0.55f, 0.12f);

  // Text
  const ImVec4 text_primary = ImVec4(0.94f, 0.91f, 0.92f, 1.00f);   // #F0E8EB
  const ImVec4 text_secondary = ImVec4(0.66f, 0.58f, 0.61f, 1.00f); // #A8959C
  const ImVec4 text_disabled = ImVec4(0.42f, 0.37f, 0.39f, 1.00f);

  // ##########
  // # Colors #
  // ##########

  colors[ImGuiCol_Text] = text_primary;
  colors[ImGuiCol_TextDisabled] = text_disabled;

  colors[ImGuiCol_WindowBg] = bg_base;
  colors[ImGuiCol_ChildBg] = bg_deep;
  colors[ImGuiCol_PopupBg] = bg_raised;

  colors[ImGuiCol_Border] = border;
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

  colors[ImGuiCol_FrameBg] = bg_deep;
  colors[ImGuiCol_FrameBgHovered] = bg_hover;
  colors[ImGuiCol_FrameBgActive] = accent_dim;

  colors[ImGuiCol_TitleBg] = bg_deep;
  colors[ImGuiCol_TitleBgActive] = bg_deep;
  colors[ImGuiCol_TitleBgCollapsed] = bg_deep;

  colors[ImGuiCol_MenuBarBg] = bg_deep;

  colors[ImGuiCol_ScrollbarBg] = bg_deep;
  colors[ImGuiCol_ScrollbarGrab] = border;
  colors[ImGuiCol_ScrollbarGrabHovered] = text_disabled;
  colors[ImGuiCol_ScrollbarGrabActive] = accent;

  colors[ImGuiCol_CheckMark] = accent_hover;

  colors[ImGuiCol_SliderGrab] = accent;
  colors[ImGuiCol_SliderGrabActive] = accent_hover;

  colors[ImGuiCol_Button] = bg_raised;
  colors[ImGuiCol_ButtonHovered] = bg_hover;
  colors[ImGuiCol_ButtonActive] = accent_dim;

  colors[ImGuiCol_Header] = accent_subtle;
  colors[ImGuiCol_HeaderHovered] = accent_dim;
  colors[ImGuiCol_HeaderActive] = accent;

  colors[ImGuiCol_Separator] = separator;
  colors[ImGuiCol_SeparatorHovered] = accent;
  colors[ImGuiCol_SeparatorActive] = accent_hover;

  colors[ImGuiCol_ResizeGrip] = accent_subtle;
  colors[ImGuiCol_ResizeGripHovered] = accent_dim;
  colors[ImGuiCol_ResizeGripActive] = accent;

  colors[ImGuiCol_Tab] = bg_deep;
  colors[ImGuiCol_TabHovered] = bg_hover;
  colors[ImGuiCol_TabActive] = bg_raised;
  colors[ImGuiCol_TabUnfocused] = bg_deep;
  colors[ImGuiCol_TabUnfocusedActive] = bg_base;
  colors[ImGuiCol_TabSelectedOverline] = accent;

  colors[ImGuiCol_DockingPreview] = accent_dim;
  colors[ImGuiCol_DockingEmptyBg] = bg_deep;

  colors[ImGuiCol_PlotLines] = accent;
  colors[ImGuiCol_PlotLinesHovered] = accent_hover;
  colors[ImGuiCol_PlotHistogram] = accent;
  colors[ImGuiCol_PlotHistogramHovered] = accent_hover;

  colors[ImGuiCol_TableHeaderBg] = bg_deep;
  colors[ImGuiCol_TableBorderStrong] = border;
  colors[ImGuiCol_TableBorderLight] = separator;
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.02f);

  colors[ImGuiCol_TextSelectedBg] = accent_dim;
  colors[ImGuiCol_DragDropTarget] = accent_hover;
  colors[ImGuiCol_NavHighlight] = accent;
  colors[ImGuiCol_NavWindowingHighlight] = accent;
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.08f, 0.08f, 0.10f, 0.78f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.08f, 0.08f, 0.10f, 0.72f);

  // #####################
  // # Layout & rounding #
  // #####################

  style.WindowPadding = ImVec2(12.0f, 10.0f);
  style.FramePadding = ImVec2(8.0f, 5.0f);
  style.CellPadding = ImVec2(6.0f, 4.0f);
  style.ItemSpacing = ImVec2(8.0f, 6.0f);
  style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
  style.IndentSpacing = 18.0f;
  style.ScrollbarSize = 10.0f;
  style.GrabMinSize = 10.0f;

  style.WindowRounding = 4.0f;
  style.ChildRounding = 2.0f;
  style.FrameRounding = 2.0f;
  style.PopupRounding = 4.0f;
  style.ScrollbarRounding = 8.0f;
  style.GrabRounding = 2.0f;
  style.TabRounding = 0.0f;

  style.WindowBorderSize = 1.5f;
  style.FrameBorderSize = 0.0f;
  style.PopupBorderSize = 1.0f;
  style.TabBorderSize = 0.0f;

  style.WindowMenuButtonPosition = ImGuiDir_None;
  style.ColorButtonPosition = ImGuiDir_Left;
}

ImFont *g_FontUI = nullptr;
ImFont *g_FontUIBold = nullptr;
ImFont *g_FontMono = nullptr;

void InitFonts() {
  ImGuiIO &io = ImGui::GetIO();

  io.Fonts->Clear();

  ImFontConfig cfg;
  cfg.OversampleH = 3;
  cfg.OversampleV = 2;
  cfg.PixelSnapH = false;

  // Primary UI font
  FontUI = io.Fonts->AddFontFromFileTTF("assets/fonts/Inter-Regular.ttf", 15.0f,
                                        &cfg);

  // Bold variant (used for panel headers, labels, etc.)
  FontUIBold =
      io.Fonts->AddFontFromFileTTF("assets/fonts/Inter-Bold.ttf", 15.0f, &cfg);

  // Monospace (console, code editor, log output)
  cfg.OversampleH = 2;
  FontMono = io.Fonts->AddFontFromFileTTF(
      "assets/fonts/JetBrainsMono-Regular.ttf", 14.0f, &cfg);

  io.Fonts->Build();
}

static void DrawMenuBar() {
  if (!ImGui::BeginMainMenuBar())
    return;

  if (ImGui::BeginMenu("File")) {
    ImGui::MenuItem("New Scene", "Ctrl+N");
    ImGui::MenuItem("Open Scene", "Ctrl+O");
    ImGui::Separator();
    ImGui::MenuItem("Save", "Ctrl+S");
    ImGui::MenuItem("Save As…", "Ctrl+Shift+S");
    ImGui::Separator();
    ImGui::MenuItem("Quit", "Alt+F4");
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Edit")) {
    ImGui::MenuItem("Undo", "Ctrl+Z");
    ImGui::MenuItem("Redo", "Ctrl+Y");
    ImGui::Separator();
    ImGui::MenuItem("Preferences…");
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("View")) {
    ImGui::MenuItem("Scene Hierarchy");
    ImGui::MenuItem("Inspector");
    ImGui::MenuItem("Console");
    ImGui::MenuItem("Asset Browser");
    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Help")) {
    ImGui::MenuItem("Documentation");
    ImGui::MenuItem("About Vida…");
    ImGui::EndMenu();
  }

  const float play_section_width = 140.0f;
  ImGui::SetCursorPosX(ImGui::GetContentRegionMax().x - play_section_width);

  ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
  if (ImGui::Button("  ▶  ")) { /* TODO: play */
  }
  ImGui::SameLine();
  if (ImGui::Button("  ⏸  ")) { /* TODO: pause */
  }
  ImGui::SameLine();
  if (ImGui::Button("  ⏹  ")) { /* TODO: stop */
  }
  ImGui::PopStyleColor();

  ImGui::EndMainMenuBar();
}

static void DrawDockspace() {
  const ImGuiViewport *vp = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(vp->WorkPos);
  ImGui::SetNextWindowSize(vp->WorkSize);
  ImGui::SetNextWindowViewport(vp->ID);

  ImGuiWindowFlags host_flags =
      ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoBackground;

  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("##vida_dockspace", nullptr, host_flags);
  ImGui::PopStyleVar(3);

  ImGuiID dockspace_id = ImGui::GetID("VidaDockspace");
  ImGui::DockSpace(dockspace_id, ImVec2(0, 0),
                   ImGuiDockNodeFlags_PassthruCentralNode);

  static bool layout_built = false;
  if (!layout_built) {
    layout_built = true;

    ImGui::DockBuilderRemoveNode(dockspace_id);
    ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
    ImGui::DockBuilderSetNodeSize(dockspace_id, vp->WorkSize);

    ImGuiID dock_center = dockspace_id;
    ImGuiID dock_left = ImGui::DockBuilderSplitNode(
        dock_center, ImGuiDir_Left, 0.20f, nullptr, &dock_center);
    ImGuiID dock_right = ImGui::DockBuilderSplitNode(
        dock_center, ImGuiDir_Right, 0.25f, nullptr, &dock_center);
    ImGuiID dock_bottom = ImGui::DockBuilderSplitNode(
        dock_center, ImGuiDir_Down, 0.25f, nullptr, &dock_center);

    ImGui::DockBuilderDockWindow("Scene", dock_left);
    ImGui::DockBuilderDockWindow("Viewport", dock_center);
    ImGui::DockBuilderDockWindow("Inspector", dock_right);
    ImGui::DockBuilderDockWindow("Console", dock_bottom);
    ImGui::DockBuilderDockWindow("Assets", dock_bottom);

    ImGui::DockBuilderFinish(dockspace_id);
  }

  ImGui::End();
}

static void DrawLeaf(const char *name, ImGuiTreeNodeFlags flags) {
  ImGui::TreeNodeEx(name, flags | ImGuiTreeNodeFlags_Leaf |
                              ImGuiTreeNodeFlags_Bullet |
                              ImGuiTreeNodeFlags_NoTreePushOnOpen);
}

static void DrawSceneHierarchy() {
  ImGui::Begin("Scene");

  static ImGuiTreeNodeFlags tree_flags =
      ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_DefaultOpen;

  if (ImGui::TreeNodeEx("Root", tree_flags)) {
    DrawLeaf("Camera", tree_flags);
    DrawLeaf("Directional Light", tree_flags);

    if (ImGui::TreeNodeEx("Environment", tree_flags)) {
      DrawLeaf("Terrain", tree_flags);
      DrawLeaf("Skybox", tree_flags);

      ImGui::TreePop();
    }

    ImGui::TreePop();
  }

  ImGui::End();
}

static void DrawViewport(ImTextureID viewport_texture, bool &out_focused,
                         bool &out_hovered) {
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
  ImGui::Begin("Viewport");

  ImVec2 size = ImGui::GetContentRegionAvail();

  ImGui::Image(viewport_texture, size, ImVec2(0, 1), ImVec2(1, 0));

  out_focused = ImGui::IsWindowFocused();
  out_hovered = ImGui::IsWindowHovered();

  ImGui::SetCursorPos(ImVec2(8, 28));
  ImGui::PushFont(FontMono);
  ImGui::TextDisabled("%.0f × %.0f", size.x, size.y);
  ImGui::PopFont();

  ImGui::End();
  ImGui::PopStyleVar();
}

static void DrawInspector() {
  ImGui::Begin("Inspector");

  // TODO: reflect selected entity's components
  ImGui::TextDisabled("No entity selected.");

  ImGui::End();
}

static void DrawConsole() {
  ImGui::Begin("Console");

  ImGui::PushFont(FontUIBold);
  if (ImGui::SmallButton("Clear")) { /* TODO */
  }
  ImGui::PopFont();
  ImGui::SameLine();
  ImGui::TextDisabled("|");
  ImGui::SameLine();
  ImGui::TextDisabled("0 errors  0 warnings"); // TODO: real counts

  ImGui::Separator();

  const float footer_height = ImGui::GetFrameHeightWithSpacing();
  ImGui::BeginChild("##log", ImVec2(0, -footer_height), false,
                    ImGuiWindowFlags_HorizontalScrollbar);

  ImGui::PushFont(FontMono);
  // TODO: iterate log entries
  ImGui::TextDisabled("[engine] Vida initialised.");
  ImGui::PopFont();

  if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    ImGui::SetScrollHereY(1.0f);

  ImGui::EndChild();

  ImGui::Separator();
  ImGui::PushFont(FontMono);
  static char cmd_buf[512] = {};
  ImGuiInputTextFlags input_flags = ImGuiInputTextFlags_EnterReturnsTrue;
  if (ImGui::InputText("##cmd", cmd_buf, sizeof(cmd_buf), input_flags)) {
    // TODO: dispatch cmd_buf
    cmd_buf[0] = '\0';
    ImGui::SetKeyboardFocusHere(-1);
  }
  ImGui::PopFont();

  ImGui::End();
}

static void DrawAssetBrowser() {
  ImGui::Begin("Assets");

  // TODO: file-tree on the left, thumbnail grid on the right
  ImGui::TextDisabled("No project open.");

  ImGui::End();
}

void DrawUI(/*ImTextureID viewport_texture, */ bool viewport_focused,
            bool viewport_hovered) {
  DrawMenuBar();
  DrawDockspace();

  DrawSceneHierarchy();
  // DrawViewport(viewport_texture, viewport_focused, viewport_hovered);
  DrawInspector();
  DrawConsole();
  DrawAssetBrowser();
}
} // namespace UI
} // namespace Vida
