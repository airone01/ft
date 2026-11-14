# TODO: testing

cmake_minimum_required(VERSION 3.20)
project(nm C)

file(GLOB_RECURSE NM_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(nm ${NM_SOURCES})
target_include_directories(nm PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

include(GNUInstallDirs)
install(TARGETS nm DESTINATION ${CMAKE_INSTALL_BINDIR})
