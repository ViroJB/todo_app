#include "todo_controller.hpp"

#include <fmt/base.h>

#include <utility>

namespace TodoApp {

// TODO FIX ALL THIS... it works, but at what cost??
// todo make -1 as id for category work. for example we could keep todos without category, if we delete a category
TodoController::TodoController() {
    // NOTE gotta go with the setup here I guess, for now?
    if (!std::filesystem::exists(Config::DB_FILE)) {
        Setup::run(Config::DB_FILE);
        Setup::insertExampleData(Config::DB_FILE);
    }

    m_database = std::make_unique<SqliteDB>();
    m_database->connect(Config::DB_FILE);
    m_currentCategory = std::make_shared<Category>();
}

TodoController::~TodoController() { m_database->disconnect(); }

void TodoController::add(std::unique_ptr<Todo> todo) {
    std::shared_ptr<Category> cat = std::make_shared<Category>();
    cat->id = todo->category.id;
    cat->name = todo->category.name;
    m_database->addTodo(std::move(todo));
    refreshTodosByCategory(cat);
    setCurrentCategory(cat);
    fmt::print("added Todo\n");
}

void TodoController::remove(int id) {
    // todo this should refresh the category it was in, and it actually should accept a Todo...
    m_database->deleteTodoById(id);
    std::shared_ptr<Category> cat = std::make_shared<Category>();
    refreshTodosByCategory(cat);
    std::cout << "Deleted Todo ID: " << id << std::endl;
}

std::map<int, std::shared_ptr<Category>> TodoController::getAllCategories() {
    if (m_categories.empty()) {
        refreshCategories();
    }

    return m_categories;
}

std::unique_ptr<Category> TodoController::getCategoryByName(std::string name) {
    return m_database->getCategoryByName(std::move(name));
}

std::shared_ptr<Category> TodoController::getCurrentCategory() { return m_currentCategory; }

void TodoController::setCurrentCategory(std::shared_ptr<Category> category) {
    refreshTodosByCategory(category);
    m_currentCategory = category;
    hasChanges = true;
}

void TodoController::update(std::unique_ptr<Todo> todo) {
    auto cat = std::make_shared<Category>(todo->category.id, todo->category.name);
    std::cout << "Updated Todo ID: " << todo->id << std::endl;
    m_database->updateTodo(std::move(todo));
}

bool TodoController::deleteTodosByCategory(std::shared_ptr<Category> category) {
    m_database->deleteTodosByCategory(std::move(category));
    return true;
}

std::unique_ptr<Todo> TodoController::get(int id) { return m_database->getTodoById(id); }

std::map<int, std::shared_ptr<Todo>> TodoController::getAll() {

    return m_todos;
}

std::map<int, std::shared_ptr<Todo>> TodoController::getAllByCategory(std::shared_ptr<Category> category) {
    if (category->id != getCurrentCategory()->id) {
        refreshTodosByCategory(std::move(category));
    }

    return m_todos;
}

void TodoController::refreshTodosByCategory(std::shared_ptr<Category> category) {
    std::map<int, std::unique_ptr<Todo>> todos;
    if (category->id == -1) {
        todos = m_database->getTodos();
    } else {
        todos = m_database->getTodosByCategory(std::move(category));
    }

    std::map<int, std::shared_ptr<Todo>> sharedPtrMap;

    for (auto& [key, uniquePtrValue] : todos) {
        sharedPtrMap[key] = std::move(uniquePtrValue);  // Move unique_ptr to shared_ptr
    }

    m_todos = sharedPtrMap;
}

void TodoController::refreshTodos() {
    std::map<int, std::shared_ptr<Todo>> sharedPtrMap;
    m_todos = sharedPtrMap;
}

void TodoController::refreshCategories() {
    auto todos = m_database->getCategories();

    std::map<int, std::shared_ptr<Category>> sharedPtrMap;

    for (auto& [key, uniquePtrValue] : todos) {
        sharedPtrMap[key] = std::move(uniquePtrValue);  // Move unique_ptr to shared_ptr
    }

    m_categories = sharedPtrMap;
}

void TodoController::addCategory(std::string category) {
    std::shared_ptr<Category> cat = std::make_shared<Category>();
    cat->name = category;
    m_database->addCategory(std::move(cat));
    refreshCategories();
    setCurrentCategory(getCategoryByName(category));
}

void TodoController::deleteCategory(std::shared_ptr<Category> category) {
    // todo we could keep the todos when we delete the category... do we want to?
    if (m_currentCategory->name == category->name) {
        setCurrentCategory(std::make_shared<Category>());
    }
    m_database->deleteCategory(category);
    m_database->deleteTodosByCategory(std::move(category));
    refreshCategories();
    hasChanges = true;
}

}  // namespace TodoAp