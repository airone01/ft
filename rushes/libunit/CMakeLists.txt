# TODO: test

cmake_minimum_required(VERSION 3.20)
project(libunit C)

file(GLOB_RECURSE LIBUNIT_SOURCES CONFIGURE_DEPENDS "framework/*.c")

add_library(libunit STATIC ${LIBUNIT_SOURCES})
target_include_directories(libunit PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/framework"
)
target_link_libraries(libunit PRIVATE 42::libft)

add_library(42::libunit ALIAS libunit)

include(GNUInstallDirs)
install(TARGETS libunit DESTINATION ${CMAKE_INSTALL_BINDIR})
