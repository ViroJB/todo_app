#include "window_add_todo.hpp"

#include <fmt/base.h>
#include <imgui.h>
#include <todo/todo_controller.hpp>

#include "gui_style.hpp"

namespace TodoApp {

void WindowAddTodo::draw(std::shared_ptr<GuiStyle>& style, const std::shared_ptr<TodoController>& todoController) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.25f, io.DisplaySize.y * 0.80f});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.75f, io.DisplaySize.y * 0.20f});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 1.0f));

    ImGui::Begin("AddTodo", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    style->pushFont(FontType::Header3);
    ImGui::Text(" Add New Todo");
    style->popFont();
    ImGui::NewLine();

    // style for input
    ImGui::GetStyle().FrameRounding = 6.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 10.0f));          // Set inner padding
    ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1.0f);                       // Set border size
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));         // Set button color
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));  // Set button color
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));   // Set button color
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.5f, 0.5f, 0.5f));         // Set border color
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));        // Set button color

    // input text field
    static char input[256];
    ImGui::SetNextItemWidth(300.0f);
    ImGui::InputTextWithHint("##AddTodoText", "Enter new todo", input, IM_ARRAYSIZE(input));
    ImGui::SameLine();

    // combo box
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));  // Set button color
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));  // Green for selected item
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, ImVec4(0.2f, 0.2f, 0.2f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));  // Darker green when active
    ImGui::PushStyleColor(ImGuiCol_PopupBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));  // Dark blue background for the popup
    ImGui::SetNextItemWidth(120.0f);

    // i hate the static int here... i hate static, get rid of it
    auto categories = todoController->getAllCategories();
    static int selectedCategory = categories.begin()->first;
    if (todoController->hasChanges && todoController->getCurrentCategory()->id != -1) {
        selectedCategory = todoController->getCurrentCategory()->id;
        todoController->hasChanges = false;
    }

    if (ImGui::BeginCombo("##CategoriesCombo", categories.at(selectedCategory)->name.c_str())) {
        for (const auto& category : categories) {
            bool selected = (selectedCategory == category.first);

            if (ImGui::Selectable(category.second->name.c_str(), selected)) {
                selectedCategory = category.second->id;
                fmt::print("category changed: {}, id: {}\n", category.second->name, selectedCategory);
            }
        }

        ImGui::EndCombo();
    }

    ImGui::SameLine();
    ImGui::PopStyleColor(7);

    // TODO fix the save button
    // add button
    if (ImGui::Button("+ Add Todo")) {
        // check if input is empty and if so, do nothing.
        if (sizeof(input) / sizeof(input[0]) != 0) {
            // std::string tempCat(categories[item_current]);
            // auto tempCat2 = todoController->getCategoryByName(tempCat);
            // auto todo = std::make_unique<Todo>();
            // todo->category = Category{tempCat2->id, tempCat2->name};
            // todo->text = std::string(input);
            //
            // todoController->add(std::move(todo));
            // // empty input
            // memset(input, 0, sizeof(input));
        }
    }

    // end style stuff
    ImGui::GetStyle().FrameRounding = 3.0f;
    ImGui::PopStyleVar(2);
    ImGui::PopStyleColor(5);

    ImGui::End();
    ImGui::PopStyleColor();
}

}  // namespace TodoApp