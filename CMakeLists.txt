cmake_minimum_required(VERSION 3.25)
project(dolkindas VERSION 0.44 DESCRIPTION "a general purpose discord bot for meowkindas")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/.env
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#TODO: Refracter this

add_executable(dolkindas
        src/main.cpp
        lib/getenv.cpp
        lib/commands.hpp
)
set(CMAKE_CXX_STANDARD 23)
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")


target_link_libraries(dolkindas dpp )

#file(STRINGS .env TOKENS)
#add_definitions(-DTOKEN=${TOKENS})

#set(CMAKE_CXX_EXTENSIONS OFF)
set_target_properties(dolkindas PROPERTIES
        CXX_STANDARD_REQUIRED ON
)
