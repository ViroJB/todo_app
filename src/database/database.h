#pragma once

#include <map>

#include "../todo/todo.h"


namespace TodoApp {

class Database {
   public:
    virtual bool Connect(const char* db_file) = 0;
    virtual void Disconnect() = 0;

    virtual int AddTodo(Todo todo) = 0;
    virtual bool UpdateTodo(Todo todo) = 0;
    virtual bool DeleteTodoById(int id) = 0;

    virtual Todo GetTodoById(int id) = 0;
    virtual std::map<int, Todo> GetAllTodos() = 0;

    virtual std::map<int, std::string> GetAllCategories() = 0;
    virtual int GetCategoryByName(std::string name) = 0;
};

}