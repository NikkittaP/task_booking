cmake_minimum_required(VERSION 3.5)

# Create a library
add_library(booking_service_lib)

file(GLOB_RECURSE SOURCES "include/*" "src/*")
target_sources(booking_service_lib PRIVATE ${SOURCES})

target_include_directories(booking_service_lib PUBLIC "include")