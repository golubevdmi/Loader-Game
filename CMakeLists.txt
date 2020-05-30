cmake_minimum_required(VERSION 3.5)

set(project_name Sokoban)
project(${project_name} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Gui Quick Qml Widgets REQUIRED)

qt5_add_resources(QRC_WRAPPERS
    resource.qrc
    )

# MOC
qt5_wrap_cpp(MOC_WRAPPERS
    Model/SokobanModel.h
    )

set(GRID_FILES
    GridGenerator/GridGenerator.cpp
    GridGenerator/GridGenerator.h
    GridGenerator/RandomGridGenerator.cpp
    GridGenerator/GridMazes.cpp
    )

set(MVC_FILES
    Model/SokobanModel.cpp
    Model/SokobanModel.h
    Model/StepCommand.cpp
    Model/StepCommand.h
    )

add_executable(${project_name}
    sokobanmain.cpp
    FieldFlags.h
    ${GRID_FILES}
    ${MVC_FILES}
    ${MOC_WRAPPERS}
    ${QRC_WRAPPERS}
    )

target_compile_definitions(${project_name} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${project_name} PRIVATE Qt5::Core Qt5::Gui Qt5::Quick Qt5::Qml Qt5::Widgets)
