cmake_minimum_required(VERSION 3.20)
project(cpp09 CXX)

set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP09_EX00_SOURCES CONFIGURE_DEPENDS "ex00/*.cpp")
add_executable(cpp09_ex00 ${CPP09_EX00_SOURCES})
target_include_directories(cpp09_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex00"
)

file(GLOB_RECURSE CPP09_EX01_SOURCES CONFIGURE_DEPENDS "ex01/*.cpp")
add_executable(cpp09_ex01 ${CPP09_EX01_SOURCES})
target_include_directories(cpp09_ex01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex01"
)

file(GLOB_RECURSE CPP09_EX02_SOURCES CONFIGURE_DEPENDS "ex02/*.cpp")
add_executable(cpp09_ex02 ${CPP09_EX02_SOURCES})
target_include_directories(cpp09_ex02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex02"
)

include(GNUInstallDirs)
install(TARGETS
  cpp09_ex00
  cpp09_ex01
  cpp09_ex02
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
