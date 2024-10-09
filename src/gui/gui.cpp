#include "gui.hpp"

namespace TodoApp {

void Gui::render() const {
    glfwPollEvents();

    // start imgui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();


    ImGui::Begin("aaaaaaaaaaa");
    ImGui::Text("Hello, world!");
    ImGui::End();


    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(m_window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(m_window);
}

GLFWwindow* Gui::getWindow() const {
    return m_window;
}

void Gui::init() {
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        fmt::print("Failed to initialize GLFW3\n");
    }

    m_window = glfwCreateWindow(800, 500, "Todo App", nullptr, nullptr);
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

    // needed for darkmode
    HWND hwnd = glfwGetWin32Window(m_window);
    enableDarkModeForWindow(hwnd);
}

void Gui::glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void Gui::enableDarkModeForWindow(HWND hwnd) {
    BOOL useDarkMode = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDarkMode, sizeof(useDarkMode));
}

}  // namespace TodoApp