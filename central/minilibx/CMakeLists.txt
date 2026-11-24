cmake_minimum_required(VERSION 3.20)
project(mlx C)

## Patch phase

set(PATCHED_DIR "${CMAKE_CURRENT_BINARY_DIR}/mlx_patched")
file(GLOB PATCHES CONFIGURE_DEPENDS "*.patch")
list(SORT PATCHES) # need them sorted for 0001 -> 0002... order
file(GLOB MLX_ORIG_SOURCES CONFIGURE_DEPENDS "src/*.c" "includes/*.h")

file(REMOVE_RECURSE "${PATCHED_DIR}")
file(COPY src includes DESTINATION "${PATCHED_DIR}")

find_program(PATCH_EXECUTABLES patch REQUIRED)
foreach(p IN LISTS PATCHES)
  execute_process(
    COMMAND ${PATCH_EXECUTABLES} -p1 --no-backup-if-mismatch -i "${p}"
    WORKING_DIRECTORY "${PATCHED_DIR}"
    RESULT_VARIABLE rc
  )
  if(NOT rc EQUAL 0)
    message(FATAL_ERROR "Failed to apply ${p}")
  endif()
endforeach()

# When building for the 3DS, don't compile anything, just include the headers.
# A window manager is not required for MLX on 3DS.
if(CMAKE_SYSTEM_NAME STREQUAL "Nintendo3DS")
  add_library(mlx INTERFACE)
  target_include_directories(mlx INTERFACE "${PATCHED_DIR}/includes")
  add_library(42::mlx ALIAS mlx)
  return()
endif()

## Compilation phase

file(GLOB_RECURSE MLX_SOURCES "${PATCHED_DIR}/src/*.c")
add_library(mlx STATIC ${MLX_SOURCES})
include(GNUInstallDirs)

target_compile_options(mlx PRIVATE
  -O3
  -w # TODO: Fix the MLX and make patch files instead of suppressing all warns
)
target_include_directories(mlx PUBLIC
  $<BUILD_INTERFACE:${PATCHED_DIR}/includes>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_target_properties(mlx PROPERTIES
  OUTPUT_NAME "mlx"
)

## Linking phase

target_link_libraries(mlx PUBLIC
  m # math
)
if(NOT CMAKE_SYSTEM_NAME STREQUAL "Nintendo3DS")
  target_link_libraries(libft PUBLIC
    42::ft_malloc
  )
endif()
if(APPLE)
  # TODO: Check on OSX
  target_link_libraries(mlx PRIVATE
    "-framework OpenGL"
    "-framework AppKit"
  )
else()
  find_package(X11 REQUIRED)
  target_link_libraries(mlx PRIVATE
    X11::X11
    X11::Xext
  )
endif()

## Install phase

install(TARGETS mlx EXPORT mlxConfig ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT mlxConfig NAMESPACE 42:: FILE mlxConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/mlx)

add_library(42::mlx ALIAS mlx)
