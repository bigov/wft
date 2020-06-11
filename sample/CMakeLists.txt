cmake_minimum_required( VERSION 3.0 )

project(
  TestWFT VERSION "0.0.1.0"
  DESCRIPTION "Example for using FreeType wrapper"
  HOMEPAGE_URL "https://www.trickrig.net"
  LANGUAGES "CXX"
  )

set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")

if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(FATAL_ERROR "Prevented in-tree built. Please create a _bin \
  directory outside of the source code and call cmake from there. Thank you.")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

SET( SKIP_INSTALL_ALL ON CACHE BOOL "" FORCE )
SET( CMAKE_VERBOSE_MAKEFILE OFF )

SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Werror -Wall -Wextra \
  -Wpedantic -Woverloaded-virtual -Wctor-dtor-privacy -Wnon-virtual-dtor \
  -Wconversion -Winit-self -Wunreachable-code -Weffc++ -Wsign-conversion -Wold-style-cast" )

if( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
  SET( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows -Wl,-subsystem,windows" )
endif()

find_package( PkgConfig REQUIRED )

if( ${MINGW} )
  SET( TR_LIBS mingw32 gdi32 )
endif()

pkg_check_modules( GLFW REQUIRED glfw3 )

add_subdirectory( "../glad" "glad" EXCLUDE_FROM_ALL )
add_subdirectory( "../" "wft" EXCLUDE_FROM_ALL )

add_executable( test-wft "main.cpp" "win.cpp" )
target_link_libraries( test-wft "${GLFW_LIBRARIES}" glad wft)
