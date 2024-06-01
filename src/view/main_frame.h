#pragma once

#include <wx/wx.h>
#include <chrono>
#include <vector>

#include "main_menu/main_menu.h"
#include "status_bar/status_bar.h"
#include "../todo/todo_controller.h"
#include "../config/config.h"
#include "panels/todo_add_panel.h"
#include "panels/todo_edit_panel.h"
#include "panels/todo_list_panel.h"


class MainFrame : public wxFrame {
   public:
    MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    void LoadInterface();
    void BindTodoListButtons();
    void FillTodoListPanel();
    void LoadTodoAddPanel();

    void OnCheckboxTodo(wxCommandEvent& event);
    void OnEditTodo(wxCommandEvent& event);
    void OnAddTodo(wxCommandEvent& event);
    void OnDeleteTodo(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);
    void OnEditSave(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

   private:
    TodoController m_todoController;

    MainMenu* m_mainMenu;
    StatusBar* m_status_bar;

    TodoListPanel* m_todoListPanel;
    TodoAddPanel* m_addTodoPanel;
    TodoEditPanel* m_editTodoPanel;

    wxPanel* m_mainPanel;
    wxPanel* m_mainPanelLeft;
    wxPanel* m_mainPanelRight;

    wxBoxSizer* m_mainSizer;
    wxBoxSizer* m_mainPanelLeftSizer;
    wxBoxSizer* m_mainPanelRightSizer;

    DECLARE_EVENT_TABLE()
};