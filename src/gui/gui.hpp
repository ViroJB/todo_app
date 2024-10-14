#pragma once

#include <thread>
#include <vector>

#include <windows.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
// needed to force dark mode, otherwise we have a white title bar
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <dwmapi.h>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <todo/todo_controller.h>

#include "gui_style.hpp"
#pragma comment(lib, "dwmapi.lib")

namespace TodoApp {

class Gui {
   public:
    void init();
    static void glfwErrorCallback(int error, const char* description);
    void render();
    void startFrame();
    void endFrame();
    GLFWwindow* getWindow() const;
    void enableDarkModeForWindow();
    std::vector<const char*> convertList(std::vector<std::string>& list);

   private:
    GLFWwindow* m_window = nullptr;
    std::shared_ptr<TodoController> m_todoController;
    GuiStyle m_style;

};

}  // namespace TodoApp
