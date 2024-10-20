#include "app.hpp"

// #include "commands/command_handler.hpp"

namespace TodoApp {

bool App::init() {
    return true;
}

void App::run() {
    Gui gui;
    gui.init();
    const auto window = gui.getWindow();

    while (!glfwWindowShouldClose(window)) {
        gui.render();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

}  // namespace TodoApp