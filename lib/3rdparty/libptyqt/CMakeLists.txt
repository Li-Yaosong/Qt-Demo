cmake_minimum_required(VERSION 3.16)

project(ptyqt LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network)

set(SOURCES
    iptyprocess.h
    ptyqt.cpp ptyqt.h
)

if (WIN32)
    list(APPEND SOURCES
        # winptyprocess.cpp winptyprocess.h
        conptyprocess.cpp conptyprocess.h
    )
else()
    list(APPEND SOURCES unixptyprocess.cpp unixptyprocess.h)
endif()

add_library(ptyqt STATIC ${SOURCES})
target_link_libraries(ptyqt PUBLIC Qt::Core)

if (WIN32)
  target_link_libraries(ptyqt PRIVATE Qt::Network)
  #target_compile_definitions(ptyqt PRIVATE PTYQT_DEBUG)
endif()

set_target_properties(ptyqt
  PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}
    QT_COMPILE_OPTIONS_DISABLE_WARNINGS ON
    POSITION_INDEPENDENT_CODE ON
)
