#include "window_category_list.hpp"

#include <fmt/base.h>
#include <imgui.h>

#include <todo/todo_controller.hpp>

#include "gui_style.hpp"

namespace TodoApp {

// TODO show amount of todos under each category
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
        bool selected = category->name == todoController->getCurrentCategory()->name;
        std::string tmpText = truncateString(category->name, 210.0f);
        if (ImGui::Selectable(tmpText.c_str(), selected, ImGuiSelectableFlags_None, ImVec2(210.0f, 0.0f))) {
            todoController->setCurrentCategory(category);
        }
        // only show tooltip with the name if it has "..." in it, aka it was truncated
        if (ImGui::IsItemHovered() && tmpText.find("...") != std::string::npos) {
            ImGui::SetTooltip(category->name.c_str());
        }
        if (ImGui::BeginPopupContextItem()) {  // this actually opens a context menu on right click
            if (ImGui::MenuItem("Delete")) {
                todoController->deleteCategory(category);
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
    if (ImGui::InputTextWithHint("##addCategory", "Enter new category", inputCategory, IM_ARRAYSIZE(inputCategory), ImGuiInputTextFlags_EnterReturnsTrue)) {
        // on pressing enter
        todoController->addCategory(std::string(inputCategory));
        memset(inputCategory, 0, sizeof(inputCategory));
    }
    style->popInputText();

    ImGui::SameLine();
    style->pushButton();
    if (ImGui::Button(" + ")) {
        if (inputCategory[0] != 0) {
            todoController->addCategory(std::string(inputCategory));
            memset(inputCategory, 0, sizeof(inputCategory));
        }
    }
    style->popButton();

    style->popInputForm();

    style->popWindowCategoryList();
    ImGui::End();
}

// need to move it somewhere else, could need it in different places
std::string WindowCategoryList::truncateString(const std::string& text, float maxWidth) {
    const float ellipsisWidth = ImGui::CalcTextSize("...").x;
    std::string result;
    float currentWidth = 0.0f;

    for (size_t i = 0; i < text.size(); ++i) {
        const char* nextChar = text.c_str() + i;
        ImVec2 charSize = ImGui::CalcTextSize(nextChar, nextChar + 1);

        // check if adding next char would exceed the available width
        if (currentWidth + charSize.x + ellipsisWidth > maxWidth) {
            result += "...";
            break;
        }

        // add char
        result += text[i];
        currentWidth += charSize.x;
    }

    // return original if no changes needed
    if (result.empty()) {
        return text;
    }

    return result;
}

}  // namespace TodoApp
