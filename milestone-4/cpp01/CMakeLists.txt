cmake_minimum_required(VERSION 3.20)
project(cpp01 CXX)

set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP01_EX00_SOURCES CONFIGURE_DEPENDS "ex00/src/*.cpp")
add_executable(cpp01_ex00 ${CPP01_EX00_SOURCES})
target_include_directories(cpp01_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex00/includes"
)

file(GLOB_RECURSE CPP01_EX01_SOURCES CONFIGURE_DEPENDS "ex01/src/*.cpp")
add_executable(cpp01_ex01 ${CPP01_EX01_SOURCES})
target_include_directories(cpp01_ex01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex01/includes"
)

file(GLOB_RECURSE CPP01_EX02_SOURCES CONFIGURE_DEPENDS "ex02/src/*.cpp")
add_executable(cpp01_ex02 ${CPP01_EX02_SOURCES})
target_include_directories(cpp01_ex02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex02/includes"
)

file(GLOB_RECURSE CPP01_EX03_SOURCES CONFIGURE_DEPENDS "ex03/src/*.cpp")
add_executable(cpp01_ex03 ${CPP01_EX03_SOURCES})
target_include_directories(cpp01_ex03 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex03/includes"
)

file(GLOB_RECURSE CPP01_EX04_SOURCES CONFIGURE_DEPENDS "ex04/src/*.cpp")
add_executable(cpp01_ex04 ${CPP01_EX04_SOURCES})
target_include_directories(cpp01_ex04 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex04/includes"
)

file(GLOB_RECURSE CPP01_EX05_SOURCES CONFIGURE_DEPENDS "ex05/src/*.cpp")
add_executable(cpp01_ex05 ${CPP01_EX05_SOURCES})
target_include_directories(cpp01_ex05 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex05/includes"
)

include(GNUInstallDirs)
install(TARGETS
  cpp01_ex00
  cpp01_ex01
  cpp01_ex02
  cpp01_ex03
  cpp01_ex04
  cpp01_ex05
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
