#pragma once

#include <sqlite3.h>

#include <iostream>
#include <map>

class Setup {
   public:
    Setup() {}
    void Run(const char* db_file) {
        sqlite3* m_db;
        int rc = sqlite3_open(db_file, &m_db);
        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        } else {
            std::cout << "Opened database successfully" << std::endl;
        }

        std::string sql =
            "CREATE TABLE IF NOT EXISTS todo (id INTEGER PRIMARY KEY AUTOINCREMENT, title TEXT NOT NULL, description TEXT "
            "NOT NULL, status TEXT NOT NULL DEFAULT 'todo', due_date TEXT, created_at TEXT DEFAULT CURRENT_TIMESTAMP, "
            "updated_at TEXT DEFAULT CURRENT_TIMESTAMP);";
        char* err_msg;
        rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
        } else {
            std::cout << "Table created successfully" << std::endl;
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

        std::map<int, Todo> sample_todos;
        sample_todos[1] = {1, "Sample Todo EINS", "This is a sample todo 1", "completed", "2021-01-01", "2021-01-01", "2021-01-01"};
        sample_todos[2] = {2, "Sample Todo ZWEI", "This is a sample todo 2", "pending", "2021-01-01", "2021-01-01", "2021-01-01"};
        sample_todos[3] = {3, "Sample Todo DREI", "This is a sample todo 3", "pending", "2021-01-01", "2021-01-01", "2021-01-01"};

        for (auto& [id, todo] : sample_todos) {
            std::string sql = "INSERT INTO todo (title, description, status, due_date, created_at, updated_at) VALUES ('" + todo.title +
                              "', '" + todo.description + "', '" + todo.status + "', '" + todo.due_date + "', '" + todo.created_at +
                              "', '" + todo.updated_at + "');";
            char* err_msg;
            int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << err_msg << std::endl;
                sqlite3_free(err_msg);
            } else {
                std::cout << "Record created successfully" << std::endl;
            }
        }
    }
};