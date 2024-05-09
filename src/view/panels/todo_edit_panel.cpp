#include "todo_edit_panel.h"

TodoEditPanel::TodoEditPanel(wxWindow* parent, Todo todo) : wxPanel(parent) {
    m_todo = todo;

    m_sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Edit Todo");

    wxStaticText* title_label = new wxStaticText(this, wxID_ANY, "Title:");
    m_sizer->Add(title_label, 0, wxALL, 5);

    m_title_text_ctrl = new wxTextCtrl(this, wxID_ANY, m_todo.title);
    m_sizer->Add(m_title_text_ctrl, 0, wxEXPAND | wxALL, 5);

    wxStaticText* description_label = new wxStaticText(this, wxID_ANY, "Description:");
    m_sizer->Add(description_label, 0, wxALL, 5);

    m_description_text_ctrl = new wxTextCtrl(this, wxID_ANY, m_todo.description, wxPoint(-1, -1), wxSize(-1, 100), wxTE_MULTILINE);
    m_sizer->Add(m_description_text_ctrl, 0, wxEXPAND | wxALL, 5);

    // TODO put buttons in own sizer to put them side by side   
    m_save_button = new wxButton(this, wxID_ANY, "Save");
    m_sizer->Add(m_save_button, 0, wxALL, 5);

    m_cancel_button = new wxButton(this, wxID_ANY, "Cancel");
    m_sizer->Add(m_cancel_button, 0, wxALL, 5);

    SetSizer(m_sizer);
    Layout();
}

Todo TodoEditPanel::GetTodo() {
    Todo todo;
    todo.id = m_todo.id;
    std::cout << "GetTodo id: " << m_todo.id << std::endl;
    todo.created_at = m_todo.created_at;
    todo.updated_at = m_todo.updated_at;
    todo.due_date = m_todo.due_date;
    todo.status = m_todo.status;

    std::cout << "Title: " << m_title_text_ctrl->GetValue() << std::endl;
    todo.title = m_title_text_ctrl->GetValue();
    todo.description = m_description_text_ctrl->GetValue();
    return todo;
}

wxButton* TodoEditPanel::GetSaveButton() {
    return m_save_button;
}

wxButton* TodoEditPanel::GetCancelButton() {
    return m_cancel_button;
}