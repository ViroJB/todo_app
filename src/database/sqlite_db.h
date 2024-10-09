#pragma once

#include <map>
#include <filesystem>

#include <sqlite3.h>

#include "database.h"
#include "setup.h"


namespace TodoApp {

class SqliteDB : public Database {
   public:
    SqliteDB();
    ~SqliteDB();

    bool Connect(const char* db_file) override;
    void Disconnect() override;

    Todo GetTodoById(int id) override;
    std::map<int, Todo> GetAllTodos() override;

    std::map<int, std::string> GetAllCategories() override;
    int GetCategoryByName(std::string name) override;

    int AddTodo(Todo todo) override;
    bool UpdateTodo(Todo todo) override;
    bool DeleteTodoById(int id) override;

   private:
    sqlite3* m_db;
};

}