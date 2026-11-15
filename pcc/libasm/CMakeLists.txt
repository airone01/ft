cmake_minimum_required(VERSION 3.20)
project(libasm LANGUAGES C ASM_NASM)

if (NOT DEFINED CMAKE_ASM_NASM_OBJECT_FORMAT)
  set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf64")
endif ()
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -w-reloc-rel-dword")

file(GLOB_RECURSE LIBASM_SOURCES CONFIGURE_DEPENDS "src/*.s")

set_source_files_properties(${LIBASM_SOURCES} PROPERTIES LANGUAGE ASM_NASM)
add_library(libasm STATIC ${LIBASM_SOURCES})
add_library(42::libasm ALIAS libasm)
set_target_properties(libasm PROPERTIES
  OUTPUT_NAME "asm"
  LINKER_LANGUAGE C
)
include(GNUInstallDirs)

install(TARGETS libasm EXPORT libasmConfig ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(EXPORT libasmConfig NAMESPACE 42:: FILE libasmConfig.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libasm)

if(BUILD_TESTING)
  set(LIBASM_TESTS
    strlen
    strcpy
    strcmp
    write
    read
    strdup
    atoi_base
    list
  )

  foreach(name ${LIBASM_TESTS})
    set(target_name "libasm_test_${name}")
    add_executable(${target_name} "tests/test_${name}.c")
    target_link_libraries(${target_name} PRIVATE 42::libasm)
    target_include_directories(${target_name} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tests")

    add_test(NAME "libasm::${name}" COMMAND ${target_name})
  endforeach()
endif()
