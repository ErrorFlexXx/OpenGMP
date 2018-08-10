cmake_minimum_required(VERSION 3.3)

set(TARGET_NAME OpenGMP-Launcher)

project(${TARGET_NAME})

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "-fPIC -Wall -Wextra")
endif()

include_directories(${Qt5Widgets_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${Qt5Network_INCLUDE_DIRS} ${Qt5Multimedia_INCLUDE_DIRS})

# list include files to variables
file (GLOB_RECURSE INCLUDE_FILES
    LIST_DIRECTORIES false
    *.h
)

# list source files to variables
file (GLOB_RECURSE SRC_FILES
    *.cpp
    *.h
)

# list ui files to variables
file(GLOB_RECURSE UI_FILES
    *.ui
)

# list resource files to variables
file(GLOB_RECURSE RES_FILES
    *.qrc
    *.rc
)

qt5_wrap_ui(UI_HEADERS ${UI_FILES})

add_executable(${TARGET_NAME} ${INCLUDE_FILES} ${SRC_FILES} ${UI_HEADERS} ${RES_FILES})

target_link_libraries(${TARGET_NAME} Qt5::Widgets ${CMAKE_THREAD_LIBS_INIT} RakNetLibStatic)
