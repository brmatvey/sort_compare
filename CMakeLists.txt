cmake_minimum_required(VERSION 3.10)

project(Sort_compare CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE=Debug)

set(SOURCE main.cpp sort_algo.cpp query_factory.cpp drawing.cpp)
set(INCLUDE log_duration.h sort_algo.h vector_processing.h query_factory.h drawing.h)

#look for SFML and add it
find_package (SFML COMPONENTS system window graphics audio REQUIRED)

include_directories(${SFML_INCLUDE_DIR})

add_executable(sort_compare ${INCLUDE} ${SOURCE})

# Set include directory search paths
target_include_directories(sort_compare
  PRIVATE
    "${PROJECT_BINARY_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
  )

# Link executable to required SFML modules
target_link_libraries(sort_compare sfml-graphics sfml-audio)
