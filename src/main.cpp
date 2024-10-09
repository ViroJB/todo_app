#include "app/app.h"

int main() {
    TodoApp::App app;
    app.init();
    app.mainLoop();

    return 0;
}