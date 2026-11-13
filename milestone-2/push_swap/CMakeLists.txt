cmake_minimum_required(VERSION 3.20)
project(push_swap C)

file(GLOB_RECURSE PS_COMMON_SOURCES CONFIGURE_DEPENDS "src/*.c")
list(FILTER PS_COMMON_SOURCES EXCLUDE REGEX "src/(checker|_main)\\.c$")

add_library(ps_common OBJECT ${PS_COMMON_SOURCES})
target_include_directories(ps_common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/includes")
target_link_libraries(ps_common PUBLIC 42::ft 42::gnl)

add_executable(push_swap src/_main.c)
target_link_libraries(push_swap PRIVATE ps_common)

add_executable(push_swap_checker src/checker.c)
target_link_libraries(push_swap_checker PRIVATE ps_common)
set_target_properties(push_swap_checker PROPERTIES OUTPUT_NAME "checker")

include(GNUInstallDirs)
install(TARGETS push_swap push_swap_checker DESTINATION ${CMAKE_INSTALL_BINDIR})