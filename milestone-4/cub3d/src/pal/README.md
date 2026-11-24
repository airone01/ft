# PAL

PAL stands for Platform Abstraction Layer. Unlike systems, they are loaded at
compile time. The goal is to have one simple API to interface with any windowing
platform out there (MLX, SDL2, ...).

If multiple platforms are compiled together, the linker will fail because of
duplicate function implementations. This is intended, CMake or other builders
should only include one platform file.
