
cmake_minimum_required (VERSION 3.0.0)
project (morphine)
# The version number.
set (Tutorial_VERSION_MAJOR 0)
set (Tutorial_VERSION_MINOR 1)

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/MorphineConfig.h.in"
  "${PROJECT_BINARY_DIR}/MorphineConfig.h"
)

add_executable(morphine morphine.cxx)