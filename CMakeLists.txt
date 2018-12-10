cmake_minimum_required (VERSION 3.5)

project(Image_Statistics)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Image_Statistics Image_Statistics.cpp)

target_link_libraries(Image_Statistics ${OpenCV_LIBS})
