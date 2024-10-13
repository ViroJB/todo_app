#pragma once
#include <fmt/base.h>

#include <memory>
#include <queue>

namespace TodoApp {

class BaseCommand {
   public:
    virtual ~BaseCommand() = default;
    virtual void execute() = 0;
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
