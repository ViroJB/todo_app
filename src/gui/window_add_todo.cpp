#include "window_add_todo.hpp"

#include <imgui.h>

namespace TodoApp {

void WindowAddTodo::draw() {
    // TODO make this just another row in the todo list table?
    // TODO are the cells and rows customizable enough?
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.3f, io.DisplaySize.y * 0.9f});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.7f, io.DisplaySize.y * 0.1f});
    ImGui::Begin("AddTodo", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("Add New Todo");

    static char input[256];
    ImGui::InputTextWithHint("##AddTodoText", "Enter new todo", input, IM_ARRAYSIZE(input));
    ImGui::SameLine();
    const char* items[] = {"AAAA", "BBBB", "CCCC"};
    static int item_current = 0;
    ImGui::Combo("##CategoriesCombo", &item_current, items, IM_ARRAYSIZE(items));
    ImGui::SameLine();
    ImGui::Button("+ Add Todo");

    ImGui::End();
}

}  // namespace TodoApp