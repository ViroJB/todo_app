#pragma once

#include <map>
#include <memory>

#include "todo/category.hpp"
#include "todo/todo.h"

namespace TodoApp {

class Database {
   public:
    virtual ~Database() = default;
    virtual bool connect(const char* dbFile) = 0;
    virtual bool disconnect() = 0;

    virtual bool addTodo(std::unique_ptr<Todo> todo) = 0;
    virtual bool updateTodo(std::unique_ptr<Todo> todo) = 0;
    virtual bool deleteTodoById(int id) = 0;

    virtual std::unique_ptr<Todo> getTodoById(int id) = 0;
    virtual std::map<int, std::unique_ptr<Todo>> getTodos() = 0;
    virtual std::map<int, std::unique_ptr<Todo>> getTodosByCategory(std::shared_ptr<Category> category) = 0;

    virtual std::map<int, std::unique_ptr<Category>> getCategories() = 0;
    virtual std::unique_ptr<Category> getCategoryByName(std::string name) = 0;
};

}  // namespace TodoApp