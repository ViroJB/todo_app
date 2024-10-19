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

void GuiStyle::pushWindowCategoryList() {
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({270.0f, ImGui::GetIO().DisplaySize.y});
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));  // Inside padding
}
void GuiStyle::popWindowCategoryList() {
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void GuiStyle::pushWindowTodoList() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({270.0f, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x - 270.0f, io.DisplaySize.y - 140.0f});
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.17f, 0.17f, 0.17f, 1.0f));
}
void GuiStyle::popWindowTodoList() {
    // ImGui::PopStyleVar();
    ImGui::PopStyleColor();
}

void GuiStyle::pushWindowAddTodo() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({270.0f, io.DisplaySize.y - 140.f});
    ImGui::SetNextWindowSize({io.DisplaySize.x - 270.0f, 140.0f});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20.0f, 20.0f));
}
void GuiStyle::popWindowAddTodo() {
    ImGui::PopStyleColor();
    ImGui::PopStyleVar();
}

void GuiStyle::pushInputForm() {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(9.0f, 0.0f));             // Inside padding
}
void GuiStyle::popInputForm() {
    ImGui::PopStyleVar();
}


void GuiStyle::pushInputText() {
    ImGui::GetStyle().FrameRounding = 6.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(9.0f, 0.0f));             // Inside padding
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));          // Set inner padding
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);                       // Set border size
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));         // Set border color
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));        // Set button color
}
void GuiStyle::popInputText() {
    ImGui::PopStyleColor(2);
    ImGui::PopStyleVar(3);
}

void GuiStyle::pushButton() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));          // Set inner padding
    // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    // ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));  // Set button color
    // ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));   // Set button color
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));         // Set border color
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);                       // Set border size
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));         // Set button color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));  // Set button color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));   // Set button color
}
void GuiStyle::popButton() {
    ImGui::PopStyleColor(4);
    ImGui::PopStyleVar(2);
}
void GuiStyle::pushComboBox() {
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));          // Set inner padding
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);                       // Set border size
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));  // Set button color
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));  // Green for selected item
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));  // Darker green when active
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));        // Set button color
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));         // Set border color
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));  // Dark blue background for the popup
}
void GuiStyle::popComboBox() {
    ImGui::PopStyleColor(9);
    ImGui::PopStyleVar(2);
}

void GuiStyle::pushFont(const FontType type) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::PushFont(fonts[type]);
}

void GuiStyle::pushSelectableMenu() {
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));                   // Inside padding
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));    // Hover color (red)
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));           // Selected color (green)
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.18f, 0.18f, 0.18f, 1.0f));  // Selected color (green)
}
void GuiStyle::popSelectableMenu() {
    ImGui::PopStyleVar();
    ImGui::PopStyleColor(3);
}

void GuiStyle::popFont() { ImGui::PopFont(); }

}  // namespace TodoApp