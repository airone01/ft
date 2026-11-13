cmake_minimum_required(VERSION 3.20)
project(minishell C)

include(FindReadline)
find_package(Readline REQUIRED)

file(GLOB_RECURSE MINISHELL_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(minishell ${MINISHELL_SOURCES})
target_include_directories(minishell PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)
target_link_libraries(minishell PRIVATE
  42::ft
  42::ft_printf
  Readline::Readline
)

include(GNUInstallDirs)
install(TARGETS minishell DESTINATION ${CMAKE_INSTALL_BINDIR})
