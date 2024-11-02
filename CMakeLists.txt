cmake_minimum_required(VERSION 3.10)
project(simple-wayland-client C)

# Find Wayland client library
find_package(PkgConfig REQUIRED)
pkg_check_modules(WAYLAND REQUIRED wayland-client)

# Create executable
add_executable(simple-wayland-client simple-wayland-client.c)
target_link_libraries(simple-wayland-client ${WAYLAND_LIBRARIES})
target_include_directories(simple-wayland-client PUBLIC ${WAYLAND_INCLUDE_DIRS})