cmake_minimum_required(VERSION 3.10)

project(LibraryInjector CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/src/imgui)

add_library(imgui STATIC
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_impl_dx11.cpp
    ${IMGUI_DIR}/imgui_impl_win32.cpp
 "src/LibInjectorApp.h" "src/LibInjectorApp.cpp" "src/Injector.h" "src/Injector.cpp" "src/HandleWrapper.h" "src/HandleWrapper.cpp")

target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
)

add_executable(LibraryInjector src/main.cpp "src/LibInjectorApp.h" "src/LibInjectorApp.cpp" "src/Injector.h" "src/Injector.cpp" "src/HandleWrapper.h" "src/HandleWrapper.cpp")

target_link_libraries(LibraryInjector PRIVATE imgui)

if(WIN32)
    target_link_libraries(LibraryInjector PRIVATE d3d11 dxgi)
endif()