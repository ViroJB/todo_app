cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(todo_app)

include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCES
        src/app/app.cpp
        src/database/sqlite_db.cpp
        src/config/config.cpp
        src/todo/todo_controller.cpp
        src/gui/gui.cpp
        src/gui/gui.hpp
)

find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(todo_app
        src/main.cpp
        ${SOURCES}
)

target_link_libraries(todo_app PRIVATE unofficial::sqlite3::sqlite3)
target_link_libraries(todo_app PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(todo_app PRIVATE fmt::fmt)
target_link_libraries(todo_app PRIVATE imgui::imgui)
target_link_libraries(todo_app PRIVATE glfw)
target_link_libraries(todo_app PRIVATE OpenGL::GL)

target_include_directories(todo_app PRIVATE ${OPENGL_INCLUDE_DIR})

enable_testing()

add_executable(tests
        tests/tests.cpp
        tests/todo_controller_test.cpp
        tests/sqlite_db_test.cpp
        src/database/sqlite_db.cpp
        src/config/config.cpp
)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(tests PRIVATE unofficial::sqlite3::sqlite3)
add_test(AllTests tests)