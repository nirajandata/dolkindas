cmake_minimum_required(VERSION 3.25)
project(dolkindas VERSION 0.44 DESCRIPTION "meowindas")



add_executable(dolkindas
        src/main.cpp)

target_link_libraries(dolkindas dpp)

set_target_properties(dolkindas PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
