cmake_minimum_required(VERSION 3.16.3)

project (ComputationalGeometry LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE Foo_SOURCES "*.cpp")
file(GLOB_RECURSE Foo_HEADERS "*.h")

#   Retrieve conan.cmake
if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake" "${CMAKE_BINARY_DIR}/conan.cmake")
endif ()

include("${CMAKE_BINARY_DIR}/conan.cmake")

conan_cmake_run(CONANFILE "conanfile.txt" BASIC_SETUP UPDATE BUILD missing)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

find_package(glm)
find_package(glfw3)
find_package(GLEW)


set (Foo_INCLUDE_DIRS "")
foreach (_headerFile ${Foo_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND Foo_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES Foo_INCLUDE_DIRS)

# message(STATUS ${Foo_SOURCES})

set(PROJECT_IMGUI_FILES
        imconfig.h
        imgui.cpp imgui.h
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_internal.h
        imgui_widgets.cpp
        imstb_rectpack.h
        imstb_textedit.h
        imstb_truetype.h

        imgui_impl_glfw.cpp imgui_impl_glfw.h
        imgui_impl_opengl3.cpp imgui_impl_opengl3.h
        )

list(TRANSFORM PROJECT_IMGUI_FILES PREPEND "../Dependencies/imgui/")

add_executable (FooExe ${Foo_SOURCES} ${PROJECT_IMGUI_FILES})

message(STATUS $(Foo_SOURCES))

# Include delle directory

target_include_directories(FooExe PRIVATE ${Foo_INCLUDE_DIRS})
target_include_directories(FooExe PRIVATE ../Dependencies/GLM)
target_include_directories(FooExe PRIVATE ../Dependencies)

# Linking delle library (conan)
target_link_libraries(FooExe PRIVATE glm::glm glfw::glfw GLEW::GLEW)

