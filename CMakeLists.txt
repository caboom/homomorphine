
cmake_minimum_required (VERSION 3.0.0)
project (morphine)

# set C++ version to 11
set (CMAKE_CXX_STANDARD 17)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

# morphine version
set (MORPHINE_VERSION_MAJOR 0)
set (MORPHINE_VERSION_MINOR 1)

# pass the information to source code
configure_file (
  "src/info.hpp.in"
  "src/info.hpp"
)

# dynamic link to Boost libraries
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

# set the package requirements
find_package(cpprestsdk REQUIRED)
find_package(Boost 1.60 REQUIRED COMPONENTS log program_options)
find_package(Threads)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# what to build...
set(SRC_FILES
   src/morphine.cpp
   src/config.cpp
   src/interface.cpp
   src/server.cpp
   src/api.cpp
   src/backend.cpp
   src/backend_factory.cpp
   src/seal_backend.cpp)

# build both service and library
add_executable(morphine-service ${SRC_FILES})
add_library(morphine SHARED ${SRC_FILES})

# link libraries
target_link_libraries(morphine-service ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest)
target_link_libraries(morphine ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest)
