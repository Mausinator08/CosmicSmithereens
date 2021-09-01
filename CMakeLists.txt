cmake_minimum_required(VERSION 3.11.0)
project(CosmicSmithereens)

include(CTest)
enable_testing()

set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_compile_options(-m64)

include_directories("Source/CosmicSmithereens" "../3rdParty/SDL2/${CMAKE_BUILD_TYPE}/include/SDL2" "../3rdParty/spdlog/${CMAKE_BUILD_TYPE}/include")
link_directories("../3rdParty/SDL2/${CMAKE_BUILD_TYPE}/lib" "../3rdParty/spdlog/${CMAKE_BUILD_TYPE}/lib")

add_library(pch Source/CosmicSmithereens/stdafx.cpp Source/CosmicSmithereens/stdafx.h)

include(../cmake-precompiled-header/PrecompiledHeader.cmake)

add_precompiled_header(pch Source/CosmicSmithereens/stdafx.h FORCEINCLUDE)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    link_libraries(mingw32)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(-Wall -g)
    link_libraries(SDL2maind SDL2d spdlogd)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    add_compile_options(-O2 -g)
    add_compile_definitions(NDEBUG)
    link_libraries(SDL2main SDL2 spdlog)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    add_compile_options(-Os)
    add_compile_definitions(NDEBUG)
    link_libraries(SDL2main SDL2 spdlog)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    add_compile_options(-O3)
    add_compile_definitions(NDEBUG)
    link_libraries(SDL2main SDL2 spdlog)
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS Source/CosmicSmithereens/*.cpp)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_compile_options(-mwindows)
    add_executable(CosmicSmithereens WIN32 ${SRC_FILES})
    target_link_options(CosmicSmithereens PRIVATE -mwindows)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_executable(CosmicSmithereens UNIX ${SRC_FILES})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_executable(CosmicSmithereens APPLE ${SRC_FILES})
endif()

include(GNUInstallDirs)
install(FILES "../3rdParty/SDL2/${CMAKE_BUILD_TYPE}/bin/SDL2d.dll" DESTINATION bin/${CMAKE_BUILD_TYPE})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
