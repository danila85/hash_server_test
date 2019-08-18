project(hash_server_unit_test)
cmake_minimum_required(VERSION 2.8)

add_executable(${PROJECT_NAME} main server_unit_test)

target_link_libraries(${PROJECT_NAME} gtest Boost::thread hash_server)

add_test(NAME ServerUnitTest COMMAND hash_server_unit_test)
