#include "app/app.hpp"

int main() {
    TodoApp::App app;
    app.init();
    app.run();

    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    TodoApp::App app;
    app.init();
    app.run();

    return 0;
}