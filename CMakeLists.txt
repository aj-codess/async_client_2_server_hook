cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(CMAKE_TOOLCHAIN_FILE /home/aj/code/Berita/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(client_2_Server_Hook VERSION 1.0)

add_executable(main main.cpp)
target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Boost)
target_include_directories(main PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(main PUBLIC ${Boost_LIBRARIES} ${Boost_DEPENDENCIES})

find_package(OpenSSL REQUIRED)
target_include_directories(main PUBLIC ${OpenSSL_INCLUDE_DIR})
target_link_libraries(main PUBLIC ${OpenSSL_LIBRARIES} ${OpenSSL_DEPENDENCIES})