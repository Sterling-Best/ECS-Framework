# CMakeList.txt : CMake project for ECSframework, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("ECSframework")

# Set C++ standard globally for all targets
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)  # Optional: disables compiler-specific extensions

# Add source to this project's executable.
add_executable (ECSframework "ECSframework.cpp" "ECSframework.h" "icomponent.h" "TransformComponent.h" "component_manager.h" "is_valid_entity_id_type.h"  "src/component_framework/component_framework.h" "src/component_framework/component_manager_registry.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ECSframework PROPERTY CXX_STANDARD 23)
endif()

# TODO: Add tests and install targets if needed.

# Include FetchContent module
include(FetchContent)

# Fetch Google Test
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2  # You can change to the desired version
)

# Make sure Google Test is available
FetchContent_MakeAvailable(googletest)

# Add your tests
enable_testing()
add_executable(YourTests ecs_test.cpp "src/component_framework/component_framework.h" "src/component_framework/component_manager_registry.h")  # Replace with your test source files
target_link_libraries(YourTests gtest gtest_main)

# Add test to CTest
add_test(NAME YourTests COMMAND YourTests)
