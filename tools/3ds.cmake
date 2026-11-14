set(CMAKE_SYSTEM_NAME "Nintendo3DS")
set(CMAKE_SYSTEM_PROCESSOR "armv6k")

set(DEVKITARM "$ENV{DEVKITARM}")
set(DEVKITPRO "$ENV{DEVKITPRO}")

if(NOT DEVKITARM)
  message(FATAL_ERROR "DEVKITARM not set. Run inside 'nix develop .#threeDS'")
endif()

# Cross-compilers
set(CMAKE_C_COMPILER "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_AR "${DEVKITARM}/bin/arm-none-eabi-ar" CACHE FILEPATH "")
set(CMAKE_RANLIB "${DEVKITARM}/bin/arm-none-eabi-ranlib" CACHE FILEPATH "")

set(ARCH_FLAGS "-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft")
set(CMAKE_C_FLAGS_INIT "${ARCH_FLAGS} -O2 -specs=3dsx.specs")

set(CMAKE_FIND_ROOT_PATH "${DEVKITPRO}/libctru")
