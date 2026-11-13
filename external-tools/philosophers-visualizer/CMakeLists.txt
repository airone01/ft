cmake_minimum_required(VERSION 3.20)
project(philo-viz CXX)

file(GLOB_RECURSE PHILO_VIZ_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(philo-viz ${PHILO_VIZ_SOURCES})
# TODO: Fix and make patch files instead
target_compile_options(philo-viz PRIVATE -w)
target_include_directories(philo-viz PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/includes"
)

include(GNUInstallDirs)
install(TARGETS philo-viz DESTINATION ${CMAKE_INSTALL_BINDIR})
