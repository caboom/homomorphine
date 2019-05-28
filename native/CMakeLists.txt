
cmake_minimum_required (VERSION 3.0.0)
project (homomorphine)

# set C++ version to 14
set (CMAKE_CXX_STANDARD 14)

if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()

# dynamic link to Boost libraries
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

# set the package requirements
find_package(cpprestsdk REQUIRED)
find_package(Boost 1.60 REQUIRED COMPONENTS log program_options unit_test_framework random)
find_package(Threads)
find_package(SEAL 3.2.0 EXACT REQUIRED)
find_library(HELIB_FOUND NAMES helib)
find_library(TFHE_FFTW_FOUND NAMES tfhe-fftw)
find_library(TFHE_AVX_FOUND NAMES tfhe-spqlios-avx)

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

# what to build and link...
set(SRC_FILES
   src/homomorphine.cpp
   src/config.cpp
   src/interface.cpp
   src/server.cpp
   src/api.cpp
   src/backend.cpp
   src/backend_factory.cpp
   src/util.cpp
   src/clang_backend_interface.cpp)

set(Other_LIBRARIES
  Threads::Threads 
  cpprestsdk::cpprest 
)

# find homomorphic libraries - currently supported SEAL and HElib
if (SEAL_FOUND)
  message (">> SEAL found - building with SEAL")
  set (SRC_FILES ${SRC_FILES} src/seal_backend.cpp)
  set (Other_LIBRARIES ${Other_LIBRARIES} SEAL::seal)
  set (HAS_SEAL "#define __HAS_SEAL__")
endif()

if (HELIB_FOUND)
  message (">> HELib found - building with HELib")
  set (SRC_FILES ${SRC_FILES} src/helib_backend.cpp)
  set (Other_LIBRARIES ${Other_LIBRARIES} helib ntl)
  set (HAS_HELIB "#define __HAS_HELIB__")
endif()

if (TFHE_FFTW_FOUND)
  message (">> TFHE with FFTW found - building with TFHE")
  set (SRC_FILES ${SRC_FILES} src/tfhe_backend.cpp)
  set (Other_LIBRARIES ${Other_LIBRARIES} tfhe-fftw)
  set (HAS_TFHE "#define __HAS_TFHE__")
elseif (TFHE_AVX_FOUND)
  message (">> TFHE with AVX found - building with TFHE")
  set (SRC_FILES ${SRC_FILES} src/tfhe_backend.cpp)
  set (Other_LIBRARIES ${Other_LIBRARIES} tfhe-spqlios-avx)
  set (HAS_TFHE "#define __HAS_TFHE__")
endif()

# set homomorphine version
set (HOMOMORPHINE_VERSION_MAJOR 0)
set (HOMOMORPHINE_VERSION_MINOR 1)
set (HOMOMORPHINE_VERSION_PATCH 0)

# pass the information to source code
configure_file (
  "src/info.hpp.in"
  "src/info.hpp"
)

# build both service and library
add_executable(homomorphine-service ${SRC_FILES})
add_library(homomorphine SHARED ${SRC_FILES})

# link libraries
target_link_libraries(homomorphine-service ${Boost_LIBRARIES} ${Other_LIBRARIES})
target_link_libraries(homomorphine ${Boost_LIBRARIES} ${Other_LIBRARIES})

# installation config
set_target_properties(homomorphine PROPERTIES PUBLIC_HEADER 
  "src/backend_factory.hpp;src/backend.hpp;src/clang_backend_interface.hpp;src/clang_types.hpp;src/constants.hpp;src/util.hpp")

install(TARGETS homomorphine-service DESTINATION bin)
install(TARGETS homomorphine LIBRARY DESTINATION lib PUBLIC_HEADER DESTINATION include/homomorphine)

# documentation
option(BUILD_DOC "Build documentation" ON)

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM )

else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

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
