#include "window_todo_list.hpp"

#include <fmt/base.h>
#include <imgui.h>

#include "gui_style.hpp"

namespace TodoApp {

void WindowTodoList::draw(std::map<int, Todo>* todoList, GuiStyle style) {
    // using namespace ImGui;
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.25f, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.75f, io.DisplaySize.y * 0.80f});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.17f, 0.17f, 0.17f, 1.0f));

    ImGui::Begin("Todo's", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    style.pushFont(FontType::Header1);
    ImGui::Text("<category> Todos");
    style.popFont();
    ImGui::NewLine();

    if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("A0");
        ImGui::TableSetupColumn("A1");

        const float rowHeight = ImGui::GetTextLineHeightWithSpacing() * 1.5f;
        const float rowSpacing = 1.0f;
        for (const auto& [id, todo] : *todoList) {
            ImGui::TableNextRow();
            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImVec4(0.15f, 0.15f, 0.15f, 1.0f)));
            ImGui::TableNextColumn();
            std::string status = "  " + todo.status;
            ImGui::Text(status.c_str());

            ImGui::TableNextColumn();

            if (ImGui::BeginTable("table_nested2", 1, ImGuiTableFlags_SizingStretchProp)) {
                ImGui::TableSetupColumn("A1");
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);
                ImGui::TableNextColumn();
                ImGui::Text(todo.title.c_str());
                ImGui::TableNextRow(ImGuiTableRowFlags_None, rowHeight);
                ImGui::TableNextColumn();
                ImGui::Text(todo.description.c_str());

                ImGui::EndTable();
            }

            ImGui::TableNextRow(ImGuiTableRowFlags_None, rowSpacing);  // spacing row
        }

        ImGui::EndTable();
    }

    ImGui::End();

    ImGui::PopStyleColor();
}

}  // namespace TodoApp
