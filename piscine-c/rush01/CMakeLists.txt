cmake_minimum_required(VERSION 3.20)
project(rush01 C)

file(GLOB_RECURSE RUSH01_SOURCES CONFIGURE_DEPENDS "ex00/*.c")

add_executable(rush01_ex00 ${RUSH01_SOURCES})
target_include_directories(rush01_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(rush01_ex00 PRIVATE 42::libft)

include(GNUInstallDirs)
install(TARGETS rush01_ex00 DESTINATION ${CMAKE_INSTALL_BINDIR})
