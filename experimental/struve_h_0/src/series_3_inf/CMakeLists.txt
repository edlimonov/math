cmake_minimum_required(VERSION 3.10)
project(MyBoostProject)

find_package(Boost REQUIRED COMPONENTS math)

add_executable(app series_3_inf.cpp)
target_link_libraries(app Boost::math)

set_target_properties(app PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)