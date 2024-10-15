#include "todo_controller.h"

// NOTE
// do we reduce the database actions (reads, writes ect)?
// so we manage everything with just the m_todos map?
// if we do that, how do we update just the changed ones to the database?
// we can add a flag to the todo object, to check if it has changed
// but we could lose stuff if we forget to save or crash
// would it have benefits? would it help in reducing the flickering when data changes in the ui?
// we would always give out references/pointers instead of copies, is that good or bad?
// i mean, we could give out copies...
// performance is absolutely not an issue here, so we can do whatever we want
// or leave it as is? like its doing nothing?


// get only new todo list when a new one was added, when the category switches or ???
// so we need to save current category and the current todo list in a variable
// like a cache... hasCache or something

namespace TodoApp {

TodoController::TodoController() {
    // NOTE gotta go with the setup here i guess, for now?
    if (!std::filesystem::exists(Config::DB_FILE)) {
        Setup setup;
        setup.Run(Config::DB_FILE);
        setup.InsertExampleData(Config::DB_FILE);
    }

    m_database = new SqliteDB();
    m_database->Connect(Config::DB_FILE);
}

TodoController::~TodoController() {
    m_database->Disconnect();
    delete m_database;
}

void TodoController::Add(Todo todo) {
    int id = m_database->AddTodo(todo);
    todo.id = id;
    m_todos[id] = todo;
    std::cout << "Added Todo, ID: " << id << std::endl;
}

void TodoController::Remove(int id) {
    m_database->DeleteTodoById(id);
    m_todos.erase(id);
    std::cout << "Deleted Todo ID: " << id << std::endl;
}

std::map<int, std::string> TodoController::GetAllCategories() {
    return m_database->GetAllCategories();
}

int TodoController::GetCategoryByName(std::string name) {
    return m_database->GetCategoryByName(name);
}

void TodoController::Update(Todo todo) {
    m_database->UpdateTodo(todo);
    m_todos[todo.id] = todo;
    std::cout << "Updated Todo ID: " << todo.id << std::endl;
}

Todo TodoController::Get(int id) { return m_database->GetTodoById(id); }

std::map<int, Todo>* TodoController::GetAll() {
    m_todos = m_database->GetAllTodos();
    return &m_todos;
}

void TodoController::Save() {}

}