#pragma once
#include <fmt/base.h>

#include <memory>
#include <queue>
#include <utility>

#include "todo/todo_controller.hpp"

namespace TodoApp {

// NOTE will probably never be used here... just some fun

// example usage:
// CommandHandler commandHandler;
// commandHandler.queueCommand<ExampleCommand>(5, 5);
// commandHandler.queueCommand<ExampleCommand>(10, 5);
// commandHandler.queueCommand<ExampleCommand>();
// std::shared_ptr<TodoController> tc = std::make_shared<TodoController>();
// std::shared_ptr<Todo> td = std::make_shared<Todo>();
// td->description = "todo add command, hehehehehe";
// commandHandler.queueCommand<AddTodoCommand>(tc, td);

// commandHandler.executeCommands();

class BaseCommand {
   public:
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
};

class AddTodoCommand : public BaseCommand {
   public:
    // AddTodoCommand() = delete;
    AddTodoCommand(std::shared_ptr<TodoController> controller, std::shared_ptr<Todo> todo)
        : controller(std::move(controller)), todo(std::move(todo)) {}

    void execute() override {
        fmt::print("Add Todo Command.\n{}\n", todo->text);

//        controller->add(*todo);
    }

   private:
    std::shared_ptr<TodoController> controller;
    std::shared_ptr<Todo> todo;
};

class ExampleCommand : public BaseCommand {
   public:
    ExampleCommand() = default;
    ExampleCommand(int a, int b) : a(a), b(b) {}

    void execute() override {
        int sum = a + b;
        fmt::print("Example Command, sum: {}\n", sum);
    }

   private:
    int a = 5;
    int b = 3;
};

class CommandHandler {
   public:
    template <typename CommandType, typename... Args>
    void queueCommand(Args&&... args) {
        m_commandQueue.push(std::make_unique<CommandType>(std::forward<Args>(args)...));
    }

    void executeCommands() {
        while (!m_commandQueue.empty()) {
            auto& command = m_commandQueue.front();
            command->execute();
            m_commandQueue.pop();
        }
    }

   private:
    std::queue<std::unique_ptr<BaseCommand>> m_commandQueue;
};

}  // namespace TodoApp
