#include "gui_style.hpp"

#include <imgui.h>

namespace TodoApp {

void GuiStyle::load() {
    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();

    style.FrameRounding = 3.f;
    style.WindowBorderSize = 0.0f;

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(10.0f, 10.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(30.0f, 20.0f));

    loadFonts();
}

void GuiStyle::loadFonts() {
    ImGuiIO& io = ImGui::GetIO();

    auto normal = io.Fonts->AddFontFromFileTTF("fonts/Inter_24pt-Regular.ttf", 22.0f);
    auto bold = io.Fonts->AddFontFromFileTTF("fonts/Inter_24pt-Bold.ttf", 22.0f);
    auto header1 = io.Fonts->AddFontFromFileTTF("fonts/Inter_24pt-Bold.ttf", 45.0f);
    auto header2 = io.Fonts->AddFontFromFileTTF("fonts/Inter_24pt-Bold.ttf", 33.0f);
    auto header3 = io.Fonts->AddFontFromFileTTF("fonts/Inter_24pt-Bold.ttf", 28.0f);

    fonts[FontType::Normal] = normal;
    fonts[FontType::Bold] = bold;
    fonts[FontType::Header1] = header1;
    fonts[FontType::Header2] = header2;
    fonts[FontType::Header3] = header3;

    io.FontDefault = fonts[FontType::Normal];
}

void GuiStyle::pushFont(const FontType type) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::PushFont(fonts[type]);
}

void GuiStyle::popFont() { ImGui::PopFont(); }

}  // namespace TodoApp