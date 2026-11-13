cmake_minimum_required(VERSION 3.20)
project(libft C)

if (CUSTOM_LIBFT_PATH)
  messagge(STATUS "Using external libft: ${CUSTOM_LIBFT_PATH}")

  add_library(42::ft STATIC IMPORTED GLOBAL)

  set_target_properties(42::ft PROPERTIES
    IMPORTED_LOCATION "${CUSTOM_LIBFT_PATH}"
  )

  if(CUSTOM_LIBFT_INCLUDE_DIR)
    set_target_properties(42::ft PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CUSTOM_LIBFT_INCLUDE_DIR}"
    )
  else()
    set_target_properties(42::ft PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    )
  endif()

else()
  file(GLOB_RECURSE LIBFT_SOURCES CONFIGURE_DEPENDS "src/*.c")

  add_library(ft STATIC ${LIBFT_SOURCES})

  target_include_directories(ft PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
  )

  add_library(42::ft ALIAS ft)
endif()
