#include "window_category_list.hpp"

#include <imgui.h>

namespace TodoApp {

void WindowCategoryList::draw() {
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos({0, 0});
    ImGui::SetNextWindowSize({io.DisplaySize.x * 0.3f, io.DisplaySize.y});
    ImGui::Begin("Categories", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("Categories");
    ImGui::NewLine();
    ImGui::Selectable("selectMe");
    ImGui::Selectable("selectMe2");




    // Draw a button with rounded top corners
    // ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5);
    // ImGui::Button("Rounded Top Corner");
    // ImGui::PopStyleVar();





    ImGui::End();
}

}  // namespace TodoApp
