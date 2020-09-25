cmake_minimum_required(VERSION 3.10)
project(baba-is-you)

set(TARGET_PATH ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin CACHE PATH "Path of the target to be built.")
set(BUILD_GODOT_CPP ON CACHE BOOL "Build godot-cpp library automatically.")
set(GODOT_CPP_TARGET_PATH ${CMAKE_SOURCE_DIR}/bin CACHE PATH "Target path of the godot-cpp library.")
set(BUILD_ANTLR_RUNTIME ON CACHE BOOL "Build ANTLR C++ runtime automatically.")

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

set(ANTLR_RUNTIME_TARGET_PATH ${BUILD_PATH} CACHE PATH "Target path of the ANTLR C++ runtime.")

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ANTLR
# Set the executable jar file of ANTLR using -DANTLR_EXECUTABLE
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions(-DANTLR4CPP_STATIC)

set(WITH_STATIC_CRT OFF)

find_package(ANTLR REQUIRED)

antlr_target(BabaIsYouLexer ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/BabaIsYouLexer.g4 LEXER)
antlr_target(BabaIsYouParser ${CMAKE_CURRENT_SOURCE_DIR}/src/grammar/BabaIsYouParser.g4 PARSER LISTENER VISITOR
        DEPENDS_ANTLR BabaIsYouLexer
        COMPILE_FLAGS -lib ${ANTLR_BabaIsYouLexer_OUTPUT_DIR})

include_directories(${ANTLR_BabaIsYouLexer_OUTPUT_DIR})
include_directories(${ANTLR_BabaIsYouParser_OUTPUT_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libs/antlr4/runtime/Cpp/runtime/src)

file(GLOB_RECURSE SOURCES src/*.c**)
file(GLOB_RECURSE HEADERS src/*.h**)

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS} ${ANTLR_BabaIsYouLexer_CXX_OUTPUTS} ${ANTLR_BabaIsYouParser_CXX_OUTPUTS} "src/entity_name_and_type.hpp")

# Use the dynamic MSVC runtime
if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(${PROJECT_NAME} PRIVATE "/MD$<$<CONFIG:Debug>:d>")
endif()

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        libs/godot-cpp/godot_headers
        libs/godot-cpp/include
        libs/godot-cpp/include/gen
        libs/godot-cpp/include/core
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
    add_subdirectory(libs/godot-cpp)
    target_link_libraries(${PROJECT_NAME} PUBLIC godot-cpp)
else ()
    # Generate the name of godot-cpp library
    if (ANDROID)
        set(GODOT_CPP_TARGET "godot-cpp.${SYSTEM_NAME}.${BUILD_TYPE}")
    else ()
        set(GODOT_CPP_TARGET "godot-cpp.${SYSTEM_NAME}.${BUILD_TYPE}.${BITS}")
    endif ()

    find_library(GODOT_CPP ${GODOT_CPP_TARGET} ${GODOT_CPP_TARGET_PATH})

    target_link_libraries(${PROJECT_NAME} PUBLIC ${GODOT_CPP})
endif ()

if (BUILD_ANTLR_RUNTIME)
    add_subdirectory(libs/antlr4/runtime/Cpp)
    target_link_libraries(${PROJECT_NAME} PUBLIC antlr4_static)
else()
    find_library(ANTLR_RUNTIME "antlr4-runtime-static" ${ANTLR_RUNTIME_TARGET_PATH})

    target_link_libraries(${PROJECT_NAME} PUBLIC ${ANTLR_RUNTIME})
endif ()
