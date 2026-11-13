cmake_minimum_required(VERSION 3.20)
project(cpp05 CXX)

set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP05_EX00_SOURCES CONFIGURE_DEPENDS "ex00/*.cpp")
add_executable(cpp05_ex00 ${CPP05_EX00_SOURCES})
target_include_directories(cpp05_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex00"
)

file(GLOB_RECURSE CPP05_EX01_SOURCES CONFIGURE_DEPENDS "ex01/*.cpp")
add_executable(cpp05_ex01 ${CPP05_EX01_SOURCES})
target_include_directories(cpp05_ex01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex01"
)

file(GLOB_RECURSE CPP05_EX02_SOURCES CONFIGURE_DEPENDS "ex02/*.cpp")
add_executable(cpp05_ex02 ${CPP05_EX02_SOURCES})
target_include_directories(cpp05_ex02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex02"
)

file(GLOB_RECURSE CPP05_EX03_SOURCES CONFIGURE_DEPENDS "ex03/*.cpp")
add_executable(cpp05_ex03 ${CPP05_EX03_SOURCES})
target_include_directories(cpp05_ex03 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex03"
)

include(GNUInstallDirs)
install(TARGETS
  cpp05_ex00
  cpp05_ex01
  cpp05_ex02
  cpp05_ex03
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
