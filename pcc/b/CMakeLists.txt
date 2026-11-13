# This one is special. In order we must:
# - Run yacc/bison on parser.y to generate y.tab.c and y.tab.h
# - Run lex/flex on lexer.l to generate lex.yy.c (which depends on y.tab.h)
# - Compile all C sources and the generated files into the B compiler binary
# - Use the B compiler binary to compiled .b (B lang) files into .s assembly
# - Assemble .s files into i386 .o objects
# - Link them into libb.a

cmake_minimum_required(VERSION 3.20)
project(B C)

## Bison and Flex
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(BParser
  "${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y"
  "${CMAKE_CURRENT_BINARY_DIR}/y.tab.c"
  DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/y.tab.h"
)

FLEX_TARGET(BLexer
  "${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.l"
  "${CMAKE_CURRENT_BINARY_DIR}/lex.yy.c"
)

# Guarantees y.tab.h is created before lexer.l
ADD_FLEX_BISON_DEPENDENCY(BLexer BParser)

## B compiler executable
file(GLOB_RECURSE B_C_SOURCES CONFIGURE_DEPENDS "src/*.c")
list(FILTER B_C_SOURCES EXCLUDE REGEX ".*(y\\.tab|lex\\.yy)\\.c$") # Exclude dev stuff

add_executable(B
  ${B_C_SOURCES}
  ${BISON_BParser_OUTPUTS}
  ${FLEX_BLexer_OUTPUTS}
)

target_compile_definitions(B PRIVATE FT_B_OPTI)
target_include_directories(B PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  "${CMAKE_CURRENT_BINARY_DIR}" # y.tab.h is there
)

## Use B to build libb
file(GLOB_RECURSE B_FILES CONFIGURE_DEPENDS "libb/*.b")

set (LIBB_OBJS "")

foreach(B_SRC ${B_FILES})
  get_filename_component(BASE_NAME ${B_SRC} NAME_WE)
  set(ASM_FILE "${CMAKE_CURRENT_BINARY_DIR}/libb/${BASE_NAME}.s")
  set(OBJ_FILE "${CMAKE_CURRENT_BINARY_DIR}/libb/${BASE_NAME}.o")

  # command for .b to .s to .o
  add_custom_command(
    OUTPUT "${OBJ_FILE}"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/libb"
    COMMAND bash -c "$<TARGET_FILE:B> < ${B_SRC} > ${ASM_FILE}"
    # TODO: This could probably use CMake NASM
    COMMAND as --32 "${ASM_FILE}" -o "${OBJ_FILE}"
    DEPENDS B "${B_SRC}"
    COMMENT "Building B source ${BASE_NAME}.b"
    VERBATIM
  )

  list(APPEND LIBB_OBJS "${OBJ_FILE}")
endforeach()

add_library (libb STATIC ${LIBB_OBJS})
set_target_properties(libb PROPERTIES LINKER_LANGUAGE C)

add_library(42::libb ALIAS libb)

