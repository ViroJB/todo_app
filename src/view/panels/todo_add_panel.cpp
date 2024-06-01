#include "todo_add_panel.h"

TodoAddPanel::TodoAddPanel(wxWindow* parent, const std::map<int, std::string> categories) : wxPanel(parent, wxID_ANY) {
    wxStaticBoxSizer* sizer = new wxStaticBoxSizer(wxVERTICAL, this, "Add Todo");

    wxStaticText* category_label = new wxStaticText(this, wxID_ANY, "Category:");
    sizer->Add(category_label, 0, wxALL, 5);

    wxArrayString wx_categories;
    for (auto const& [id, category] : categories) {
        wx_categories.Add(category);
    }

    m_category_combo_box = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wx_categories,
                                                    wxCB_READONLY);
    sizer->Add(m_category_combo_box, 0, wxALL | wxEXPAND, 5);

    m_category_combo_box->GetSelection();

    wxStaticText* title_label = new wxStaticText(this, wxID_ANY, "Title:");
    sizer->Add(title_label, 0, wxALL, 5);

    m_title_text_ctrl = new wxTextCtrl(this, wxID_ANY);
    sizer->Add(m_title_text_ctrl, 0, wxALL | wxEXPAND, 5);

    wxStaticText* description_label = new wxStaticText(this, wxID_ANY, "Description:");
    sizer->Add(description_label, 0, wxALL, 5);

    m_description_text_ctrl =
        new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    sizer->Add(m_description_text_ctrl, 1, wxALL | wxEXPAND, 5);

    m_add_button = new wxButton(this, wxID_ANY, "Add");
    sizer->Add(m_add_button, 0, wxALL | wxALIGN_RIGHT, 5);

    m_cancel_button = new wxButton(this, wxID_ANY, "Cancel");
    sizer->Add(m_cancel_button, 0, wxALL | wxALIGN_RIGHT, 5);

    SetSizer(sizer);
    Layout();
}

wxTextCtrl* TodoAddPanel::GetTitleTextCtrl() { return m_title_text_ctrl; }
wxTextCtrl* TodoAddPanel::GetDescriptionTextCtrl() { return m_description_text_ctrl; }
wxButton* TodoAddPanel::GetAddButton() { return m_add_button; }
wxButton* TodoAddPanel::GetCancelButton() { return m_cancel_button; }
wxComboBox* TodoAddPanel::GetCategoryComboBox() { return m_category_combo_box; }

void TodoAddPanel::OnAdd(wxCommandEvent& event) { event.Skip(); }

void TodoAddPanel::OnCancel(wxCommandEvent& event) { event.Skip(); }