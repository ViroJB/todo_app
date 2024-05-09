#pragma once

#include <wx/wx.h>

#include "../../todo/todo.h"

class TodoEditPanel : public wxPanel {
   public:
    TodoEditPanel(wxWindow* parent, Todo todo);
    wxButton* GetSaveButton();
    wxButton* GetCancelButton();
    Todo GetTodo();

   private:
    Todo m_todo;
    wxStaticBoxSizer* m_sizer;
    wxTextCtrl* m_title_text_ctrl;
    wxTextCtrl* m_description_text_ctrl;
    wxButton* m_save_button;
    wxButton* m_cancel_button;
};