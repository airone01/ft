cmake_minimum_required(VERSION 3.20)
project(libft C)

if (CUSTOM_LIBFT_PATH)
  messagge(STATUS "Using external libft: ${CUSTOM_LIBFT_PATH}")

  add_library(42::libft STATIC IMPORTED GLOBAL)

  set_target_properties(42::libft PROPERTIES
    IMPORTED_LOCATION "${CUSTOM_LIBFT_PATH}"
  )

  if(CUSTOM_LIBFT_INCLUDE_DIR)
    set_target_properties(42::libft PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CUSTOM_LIBFT_INCLUDE_DIR}"
    )
  else()
    set_target_properties(42::libft PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    )
  endif()

else()
  file(GLOB_RECURSE LIBFT_SOURCES CONFIGURE_DEPENDS "src/*.c")

  add_library(libft STATIC ${LIBFT_SOURCES})
  add_library(42::libft ALIAS libft)
  include(GNUInstallDirs)

  target_include_directories(libft PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

  install(TARGETS libft EXPORT libftConfig ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(EXPORT libftConfig NAMESPACE 42:: FILE libftConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libft)

  if(BUILD_TESTING)
    set(LIBFT_TESTS
      atoi
      bzero
      calloc
      isalnum
      isalpha
      isascii
      isdigit
      isprint
      itoa
      memchr
      memcmp
      memcpy
      memmove
      memset
      putchar_fd
      putendl_fd
      split
      strchr
      strdup
      striteri
      strjoin
      strlcat
      strlcpy
      strlen
      strmapi
      strncmp
      strnstr
      strrchr
      strtrim
      substr
      tolower
      toupper
    )
  
    foreach(name ${LIBFT_TESTS})
      set(target_name "libft_test_${name}")
      add_executable(${target_name} "tests/test_${name}.c")
      target_link_libraries(${target_name} PRIVATE 42::libft)
      target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tests")
  
      add_test(NAME "libft::${name}" COMMAND ${target_name})
    endforeach()
  endif()
endif()
