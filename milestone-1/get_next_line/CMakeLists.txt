cmake_minimum_required(VERSION 3.20)
project(gnl C)

if (CUSTOM_GNL_PATH)
  messagge(STATUS "Using external gnl: ${CUSTOM_GNL_PATH}")

  add_library(42::gnl STATIC IMPORTED GLOBAL)

  set_target_properties(42::gnl PROPERTIES
    IMPORTED_LOCATION "${CUSTOM_GNL_PATH}"
  )

  if(CUSTOM_LIBFT_INCLUDE_DIR)
    set_target_properties(42::gnl PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CUSTOM_LIBFT_INCLUDE_DIR}"
    )
  else()
    set_target_properties(42::gnl PROPERTIES
      INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/includes"
    )
  endif()

else()
  file(GLOB_RECURSE GNL_SOURCES CONFIGURE_DEPENDS "src/*.c")
  list(FILTER GNL_SOURCES EXCLUDE REGEX "src/main\\.c$")

  add_library(gnl STATIC ${GNL_SOURCES})
  add_library(42::gnl ALIAS gnl)
  include(GNUInstallDirs)

  target_include_directories(gnl PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/includes>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )
  if(NOT TARGET 42::libft)
    find_package(libft CONFIG REQUIRED)
  endif()
  target_link_libraries(gnl PRIVATE 42::libft)

  install(TARGETS gnl EXPORT gnlConfig ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
  install(DIRECTORY includes/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
  install(EXPORT gnlConfig NAMESPACE 42:: FILE gnlConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/gnl)
endif()
