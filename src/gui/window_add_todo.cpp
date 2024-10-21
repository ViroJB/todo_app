#include "window_add_todo.hpp"

#include <fmt/base.h>
#include <imgui.h>

#include <todo/todo_controller.hpp>

#include "gui_style.hpp"

namespace TodoApp {

// todo handle long category names in combo box
void WindowAddTodo::draw(std::shared_ptr<GuiStyle>& style, const std::shared_ptr<TodoController>& todoController) {
    style->pushWindowAddTodo();
    ImGui::Begin("AddTodo", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    style->pushFont(FontType::Header3);
    ImGui::Text(" Add New Todo");
    style->popFont();

    ImGui::NewLine();

    bool enterPressed = false;
    // todo is char needed here? or can we go with vector, so we don't need to specify a size
    // input text field
    static char input[256];
    // calculate size of the input field dynamically
    float availableWidth = ImGui::GetContentRegionAvail().x;
    float inputFieldWidth = availableWidth - 120.0f - 115.0f - ImGui::GetStyle().ItemSpacing.x * 2;
    ImGui::SetNextItemWidth(inputFieldWidth);
    style->pushInputText();
    if (ImGui::InputTextWithHint("##AddTodoText", "Enter new todo", input, IM_ARRAYSIZE(input),
                                 ImGuiInputTextFlags_EnterReturnsTrue)) {
        enterPressed = true;
    }
    style->popInputText();

    // combo box
    // i hate the static int here... I hate static, get rid of it
    auto categories = todoController->getAllCategories();
    static int selectedCategory = 0;

    // there is no actual category with -1, it's for All. so it can't be shown as combo item, therefor this "thing"
    if (todoController->hasChanges && todoController->getCurrentCategory()->id != -1) {
        selectedCategory = todoController->getCurrentCategory()->id;
        todoController->hasChanges = false;
    } else if (todoController->hasChanges) {
        // todo this is fucked again... always jumps back to the first in the list...
        // right... when categories is empty, we cant do that.
        if (!todoController->getAllCategories().empty()) {
            selectedCategory = todoController->getAllCategories().begin()->first;
        }
        todoController->hasChanges = false;
    }

    style->pushComboBox();
    ImGui::SameLine();
    ImGui::SetNextItemWidth(120.0f);
    std::string previewValue = categories.empty() ? "" : categories.at(selectedCategory)->name;
    if (ImGui::BeginCombo("##CategoriesCombo", previewValue.c_str())) {
        for (const auto& category : categories) {
            bool selected = (selectedCategory == category.first);

            if (ImGui::Selectable(category.second->name.c_str(), selected)) {
                selectedCategory = category.second->id;
                // fmt::print("category changed: {}, id: {}\n", category.second->name, selectedCategory);
            }
        }

        ImGui::EndCombo();
    }
    if (ImGui::IsItemFocused() && ImGui::IsKeyPressed(ImGuiKey_Enter)) {
        enterPressed = true;
    }
    style->popComboBox();

    // add button
    style->pushButton();
    ImGui::SameLine();
    if (ImGui::Button("+ Add Todo")) {
        enterPressed = true;
    }
    style->popButton();

    if (enterPressed) {
        if (input[0] != 0) {
            auto todo = std::make_unique<Todo>();
            todo->category.id = categories.at(selectedCategory)->id;
            todo->category.name = categories.at(selectedCategory)->name;
            todo->text = std::string(input);

            todoController->add(std::move(todo));
            // empty input
            memset(input, 0, sizeof(input));
        }
    }

    style->popWindowAddTodo();
    ImGui::End();
}

}  // namespace TodoApp