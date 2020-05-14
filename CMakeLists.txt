cmake_minimum_required(VERSION 3.5)

project(LoaderGame LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Quick Qml Widgets REQUIRED)

qt5_add_resources(QRC_WRAPPERS
    resource.qrc
    )

# MOC
qt5_wrap_cpp(MOC_WRAPPERS
    MVC/GridModel.h
    MVC/GridTableView.h
    GridWindow.h
    )

# UIC
qt5_wrap_ui(UIC_WRAPPERS
    GridWindow.ui
    )

set(GRID_FILES
    GridGenerator/GridGenerator.cpp
    GridGenerator/GridGenerator.h
    GridGenerator/RandomGridGenerator.cpp
    )

set(MVC_FILES
    MVC/GridTableView.cpp
    MVC/GridTableView.h
    MVC/GridModel.cpp
    MVC/GridModel.h
    MVC/GridDelegate.cpp
    MVC/GridDelegate.h
    )

add_executable(LoaderGame
    loadermain.cpp
    GridWindow.cpp
    GridWindow.h
    ${GRID_FILES}
    ${MVC_FILES}
    ${MOC_WRAPPERS}
    ${QRC_WRAPPERS}
    ${UIC_WRAPPERS}
    )

target_compile_definitions(LoaderGame PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(LoaderGame PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Qml Qt5::Widgets)
