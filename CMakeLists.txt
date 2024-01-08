cmake_minimum_required(VERSION 3.25)
project(dolkindas VERSION 0.44 DESCRIPTION "a general purpose discord bot for meowkindas")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/.env
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#file(GLOB_RECURSE LIBRARY_FILES ${CMAKE_SOURCE_DIR}/lib/*.{cpp,h,hpp,cxx})
#file(COPY ${LIBRARY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



#include(FetchContent)
#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)

add_library(mod)
target_sources(mod
        PUBLIC
        FILE_SET CXX_MODULES FILES
        mod/getenv.cxx
)


add_executable(dolkindas
        src/main.cpp
#        lib/commands.hpp
)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")


target_link_libraries(dolkindas PUBLIC mod  )
target_compile_definitions(dolkindas PUBLIC DPP_CORO FIRST_TIME)
target_compile_features(dolkindas PUBLIC cxx_std_20)

#target_link_libraries(dolkindas simdjson)
#target_include_directories(dolkindas ${CMAKE_SOURCE_DIR}/include)


#file(STRINGS .env TOKENS)
#add_definitions(-DTOKEN=${TOKENS})

set_target_properties(dolkindas PROPERTIES
        CXX_STANDARD_REQUIRED ON
)
