#pragma once

#include <sqlite3.h>

#include <iostream>

namespace TodoApp {

// TODO make example todos that explain the usage of the app. like a in Tutorial category or something like that

class Setup {
   public:
    static void run(const char* db_file) {
        sqlite3* m_db;
        int rc = sqlite3_open(db_file, &m_db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        const std::string sql_category_table =
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

        const std::string sql_todo_table =
            "CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY AUTOINCREMENT, category_id INTEGER NOT NULL, text TEXT NOT NULL, "
            "completed INTEGER NOT NULL DEFAULT '0', due_date TEXT, created_at TEXT DEFAULT CURRENT_TIMESTAMP, "
            "updated_at TEXT DEFAULT CURRENT_TIMESTAMP);";
        err_msg = nullptr;
        rc = sqlite3_exec(m_db, sql_todo_table.c_str(), NULL, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        } else {
            std::cout << "todo table created successfully" << std::endl;
        }
    }

    static void insertExampleData(const char* db_file) {
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
        todo1.category.id = 1;
        todo1.text = "Sample Todo EINS";
        todo2.category.id = 2;
        todo2.text = "Sample Todo ZWEI";
        todo3.category.id = 3;
        todo3.text = "Sample Todo DREI";
        todo4.category.id = 4;
        todo4.text = "Sample Todo VIER";
        sample_todos.push_back(todo1);
        sample_todos.push_back(todo2);
        sample_todos.push_back(todo3);
        sample_todos.push_back(todo4);

        for (auto& todo : sample_todos) {
            int completed = todo.completed;
            std::string sql =
                "INSERT INTO todo (category_id, text, completed) VALUES ('" +
                std::to_string(todo.category.id) + "', '" + todo.text + "', '" + std::to_string(completed) +
                "');";
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