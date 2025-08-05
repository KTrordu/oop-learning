cmake_minimum_required(VERSION 3.28)  # Daha yeni versiyon gerekli
project(GeometrySystem CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GCC için module support
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmodules-ts")
endif()

# Önce module interface'i compile et
add_library(geometry_module)
target_sources(geometry_module
  PUBLIC
    FILE_SET CXX_MODULES FILES
    src/geometry.ixx
)

# Sonra implementation'ı ekle
target_sources(geometry_module PRIVATE src/geometry.cpp)

# Son olarak main executable
add_executable(GeometrySystem src/main.cpp)
target_link_libraries(GeometrySystem PRIVATE geometry_module)