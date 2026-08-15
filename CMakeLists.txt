cmake_minimum_required(VERSION 3.10)
project(CVison C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra)
endif()

add_executable(cvison
    main.c
    utils/conv.c
    utils/libPPM.c
)

target_include_directories(cvison PRIVATE header)

if(NOT MSVC)
    target_link_libraries(cvison m)
endif()
