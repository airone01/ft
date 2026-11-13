cmake_minimum_required(VERSION 3.20)
project(pipex C)

file(GLOB_RECURSE PIPEX_SOURCES CONFIGURE_DEPENDS "src/*.c")
list(FILTER PIPEX_SOURCES EXCLUDE REGEX "src/(_main|args_valid)\\.c")

add_executable(pipex ${PIPEX_SOURCES})
target_include_directories(pipex PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)
target_link_libraries(pipex PRIVATE
  42::ft
  42::ft_printf
  42::gnl
)

include(GNUInstallDirs)
install(TARGETS pipex DESTINATION ${CMAKE_INSTALL_BINDIR})
