cmake_minimum_required(VERSION 3.20)
project(ft_monorepo C)

set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON) # compile-commands.json

add_compile_options(
  $<$<COMPILE_LANGUAGE:C>:-Wall>
  $<$<COMPILE_LANGUAGE:C>:-Wextra>
  $<$<COMPILE_LANGUAGE:C>:-Werror>
  $<$<COMPILE_LANGUAGE:C>:-Wpedantic>
  $<$<COMPILE_LANGUAGE:CXX>:-Wall>
  $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
  $<$<COMPILE_LANGUAGE:CXX>:-Werror>
  $<$<COMPILE_LANGUAGE:CXX>:-Wpedantic>
)

set(CUSTOM_LIBFT_PATH "" CACHE FILEPATH "Optional path to a precompiled libft.a")
set(CUSTOM_LIBFT_INCLUDE_DIR "" CACHE FILEPATH "Optional path to a custom libft header directory")
set(CUSTOM_FT_PRINTF_PATH "" CACHE FILEPATH "Optional path to a precompiled libft_printf.a")
set(CUSTOM_FT_PRINTF_INCLUDE_DIR "" CACHE FILEPATH "Optional path to a custom libft_printf header directory")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools")

add_subdirectory(milestone-0/libft)
add_subdirectory(central/minilibx)
add_subdirectory(milestone-1/ft_printf)
add_subdirectory(milestone-1/get_next_line)
add_subdirectory(milestone-4/cub3d)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Nintendo3DS")
  add_subdirectory(external-tools/philosophers-visualizer)
  add_subdirectory(milestone-2/fdf)
  add_subdirectory(milestone-2/pipex)
  add_subdirectory(milestone-2/push_swap)
  add_subdirectory(milestone-3/minishell)
  add_subdirectory(milestone-3/philosophers)
  add_subdirectory(milestone-4/cpp00)
  add_subdirectory(milestone-4/cpp01)
  add_subdirectory(milestone-4/cpp02)
  add_subdirectory(milestone-4/cpp03)
  add_subdirectory(milestone-4/cpp04)
  add_subdirectory(milestone-5/cpp05)
  add_subdirectory(milestone-5/cpp06)
  add_subdirectory(milestone-5/cpp07)
  add_subdirectory(milestone-5/cpp08)
  add_subdirectory(milestone-5/cpp09)
  add_subdirectory(pcc/b)
  add_subdirectory(pcc/libasm)
  add_subdirectory(pcc/malloc)
endif()

