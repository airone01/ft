# TODO: test

cmake_minimum_required(VERSION 3.20)
project(hotrace C)

file(GLOB_RECURSE HOTRACE_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(hotrace ${HOTRACE_SOURCES})
target_include_directories(hotrace PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)
target_link_libraries(hotrace PRIVATE
  42::ft
  42::gnl
)

include(GNUInstallDirs)
install(TARGETS hotrace DESTINATION ${CMAKE_INSTALL_BINDIR})
