set(SOURCES src/main.cpp
        src/MainWindow.cpp
        src/MainWindow.h
        src/SourceImageViewWidget.cpp
        src/SourceImageViewWidget.h
        src/AbstractImageViewWidget.cpp
        src/AbstractImageViewWidget.h
        src/ModifiedImageViewWidget.cpp
        src/ModifiedImageViewWidget.h
        src/archiver.cpp
        src/archiver.h
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt)
