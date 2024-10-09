#pragma once

#include <string>

namespace TodoApp {

struct Todo {
    int id = -1;
    int category = -1;
    std::string title;
    std::string description;
    std::string status = "pending";
    std::string due_date = "";
    std::string created_at = "";
    std::string updated_at = "";
    std::string category_name = "";
};

}