cmake_minimum_required(VERSION 3.20)
project(rush02 C)

file(GLOB_RECURSE RUSH01_SOURCES CONFIGURE_DEPENDS "ex00/*.c")

add_executable(rush02_ex00 ${RUSH01_SOURCES})
target_include_directories(rush02_ex00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(rush02_ex00 PRIVATE 42::libft)

include(GNUInstallDirs)
install(TARGETS rush02_ex00 DESTINATION ${CMAKE_INSTALL_BINDIR})
