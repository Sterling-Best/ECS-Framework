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

# Include path for ankerl::unordered_dense
set(ANKERL_UNORDERED_DENSE_PATH "${CMAKE_SOURCE_DIR}/external/ankerl/unordered_dense_install")
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${ANKERL_UNORDERED_DENSE_PATH}/include")
# Add this directory to the prefix path in case we need to find it
list(APPEND CMAKE_PREFIX_PATH "${ANKERL_UNORDERED_DENSE_PATH}/lib/cmake/unordered_dense")

# Collect all .cpp and .h files recursively from each relevant directory
file(GLOB_RECURSE COMPONENT_SRC_FILES "${COMPONENT_FRAMEWORK_DIR}/*.cpp")
file(GLOB_RECURSE ENTITY_SRC_FILES "${ENTITY_FRAMEWORK_DIR}/*.cpp")
file(GLOB_RECURSE ID_SRC_FILES "${ID_FRAMEWORK_DIR}/*.cpp")
file(GLOB_RECURSE MODULE_SRC_FILES "${MODULES_DIR}/*.cpp" )

message(STATUS "Component Source Files: ${COMPONENT_SRC_FILES}")
message(STATUS "Entity Source Files: ${ENTITY_SRC_FILES}")
message(STATUS "ID Source Files: ${ID_SRC_FILES}")

# Combine all source files
set(SRC_FILES ${COMPONENT_SRC_FILES} ${ENTITY_SRC_FILES} ${ID_SRC_FILES} ${MODULE_SRC_FILES})

# Create a static library from the ECS source files
add_library(ECSframeworkLib STATIC dummy.cpp)

# Set output directory for the library
set_target_properties(ECSframeworkLib PROPERTIES LINKER_LANGUAGE CXX)

find_package(unordered_dense CONFIG REQUIRED)
target_link_libraries(ECSframeworkLib unordered_dense::unordered_dense)

message(STATUS "ankerl include path: ${CMAKE_SOURCE_DIR}/external/ankerl/unordered_dense_install/include")

# Include directories for the ECSframeworkLib library
target_include_directories(ECSframeworkLib PRIVATE 
    ${SRC_DIR}
    ${CMAKE_SOURCE_DIR}/external/ankerl/unordered_dense_install/include   # Add include directory for unordered_dense.h
)


# Define the main executable using ECSframeworkLib
add_executable(ECSframework "main.cpp")

# Set output directory for the executable
set_target_properties(ECSframework PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Include directories for the executable
target_include_directories(ECSframework PRIVATE 
    ${SRC_DIR}
    ${CMAKE_SOURCE_DIR}/external/ankerl/unordered_dense_install/include   # Add include directory for unordered_dense.h
)

#find_package(ankerl::unordered_dense CONFIG REQUIRED)
#target_link_libraries(ECSframeworkLib unordered_dense::unordered_dense)

# Link ECSframeworkLib to ECSframework
target_link_libraries(ECSframework PRIVATE ECSframeworkLib)

# Set C++ standard for the target
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ECSframework PROPERTY CXX_STANDARD 23)
endif()

# Add dependency to ensure ECSframeworkLib builds before ECSframework
add_dependencies(ECSframework ECSframeworkLib)

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