cmake_minimum_required(VERSION 3.28)

find_package(Qt6 COMPONENTS Core  Widgets  Gui REQUIRED)

if (Qt6_FOUND)
        message(STATUS "Qt6 found successfully")

        add_library(Qt INTERFACE)
        target_link_libraries(Qt INTERFACE Qt6::Core Qt6::Widgets Qt6::Gui)
else()
        message(STATUS "Qt6 not found")
endif()
