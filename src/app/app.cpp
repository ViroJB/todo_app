#include "app.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame(Config::APP_NAME, wxPoint(50, 50), wxSize(450, 340));
    mainFrame->SetMinSize(wxSize(Config::APP_MIN_WIDTH, Config::APP_MIN_HEIGHT));
    mainFrame->Center();
    mainFrame->Show();

    return true;
}

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()