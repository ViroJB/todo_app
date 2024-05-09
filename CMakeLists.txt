cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(todo_app)

# Set the build type. Options are: None, Debug, Release, RelWithDebInfo, MinSizeRel.
set(CMAKE_BUILD_TYPE Debug) 

include_directories(C:\\Development\\Tools\\vcpkg\\installed\\x64-windows\\include)
link_directories(C:\\Development\\Tools\\vcpkg\\installed\\x64-windows\\lib)

find_package(wxWidgets CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

# create seperate cmakelist files for src and tests dirs and see move the stuff there, see how it goes
# add_subdirectory(src)
# add_subdirectory(tests)

add_executable(todo_app 
    WIN32
    src/app/app.cpp
    src/database/sqlite_db.cpp
    src/config/config.cpp
    src/todo/todo_controller.cpp
    src/view/main_frame.cpp
    src/view/main_menu/main_menu.cpp
    src/view/panels/todo_list_panel.cpp
    src/view/panels/todo_add_panel.cpp
    src/view/panels/todo_edit_panel.cpp
)

target_link_libraries(todo_app PRIVATE wx::core wx::base fmt::fmt)
target_link_libraries(todo_app PRIVATE unofficial::sqlite3::sqlite3)

enable_testing()

# so we have to create a seperate executable for each test file to make em show at least a bit seperate in vscode testexplorer
# do we have to link the libraries like sqlite for the tests too? i guess?
add_executable(tests
    tests/tests.cpp
    tests/todo_controller_test.cpp
    tests/sqlite_db_test.cpp
    src/database/sqlite_db.cpp
    src/config/config.cpp # for now because of bad design
)

target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
target_link_libraries(tests PRIVATE unofficial::sqlite3::sqlite3)
add_test(AllTests tests)