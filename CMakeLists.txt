cmake_minimum_required(VERSION 3.23)
project(CosmicSmithereens)

include(CTest)
include(GoogleTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

add_compile_options(-m64 -fpermissive -Wunknown-pragmas)

file(TO_CMAKE_PATH $ENV{ReposDir} ReposDir)
file(TO_CMAKE_PATH $ENV{3rdPartyDir} 3rdPartyDir)

include_directories(Source/CosmicSmithereens ${3rdPartyDir}/SDL2/${CMAKE_BUILD_TYPE}/include/SDL2 ${3rdPartyDir}/spdlog/${CMAKE_BUILD_TYPE}/include
${3rdPartyDir}/MemPlumber/${CMAKE_BUILD_TYPE}/include ${3rdPartyDir}/cwalk/${CMAKE_BUILD_TYPE}/include ${3rdPartyDir}/googletest/googletest/include ${3rdPartyDir}/googletest/googlemock/include)

link_directories(${3rdPartyDir}/SDL2/${CMAKE_BUILD_TYPE}/lib ${3rdPartyDir}/spdlog/${CMAKE_BUILD_TYPE}/lib ${3rdPartyDir}/MemPlumber/${CMAKE_BUILD_TYPE}/lib
${3rdPartyDir}/cwalk/${CMAKE_BUILD_TYPE}/lib ${3rdPartyDir}/googletest/build/lib)

add_compile_definitions(UNICODE _UNICODE)

add_library(pch Source/CosmicSmithereens/stdafx.cpp Source/CosmicSmithereens/stdafx.h)

include(${3rdPartyDir}/cmake-precompiled-header/PrecompiledHeader.cmake)

add_precompiled_header(pch Source/CosmicSmithereens/stdafx.h FORCEINCLUDE)

link_libraries(memplumber cwalk)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    link_libraries(mingw32)
endif()

if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    add_compile_options(-Wall -g -O0)
    add_compile_definitions(_DEBUG)
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
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS Tests/*.cpp)

include(GNUInstallDirs)
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    install(FILES ${3rdPartyDir}/SDL2/${CMAKE_BUILD_TYPE}/bin/SDL2d.dll DESTINATION bin/${CMAKE_BUILD_TYPE})
else()
    install(FILES ${3rdPartyDir}/SDL2/${CMAKE_BUILD_TYPE}/bin/SDL2.dll DESTINATION bin/${CMAKE_BUILD_TYPE})
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    foreach(TEST_SOURCE_FILE ${TEST_FILES})
        string(REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE_FILE})
        string(REGEX REPLACE ".*/CosmicSmithereens/Tests/" "TEST" TEST_NAME ${TEST_NAME})
        string(REPLACE "/" "_" TEST_NAME ${TEST_NAME})
        add_executable(${TEST_NAME} WIN32 ${SRC_FILES} ${TEST_SOURCE_FILE})
        target_link_libraries(${TEST_NAME} PRIVATE gtest gmock)
        gtest_discover_tests(${TEST_NAME})
    endforeach(TEST_SOURCE_FILE ${TEST_FILES})

    add_compile_options(-mwindows)
    add_executable(CosmicSmithereens WIN32 ${SRC_FILES})
    target_link_options(CosmicSmithereens PRIVATE -mwindows)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    
    foreach(TEST_SOURCE_FILE ${TEST_FILES})
        string(REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE_FILE})
        string(REPLACE "/" "_" TEST_NAME ${TEST_NAME})
        add_executable(${TEST_NAME} UNIX ${SRC_FILES} ${TEST_SOURCE_FILE})
        target_link_libraries(${TEST_NAME} PRIVATE gtest gmock)
        gtest_discover_tests(${TEST_NAME} DISCOVERY_MODE PRE_TEST)
    endforeach(TEST_SOURCE_FILE ${TEST_FILES})

    add_executable(CosmicSmithereens UNIX ${SRC_FILES})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    
    foreach(TEST_SOURCE_FILE ${TEST_FILES})
        string(REPLACE ".cpp" "" TEST_NAME ${TEST_SOURCE_FILE})
        string(REPLACE "/" "_" TEST_NAME ${TEST_NAME})
        add_executable(${TEST_NAME} APPLE ${SRC_FILES} ${TEST_SOURCE_FILE})
        target_link_libraries(${TEST_NAME} PRIVATE gtest gmock)
        gtest_discover_tests(${TEST_NAME} DISCOVERY_MODE PRE_TEST)
    endforeach(TEST_SOURCE_FILE ${TEST_FILES})

    add_executable(CosmicSmithereens APPLE ${SRC_FILES})
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
