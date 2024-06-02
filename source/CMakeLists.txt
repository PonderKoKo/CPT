set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-isystem /Users/konradletz/Documents/projects/CPT)
if (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(
            -O2
    )
else()
add_compile_options(
        -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion
        -Wno-sign-conversion
        -O0
        -g
        -DDEBUG
)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all
        -fno-optimize-sibling-calls
)
add_link_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
)
else()
    set (CMAKE_CXX_STANDARD 17)
endif()

endif()
add_executable(example example.cpp)
