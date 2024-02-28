cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME "task_booking")
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

# Add the subdirectory with service library
add_subdirectory(booking_service_lib)

# Create an executable from main.cpp and link it with the library
add_executable(${PROJECT_NAME} src/main.cpp)

# Link the executable with the library
target_link_libraries(${PROJECT_NAME} booking_service_lib)



# If gtest is not build from sources, we should seek for conan pkg or system-provided lib
if (NOT TARGET gtest)
    message("gtest not found in project tree, using FIND_PACKAGE")
    FIND_PACKAGE(GTest REQUIRED)
    set(GTEST_TARGET GTest::GTest)
else (NOT TARGET gtest)
    set(GTEST_TARGET gtest gmock)
endif () 

# Test project name
set(TEST_PROJECT_NAME "test_${PROJECT_NAME}")

# Test executable
add_executable(${TEST_PROJECT_NAME} "")

# Test Sources
file(GLOB TEST_SOURCES "tests/*")
#target_include_directories(${TEST_PROJECT_NAME} PUBLIC "include" PRIVATE "tests")
target_sources(${TEST_PROJECT_NAME} PRIVATE ${TEST_SOURCES})

# Test link Libraries
target_link_libraries(${TEST_PROJECT_NAME} ${GTEST_TARGET} booking_service_lib)

# Test command
add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})