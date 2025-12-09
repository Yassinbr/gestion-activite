cmake_minimum_required(VERSION 3.16)

project(BALII LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.7.3 COMPONENTS
    Core
    Gui
    Widgets
    Sql
    Network
    PrintSupport
    Charts
    REQUIRED
)

qt_standard_project_setup()

qt_add_executable(BALII
    main.cpp
    activite.cpp
    connection.cpp
    statistics.cpp
    qr_activite.cpp
    qr_dialog.cpp
    recommendations_dialog.cpp

    activite.h
    connection.h
    statistics.h
    qr_activite.h
    qr_dialog.h
    recommendations_dialog.h

    activite.ui
)

target_link_libraries(BALII PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::PrintSupport
    Qt6::Charts
)
