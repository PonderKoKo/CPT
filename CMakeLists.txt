cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project(CPT)
set (CMAKE_CXX_STANDARD 23)
add_compile_options(
        -Wall -Wshadow -Werror=uninitialized -Werror=return-type -Werror=return-local-addr
)
if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options(
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
            -fno-sanitize-recover=all
            -D_LIBCPP_DEBUG
    )
    add_link_options(-fsanitize=address,undefined)
else()
    add_compile_options(-O2)
endif()
add_executable(solution solution.cpp)