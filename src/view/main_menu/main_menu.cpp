#include "main_menu.h"

MainMenu::MainMenu(wxWindow *parent) {
    _fileMenu = new wxMenu;
    _fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt-X"), wxT("Quit this program"));
    _fileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl-O"), wxT("Open a file"));
    _fileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl-S"), wxT("Save a file"));
    _fileMenu->Append(wxID_SAVEAS, wxT("Save &As\tCtrl-Shift-S"), wxT("Save a file as"));
    _fileMenu->Append(wxID_NEW, wxT("&New\tCtrl-N"), wxT("Create a new file"));

    _todoMenu = new wxMenu;
    _todoMenu->Append(wxID_ADD, wxT("&Add\tCtrl-A"), wxT("Add a new todo"));
    _todoMenu->Append(wxID_EDIT, wxT("&Edit\tCtrl-E"), wxT("Edit a todo"));
    _todoMenu->Append(wxID_DELETE, wxT("&Delete\tCtrl-D"), wxT("Delete a todo"));

    _helpMenu = new wxMenu;
    _helpMenu->Append(wxID_ABOUT, wxT("&About\tF1"), wxT("Show about dialog"));

    Append(_fileMenu, wxT("&File"));
    Append(_todoMenu, wxT("&Todo"));
    Append(_helpMenu, wxT("&Help"));

    Bind(wxEVT_MENU, &MainMenu::OnAboutClicked, this, wxID_ABOUT);
}

MainMenu::~MainMenu() {}

void MainMenu::OnAboutClicked(wxCommandEvent &event) {
    wxAboutDialogInfo info;
    info.SetName("Todo App");
    info.SetVersion("0.1.0");
    info.SetDescription("Craziest Todo App ever!\nSuck it!");
    info.SetCopyright("(C) 2024 Viro");
    wxAboutBox(info);
}