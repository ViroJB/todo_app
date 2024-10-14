#include "window_add_todo.hpp"

#include <imgui.h>
#include <todo/todo.h>
#include <todo/todo_controller.h>

#include "gui_style.hpp"

namespace TodoApp {

void WindowAddTodo::draw(const std::vector<const char*>& categories, GuiStyle style ) {
    // TODO make this just another row in the todo list table?
    // TODO are the cells and rows customizable enough?
    // TODO if that doesn't work, we can calculate the high of the todo window with the list somehow and use that as next position

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.3f, io.DisplaySize.y * 0.85f});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.7f, io.DisplaySize.y * 0.15f});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.13f, 0.13f, 0.13f, 1.0f));

    ImGui::Begin("AddTodo", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    style.pushFont(FontType::Header2);
    ImGui::Text("Add New Todo");
    style.popFont();

    static char input[256];
    ImGui::SetNextItemWidth(350.0f);
    ImGui::InputTextWithHint("##AddTodoText", "Enter new todo", input, IM_ARRAYSIZE(input));
    ImGui::SameLine();

    static int item_current = 0;
    ImGui::SetNextItemWidth(150.0f);
    ImGui::Combo("##CategoriesCombo", &item_current, categories.data(), categories.size());
    ImGui::SameLine();
    if (ImGui::Button("+ Add Todo")) {
        // check if input is empty and if so, do nothing.
        if (sizeof(input) / sizeof(input[0]) == 0) {
            // array is empty
        }
        // get input and category and save item.
        Todo todo;
        todo.category_name = categories[item_current];
        todo.description = std::string(input);

        TodoController tc;
        tc.Add(todo);

        memset(input, 0, sizeof(input));
    }

    ImGui::End();
    ImGui::PopStyleColor();
}

}  // namespace TodoApp