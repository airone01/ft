cmake_minimum_required(VERSION 3.20)
project(cpp08 CXX)

set (CMAKE_CXX_STANDARD 98)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE CPP08_EX00_SOURCES CONFIGURE_DEPENDS "ex00/*.cpp")
add_executable(cpp08_ex00 ${CPP08_EX00_SOURCES})
target_include_directories(cpp08_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex00"
)

file(GLOB_RECURSE CPP08_EX01_SOURCES CONFIGURE_DEPENDS "ex01/*.cpp")
add_executable(cpp08_ex01 ${CPP08_EX01_SOURCES})
target_include_directories(cpp08_ex01 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex01"
)

file(GLOB_RECURSE CPP08_EX02_SOURCES CONFIGURE_DEPENDS "ex02/*.cpp")
add_executable(cpp08_ex02 ${CPP08_EX02_SOURCES})
target_include_directories(cpp08_ex02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/ex02"
)

include(GNUInstallDirs)
install(TARGETS
  cpp08_ex00
  cpp08_ex01
  cpp08_ex02
  DESTINATION ${CMAKE_INSTALL_BINDIR}
)
