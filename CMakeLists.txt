cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include(FindPkgConfig)
if(!${PKG_CONFIG_FOUND})
  MESSAGE(FATAL_ERROR "pkg-config required. Please install it")
  return ("Error - pkg-config not found")
endif()

pkg_check_modules(GSTREAMER gstreamer-1.0>=1.6 gstreamer-video-1.0>=1.6 REQUIRED)

find_package(Qt5 COMPONENTS REQUIRED
             Quick
             QuickControls2
             QuickWidgets
             Qml
             Widgets)

file(GLOB_RECURSE PROJECT_HEADERS "include/*.h")
file(GLOB_RECURSE PROJECT_SOURCES "source/*.cpp")
file(GLOB_RECURSE PROJECT_RESOURCES "resources/*.qrc")

set(TARGET_NAME simpletest)

add_executable(${TARGET_NAME}
    ${PROJECT_HEADERS}
    ${PROJECT_SOURCES}
    ${PROJECT_RESOURCES})


link_directories(${GSTREAMER_LIBRARY_DIRS})
include_directories (${GSTREAMER_INCLUDE_DIRS})

target_include_directories(${TARGET_NAME} PUBLIC "include")

target_link_libraries(${TARGET_NAME} PUBLIC
                          Qt5::Quick
                          Qt5::QuickControls2
                          Qt5::QuickWidgets
                          Qt5::Qml
                          Qt5::Widgets
                          ${GSTREAMER_LIBRARIES})


install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
