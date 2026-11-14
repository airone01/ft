cmake_minimum_required(VERSION 3.20)
project(bsq C)

file(GLOB_RECURSE BSQ_SOURCES CONFIGURE_DEPENDS "*.c")

add_executable(bsq ${BSQ_SOURCES})
target_include_directories(bsq PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(bsq PRIVATE 42::ft)

include(GNUInstallDirs)
install(TARGETS bsq DESTINATION ${CMAKE_INSTALL_BINDIR})
