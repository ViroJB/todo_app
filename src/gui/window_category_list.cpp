#include "window_category_list.hpp"

#include <fmt/base.h>
#include <imgui.h>
#include <todo/todo_controller.hpp>

#include "gui_style.hpp"

namespace TodoApp {

void WindowCategoryList::draw(std::shared_ptr<GuiStyle>& style, std::shared_ptr<TodoController>& todoController) {
    style->pushWindowCategoryList();
    ImGui::Begin("Categories", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    style->pushFont(FontType::Header2);
    ImGui::Text("Categories");
    style->popFont();

    ImGui::NewLine();

    style->pushFont(FontType::Bold);
    style->pushSelectableMenu();
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
    if (ImGui::Selectable("All", selected)) {
        auto cat = std::make_shared<Category>();
        todoController->setCurrentCategory(cat);
    }
    style->popSelectableMenu();
    style->popFont();

    // continue at the bottom of the window
    float availableHeight = ImGui::GetContentRegionAvail().y;
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + availableHeight - ImGui::GetFrameHeightWithSpacing());
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() - 10.0f);

    // input form
    style->pushInputForm();

    static char inputCategory[256];
    style->pushInputText();
    ImGui::SetNextItemWidth(180.0f);
    ImGui::InputTextWithHint("##addCategory", "Enter new category", inputCategory, IM_ARRAYSIZE(inputCategory));
    style->popInputText();

    ImGui::SameLine();
    style->pushButton();
    if (ImGui::Button(" + ")) {
        // TODO save category
    }
    style->popButton();

    style->popInputForm();

    style->popWindowCategoryList();
    ImGui::End();
}

}  // namespace TodoApp
