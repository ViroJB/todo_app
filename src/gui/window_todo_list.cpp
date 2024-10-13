#include "window_todo_list.hpp"

#include <imgui.h>

namespace TodoApp {

void WindowTodoList::draw(std::map<int, Todo>* todoList) {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.3f, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.7f, io.DisplaySize.y * 0.9f});
    ImGui::Begin("Todo's", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    // ImGui::Begin("Todo's", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground);
    ImGui::Text("Todos");
    ImGui::NewLine();

    if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable)) {
        ImGui::TableSetupColumn("A0");
        ImGui::TableSetupColumn("A1", ImGuiTableFlags_SizingFixedFit);

        const float rowHeight = ImGui::GetTextLineHeightWithSpacing() * 1.3f;
        for (const auto& [id, todo] : *todoList) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text(todo.status.c_str());

            ImGui::TableNextColumn();

            if (ImGui::BeginTable("table_nested2", 1)) {
                ImGui::TableSetupColumn("A1");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);
                ImGui::TableNextColumn();
                ImGui::Text(todo.title.c_str());
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);
                ImGui::TableNextColumn();
                ImGui::Text(todo.description.c_str());

                ImGui::EndTable();
            }
        }
        ImGui::EndTable();
    }

    ImGui::NewLine();

    ImGui::End();
}

}  // namespace TodoApp
