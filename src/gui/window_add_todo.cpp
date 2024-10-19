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

    // input text field
    static char input[256];
    ImGui::SetNextItemWidth(300.0f);
    style->pushInputText();
    ImGui::InputTextWithHint("##AddTodoText", "Enter new todo", input, IM_ARRAYSIZE(input));
    style->popInputText();

    // combo box
    // i hate the static int here... I hate static, get rid of it
    auto categories = todoController->getAllCategories();
    static int selectedCategory = categories.begin()->first;
    // there is no actual category with -1, its for All. so it can't be shown as combo item, therefor this "thing"
    if (todoController->hasChanges && todoController->getCurrentCategory()->id != -1) {
        selectedCategory = todoController->getCurrentCategory()->id;
        todoController->hasChanges = false;
    } else if (todoController->hasChanges) {
        selectedCategory = todoController->getAllCategories().begin()->first;
        todoController->hasChanges = false;
    }

    style->pushComboBox();
    ImGui::SameLine();
    ImGui::SetNextItemWidth(120.0f);
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
    style->popComboBox();

    // add button
    style->pushButton();
    ImGui::SameLine();
    if (ImGui::Button("+ Add Todo")) {
        // check if input is empty and if so, do nothing.
        if (input[0] != 0) {
            auto todo = std::make_unique<Todo>();
            todo->category.id = categories.at(selectedCategory)->id;
            todo->category.name = categories.at(selectedCategory)->name;
            todo->text = std::string(input);

            todoController->add(std::move(todo));
            // // empty input
            memset(input, 0, sizeof(input));
        }
    }
    style->popButton();

    style->popWindowAddTodo();
    ImGui::End();

}

}  // namespace TodoApp