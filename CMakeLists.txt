cmake_minimum_required(VERSION 3.25)
project(dolkindas VERSION 0.44 DESCRIPTION "a general purpose discord bot for meowkindas")

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/.env
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#file(GLOB_RECURSE LIBRARY_FILES ${CMAKE_SOURCE_DIR}/lib/*.{cpp,h,hpp,cxx})
#file(COPY ${LIBRARY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})



#TODO: Refracter this
include(FetchContent)

#FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
#FetchContent_MakeAvailable(json)


add_executable(dolkindas
        main.cpp
        lib/getenv.cpp
        lib/commands.hpp
)
set(CMAKE_CXX_STANDARD 23)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")


target_link_libraries(dolkindas PRIVATE dpp )
target_compile_definitions(dolkindas PUBLIC DPP_CORO)
#target_link_libraries(dolkindas simdjson)
#target_include_directories(dolkindas ${CMAKE_SOURCE_DIR}/include)


#file(STRINGS .env TOKENS)
#add_definitions(-DTOKEN=${TOKENS})

#set(CMAKE_CXX_EXTENSIONS OFF)
set_target_properties(dolkindas PROPERTIES
        CXX_STANDARD_REQUIRED ON
)
