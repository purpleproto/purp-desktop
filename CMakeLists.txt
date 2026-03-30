cmake_minimum_required(VERSION 3.19)
project(purp-desktop LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets LinguistTools)

qt_standard_project_setup()

qt_add_executable(purp-desktop
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    README.md
    .gitignore
)

qt_add_translations(
    TARGETS purp-desktop
    TS_FILES purp-desktop_ru_RU.ts
)

target_link_libraries(purp-desktop
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS purp-desktop
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET purp-desktop
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
