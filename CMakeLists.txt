cmake_minimum_required(VERSION 3.14)
project(Variant30ArcLength)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")
include(FetchContent)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(core
    src/Angle.cpp
    src/Point.cpp
    src/ArcLength.cpp
)
target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(core PUBLIC $<$<COMPILE_LANGUAGE:CXX>:/utf-8>)
endif()

add_executable(variant30_app
    src/Main.cpp
)


target_link_libraries(variant30_app PRIVATE core)


add_executable(tests
    tests/tests.cpp
)

target_include_directories(tests PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(tests
    PRIVATE
    core
    gtest
)

include(GoogleTest)
gtest_discover_tests(tests)