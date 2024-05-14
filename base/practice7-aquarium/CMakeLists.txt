cmake_minimum_required(VERSION 3.5)

project("practice7-aquarium" CXX)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)

if(WIN32)
  add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${Qt6_DIR}/../../tools/Qt6/bin/windeployqt $<TARGET_FILE:${PROJECT_NAME}>
  )

  set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE TRUE)
endif(WIN32)
