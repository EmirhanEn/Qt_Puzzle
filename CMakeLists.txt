cmake_minimum_required(VERSION 3.19)
project(Qt_Puzzle LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

# .qrc dosyalarının otomatik derlenmesi için (resimler programa gömülür)
set(CMAKE_AUTORCC ON)

# Designer'da promote edilen PuzzlePiece'in başlığı (puzzlepiece.h) bulunabilsin
set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt_add_executable(Qt_Puzzle
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    puzzlepiece.cpp
    puzzlepiece.h
    resources.qrc
)

target_link_libraries(Qt_Puzzle
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Qt_Puzzle
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Qt_Puzzle
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
