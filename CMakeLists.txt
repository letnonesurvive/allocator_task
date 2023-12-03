cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(allocator_task VERSION ${PROJECT_VESRION})

add_executable(allocator_task main.cpp Allocator.h Container.h)

set_target_properties(allocator_task allocator_task PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(allocator_task
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(allocator_task PRIVATE
        /W4
    )
    target_compile_options(allocator_task PRIVATE
        /W4
    )
else ()
    target_compile_options(allocator_task PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(allocator_task PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS allocator_task RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT hippiman1221@gmail.com)
include(CPack)
