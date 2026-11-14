cmake_minimum_required(VERSION 3.20)
project(philo C)

if(CMAKE_SYSTEM_NAME STREQUAL "Nintendo3DS")
	file(GLOB CUB3D_SRCS CONFIGURE_DEPENDS "src/*.c" "src/*_b*.c" "3ds/mlx_3ds.c")
	list(FILTER CUB3D_SRCS EXCLUDE REGEX ".*_m2?\\.c$")

	add_executable(cub3d ${CUB3D_SRCS})

	target_compile_definitions(cub3d PRIVATE __3DS__)
	target_include_directories(cub3d PRIVATE
		"includes"
		"3ds"
		"$ENV{DEVKITPRO}/libctru/include"
	)
	target_compile_options(cub3d PRIVATE -Wno-cast-function-type)

	target_link_libraries(cub3d PRIVATE
		42::ft
		42::ft_printf
		42::gnl
		# 3DS version of the MLX is just a header interface
		42::mlx
		ctru
		m
	)
	target_link_directories(cub3d PRIVATE "$ENV{DEVKITPRO}/libctru/lib")

	find_program(SMDHTOOL smdhtool HINTS "$ENV{DEVKITPRO}/tools/bin")
	find_program(TOOL3DS 3dsxtool HINTS "$ENV{DEVKITPRO}/tools/bin")

	add_custom_command(TARGET cub3d POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E echo "Dereferencing ROMFS..."
		COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_CURRENT_BINARY_DIR}/romfs"
		COMMAND cp -rL "${CMAKE_CURRENT_SOURCE_DIR}/romfs" "${CMAKE_CURRENT_BINARY_DIR}/romfs"

		COMMAND ${CMAKE_COMMAND} -E echo "Generating 3DS Homebrew package..."
		# SMDH icon
		COMMAND ${SMDHTOOL} --create "cub3d" "cub3d port" "airone01"
			"${CMAKE_CURRENT_SOURCE_DIR}/assets/icon_48.png"
			"${CMAKE_CURRENT_BINARY_DIR}/cub3d.smdh"
		# package elf into 3dsx
		COMMAND ${TOOL3DS} "$<TARGET_FILE:cub3d>" "${CMAKE_CURRENT_BINARY_DIR}/cub3d.3dsx"
			"--romfs=${CMAKE_CURRENT_SOURCE_DIR}/romfs"
			"--smdh=${CMAKE_CURRENT_BINARY_DIR}/cub3d.smdh"
		COMMENT "Building cub3d.3dsx"
	)
else()
	file(GLOB_RECURSE CUB3D_COMMON_SOURCES CONFIGURE_DEPENDS "src/*.c")
	file(GLOB_RECURSE CUB3D_MANDATORY_SOURCES CONFIGURE_DEPENDS "src/*_m.c" "src/*_m2.c")
	file(GLOB_RECURSE CUB3D_BONUS_SOURCES CONFIGURE_DEPENDS "src/*_b.c" "src/*_b2.c" "src/*_e.c" "src/*_e2.c")
	list(FILTER CUB3D_COMMON_SOURCES EXCLUDE REGEX "src/.*_[bm]2?\\.c$")

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
endif()
