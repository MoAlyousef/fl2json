cmake_minimum_required(VERSION 3.15)
project(fl2json)

# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-fsanitize=address")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(fl2json src/main.cpp src/token.cpp src/lexer.cpp src/parser.cpp src/ast.cpp)
target_compile_features(fl2json PRIVATE cxx_std_20)
target_link_libraries(fl2json PRIVATE nlohmann_json::nlohmann_json)

