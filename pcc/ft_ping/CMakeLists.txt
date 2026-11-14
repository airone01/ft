cmake_minimum_required(VERSION 3.20)
project(ft_ping C)

file(GLOB_RECURSE FT_PING_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(ft_ping ${FT_PING_SOURCES})
target_include_directories(ft_ping PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

include(GNUInstallDirs)
install(TARGETS ft_ping DESTINATION ${CMAKE_INSTALL_BINDIR})
