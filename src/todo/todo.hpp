#pragma once

#include <string>

#include "category.hpp"

namespace TodoApp {

struct Todo {
    // todo add constructor with id, cat and text and maybe just with cat and text for adding
    // Todo()
    int id = -1;
    Category category;
    std::string text;
    bool completed = false;
    std::string dueDate;
    std::string createdAt;
    std::string updatedAt;
};

}