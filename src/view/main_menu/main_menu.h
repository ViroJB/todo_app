#pragma once

#include <wx/wx.h>
#include <wx/aboutdlg.h>

class MainMenu : public wxMenuBar {
   public:
    MainMenu(wxWindow *parent);
    ~MainMenu();

    void OnAboutClicked(wxCommandEvent &event);

   private:
    wxMenu *_fileMenu;
    wxMenu *_todoMenu;
    wxMenu *_helpMenu;
};