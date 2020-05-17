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
    Model/GridModel.h
    )

set(GRID_FILES
    GridGenerator/GridGenerator.cpp
    GridGenerator/GridGenerator.h
    GridGenerator/RandomGridGenerator.cpp
    GridGenerator/TestGridGenerator.cpp
    )

set(MVC_FILES
    Model/GridModel.cpp
    Model/GridModel.h
    Model/StepCommand.cpp
    Model/StepCommand.h
    )

add_executable(LoaderGame
    loadermain.cpp
    ${GRID_FILES}
    ${MVC_FILES}
    ${MOC_WRAPPERS}
    ${QRC_WRAPPERS}
    )

target_compile_definitions(LoaderGame PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(LoaderGame PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Qml Qt5::Widgets)
