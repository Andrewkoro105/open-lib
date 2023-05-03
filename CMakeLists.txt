cmake_minimum_required(VERSION 3.0)
project(openLib)

set(CMAKE_CXX_STANDARD 17)

add_library(lib SHARED lib.cpp)

add_library(${PROJECT_NAME}  lib/openLib.cpp)

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PUBLIC ${PROJECT_NAME})
file(GLOB_RECURSE headers "lib/*.hpp" "lib/*.inl")
message(${headers})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}-config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
        )