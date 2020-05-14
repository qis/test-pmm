cmake_minimum_required(VERSION 3.17 FATAL_ERROR)
project(test VERSION 0.1.0 LANGUAGES CXX)

include(pmm.cmake)

if(WIN32)
  set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
  set(VCPKG_TARGET_TRIPLET "x64-linux" CACHE STRING "")
else()
  message(FATAL_ERROR "Unsupported system: ${CMAKE_SYSTEM_NAME}")
endif()

unset(ENV{VCPKG_ROOT})
pmm(DEBUG VCPKG REVISION 2020.04 TRIPLET ${VCPKG_TARGET_TRIPLET} REQUIRES fmt)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "")  

# Sources
file(GLOB_RECURSE sources src/*.[hc]pp)

# Executable
add_executable(${PROJECT_NAME} ${sources} src/main.manifest)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/main.hpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX WIN32_LEAN_AND_MEAN)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Dependencies
find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

if(CMAKE_CXX_COMPILER_ID STREQUAL GNU)
  target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)
  target_link_options(${PROJECT_NAME} PRIVATE -static-libstdc++)
endif()

# Install
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
