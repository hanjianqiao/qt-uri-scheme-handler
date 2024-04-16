cmake_minimum_required(VERSION 3.5)

project(qt-uri-scheme-handler VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets LinguistTools)

set(TS_FILES qt-uri-scheme-handler-example_zh_CN.ts)

qt_add_library(qt-uri-scheme-handler SHARED
    hurischemehandler.h hurischemehandler.cpp
)

target_compile_definitions(qt-uri-scheme-handler PRIVATE QT_URL_SCHEME_HANDLER_LIB)
target_link_libraries(qt-uri-scheme-handler PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(PROJECT_IS_TOP_LEVEL)

    set(PROJECT_SOURCES
            main.cpp
            widget.cpp
            widget.h
            ${TS_FILES}
    )

    if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
        qt_add_executable(qt-uri-scheme-handler-example
            MANUAL_FINALIZATION
            qt-uri-scheme-handler-example.rc
            ${PROJECT_SOURCES}
        )


    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET qt-uri-scheme-handler APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

        qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    else()
        if(ANDROID)
            add_library(qt-uri-scheme-handler-example SHARED
                ${PROJECT_SOURCES}
            )
    # Define properties for Android with Qt 5 after find_package() calls as:
    #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
        else()
            add_executable(qt-uri-scheme-handler-example
                ${PROJECT_SOURCES}
            )
        endif()

        qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    endif()

    target_link_libraries(qt-uri-scheme-handler-example PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    target_link_libraries(qt-uri-scheme-handler-example PRIVATE qt-uri-scheme-handler)

    # set_target_properties(qt-uri-scheme-handler-example PROPERTIES LINK_FLAGS
    #         "/MANIFESTUAC:\"level='requireAdministrator' uiAccess='false'\"")

    # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
    # If you are developing for iOS or macOS you should consider setting an
    # explicit, fixed bundle identifier manually though.
    if(${QT_VERSION} VERSION_LESS 6.1.0)
      set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.qt-uri-scheme-handler-example)
    endif()
    set_target_properties(qt-uri-scheme-handler-example PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
    )

    include(GNUInstallDirs)
    install(TARGETS qt-uri-scheme-handler-example
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )

    if(QT_VERSION_MAJOR EQUAL 6)
        qt_finalize_executable(qt-uri-scheme-handler-example)
    endif()
endif()
