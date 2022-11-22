cmake_minimum_required(VERSION 3.14)

project(EjemploTesting LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

enable_testing(true)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Test)

add_executable(EjemploTesting
  TestQString.cpp
)
#main.cpp -- sacado -- no se usa

target_link_libraries(EjemploTesting Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Test)

#install(TARGETS EjemploTesting
#    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
