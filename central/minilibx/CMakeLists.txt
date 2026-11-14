cmake_minimum_required(VERSION 3.20)
project(mlx C)

# When building for the 3DS, don't compile anything
# X11 is hence not required for MLX on 3DS
if(CMAKE_SYSTEM_NAME STREQUAL "Nintendo3DS")
  add_library(mlx INTERFACE)
  target_include_directories(mlx INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
  add_library(42::mlx ALIAS mlx)
  return()
endif()

file(GLOB MLX_SOURCES CONFIGURE_DEPENDS "mlx_*.c")
list(FILTER MLX_SOURCES EXCLUDE REGEX ".*(mlx_lib_xpm|mlx_ext_randr)\\.c$")

add_library(mlx STATIC ${MLX_SOURCES})
target_compile_options(mlx PRIVATE
  -O3
  -w # suppress all warnings in 3rd-party/legacy code
  # TODO: Fix the MLX and make patch files instead
)
target_include_directories(mlx PUBLIC
  "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(mlx PUBLIC m) # math
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

set_target_properties(mlx PROPERTIES
  OUTPUT_NAME "mlx"
)

add_library(42::mlx ALIAS mlx)

include(GNUInstallDirs)
install(TARGETS mlx DESTINATION ${CMAKE_INSTALL_BINDIR})
