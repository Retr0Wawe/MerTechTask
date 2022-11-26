cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

project(Task LANGUAGES CXX)

file(GLOB_RECURSE TASK_HEADERS ${PROJECT_SOURCE_DIR}/include/*.hpp)

file(GLOB_RECURSE TASK_SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME}
    ${TASK_SOURCES}
    main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)