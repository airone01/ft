cmake_minimum_required(VERSION 3.20)
project(rush00 C)

add_executable(rush00_00 ./main.c ./rush00.c)
target_include_directories(rush00_00 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(rush00_00 PRIVATE 42::libft)

add_executable(rush00_02 ./main.c ./rush02.c)
target_include_directories(rush00_02 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(rush00_02 PRIVATE 42::libft)

add_executable(rush00_03 ./main.c ./rush03.c)
target_include_directories(rush00_03 PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)
target_link_libraries(rush00_03 PRIVATE 42::libft)

include(GNUInstallDirs)
install(TARGETS rush00_00 rush00_02 rush00_03 DESTINATION ${CMAKE_INSTALL_BINDIR})
