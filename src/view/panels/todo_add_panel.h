#pragma once

#include <wx/wx.h>
#include <map>

#include "../../todo/todo.h"

class TodoAddPanel : public wxPanel {
   public:
    TodoAddPanel(wxWindow* parent, std::map<int, std::string> categories);
    void OnAdd(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    wxButton* GetAddButton();
    wxButton* GetCancelButton();
    wxTextCtrl* GetTitleTextCtrl();
    wxTextCtrl* GetDescriptionTextCtrl();
    wxComboBox* GetCategoryComboBox();

   private:
    wxTextCtrl* m_title_text_ctrl;
    wxTextCtrl* m_description_text_ctrl;
    wxButton* m_add_button;
    wxButton* m_cancel_button;
    wxComboBox* m_category_combo_box;
};