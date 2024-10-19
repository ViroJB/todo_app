#include "sqlite_db.hpp"

namespace TodoApp {

SqliteDB::~SqliteDB() { sqlite3_close(m_db); }

bool SqliteDB::connect(const char* dbFile) {
    int rc = sqlite3_open(dbFile, &m_db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(m_db) << std::endl;
        return false;
    }

    std::cout << "Opened database successfully" << std::endl;
    return true;
}

bool SqliteDB::disconnect() {
    sqlite3_close(m_db);
    return true;
}

std::map<int, std::unique_ptr<Category>> SqliteDB::getCategories() {
    std::map<int, std::unique_ptr<Category>> categories;

    std::string sql = "SELECT * FROM category;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            categories.emplace(id, std::make_unique<Category>(id, name));
        }
    }

    sqlite3_finalize(stmt);
    std::cout << "Fetched all categories, size: " << categories.size() << std::endl;
    return categories;
}

std::unique_ptr<Category> SqliteDB::getCategoryByName(std::string searchName) {
    std::unique_ptr<Category> category = std::make_unique<Category>();
    std::string sql = "SELECT id, name FROM category WHERE name = '" + searchName + "';";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            std::string name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::cout << "Fetched category id: " << id << std::endl;
            category->id = id;
            category->name = name;
        }
    }
    sqlite3_finalize(stmt);
    return category;
}

std::map<int, std::unique_ptr<Todo>> SqliteDB::getTodosByCategory(std::shared_ptr<Category> category) {
    std::map<int, std::unique_ptr<Todo>> todos;
    std::string sql =
        "SELECT todo.id, todo.text, todo.completed, todo.due_date, todo.created_at, todo.updated_at "
        "FROM todo WHERE todo.category_id = " +
        std::to_string(category->id) + ";";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::unique_ptr<Todo> todo = std::make_unique<Todo>();
            todo->id = sqlite3_column_int(stmt, 0);
            todo->text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            todo->completed = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))) == "1";
            // TODO reenable duedate. currently errors because it can be empty and sqlite gives out a NULL then
            // todo->dueDate = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)));
            todo->createdAt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            todo->updatedAt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            // FIXME everything goes to shit here, because there is a zero inserted in categorie.id, which should never
            // happen..
            // FIXME might add todos without category, maybe
            todo->category.id = category->id;
            todo->category.name = category->name;

            todos.emplace(todo->id, std::move(todo));
        }
    }
    sqlite3_finalize(stmt);
    std::cout << "Fetched all todos, size: " << todos.size() << std::endl;
    return todos;
}

// todo
bool SqliteDB::addCategory(std::shared_ptr<Category> category) {
    std::string sql =
        "INSERT INTO category (name) "
        "VALUES ('" + category->name + "');";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }

    int id = sqlite3_last_insert_rowid(m_db);
    std::cout << "Category created successfully, ID: " << id << std::endl;

    return true;
}

// todo
bool SqliteDB::deleteCategory(std::shared_ptr<Category> category) {
    std::string sql = "DELETE FROM category WHERE id = " + std::to_string(category->id) + ";";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    } else {
        std::cout << "Category deleted successfully" << std::endl;
        return true;
    }
}

bool SqliteDB::addTodo(std::unique_ptr<Todo> todo) {
    int completed = todo->completed;
    // TODO add proper due_date
    std::string sql =
        "INSERT INTO todo "
        "(category_id, text, completed, due_date)"
        " VALUES ('" +
        std::to_string(todo->category.id) +
        "', "
        "'" +
        todo->text + "', '" + std::to_string(completed) + "', '');";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }

    int id = sqlite3_last_insert_rowid(m_db);
    std::cout << "Todo created successfully, ID: " << id << std::endl;

    return true;
}

bool SqliteDB::updateTodo(std::unique_ptr<Todo> todo) {
    int completed = todo->completed;
    std::string sql = "UPDATE todo SET text = '" + todo->text + "', category_id = '" +
                      std::to_string(todo->category.id) + "', completed = '" + std::to_string(completed) +
                      "'  WHERE id = " + std::to_string(todo->id) + ";";
    char* err_msg;
    int rc = sqlite3_exec(m_db, sql.c_str(), NULL, 0, &err_msg);
    if (rc != SQLITE_OK) {
        std::cout << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }
    std::cout << "Record updated successfully" << std::endl;
    return true;
}

bool SqliteDB::deleteTodoById(int id) {
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

std::unique_ptr<Todo> SqliteDB::getTodoById(int id) {
    std::unique_ptr<Todo> todo;
    // select everything for the id and join category to get the name
    std::string sql =
        "SELECT todo.id, todo.category_id, todo.text, todo.completed, todo.due_date, todo.created_at, todo.updated_at, "
        "category.name "
        "FROM todo "
        "LEFT JOIN category ON todo.category_id = category.id "
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
            todo->id = sqlite3_column_int(stmt, 0);
            todo->category.id = sqlite3_column_int(stmt, 1);
            todo->text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            todo->completed = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))) == "1";
            todo->dueDate = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            todo->createdAt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            todo->updatedAt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            todo->category.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));

            std::cout << "Fetched Todo, ID: " << todo->id << std::endl;
        }
    }
    sqlite3_finalize(stmt);
    return todo;
}

std::map<int, std::unique_ptr<Todo>> SqliteDB::getTodos() {
    std::map<int, std::unique_ptr<Todo>> todos;
    std::string sql =
        "SELECT todo.id, todo.category_id, todo.text, todo.completed, todo.due_date, todo.created_at, todo.updated_at, category.name FROM todo LEFT JOIN category ON todo.category_id = category.id;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::unique_ptr<Todo> todo = std::make_unique<Todo>();
            todo->id = sqlite3_column_int(stmt, 0);
            todo->category.id = sqlite3_column_int(stmt, 1);
            todo->text = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)));
            todo->completed = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3))) == "1";

            // TODO reenable duedate. currently errors because it can be empty and sqlite gives out a NULL then
            // todo->dueDate = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4)));
            todo->createdAt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5)));
            todo->updatedAt = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6)));
            // FIXME everything goes to shit here, because there is a zero inserted in categorie.id, which should never happen..
            // FIXME might add todos without category, maybe
            todo->category.name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 7)));

            todos.emplace(todo->id, std::move(todo));
        }
    }
    sqlite3_finalize(stmt);
    std::cout << "Fetched all todos, size: " << todos.size() << std::endl;
    return todos;
}

}  // namespace TodoApp