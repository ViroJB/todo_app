#include "gui.hpp"

#include "gui/window_todo_list.hpp"
#include "gui_style.hpp"
#include "todo/todo_controller.h"
#include "window_add_todo.hpp"
#include "window_category_list.hpp"

namespace TodoApp {

void Gui::init() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        fmt::print("Failed to initialize GLFW3\n");
    }

    m_window = glfwCreateWindow(1024, 500, "Todo App", nullptr, nullptr);
    if (m_window != nullptr) {
        glfwMakeContextCurrent(m_window);
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // enable keyboard controls

    // init opengl for imgui
    // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();
    ImGui::StyleColorsDark();

    // style stuff
    // needed for dark mode
    enableDarkModeForWindow();
    m_style.load();

    m_todoController = std::make_shared<TodoController>();
}

void Gui::render() {
    glfwPollEvents();
    // close on esc
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
    startFrame();

    WindowCategoryList::draw(m_todoController->GetAllCategories(), m_style);
    WindowTodoList::draw(m_todoController->GetAll(), m_style);

    // temp, needs to be gone asap!
    auto list = m_todoController->GetAllCategories();
    std::vector<const char*> categories;
    categories.reserve(list.size());
    for (const auto& item : list) {
        categories.push_back(item.second.c_str());
    }

    WindowAddTodo::draw(categories, m_style);

    // ImGui::ShowDemoWindow();
    endFrame();
}

void Gui::startFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::endFrame() {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
}

GLFWwindow* Gui::getWindow() const { return m_window; }

void Gui::glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void Gui::enableDarkModeForWindow() {
    BOOL useDarkMode = TRUE;
    HWND hwnd = glfwGetWin32Window(m_window);
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDarkMode, sizeof(useDarkMode));
}

std::vector<const char*> Gui::convertList(std::vector<std::string>& list) {
    std::vector<const char*> charArray;
    charArray.reserve(list.size());  // reserve memory for performance
    for (const auto& str : list) {
        charArray.push_back(str.c_str());  // use c_str() to get const char*
    }
    return charArray;
}

}  // namespace TodoApp