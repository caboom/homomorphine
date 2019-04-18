
cmake_minimum_required (VERSION 3.0.0)
project (morphine)

# set C++ version to 11
set (CMAKE_CXX_STANDARD 11)

# morphine version
set (MORPHINE_VERSION_MAJOR 0)
set (MORPHINE_VERSION_MINOR 1)

# pass the information to source code
configure_file (
  "src/MorphineInfo.hpp.in"
  "src/MorphineInfo.hpp"
)

# dynamic link to Boost libraries
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

# set the package requirements
find_package(Boost 1.60 REQUIRED COMPONENTS log)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# what to build...
set(SRC_FILES
   src/Morphine.cxx
   src/Options.cxx)

add_executable(morphine ${SRC_FILES})

# link libraries
target_link_libraries(morphine ${Boost_LIBRARIES} Threads::Threads)
