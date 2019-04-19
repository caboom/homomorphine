
cmake_minimum_required (VERSION 3.0.0)
project (morphine)

# set C++ version to 11
set (CMAKE_CXX_STANDARD 11)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

# morphine version
set (MORPHINE_VERSION_MAJOR 0)
set (MORPHINE_VERSION_MINOR 1)

# pass the information to source code
configure_file (
  "src/info.h.in"
  "src/info.h"
)

# dynamic link to Boost libraries
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

# set the package requirements
find_package(Boost 1.60 REQUIRED COMPONENTS log program_options)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# what to build...
set(SRC_FILES
   src/morphine.cpp
   src/config.cpp)

add_executable(morphine ${SRC_FILES})

# link libraries
target_link_libraries(morphine ${Boost_LIBRARIES} Threads::Threads)
