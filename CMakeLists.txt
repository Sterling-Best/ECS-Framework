cmake_minimum_required(VERSION 3.14)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("ECSframework")

# Set C++ standard globally for all targets
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define source directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(COMPONENT_FRAMEWORK_DIR "${SRC_DIR}/component_framework")
set(ENTITY_FRAMEWORK_DIR "${SRC_DIR}/entity_framework")
set(ID_FRAMEWORK_DIR "${SRC_DIR}/id_framework")
set(MODULES_DIR "${SRC_DIR}/modules")

# Collect all .cpp and .h files recursively from each relevant directory
file(GLOB_RECURSE COMPONENT_SRC_FILES "${COMPONENT_FRAMEWORK_DIR}/*.cpp" "${COMPONENT_FRAMEWORK_DIR}/*.h")
file(GLOB_RECURSE ENTITY_SRC_FILES "${ENTITY_FRAMEWORK_DIR}/*.cpp" "${ENTITY_FRAMEWORK_DIR}/*.h")
file(GLOB_RECURSE ID_SRC_FILES "${ID_FRAMEWORK_DIR}/*.cpp" "${ID_FRAMEWORK_DIR}/*.h")
file(GLOB_RECURSE MODULE_HEADERS "${MODULES_DIR}/*.cpp" "${MODULES_DIR}/*.h")


# Combine all source files
set(SRC_FILES ${COMPONENT_SRC_FILES} ${ENTITY_SRC_FILES} ${ID_SRC_FILES})

# Create a library from the ECS source files
add_library(ECSframeworkLib STATIC ${SRC_FILES})
# Add ankerl_unordered_dense as an interface library
set_target_properties(ECSframeworkLib PROPERTIES LINKER_LANGUAGE CXX)

message(STATUS "ankerl include path: ${CMAKE_SOURCE_DIR}/external/ankerl/unordered_dense_install/include")
target_include_directories(ECSframeworkLib PRIVATE 
    ${SRC_DIR}
    ${CMAKE_SOURCE_DIR}/external/ankerl/unordered_dense_install/include
)

# Define the main executable using ECSframeworkLib
add_executable(ECSframework "main.cpp")

# Properly include generated headers, source directories, and external files for ECSframeworkLib

target_include_directories(ECSframework PRIVATE 
    ${SRC_DIR}
)

# Include the installed headers from ankerl::unordered_dense
# Replace "src/main.cpp" with your actual main entry point
# Link the interface library to your target
target_link_libraries(ECSframework PRIVATE ECSframeworkLib)


# Set C++ standard for the target
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ECSframework PROPERTY CXX_STANDARD 23)
endif()

# Include FetchContent module for Google Test
#include(FetchContent)

# Fetch Google Test
#FetchContent_Declare(
#    googletest
#    GIT_REPOSITORY https://github.com/google/googletest.git
#    GIT_TAG        v1.15.2  # You can change to the desired version
#)

# Make sure Google Test is available
#FetchContent_MakeAvailable(googletest)

# Enable testing
#enable_testing()

# Add tests
#(YourTests "tests/ecs_test.cpp")
#target_link_libraries(YourTests gtest gtest_main ECSframework)

# Add test to CTest
#add_test(NAME YourTests COMMAND YourTests)