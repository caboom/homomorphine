
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
find_package(Boost 1.60 REQUIRED COMPONENTS log program_options unit_test_framework random)
find_package(Threads)
find_package(SEAL 3.2.0 EXACT REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# what to build...
set(SRC_FILES
   src/homomorphine.cpp
   src/constants.cpp
   src/config.cpp
   src/interface.cpp
   src/server.cpp
   src/api.cpp
   src/backend.cpp
   src/backend_factory.cpp
   src/seal_backend.cpp
   src/util.cpp)

# build both service and library
add_executable(homomorphine-service ${SRC_FILES})
add_library(homomorphine SHARED ${SRC_FILES})

# link libraries
target_link_libraries(homomorphine-service ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest SEAL::seal)
target_link_libraries(homomorphine ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest SEAL::seal)

# tests for homomorphine
enable_testing()

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} test/*.cpp)

foreach(testSrc ${TEST_SRCS})
  get_filename_component(testName ${testSrc} NAME_WE)
  
  add_executable(${testName} ${testSrc})

  target_link_libraries(${testName} ${Boost_LIBRARIES} Threads::Threads cpprestsdk::cpprest SEAL::seal homomorphine)

  set_target_properties(${testName} 
    PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}/test_output
  )

  #Finally add it to test execution - 
  #Notice the WORKING_DIRECTORY and COMMAND
  add_test(NAME ${testName} 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test_output 
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test_output/${testName}
  )
endforeach(testSrc)
