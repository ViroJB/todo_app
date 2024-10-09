#pragma once

#include <thread>
#include <vector>

#include <windows.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
// needed to force dark mode, otherwise we have a white title bar
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <fmt/core.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")

namespace TodoApp {

class Gui {
   public:
    void init();
    static void glfwErrorCallback(int error, const char* description);
    void render() const;
    GLFWwindow* getWindow() const;
    void enableDarkModeForWindow(HWND hwnd);

   private:
    GLFWwindow* m_window = nullptr;
};

}  // namespace TodoApp
