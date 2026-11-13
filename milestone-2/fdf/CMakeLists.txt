cmake_minimum_required(VERSION 3.20)
project(fdf C)

file(GLOB_RECURSE FDF_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(fdf ${FDF_SOURCES})
target_include_directories(fdf PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)
# Disable -Wpedantic for mlx.h which uses old K&R C prototypes
# TODO: Fix the MLX and make patch files instead
target_compile_options(fdf PRIVATE -Wno-cast-function-type)
target_link_libraries(fdf PRIVATE
  42::ft
  42::gnl
  42::ft_printf
  42::mlx
  m # Math
)

include(GNUInstallDirs)
install(TARGETS fdf DESTINATION ${CMAKE_INSTALL_BINDIR})
