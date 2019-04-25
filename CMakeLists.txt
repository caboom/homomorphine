
cmake_minimum_required (VERSION 3.0.0)
project (homomorphine)

# set C++ version to 11
set (CMAKE_CXX_STANDARD 17)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

# morphine version
set (HOMOMORPHINE_VERSION_MAJOR 0)
set (HOMOMORPHINE_VERSION_MINOR 1)

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
find_package(SEAL 3.2.0 EXACT REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# what to build...
set(SRC_FILES
   src/homomorphine.cpp
   src/config.cpp
   src/interface.cpp
   src/server.cpp
   src/api.cpp
   src/backend.cpp
   src/backend_factory.cpp
   src/seal_backend.cpp)

# build both service and library
add_executable(homomorphine-service ${SRC_FILES})
add_library(homomorphine SHARED ${SRC_FILES})

# link libraries
target_link_libraries(homomorphine-service ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest SEAL::seal)
target_link_libraries(homomorphine ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest SEAL::seal)
