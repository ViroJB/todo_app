#include "window_todo_list.hpp"

#include <fmt/base.h>
#include <imgui.h>

#include <todo/todo_controller.hpp>

#include "../fonts/IconsFontAwesome.h"
#include "gui_style.hpp"

namespace TodoApp {

void WindowTodoList::draw(std::shared_ptr<GuiStyle>& style, std::shared_ptr<TodoController>& todoController) {
    style->pushWindowTodoList();
    ImGui::Begin("Todos", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    style->pushFont(FontType::Header1);
    std::string headline = todoController->getCurrentCategory()->name.empty() ? "All" : todoController->getCurrentCategory()->name;
    headline = headline + " Todos";
    ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionMax().x - 5.0f);
    ImGui::Text(headline.c_str());
    ImGui::PopTextWrapPos();
    style->popFont();

    ImGui::NewLine();

    if (ImGui::BeginTable("table_nested1", 2, ImGuiTableFlags_SizingStretchProp)) {
        ImGui::TableSetupColumn("A0", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("A1");

        auto tempList = todoController->getAllByCategory(todoController->getCurrentCategory());
        for (auto it = tempList.rbegin(); it != tempList.rend(); ++it) {
            ImGui::TableNextRow();
            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0, ImGui::GetColorU32(ImVec4(0.15f, 0.15f, 0.15f, 1.0f)));

            ImGui::TableNextColumn();

            ImGui::Dummy({1.0f, 10.0f});
            // add another dummy if the text will be truncated
            if (ImGui::CalcTextSize(it->second->text.c_str()).x > (ImGui::GetWindowContentRegionMax().x - 105.0f)) {
                ImGui::Dummy({1.0f, 10.0f});
            }
            ImGui::Dummy({13.0f, 1.0f});
            ImGui::SameLine();

            style->pushFont(Awesome);
            if (it->second->completed) {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
                ImGui::Text(ICON_FA_CHECK_SQUARE);
                ImGui::PopStyleColor();
            } else {
                ImGui::Text(ICON_FA_SQUARE);
            }
            if (ImGui::IsItemClicked()) {
                it->second->completed = !it->second->completed;
                auto todo = std::make_unique<Todo>(*it->second);
                todoController->update(std::move(todo));
            }
            style->popFont();

            ImGui::TableNextColumn();

            ImGui::Dummy({1.0f, 11.0f});

            if (it->second->completed) {
                // if completed grey out the text
                ImGui::PushStyleColor(ImGuiCol_Text, {0.3f, 0.3f, 0.3f, 1.0f});
                ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionMax().x - 5.0f);
                ImGui::Text(it->second->text.c_str());
                ImGui::PopTextWrapPos();
                ImGui::PopStyleColor();

                // draw crossed out/strikethrough line for text (need to figure out how to do it with multiline)
                // ImVec2 textPos = ImGui::GetItemRectMin();
                // ImVec2 textSize = ImGui::CalcTextSize(it->second->text.c_str());
                //
                // ImVec2 strikePosStart = ImVec2(textPos.x - 2, textPos.y + textSize.y / 2);
                // ImVec2 strikePosEnd = ImVec2(textPos.x + textSize.x + 2, textPos.y + textSize.y / 2);
                //
                // ImDrawList* draw_list = ImGui::GetWindowDrawList();
                // draw_list->AddLine(strikePosStart, strikePosEnd, IM_COL32(100, 100, 100, 255), 2.0f);
            } else {
                ImGui::PushTextWrapPos(ImGui::GetWindowContentRegionMax().x - 5.0f);
                ImGui::Text(it->second->text.c_str());
                ImGui::PopTextWrapPos();
            }
            ImGui::Dummy({1.0f, 10.0f});

            // little separator row, just empty
            ImGui::TableNextRow(ImGuiTableRowFlags_None, 1.0f);
        }

        ImGui::EndTable();
    }

    style->popWindowTodoList();
    ImGui::End();
}

}  // namespace TodoApp
