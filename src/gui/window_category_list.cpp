#include "window_category_list.hpp"

#include <fmt/base.h>
#include <imgui.h>
#include <todo/todo_controller.hpp>

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
    ImGui::Dummy({1.0f, 10.0f});
    bool selected = todoController->getCurrentCategory()->id == -1;
    // TODO when all is selected and you click the completed button on a todo, the category of that todo is loading instead of the all one
    if (ImGui::Selectable("All", selected)) {
        auto cat = std::make_shared<Category>();
        todoController->setCurrentCategory(cat);
    }

    style->popFont();

    // Todo add something to add a new category. maybe just an inputfield and done
    // Calculate the available height below the text content
    float availableHeight = ImGui::GetContentRegionAvail().y;
    // Set the cursor position to the bottom of the window body
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + availableHeight - ImGui::GetFrameHeightWithSpacing());


    // style for input
    ImGui::GetStyle().FrameRounding = 6.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(9.0f, 0.0f));                   // Inside padding
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));          // Set inner padding
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);                       // Set border size
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));         // Set button color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));  // Set button color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));   // Set button color
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));         // Set border color
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));        // Set button color

    static char inputCategory[256];
    ImGui::SetNextItemWidth(180.0f);
    ImGui::InputTextWithHint("##addCategory", "Enter new category", inputCategory, IM_ARRAYSIZE(inputCategory));
    ImGui::SameLine();
    // Add a button at the bottom
    if (ImGui::Button(" + ")) {
        // Button action here
    }

    ImGui::PopStyleColor(5);
    ImGui::PopStyleVar(3);

    ImGui::PopStyleColor(3);
    ImGui::PopStyleVar();

    ImGui::End();
    ImGui::PopStyleColor();
}

}  // namespace TodoApp
