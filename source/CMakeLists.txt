if (CMAKE_BUILD_TYPE MATCHES Debug)
add_compile_options(
        # warnings
        -Wall -Wextra -Wshadow -Wfloat-equal -Wconversion
        # sanitizers
        #-fsanitize=address,undefined
        -fno-omit-frame-pointer
        -fno-sanitize-recover=all
        # debug mode of STL
        -g
        # -D_GLIBCXX_DEBUG # set debug macro for libstdc++ (gcc std lib)
        # -D_LIBCPP_DEBUG # set debug macro for libc++ (clang std lib)
        -D DEBUG
)
add_link_options(
        #-fsanitize=address,undefined
        -fno-omit-frame-pointer
)
endif()
if (CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options(
            -O2
    )
endif()
add_executable(example example.cpp)
