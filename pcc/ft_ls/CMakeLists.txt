cmake_minimum_required(VERSION 3.20)
project(ft_ls C)

file(GLOB_RECURSE FT_LS_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(ft_ls ${FT_LS_SOURCES})
target_include_directories(ft_ls PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_link_libraries(ft_ls PRIVATE 42::libft)

include(GNUInstallDirs)
install(TARGETS ft_ls DESTINATION ${CMAKE_INSTALL_BINDIR})
