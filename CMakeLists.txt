cmake_minimum_required(VERSION 2.8)

project(BBUtil LANGUAGES C CXX)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(PROJECT_DIR ${CMAKE_SOURCE_DIR})
set(SOURCE_DIR ${PROJECT_DIR}/src)

set(CMAKE_CXX_FLAGS "-std=c++11")

set(SOURCE_FILES
  ${SOURCE_DIR}/main.cpp
  ${SOURCE_DIR}/bit_converter.cpp
)


set(HEADER_DIR
  ${PROJECT_DIR}/src
  ${PROJECT_DIR}/include
)

add_definitions(
)

set(THIRD_PARTY_INCLUDE
  ${PROJECT_DIR}/third_party
)


set(SYSTEM_LIB
  /usr/lib
  /usr/local/lib
)



set(CODE_INCLUDE
  ${HEADER_DIR}
  ${THIRD_PARTY_INCLUDE}
)

set(CODE_LIB
  ${SYSTEM_LIB}
  ${THIRD_PARTY_LIB}
)
  
include_directories(${CODE_INCLUDE})
link_directories(${CODE_LIB})

add_executable(bbTest ${SOURCE_FILES})

#add_subdirectory(aaa)
