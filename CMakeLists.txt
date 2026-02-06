cmake_minimum_required(VERSION 3.16)

project(dataSpliter VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)


qt_add_executable(appdataSpliter
    main.cpp
)

target_include_directories(appdataSpliter
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/c++
        ${CMAKE_CURRENT_SOURCE_DIR}/c++/backend
)
#加入qml模块
qt_add_qml_module(appdataSpliter
    URI DataSpliter
    VERSION 1.0
    QML_FILES
        qml/Main.qml
        qml/components/DicSelector.qml
        qml/components/Part.qml
    SOURCES
        c++/backend/Backend.h
        c++/backend/Backend.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appdataSpliter PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appdataSpliter
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appdataSpliter
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appdataSpliter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
