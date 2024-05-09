#pragma once

#include <wx/wx.h>

#include <map>

#include "../../todo/todo.h"

class TodoListPanel : public wxPanel {
   public:
    TodoListPanel(wxWindow* parent);
    void PopulateTodoList(std::map<int, Todo>* todos);
    void ClearTodoList();
    std::unordered_map<int, int>* GetTodoButtonMap() { return &m_todo_button_map; }
    std::map<int, wxButton*> GetEditButtons() { return m_edit_buttons; }
    std::map<int, wxButton*> GetDeleteButtons() { return m_delete_buttons; }

   private:
    wxBoxSizer* m_sizer;
    wxScrolledWindow* m_scrolled_window;
    wxBoxSizer* m_scrolled_window_sizer;
    std::map<int, wxButton*> m_edit_buttons;
    std::map<int, wxButton*> m_delete_buttons;
    std::vector<wxStaticText*> m_todo_labels;
    std::unordered_map<int, int> m_todo_button_map;  // button id to todo id map
};