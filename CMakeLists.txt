cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
project(oop)
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SFML_DIR "./sfml/lib/cmake/SFML")

include(cmake/Options.cmake)

###############################################################################

# external dependencies with FetchContent
#include(FetchContent)
#
## NOTE: Also update env vars used for caching in
##         - .github/actions/configure-cmake/action.yml
##         - .github/workflows/cmake.yml
#FetchContent_Declare(
#         SFML
#         GIT_REPOSITORY https://github.com/SFML/SFML.git
#         GIT_TAG        2.6.0
#)
#
#FetchContent_MakeAvailable(SFML)

#set_custom_stdlib_and_sanitizers(sfml-system false)
#set_custom_stdlib_and_sanitizers(sfml-window false)
#set_custom_stdlib_and_sanitizers(sfml-graphics false)

###############################################################################

# external dependencies with find_package
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

#find_package(Threads REQUIRED)
#if(NOT APPLE AND UNIX)
#    find_package(X11)
#endif()

###############################################################################

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing name here
add_executable(${PROJECT_NAME}
    main.cpp
)

include(cmake/CompilerFlags.cmake)

###############################################################################

# use SYSTEM so cppcheck and clang-tidy do not report warnings from these directories

#target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SFML_SOURCE_DIR}/include)
#target_link_directories(${PROJECT_NAME} PRIVATE ${SFML_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

###############################################################################

# copy binaries to "bin" folder; these are uploaded as artifacts on each release
# DESTINATION_DIR is set as "bin" in cmake/Options.cmake:6
install(TARGETS ${PROJECT_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

# include(cmake/CopyHelper.cmake)
# copy_files(FILES tastatura.txt)
# copy_files(FILES tastatura.txt config.json DIRECTORY images sounds)
# copy_files(DIRECTORY images sounds)
