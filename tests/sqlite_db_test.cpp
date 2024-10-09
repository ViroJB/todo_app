#include "gtest/gtest.h"
#include "database/sqlite_db.h"

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
    EXPECT_TRUE(db.Connect("test.db"));
    TodoApp::Setup::Run("test.db");

    // Test AddTodo function
    TodoApp::Todo todo1;
    todo1.title = "Test Todo 1";
    todo1.description = "Test Description 1";
    todo1.status = "Pending";
    todo1.created_at = "2024-05-09";
    todo1.updated_at = "2024-05-09";
    int id1 = db.AddTodo(todo1);
    ASSERT_NE(id1, -1); // Check if id is valid

    // Test UpdateTodo function
    TodoApp::Todo todo2;
    todo2.id = id1;
    todo2.title = "Updated Test Todo";
    todo2.description = "Updated Test Description";
    ASSERT_TRUE(db.UpdateTodo(todo2));

    // Test GetTodoById function
    TodoApp::Todo fetchedTodo = db.GetTodoById(id1);
    EXPECT_EQ(fetchedTodo.title, todo2.title);
    EXPECT_EQ(fetchedTodo.description, todo2.description);

    // Test GetAllTodos function
    std::map<int, TodoApp::Todo> allTodos = db.GetAllTodos();
    ASSERT_GT(allTodos.size(), 0); // Ensure there are todos in the database

    // Test DeleteTodoById function
    EXPECT_TRUE(db.DeleteTodoById(id1));
}