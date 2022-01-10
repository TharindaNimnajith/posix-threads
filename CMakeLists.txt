cmake_minimum_required(VERSION 3.15)
project(Threads_CMakeProject)

set(CMAKE_CXX_STANDARD 14)

file( GLOB APP_SOURCES *.cpp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
foreach( SOURCE_FILE ${APP_SOURCES} )
    get_filename_component(APP_NAME ${SOURCE_FILE} NAME_WE)
    add_executable( ${APP_NAME} ${APP_NAME} )
    target_link_libraries (${APP_NAME} Threads::Threads)
    message("added ${SOURCE_FILE}")
endforeach( SOURCE_FILE ${APP_SOURCES} )


set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(pthread-create-example example_pthread_create.cpp)
target_link_libraries (pthread-create-example Threads::Threads)
