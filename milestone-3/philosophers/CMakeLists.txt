cmake_minimum_required(VERSION 3.20)
project(philo C)

file(GLOB_RECURSE PHILOSOPHERS_SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(philo ${PHILOSOPHERS_SOURCES})
target_include_directories(philo PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)
target_link_libraries(philo PRIVATE 42::ft)

include(GNUInstallDirs)
install(TARGETS philo DESTINATION ${CMAKE_INSTALL_BINDIR})
