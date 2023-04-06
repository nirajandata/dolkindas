cmake_minimum_required(VERSION 3.25)
project(dolkindas VERSION 0.44 DESCRIPTION "a general purpose discord bot for meowkindas")


add_executable(dolkindas
        src/main.cpp src/token.h)

target_link_libraries(dolkindas dpp)

#file(STRINGS .env TOKENS)
#add_definitions(-DTOKEN=${TOKENS})

set_target_properties(dolkindas PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
