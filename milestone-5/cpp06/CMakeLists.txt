cmake_minimum_required(VERSION 3.20)
project(cpp06 CXX)

set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP06_EX00_SOURCES CONFIGURE_DEPENDS "ex00/*.cpp")
add_executable(cpp06_ex00 ${CPP06_EX00_SOURCES})
target_include_directories(cpp06_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex00"
)

file(GLOB_RECURSE CPP06_EX01_SOURCES CONFIGURE_DEPENDS "ex01/*.cpp")
add_executable(cpp06_ex01 ${CPP06_EX01_SOURCES})
target_include_directories(cpp06_ex01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex01"
)

file(GLOB_RECURSE CPP06_EX02_SOURCES CONFIGURE_DEPENDS "ex02/*.cpp")
add_executable(cpp06_ex02 ${CPP06_EX02_SOURCES})
target_include_directories(cpp06_ex02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex02"
)

include(GNUInstallDirs)
install(TARGETS
  cpp06_ex00
  cpp06_ex01
  cpp06_ex02
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
