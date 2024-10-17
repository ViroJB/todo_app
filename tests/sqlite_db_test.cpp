#include "gtest/gtest.h"
#include "database/sqlite_db.hpp"

class SqliteDBTest : public ::testing::Test {
protected:
    // Member variables accessible to all tests
 TodoApp::SqliteDB db;

    // Set up function, called before each test
    void SetUp() override {
        // Initialize your database or any other setup
        // For simplicity, leaving it empty as the constructor handles setup
    }

    // Tear down function, called after each test
    void TearDown() override {
        // Clean up any resources used by the tests
        // For simplicity, leaving it empty as the destructor handles cleanup
    }
};

// Test fixture for all functions in SqliteDB
TEST_F(SqliteDBTest, TestAllFunctions) {
    // Test Connect function
    TodoApp::Setup::run("test.db");
    EXPECT_TRUE(db.connect("test.db"));

    // Test AddTodo function
    std::unique_ptr<TodoApp::Todo> todo1 = std::make_unique<TodoApp::Todo>();
    todo1->text = "Test Todo 1";
    todo1->completed = "Pending";
    db.addTodo(std::move(todo1));

    // // Test UpdateTodo function
    // std::unique_ptr<TodoApp::Todo> todo2 = std::make_unique<TodoApp::Todo>();
    // todo2->id = id1;
    // todo2->text = "Updated Test Todo";
    // ASSERT_TRUE(db.updateTodo(std::move(todo2)));
    //
    // // Test GetTodoById function
    // auto fetchedTodo = db.getTodoById(id1);
    // EXPECT_EQ(fetchedTodo->text, todo2->text);
    //
    // // Test GetAllTodos function
    // auto allTodos = db.getTodos();
    // ASSERT_GT(allTodos.size(), 0); // Ensure there are todos in the database
    //
    // // Test DeleteTodoById function
    // EXPECT_TRUE(db.deleteTodoById(id1));
}