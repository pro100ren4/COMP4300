cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME Assigment2)
project(${PROJECT_NAME})

add_executable(${PROJECT_NAME}
  src/main.cpp
  src/Entity.h
  src/Entity.cpp
  src/EntityManager.h
  src/EntityManager.cpp
  src/Game.h
  src/Game.cpp
  src/Vec2.h
  src/Vec2.cpp
  src/Config.h
  src/Components.h
)

add_subdirectory(external/raylib-5.5)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
          ${CMAKE_SOURCE_DIR}/res
          $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)
