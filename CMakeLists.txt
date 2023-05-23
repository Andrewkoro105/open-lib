cmake_minimum_required(VERSION 3.0)
project(openLib)

set(CMAKE_CXX_STANDARD 17)

file(COPY lib/openLib.hpp lib/openLib.inl DESTINATION ${CMAKE_CURRENT_LIST_DIR}/include/openLib)
file(GLOB_RECURSE headers "lib/*.hpp" "lib/*.inl")

add_library(lib SHARED lib.cpp)

add_library(${PROJECT_NAME} lib/openLib.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${headers}")

add_executable(${PROJECT_NAME}_ex main.cpp)
target_link_libraries(${PROJECT_NAME}_ex PUBLIC ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
        )

install(EXPORT ${PROJECT_NAME}
        FILE ${PROJECT_NAME}Config.cmake
        NAMESPACE ${PROJECT_NAME}::
        DESTINATION lib/cmake/${PROJECT_NAME}
        )