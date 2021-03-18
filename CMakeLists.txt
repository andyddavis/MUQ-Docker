cmake_minimum_required (VERSION 2.8)

project(Client)

find_package(MUQ REQUIRED)

include_directories(${MUQ_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS ${MUQ_CXX_FLAGS})
set(CMAKE_CXX_COMPILER ${MUQ_CXX_COMPILER})

add_executable(run-docker _docker.cpp)
target_link_libraries(run-docker ${MUQ_LIBRARIES} ${MUQ_LINK_LIBRARIES})

add_executable(run-client _main.cpp)
target_link_libraries(run-client ${MUQ_LIBRARIES} ${MUQ_LINK_LIBRARIES})
