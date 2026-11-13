cmake_minimum_required(VERSION 3.20)
project(ft_malloc C)

file(GLOB_RECURSE MALLOC_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_library(ft_malloc SHARED ${MALLOC_SOURCES})
target_include_directories(ft_malloc PRIVATE "src")
target_link_libraries(ft_malloc PRIVATE 42::ft)

set_target_properties(ft_malloc PROPERTIES
  OUTPUT_NAME "ft_malloc"
  PREFIX "lib"
)
