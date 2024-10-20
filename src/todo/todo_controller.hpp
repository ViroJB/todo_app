#pragma once

#include <map>
#include <memory>
#include <string>

#include "category.hpp"
#include "config/config.hpp"
#include "database/database.hpp"
#include "database/sqlite_db.hpp"
#include "todo.hpp"

namespace TodoApp {

class TodoController {
   public:
    TodoController();
    ~TodoController();

    void add(std::unique_ptr<Todo> todo);
    void remove(int id);
    void update(std::unique_ptr<Todo> todo);
    bool deleteTodosByCategory(std::shared_ptr<Category> category);
    std::unique_ptr<Todo> get(int id);
    std::map<int, std::shared_ptr<Todo>> getAll();
    std::map<int, std::shared_ptr<Todo>> getAllByCategory(std::shared_ptr<Category> category);
    void refreshTodosByCategory(std::shared_ptr<Category> category);
    void refreshTodos();
    void refreshCategories();

    void addCategory(std::string category);
    void deleteCategory(std::shared_ptr<Category> category);
    std::map<int, std::shared_ptr<Category>> getAllCategories();
    std::unique_ptr<Category> getCategoryByName(std::string name);
    std::shared_ptr<Category> getCurrentCategory();
    void setCurrentCategory(std::shared_ptr<Category> category);

   public:
    bool hasChanges = false;

   private:
    std::unique_ptr<Database> m_database;
    std::map<int, std::shared_ptr<Todo>> m_todos;
    std::map<int, std::shared_ptr<Category>> m_categories;
    std::shared_ptr<Category> m_currentCategory;
};

}  // namespace TodoApp