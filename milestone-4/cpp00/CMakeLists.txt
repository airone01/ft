cmake_minimum_required(VERSION 3.20)
project(cpp00 CXX)

set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP00_EX00_SOURCES CONFIGURE_DEPENDS "ex00/src/*.cpp")
add_executable(cpp00_ex00 ${CPP00_EX00_SOURCES})

file(GLOB_RECURSE CPP00_EX01_SOURCES CONFIGURE_DEPENDS "ex01/src/*.cpp")
add_executable(cpp00_ex01 ${CPP00_EX01_SOURCES})
target_include_directories(cpp00_ex01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex01/includes"
)

file(GLOB_RECURSE CPP00_EX02_SOURCES CONFIGURE_DEPENDS "ex02/src/*.cpp")
add_executable(cpp00_ex02 ${CPP00_EX02_SOURCES})
target_include_directories(cpp00_ex02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex02/includes"
)

include(GNUInstallDirs)
install(TARGETS
  cpp00_ex00
  cpp00_ex01
  cpp00_ex02
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
