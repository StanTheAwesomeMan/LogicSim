cmake_minimum_required(VERSION 3.16)

project(LogicSim VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt6Core_INCLUDE_DIRS} ${Qt6Widgets_INCLUDE_DIRS} ${Qt6Gui_INCLUDE_DIRS})
qt_standard_project_setup()

file(GLOB LogicSim_SRC CONFIGURE_DEPENDS
    "src/*.cpp"
    "include/*.h"
    "font/fonts.qrc"
)

add_executable(LogicSim ${LogicSim_SRC})

target_link_libraries(LogicSim PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)
