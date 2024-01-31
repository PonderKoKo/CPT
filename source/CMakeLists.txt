add_compile_options(-isystem /Users/konradletz/Documents/projects/CPT)
if (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(
            -O2
    )
else()
add_compile_options(
        -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion
        -O0
        -D DEBUG
)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
add_compile_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all
        -fno-optimize-sibling-calls
        #-include-pch bits/stdc++.pch
)
add_link_options(
        -fsanitize=address,undefined
        -fno-omit-frame-pointer
)
endif()
endif()
add_executable(example example.cpp)
