cmake_minimum_required(VERSION 3.28)
project(dolkindas CXX)

file(COPY .env DESTINATION ${CMAKE_BINARY_DIR})
set(CMAKE_CXX_STANDARD 20)
add_library(mod)

target_sources(mod
        PUBLIC
        FILE_SET CXX_MODULES FILES
        mod/getenv.cxx
)

add_executable(dolkindas
        src/main.cpp
        src/commands.hpp
        src/commands.cpp
)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
target_compile_definitions(dolkindas PUBLIC DPP_CORO FIRST_TIME)
target_link_libraries(dolkindas mod dpp)
