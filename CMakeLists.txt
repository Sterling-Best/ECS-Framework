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

# Define the output header file paths
set(GENERATED_IDCONFIG_HEADER "${CMAKE_BINARY_DIR}/collected_id_configs.h")
set(GENERATED_COMPONENT_HEADER "${CMAKE_BINARY_DIR}/collected_components.h")
set(GENERATED_FACTORY_HEADER "${CMAKE_BINARY_DIR}/collected_factories.h")

# Collect all .cpp and .h files recursively from each relevant directory
file(GLOB_RECURSE COMPONENT_SRC_FILES "${COMPONENT_FRAMEWORK_DIR}/*.cpp" "${COMPONENT_FRAMEWORK_DIR}/*.h")
file(GLOB_RECURSE ENTITY_SRC_FILES "${ENTITY_FRAMEWORK_DIR}/*.cpp" "${ENTITY_FRAMEWORK_DIR}/*.h")
file(GLOB_RECURSE ID_SRC_FILES "${ID_FRAMEWORK_DIR}/*.cpp" "${ID_FRAMEWORK_DIR}/*.h")
file(GLOB_RECURSE MODULE_HEADERS "${MODULES_DIR}/*.h")

# Write headers for each category
file(WRITE ${GENERATED_IDCONFIG_HEADER} "// Automatically generated IdConfig header file\n")
file(WRITE ${GENERATED_COMPONENT_HEADER} "// Automatically generated Component header file\n")
file(WRITE ${GENERATED_FACTORY_HEADER} "// Automatically generated Factory header file\n")

# Iterate through the collected headers and classify them
foreach(header ${MODULE_HEADERS})
    if(header MATCHES ".*IdConfig\\.h$")
        file(APPEND ${GENERATED_IDCONFIG_HEADER} "#include \"${header}\"\n")
    elseif(header MATCHES ".*ComponentFactory\\.h$")
        # If the header contains both a component and a factory, add to both headers
        file(APPEND ${GENERATED_COMPONENT_HEADER} "#include \"${header}\"\n")
        file(APPEND ${GENERATED_FACTORY_HEADER} "#include \"${header}\"\n")
    elseif(header MATCHES ".*Component\\.h$")
        file(APPEND ${GENERATED_COMPONENT_HEADER} "#include \"${header}\"\n")
    elseif(header MATCHES ".*Factory\\.h$")
        file(APPEND ${GENERATED_FACTORY_HEADER} "#include \"${header}\"\n")
    endif()
endforeach()

# Combine all source files
set(SRC_FILES ${COMPONENT_SRC_FILES} ${ENTITY_SRC_FILES} ${ID_SRC_FILES})

# Create a library from the ECS source files
add_library(ECSframeworkLib STATIC ${SRC_FILES})
set_target_properties(ECSframeworkLib PROPERTIES LINKER_LANGUAGE CXX)

# Define the main executable using ECSframeworkLib
add_executable(ECSframework "main.cpp")

# Properly include generated headers and source directories
target_include_directories(ECSframework PRIVATE ${CMAKE_BINARY_DIR} ${SRC_DIR})

  # Replace "src/main.cpp" with your actual main entry point
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