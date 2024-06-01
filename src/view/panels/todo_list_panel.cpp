#include "todo_list_panel.h"

TodoListPanel::TodoListPanel(wxWindow* parent) : wxPanel(parent, wxID_ANY) {
    m_sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(m_sizer);

    m_scrolled_window = new wxScrolledWindow(this, wxID_ANY);
    m_scrolled_window_sizer = new wxBoxSizer(wxVERTICAL);
    m_scrolled_window->SetSizer(m_scrolled_window_sizer);
    m_scrolled_window->SetScrollRate(0, 20);
    m_scrolled_window->FitInside();
    m_sizer->Add(m_scrolled_window, 1, wxEXPAND | wxALL, 10);
}

void TodoListPanel::PopulateTodoList(std::map<int, Todo>* todos) {
    int wx_id = 200;  // currently there to avoid collision with other IDs, try to use only 0-199 in other panels

    for (auto it = todos->rbegin(); it != todos->rend(); ++it) {
        Todo todo = it->second;

        // TODO check the m_todo_button_map, do we clear it? does it need to be cleared? just have an eye on it
        wxBoxSizer* todo_sizer = new wxBoxSizer(wxHORIZONTAL);
        // NOTE the checkbox has a label, do we just put the title there?
        wxCheckBox* checkbox_button = new wxCheckBox(m_scrolled_window, wx_id++, "");
        if (todo.status == "completed") {
            checkbox_button->SetValue(true);
        } else {
            checkbox_button->SetValue(false);
        }
        wxStaticText* label = new wxStaticText(m_scrolled_window, wxID_ANY, std::to_string(todo.id) + ". " + todo.title +  " (" + todo.category_name + ")");
        wxButton* edit_button = new wxButton(m_scrolled_window, wx_id++, "Edit");
        wxButton* delete_button = new wxButton(m_scrolled_window, wx_id++, "Delete");

        m_todo_button_map[checkbox_button->GetId()] = todo.id;
        m_todo_button_map[edit_button->GetId()] = todo.id;
        m_todo_button_map[delete_button->GetId()] = todo.id;

        todo_sizer->Add(checkbox_button, 0, wxEXPAND | wxALL, 10);
        todo_sizer->Add(label, 1, wxEXPAND | wxALL, 10);
        todo_sizer->Add(edit_button, 0, wxEXPAND | wxALL, 10);
        todo_sizer->Add(delete_button, 0, wxEXPAND | wxALL, 10);

        m_scrolled_window_sizer->Add(todo_sizer, 0, wxEXPAND | wxALL, 10);

        m_todo_checkboxes[checkbox_button->GetId()] = checkbox_button;
        m_todo_labels.push_back(label);
        m_edit_buttons[edit_button->GetId()] = edit_button;
        m_delete_buttons[delete_button->GetId()] = delete_button;
    }
}

void TodoListPanel::ClearTodoList() {
    for (auto [id, checkbox] : m_todo_checkboxes) {
        checkbox->Destroy();
    }

    for (auto label : m_todo_labels) {
        label->Destroy();
    }

    for (auto [id, button] : m_edit_buttons) {
        button->Destroy();
    }

    for (auto [id, button] : m_delete_buttons) {
        button->Destroy();
    }

    m_todo_checkboxes.clear();
    m_todo_labels.clear();
    m_edit_buttons.clear();
    m_delete_buttons.clear();
}