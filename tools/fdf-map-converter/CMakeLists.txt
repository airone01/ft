cmake_minimum_required(VERSION 3.20)
project(fdfMapConverter C)

set(CMAKE_C_STANDARD_REQUIRED OFF)

file(GLOB_RECURSE FDF_MAP_CONVERTER_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(fdfMapConverter ${FDF_MAP_CONVERTER_SOURCES})
target_include_directories(fdfMapConverter PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

target_link_libraries(fdfMapConverter
  # TODO: link with ft_malloc when merged in main
  # 42::ft_malloc
  m # lroundf
)

include(GNUInstallDirs)
install(TARGETS fdf DESTINATION ${CMAKE_INSTALL_BINDIR})
