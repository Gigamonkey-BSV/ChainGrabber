
cmake_minimum_required(VERSION 3.1...3.14)

# Back compatibility for VERSION range
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()


ADD_EXECUTABLE(testChainGrabber   testLib.cpp src/MockDatabaseImpl.cpp src/MockDatabaseImpl.h testAddress.cpp)
target_include_directories(testChainGrabber PUBLIC .)

target_link_libraries(testChainGrabber chain_grabber chain_link gmock_main ${Boost_LIBRARIES} ${LIBMONGOCXX_LIBRARIES}  nlohmann_json::nlohmann_json)
get_target_property(OUT testChainGrabber LINK_LIBRARIES)
message(STATUS ${OUT})

