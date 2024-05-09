#pragma once

#include <wx/wx.h>

#include "../../todo/todo.h"

class TodoAddPanel : public wxPanel {
   public:
    TodoAddPanel(wxWindow* parent);
    void OnAdd(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    wxButton* GetAddButton();
    wxButton* GetCancelButton();
    wxTextCtrl* GetTitleTextCtrl();
    wxTextCtrl* GetDescriptionTextCtrl();

   private:
    wxTextCtrl* m_title_text_ctrl;
    wxTextCtrl* m_description_text_ctrl;
    wxButton* m_add_button;
    wxButton* m_cancel_button;
};