#include "gui_style.hpp"

#include <imgui.h>

namespace TodoApp {

void GuiStyle::load() {
    ImGuiStyle& style = ImGui::GetStyle();
    style.FrameRounding = 3.f; // Set global frame rounding to 5 pixels
    style.WindowBorderSize = 0.0f;
}

} // TodoApp