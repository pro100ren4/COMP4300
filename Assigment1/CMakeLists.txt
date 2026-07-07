cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Assigment1)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
	src/main.cpp
)

add_subdirectory(external/raylib-5.5)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/res
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)