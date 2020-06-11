#
# Making wft as lib
#
cmake_minimum_required( VERSION 3.15 )

project(
  wft VERSION "0.0.1.2"
  DESCRIPTION "Simple using FreeType wrapper"
  HOMEPAGE_URL "https://www.trickrig.net"
  LANGUAGES "CXX"
)

set(PROJECT_AUTHOR "bigov")
set(PROJECT_AUTHOR_EMAIL "bigov@yandex.ru")

find_package( PkgConfig REQUIRED )

pkg_check_modules( FREETYPE2 REQUIRED freetype2 )
include_directories( ${FREETYPE2_INCLUDE_DIRS} )
SET( CMAKE_C_FLAGS "${FREETYPE2_CFLAGS_OTHER}" )

# On Linux platform require: -libdl
if   ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
  SET( LIBS GL "dl" )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# AS SHARED LIB
#set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
#ADD_LIBRARY( wft SHARED "wft.cpp" )

# AS STATIC LIB
ADD_LIBRARY( wft STATIC "wft.cpp" )
TARGET_LINK_LIBRARIES( wft "${LIBS}" "${FREETYPE2_LIBRARIES}")
