#include "window_category_list.hpp"

#include <fmt/base.h>
#include <imgui.h>
#include <todo/todo_controller.h>

#include "gui_style.hpp"

namespace TodoApp {

void WindowCategoryList::draw(const std::map<int, std::string>& categories, GuiStyle& style) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.25f, io.DisplaySize.y});
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    ImGui::Begin("Categories", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    style.pushFont(FontType::Header2);
    ImGui::Text("Categories");
    style.popFont();

    ImGui::NewLine();
    style.pushFont(FontType::Bold);
    for (auto [id, category] : categories) {
        const char* cat = category.c_str();
        if (ImGui::Selectable(cat)) {
            fmt::print("{}\n", cat);
        }
    }
    style.popFont();

    ImGui::End();
    ImGui::PopStyleColor();
}

}  // namespace TodoApp
