#include "window_todo_list.hpp"

#include <fmt/base.h>
#include <imgui.h>

#include <todo/todo_controller.hpp>

#include "gui_style.hpp"

namespace TodoApp {

void WindowTodoList::draw(std::shared_ptr<GuiStyle>& style, std::shared_ptr<TodoController>& todoController) {
    // using namespace ImGui;
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({io.DisplaySize.x * 0.25f, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.75f, io.DisplaySize.y * 0.80f});

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.17f, 0.17f, 0.17f, 1.0f));

    ImGui::Begin("Todo's", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);
    style->pushFont(FontType::Header1);
    std::string headline(todoController->getCurrentCategory()->name + " Todos");
    ImGui::Text(headline.c_str());
    style->popFont();
    ImGui::NewLine();

    if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("A0", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("A1");

        // const float rowHeight = ImGui::GetTextLineHeightWithSpacing() * 1.5f;
        const float rowSpacing = 1.0f;

        auto tempList = todoController->getAllByCategory(todoController->getCurrentCategory());
        for (auto it = tempList.rbegin(); it != tempList.rend(); ++it) {
            // for (const auto& [id, todo] : todoList) {
            ImGui::TableNextRow();
            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImVec4(0.15f, 0.15f, 0.15f, 1.0f)));

            ImGui::TableNextColumn();

            ImGui::Dummy({1.0f, 10.0f});
            ImGui::Dummy({13.0f, 1.0f});
            ImGui::SameLine();

            std::string label = "##radio" + std::to_string(it->first);
            if (ImGui::RadioButton(label.c_str(), it->second->completed)) {
                it->second->completed = !it->second->completed;
                fmt::print("Radio Button clicked. id: {}\n", it->first);

                auto todo = std::make_unique<Todo>(*it->second);
                fmt::print("tmp todo id: {}\n", todo->id);

                todoController->update(std::move(todo));
            }

            ImGui::Dummy({1.0f, 10.0f});

            ImGui::TableNextColumn();

            ImGui::Dummy({1.0f, 11.0f});
            // ImGui::Dummy({13.0f, 1.0f});

            if (it->second->completed) {
                // draw crossed out/strikethrough line for text with grey-ish color
                ImGui::PushStyleColor(ImGuiCol_Text, {0.4f, 0.4f, 0.4f, 1.0f});
                ImGui::Text(it->second->text.c_str());
                ImVec2 textPos = ImGui::GetItemRectMin();
                ImVec2 textSize = ImGui::CalcTextSize(it->second->text.c_str());

                ImVec2 strikePosStart = ImVec2(textPos.x - 2, textPos.y + textSize.y / 2);
                ImVec2 strikePosEnd = ImVec2(textPos.x + textSize.x + 2, textPos.y + textSize.y / 2);

                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                draw_list->AddLine(strikePosStart, strikePosEnd, IM_COL32(100, 100, 100, 255), 2.0f);
                ImGui::PopStyleColor();
            } else {
                ImGui::Text(it->second->text.c_str());
            }

            ImGui::TableNextRow(ImGuiTableRowFlags_None, rowSpacing);  // spacing row
        }

        ImGui::EndTable();
    }

    ImGui::End();

    ImGui::PopStyleColor();
}

}  // namespace TodoApp
