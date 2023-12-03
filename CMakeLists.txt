cmake_minimum_required(VERSION 3.10)

project(fffmock)
set(CMAKE_CXX_STANDARD 17)

# Check gtest submodule
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/googletest/CMakeLists.txt")
  message(FATAL_ERROR "Could not find googletest")
endif()

# Check ffff submodule
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/fff/CMakeLists.txt")
  message(FATAL_ERROR "Could not find fff")
endif()

#################################
# create static library fffmock #
#################################

# Add 3th party code
add_subdirectory(googletest)
add_subdirectory(fff)

# Create a static library
set(SOURCE_FILES fffmock.hpp)
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Link FFF and Google Test libraries
target_link_libraries(${PROJECT_NAME} PRIVATE fff gtest)

# Specify the include directories for your library
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Specify the include directories for FFF and Google Test
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/fff
    ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)

# Create example
add_subdirectory(examples)