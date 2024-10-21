#pragma once
#include <string>
#include <utility>

struct Category {
    Category() = default;
    Category(int id, std::string name) : id(id), name(std::move(name)) {}
    int id = -1;
    std::string name;
};
