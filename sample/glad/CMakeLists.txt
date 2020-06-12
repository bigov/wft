#
# Сборка библиотеки GLAD
#
cmake_minimum_required( VERSION 3.15 )
project( lib_glad )

#target_include_directories( glad INTERFACE "../${CMAKE_SOURCE_DIR}" )

# On Linux platform glad require: -libdl
if   ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
  SET( LIBS GL "dl" )
endif( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

# Включение экспорта всех символов для создания динамической библиотеки
#set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
#ADD_LIBRARY( glad SHARED "glad.c" )

ADD_LIBRARY( glad STATIC "glad.c" )
TARGET_LINK_LIBRARIES( glad ${LIBS} )
