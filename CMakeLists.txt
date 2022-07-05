cmake_minimum_required(VERSION 3.13.4)
project(Octothorpe VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

set (LEXER
    Lexer/lexer.cpp
)

add_executable(${PROJECT_NAME} main.cpp)

add_library(${PROJECT_NAME}-lexer STATIC ${LEXER})

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lexer)

set_target_properties(${PROJECT_NAME}-lexer PROPERTIES
                        CXX_STANDARD 17
                        CXX_STANDARD_REQUIRED ON 
)