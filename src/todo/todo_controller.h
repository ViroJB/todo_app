#pragma once

#include <map>
#include <string>

#include "../config/config.h"
#include "../database/database.h"
#include "../database/sqlite_db.h"
#include "todo.h"


class TodoController {
   public:
    TodoController();
    ~TodoController();

    void Add(Todo todo);
    void Remove(int id);
    void Update(Todo todo);
    Todo Get(int id);
    std::map<int, Todo>* GetAll();
    void Save();

    std::map<int, std::string> GetAllCategories();
    int GetCategoryByName(std::string name);

   private:
    std::map<int, Todo> m_todos;
    Database* m_database;
};