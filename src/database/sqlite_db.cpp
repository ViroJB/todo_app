#include "sqlite_db.h"


namespace TodoApp {

SqliteDB::SqliteDB() {}

SqliteDB::~SqliteDB() { sqlite3_close(m_db); }

bool SqliteDB::Connect(const char* db_file) {
    int rc = sqlite3_open(db_file, &m_db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        return false;
    } else {
        std::cout << "Opened database successfully" << std::endl;
        return true;
    }
}

void SqliteDB::Disconnect() { sqlite3_close(m_db); }

std::map<int, std::string> SqliteDB::GetAllCategories() {
    std::map<int, std::string> categories;
    std::string sql = "SELECT * FROM category;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            categories[id] = name;
        }
    }
    sqlite3_finalize(stmt);
    std::cout << "Fetched all categories, size: " << categories.size() << std::endl;
    return categories;
}

int SqliteDB::GetCategoryByName(std::string name) {
    std::string sql = "SELECT id FROM category WHERE name = '" + name + "';";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::cout << "Fetched category id: " << id << std::endl;
            return id;
        }
    }
    sqlite3_finalize(stmt);
    return -1;
}

int SqliteDB::AddTodo(Todo todo) {
    std::string sql =
        "INSERT INTO todo "
        "(title, description, status, due_date, created_at, updated_at)"
        " VALUES ("
        "'" +
        todo.title + "', '" + todo.description + "', '" + todo.status + "', '', '" + todo.created_at + "', '" + todo.updated_at + "');";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return -1;
    } else {
        int id = sqlite3_last_insert_rowid(m_db);
        std::cout << "Record created successfully, ID: " << id << std::endl;

        return id;
    }
}

bool SqliteDB::UpdateTodo(Todo todo) {
    std::string sql = "UPDATE todo SET title = '" + todo.title + "', category = '" + std::to_string(todo.category) + "', description = '" +
                      todo.description + "', status = '" + todo.status + "', updated_at = '" + todo.updated_at +
                      "' WHERE id = " + std::to_string(todo.id) + ";";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    } else {
        std::cout << "Record updated successfully" << std::endl;
        return true;
    }
}

bool SqliteDB::DeleteTodoById(int id) {
    std::string sql = "DELETE FROM todo WHERE id = " + std::to_string(id) + ";";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    } else {
        std::cout << "Record deleted successfully" << std::endl;
        return true;
    }
}

Todo SqliteDB::GetTodoById(int id) {
    Todo todo;
    // select everything for the id and join category to get the name
    std::string sql =
        "SELECT todo.id, todo.category, todo.title, todo.description, todo.status, todo.due_date, todo.created_at, todo.updated_at, "
        "category.name "
        "FROM todo "
        "LEFT JOIN category ON todo.category = category.id "
        "WHERE todo.id = " +
        std::to_string(id) + ";";
    // std::string sql = "SELECT * FROM todo WHERE id = " + std::to_string(id) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            todo.id = sqlite3_column_int(stmt, 0);
            todo.category = sqlite3_column_int(stmt, 1);
            todo.title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            todo.description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            todo.status = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            todo.due_date = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            todo.created_at = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            todo.updated_at = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));

            const char* category_name_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
            if (category_name_text != nullptr) {
                todo.category_name = std::string(category_name_text);
            } else {
                todo.category_name = "";
            }

            std::cout << "Fetched Todo, ID: " << todo.id << std::endl;
        }
    }
    sqlite3_finalize(stmt);
    return todo;
}

std::map<int, Todo> SqliteDB::GetAllTodos() {
    std::map<int, Todo> todos;
    std::string sql = "SELECT todo.id, todo.category, todo.title, todo.description, todo.status, todo.due_date, todo.created_at, todo.updated_at, category.name FROM todo LEFT JOIN category ON todo.category = category.id ORDER BY todo.id DESC;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            Todo todo;
            todo.id = sqlite3_column_int(stmt, 0);
            todo.category = sqlite3_column_int(stmt, 1);
            todo.title = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            todo.description = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            todo.status = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            todo.due_date = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            todo.created_at = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            todo.updated_at = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));

            const char* category_name_text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 8));
            if (category_name_text != nullptr) {
                todo.category_name = std::string(category_name_text);
            } else {
                todo.category_name = ""; 
            }

            todos[todo.id] = todo;
        }
    }
    sqlite3_finalize(stmt);
    std::cout << "Fetched all todos, size: " << todos.size() << std::endl;
    return todos;
}

}