cmake_minimum_required(VERSION 3.10)
project(baba-is-you)

set(TARGET_PATH ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin CACHE PATH "Path of the target to be built.")
set(BUILD_GODOT_CPP ON CACHE BOOL "Build godot-cpp library automatically.")
set(GODOT_CPP_TARGET_PATH ${CMAKE_SOURCE_DIR}/bin CACHE PATH "Target path of the godot-cpp library.")

set(BITS 32)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(BITS 64)
endif (CMAKE_SIZEOF_VOID_P EQUAL 8)

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME)
string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

# Change the output directory
set(BUILD_PATH ${TARGET_PATH}/${SYSTEM_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${BUILD_PATH}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_PATH}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG "${BUILD_PATH}")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE "${BUILD_PATH}")

# Specify C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES src/*.c**)
file(GLOB_RECURSE HEADERS src/*.h**)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        godot-cpp/godot_headers
        godot-cpp/include
        godot-cpp/include/gen
        godot-cpp/include/core
)

if (ANDROID)
    # Added the android abi after system name
    set(SYSTEM_NAME ${SYSTEM_NAME}.${ANDROID_ABI})
    # Android does not have the bits at the end if you look at the main godot repo build
    set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}.${BUILD_TYPE}")
else ()
    set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}.${BUILD_TYPE}.${BITS}")
endif ()

if (BUILD_GODOT_CPP)
    add_subdirectory(godot-cpp)
    target_link_libraries(${PROJECT_NAME} PUBLIC godot-cpp)
else ()
    # Generate the name of godot-cpp library
    if (ANDROID)
        set(GODOT_CPP_TARGET "godot-cpp.${SYSTEM_NAME}.${BUILD_TYPE}")
    else ()
        set(GODOT_CPP_TARGET "godot-cpp.${SYSTEM_NAME}.${BUILD_TYPE}.${BITS}")
    endif ()

    find_library(GODOT_CPP ${GODOT_CPP_TARGET} ${GODOT_CPP_TARGET_PATH})

    target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${GODOT_CPP})
endif ()
