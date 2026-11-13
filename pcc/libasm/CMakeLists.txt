cmake_minimum_required(VERSION 3.20)
project(libasm LANGUAGES C ASM_NASM)

if (NOT DEFINED CMAKE_ASM_NASM_OBJECT_FORMAT)
  set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf64")
endif ()
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -w-reloc-rel-dword")

file(GLOB_RECURSE ASM_SOURCES CONFIGURE_DEPENDS "src/*.s")

set_source_files_properties(${ASM_SOURCES} PROPERTIES LANGUAGE ASM_NASM)
add_library(libasm STATIC ${ASM_SOURCES})
target_include_directories(libasm PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
set_target_properties(libasm PROPERTIES
  OUTPUT_NAME "asm"
  LINKER_LANGUAGE C
)

add_library(42::libasm ALIAS libasm)

add_executable(libasm_test test.c)
target_link_libraries(libasm_test PRIVATE 42::libasm)

