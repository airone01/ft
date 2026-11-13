cmake_minimum_required(VERSION 3.20)
project(philo C)

file(GLOB_RECURSE CUB3D_COMMON_SOURCES CONFIGURE_DEPENDS "src/*.c")
list(FILTER CUB3D_COMMON_SOURCES EXCLUDE REGEX "src/.*_[bm]2?\\.c$")

file(GLOB_RECURSE CUB3D_MANDATORY_SOURCES CONFIGURE_DEPENDS "src/*_m.c" "src/*_m2.c")
file(GLOB_RECURSE CUB3D_BONUS_SOURCES CONFIGURE_DEPENDS "src/*_b.c" "src/*_b2.c" "src/*_e.c" "src/*_e2.c")

add_library(cub3d_common OBJECT ${CUB3D_COMMON_SOURCES})
target_include_directories(cub3d_common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")
target_compile_options(cub3d_common PUBLIC -Wno-cast-function-type)
target_link_libraries(cub3d_common PUBLIC
	42::ft
	42::ft_printf
	42::gnl
	42::mlx
	m
)

add_executable(cub3d ${CUB3D_MANDATORY_SOURCES})
target_link_libraries(cub3d PRIVATE cub3d_common)

add_executable(cub3d_bonus ${CUB3D_BONUS_SOURCES})
target_link_libraries(cub3d_bonus PRIVATE cub3d_common)

include(GNUInstallDirs)
install(TARGETS cub3d cub3d_bonus DESTINATION ${CMAKE_INSTALL_BINDIR})
