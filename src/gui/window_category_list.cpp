#include "window_category_list.hpp"

#include <fmt/base.h>
#include <imgui.h>
#include <todo/todo_controller.h>

#include "gui_style.hpp"

namespace TodoApp {

void WindowCategoryList::draw(std::shared_ptr<GuiStyle>& style, std::shared_ptr<TodoController>& todoController) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.25f, io.DisplaySize.y});
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    ImGui::Begin("Categories", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    style->pushFont(FontType::Header2);
    ImGui::Text("Categories");
    style->popFont();

    ImGui::NewLine();

    style->pushFont(FontType::Bold);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(20, 20));                   // Inside padding
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));    // Hover color (red)
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));           // Selected color (green)
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.18f, 0.18f, 0.18f, 1.0f));  // Selected color (green)

    auto categories = todoController->getAllCategories();

    for (const auto& [id, category] : categories) {
        const char* cat = category->name.c_str();
        bool selected = category->name == todoController->getCurrentCategory()->name;
        if (ImGui::Selectable(cat, selected)) {
            todoController->setCurrentCategory(category);
        }
        if (ImGui::BeginPopupContextItem()) {  // this actually opens a context menu on right click
            if (ImGui::MenuItem("Delete")) {
                // TODO handle...
            }
            ImGui::EndPopup();
        }
    }
    // Todo add another selectable for All Todos (just All maybe)
    ImGui::Dummy({1.0f, 10.0f});
    bool selected = todoController->getCurrentCategory()->id == -1;
    if (ImGui::Selectable("All", selected)) {
        auto cat = std::make_shared<Category>();
        todoController->setCurrentCategory(cat);
    }

    // Todo add something to add a new category. maybe just an inputfield and done
    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();
    style->popFont();

    ImGui::End();
    ImGui::PopStyleColor();
}

}  // namespace TodoApp
