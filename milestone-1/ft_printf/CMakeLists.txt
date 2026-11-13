cmake_minimum_required(VERSION 3.20)
project(ft_printf C)

if (CUSTOM_FT_PRINTF_PATH)
  messagge(STATUS "Using external ft_printf: ${CUSTOM_FT_PRINTF_PATH}")

  add_library(42::ft_printf STATIC IMPORTED GLOBAL)

  set_target_properties(42::ft_printf PROPERTIES
    IMPORTED_LOCATION "${CUSTOM_FT_PRINTF_PATH}"
  )

  if(CUSTOM_LIBFT_INCLUDE_DIR)
    set_target_properties(42::ft_printf PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CUSTOM_LIBFT_INCLUDE_DIR}"
    )
  else()
    set_target_properties(42::ft_printf PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    )
  endif()

else()
  file(GLOB_RECURSE FT_PRINTF_SOURCES CONFIGURE_DEPENDS "src/*.c")

  add_library(ft_printf STATIC ${FT_PRINTF_SOURCES})

  target_include_directories(ft_printf PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/includes"
  )
  target_link_libraries(ft_printf PRIVATE 42::ft)

  add_library(42::ft_printf ALIAS ft_printf)
endif()
