#include "app/app.hpp"

int main() {
    TodoApp::App app;
    app.init();
    app.run();

    return 0;
}