#include "main_frame.h"

// TODO move all the click handler methods to a separate class, like a event handler something?

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size) {
    m_mainMenu = new MainMenu(this);
    SetMenuBar(m_mainMenu);
    LoadInterface();

    m_todoListPanel = new TodoListPanel(m_mainPanelLeft);
    m_mainPanelLeftSizer->Add(m_todoListPanel, 1, wxEXPAND | wxALL, 10);
    FillTodoListPanel();

    LoadTodoAddPanel();
}

void MainFrame::LoadInterface() {
    m_mainSizer = new wxBoxSizer(wxHORIZONTAL);
    SetSizer(m_mainSizer);
    m_mainPanelLeft = new wxPanel(this, wxID_ANY);
    m_mainPanelRight = new wxPanel(this, wxID_ANY);

    m_mainSizer->Add(m_mainPanelLeft, 1, wxEXPAND | wxALL, 10);
    m_mainSizer->Add(m_mainPanelRight, 0, wxALL, 10);

    m_mainPanelLeftSizer = new wxBoxSizer(wxVERTICAL);
    m_mainPanelLeft->SetSizer(m_mainPanelLeftSizer);

    m_mainPanelRightSizer = new wxBoxSizer(wxVERTICAL);
    m_mainPanelRightSizer->SetMinSize(300, 0);
    m_mainPanelRight->SetSizer(m_mainPanelRightSizer);

    m_status_bar = new StatusBar(this);

    SetStatusBar(m_status_bar);
}

void MainFrame::FillTodoListPanel() {
    m_todoListPanel->ClearTodoList();
    m_todoListPanel->PopulateTodoList(m_todoController.GetAll());
    BindTodoListButtons();

    Layout();
}

void MainFrame::BindTodoListButtons() {
    std::map<int, wxCheckBox*> checkboxes = m_todoListPanel->GetTodoCheckboxes();
    std::map<int, wxButton*> edit_buttons = m_todoListPanel->GetEditButtons();
    std::map<int, wxButton*> delete_buttons = m_todoListPanel->GetDeleteButtons();

    for (auto it = checkboxes.begin(); it != checkboxes.end(); ++it) {
        it->second->Bind(wxEVT_CHECKBOX, &MainFrame::OnCheckboxTodo, this);
    }

    for (auto it = edit_buttons.begin(); it != edit_buttons.end(); ++it) {
        it->second->Bind(wxEVT_BUTTON, &MainFrame::OnEditTodo, this);
    }

    for (auto it = delete_buttons.begin(); it != delete_buttons.end(); ++it) {
        it->second->Bind(wxEVT_BUTTON, &MainFrame::OnDeleteTodo, this);
    }
}

void MainFrame::OnCheckboxTodo(wxCommandEvent& event) {
    std::unordered_map<int, int>* todo_button_map = m_todoListPanel->GetTodoButtonMap();
    int checkbox_id = event.GetId();
    int todo_id = todo_button_map->at(checkbox_id);
    std::cout << "Clicked checkbox todo with ID: " << todo_id << std::endl;
    Todo todo = m_todoController.Get(todo_id);

    // TODO redo the status thing, guess a completed boolean field would be enough
    if (todo.status == "completed") {
        todo.status = "pending";
    } else {
        todo.status = "completed";
    }

    m_todoController.Update(todo);

    FillTodoListPanel();
}

void MainFrame::OnEditTodo(wxCommandEvent& event) {
    std::unordered_map<int, int>* todo_button_map = m_todoListPanel->GetTodoButtonMap();
    int button_id = event.GetId();
    int todo_id = todo_button_map->at(button_id);
    std::cout << "Clicked edit todo with ID: " << todo_id << std::endl;
    Todo todo = m_todoController.Get(todo_id);

    // Remove the add panel and add the edit panel
    m_mainPanelRightSizer->Clear(true);

    m_editTodoPanel = new TodoEditPanel(m_mainPanelRight, todo);
    m_mainPanelRightSizer->Add(m_editTodoPanel, 1, wxEXPAND | wxALL, 10);

    // TODO move the bindings somewhere else... are they supposed to be where they are defined?
    wxButton* save_button = m_editTodoPanel->GetSaveButton();
    save_button->Bind(wxEVT_BUTTON, &MainFrame::OnEditSave, this);

    wxButton* cancel_button = m_editTodoPanel->GetCancelButton();
    cancel_button->Bind(wxEVT_BUTTON, &MainFrame::OnCancel, this);

    Layout();  // why is this needed to refresh the panel so the new edit panel is shown?
}

void MainFrame::OnDeleteTodo(wxCommandEvent& event) {
    // TODO close edit panel if it has the deleted todo open
    std::unordered_map<int, int>* todo_button_map = m_todoListPanel->GetTodoButtonMap();
    int button_id = event.GetId();
    int todo_id = todo_button_map->at(button_id);
    std::cout << "Delete todo with ID: " << todo_id << std::endl;
    m_todoController.Remove(todo_id);

    FillTodoListPanel();

    Layout();
}

void MainFrame::LoadTodoAddPanel() {
    m_mainPanelRightSizer->Clear(true);
    m_addTodoPanel = new TodoAddPanel(m_mainPanelRight, m_todoController.GetAllCategories());
    m_mainPanelRightSizer->Add(m_addTodoPanel, 1, wxEXPAND | wxALL, 10);

    // TODO bind buttons
    m_addTodoPanel->GetAddButton()->Bind(wxEVT_BUTTON, &MainFrame::OnAddTodo, this);
    m_addTodoPanel->GetCancelButton()->Bind(wxEVT_BUTTON, &MainFrame::OnCancel, this);

    Layout();
}

void MainFrame::OnCancel(wxCommandEvent& event) { LoadTodoAddPanel(); }

void MainFrame::OnEditSave(wxCommandEvent& event) {
    std::cout << "Clicked save edit" << std::endl;
    Todo todo = m_editTodoPanel->GetTodo();

    m_todoController.Update(todo);

    FillTodoListPanel();
    LoadTodoAddPanel();
}

void MainFrame::OnAddTodo(wxCommandEvent& event) {
    Todo todo;
    todo.title = m_addTodoPanel->GetTitleTextCtrl()->GetValue().ToStdString();
    todo.description = m_addTodoPanel->GetDescriptionTextCtrl()->GetValue().ToStdString();
    // check if category is empty and if not, get id by name and fill it in
    todo.category_name = m_addTodoPanel->GetCategoryComboBox()->GetStringSelection().ToStdString();
    todo.category = m_todoController.GetCategoryByName(todo.category_name);

    todo.created_at = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    todo.updated_at = std::to_string(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
    todo.status = "pending";
    todo.due_date = "2029-12-31";

    m_todoController.Add(todo);

    FillTodoListPanel();
}

void MainFrame::OnClose(wxCloseEvent& event) { Destroy(); }