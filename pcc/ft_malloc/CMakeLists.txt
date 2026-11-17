cmake_minimum_required(VERSION 3.20)
project(ft_malloc C)

file(GLOB_RECURSE FT_MALLOC_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_library(ft_malloc SHARED ${FT_MALLOC_SOURCES})
add_library(42::ft_malloc ALIAS ft_malloc)
include(GNUInstallDirs)

target_include_directories(ft_malloc PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_compile_options(ft_malloc PRIVATE -O3 -fno-builtin)

install(TARGETS ft_malloc EXPORT mallocConfig ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT mallocConfig NAMESPACE 42:: FILE mallocConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ft_malloc)

if(BUILD_TESTING)
  set(FT_MALLOC_TESTS
    basic
    edge
    free
    large
    realloc
    # show_alloc_mem
    stress
  )

  foreach(name ${FT_MALLOC_TESTS})
    set(target_name "ft_malloc_test_${name}")
    add_executable(${target_name} "tests/test_${name}.c")
    target_link_libraries(${target_name} PRIVATE 42::ft_malloc)
    target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tests")
    target_compile_options(${target_name} PRIVATE -w -O3 -fno-builtin)

    add_test(NAME "ft_malloc::${name}" COMMAND ${target_name})
  endforeach()
endif()
