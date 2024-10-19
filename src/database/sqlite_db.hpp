#pragma once

#include <sqlite3.h>

#include <filesystem>
#include <map>
#include <memory>

#include "database.hpp"
#include "setup.h"
#include "todo/category.hpp"

namespace TodoApp {

class SqliteDB : public Database {
   public:
    ~SqliteDB() override;

    bool connect(const char* dbFile) override;
    bool disconnect() override;

    std::unique_ptr<Todo> getTodoById(int id) override;
    std::map<int, std::unique_ptr<Todo>> getTodos() override;

    std::map<int, std::unique_ptr<Category>> getCategories() override;
    std::unique_ptr<Category> getCategoryByName(std::string searchName) override;
    std::map<int, std::unique_ptr<Todo>> getTodosByCategory(std::shared_ptr<Category> category) override;

    bool addCategory(std::shared_ptr<Category> category) override;
    bool deleteCategory(std::shared_ptr<Category> category) override;

    bool addTodo(std::unique_ptr<Todo> todo) override;
    bool updateTodo(std::unique_ptr<Todo> todo) override;
    bool deleteTodoById(int id) override;

   private:
    sqlite3* m_db = nullptr;
};

}  // namespace TodoApp