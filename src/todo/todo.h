#pragma once

#include <string>

struct Todo {
    int id = -1;
    std::string title;
    std::string description;
    std::string status;
    std::string due_date;
    std::string created_at;
    std::string updated_at;
};
