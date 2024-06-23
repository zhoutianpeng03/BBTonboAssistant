cmake_minimum_required(VERSION 3.5)

project(BBTonboAssitant VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Multimedia)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Multimedia)


set(PROJECT_SOURCES
        src/main.cpp


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(BBTonboAssitant
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        src/BBTonboAssistantWindow.h
        src/BBTonboAssistantWindow.cpp
        resource.qrc
        src/audio/BBTonboAudioWorker.h
        src/audio/BBTonboAudioWorker.cpp
        src/audio/BBTonboTextWorker.h
        src/audio/BBTonboTextWorker.cpp
        src/audio/BBTonboSpeakerWorker.h
        src/audio/BBTonboSpeakerWorker.cpp
        src/audio/BBTonboSession.h
        src/audio/BBTonboSession.cpp
        src/util/BBTonboAudioInputHelper.h
        src/util/BBTonboAudipInputHelper.cpp
        src/BBTonboAssistantController.h
        src/BBTonboAssistantController.cpp
        src/BBTonboContext.h
        src/BBTonboContext.cpp
        Info.plist
        src/base/ThreadSafeQueue.h
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET BBTonboAssitant APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(BBTonboAssitant SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(BBTonboAssitant
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(BBTonboAssitant PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.BBTonboAssitant)
endif()
set_target_properties(BBTonboAssitant PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
)

include(GNUInstallDirs)
install(TARGETS BBTonboAssitant
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(BBTonboAssitant)
endif()
