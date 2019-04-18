
cmake_minimum_required (VERSION 3.0.0)
project (morphine)

# morphine version
set (MORPHINE_VERSION_MAJOR 0)
set (MORPHONE_VERSION_MINOR 1)

# pass the information to source code
configure_file (
  "src/MorphineInfo.h.in"
  "src/MorphineInfo.h"
)

find_package(Boost 1.60 REQUIRED COMPONENTS
             date_time filesystem iostreams)

include_directories( ${MY_SOURCE_DIR}/src )

add_executable(morphine src/Morphine.cxx)

target_link_libraries(morphine Boost::date_time Boost::filesystem
                          Boost::iostreams)
