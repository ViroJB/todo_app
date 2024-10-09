#pragma once

#include <sqlite3.h>

#include <iostream>
#include <map>

namespace TodoApp {

class Setup {
   public:
    Setup() {}
    static void Run(const char* db_file) {
        sqlite3* m_db;
        int rc = sqlite3_open(db_file, &m_db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        std::string sql_category_table =
            "CREATE TABLE IF NOT EXISTS category (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, "
            "created_at TEXT DEFAULT CURRENT_TIMESTAMP, updated_at TEXT DEFAULT CURRENT_TIMESTAMP);";
        char* err_msg;
        rc = sqlite3_exec(m_db, sql_category_table.c_str(), NULL, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        } else {
            std::cout << "category table created successfully" << std::endl;
        }

        std::string sql_todo_table =
            "CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY AUTOINCREMENT, category INTEGER, title TEXT NOT NULL, description "
            "TEXT "
            "NOT NULL, status TEXT NOT NULL DEFAULT 'todo', due_date TEXT, created_at TEXT DEFAULT CURRENT_TIMESTAMP, "
            "updated_at TEXT DEFAULT CURRENT_TIMESTAMP);";
        // clear err_msg
        err_msg = nullptr;
        rc = sqlite3_exec(m_db, sql_todo_table.c_str(), NULL, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        } else {
            std::cout << "todo table created successfully" << std::endl;
        }
    }

    void InsertExampleData(const char* db_file) {
        sqlite3* m_db;
        int rc = sqlite3_open(db_file, &m_db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        std::vector<std::string> sample_categories = {"Work", "Personal", "Shopping", "Others"};
        for (auto& category : sample_categories) {
            std::string sql = "INSERT INTO category (name) VALUES ('" + category + "');";
            char* err_msg;
            int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << err_msg << std::endl;
                sqlite3_free(err_msg);
            } else {
                std::cout << "sample category created successfully" << std::endl;
            }
        }

        std::vector<Todo> sample_todos;
        Todo todo1, todo2, todo3, todo4;
        todo1.category = 1;
        todo1.title = "Sample Todo EINS";
        todo1.description = "This is a sample todo 1";
        todo2.category = 2;
        todo2.title = "Sample Todo ZWEI";
        todo2.description = "This is a sample todo 2";
        todo3.category = 3;
        todo3.title = "Sample Todo DREI";
        todo3.description = "This is a sample todo 3";
        todo4.category = 4;
        todo4.title = "Sample Todo VIER";
        todo4.description = "This is a sample todo 4";
        sample_todos.push_back(todo1);
        sample_todos.push_back(todo2);
        sample_todos.push_back(todo3);
        sample_todos.push_back(todo4);

        for (auto& todo : sample_todos) {
            std::string sql =
                "INSERT INTO todo (category, title, description, status, due_date, created_at, updated_at) VALUES ('" +
                std::to_string(todo.category) + "', '" + todo.title + "', '" + todo.description + "', '" + todo.status +
                "', '" + todo.due_date + "', '" + todo.created_at + "', '" + todo.updated_at + "');";
            char* err_msg;
            int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << err_msg << std::endl;
                sqlite3_free(err_msg);
            } else {
                std::cout << "sample todo created successfully" << std::endl;
            }
        }
    }
};
}  // namespace TodoApp