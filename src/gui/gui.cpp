#include "gui.hpp"

#include "config/config.hpp"
#include "gui/window_todo_list.hpp"
#include "gui_style.hpp"
#include "todo/todo_controller.hpp"
#include "window_add_todo.hpp"
#include "window_category_list.hpp"

namespace TodoApp {

// TODO redo most of the gui stuff. use one begin and end, and the rest with child windows.

void Gui::init() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        fmt::print("Failed to initialize GLFW3\n");
    }

    m_window = glfwCreateWindow(Config::APP_DEFAULT_WIDTH, Config::APP_DEFAULT_HEIGHT, Config::APP_NAME.c_str(), nullptr, nullptr);
    if (m_window != nullptr) {
        glfwMakeContextCurrent(m_window);
        glfwSetWindowSizeLimits(m_window, Config::APP_MIN_WIDTH , Config::APP_MIN_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);

        // center window
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        if (primaryMonitor) {
            const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);

            int windowPosX = (vidMode->width - Config::APP_DEFAULT_WIDTH) / 2;
            int windowPosY = (vidMode->height - Config::APP_DEFAULT_HEIGHT) / 2;

            glfwSetWindowPos(m_window, windowPosX, windowPosY);
        }
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
    m_style = std::make_shared<GuiStyle>();
    m_style->load();

    m_todoController = std::make_shared<TodoController>();

    std::shared_ptr<Category> cat = std::make_shared<Category>();
    m_todoController->setCurrentCategory(cat);
}

void Gui::render() {
    glfwPollEvents();
    // close on esc
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(m_window, GLFW_TRUE);
    }
    startFrame();

    WindowCategoryList::draw(m_style, m_todoController);
    WindowTodoList::draw(m_style, m_todoController);
    WindowAddTodo::draw(m_style, m_todoController);

    // fixme its probably not working because we actually use 3 different windows, not child windows..
    // if (ImGui::IsWindowFocused()) {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(10));
    // } else {
    //     std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // }
    // ImGui::ShowDemoWindow();
    endFrame();
    // glfwIconifyWindow(m_window); // minimize window
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