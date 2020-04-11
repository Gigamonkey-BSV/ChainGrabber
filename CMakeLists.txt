 
cmake_minimum_required(VERSION 3.1...3.14)

# Back compatibility for VERSION range
if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(chain_grabber 	VERSION 1.0
		DESCRIPTION "Downloads the needed parts of the chain into a db"
		LANGUAGES CXX)
		

# Set cmake as import path for Find*.cmake files
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

### Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

## Check if GTests is installed. If not, install it

option(PACKAGE_TESTS "Build the tests" ON)
if(NOT TARGET gtest_main AND PACKAGE_TESTS)
	# Download and unpack googletest at configure time
	configure_file(cmake/gtests.txt.in googletest-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
			RESULT_VARIABLE result
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "CMake step for googletest failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
			RESULT_VARIABLE result
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
	if(result)
		message(FATAL_ERROR "Build step for googletest failed: ${result}")
	endif()

	# Prevent overriding the parent project's compiler/linker
	# settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	
	# Add googletest directly to our build. This defines
	# the gtest and gtest_main targets.
	add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
			${CMAKE_CURRENT_BINARY_DIR}/googletest-build)
endif()


# Boost settings
set(Boost_LIB_PREFIX            "lib"       CACHE STRING "")
set(Boost_USE_MULTITHREADED     ON          CACHE BOOL "") # '-mt' flag
set(Boost_USE_STATIC_LIBS       ON          CACHE BOOL "")
set(Boost_USE_STATIC_RUNTIME    OFF         CACHE BOOL "") # '-s' tag
set(Boost_USE_DEBUG_RUNTIME     OFF         CACHE BOOL "") # '-g' tag
set(Boost_COMPILER              "-mgw49"    CACHE STRING "")

# Include Boost
find_package(Boost 1.72.0 COMPONENTS system program_options  REQUIRED)

if(Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions("-DHAS_BOOST")

endif()


#mongodb cxx wrapper
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_LIBRARIES})
include_directories(${LIBBSONCXX_LIBRARIES})
include_directories(${LIBMONGOCXX_INCLUDE_DIRS})
include_directories(${LIBBSONCXX_INCLUDE_DIRS})

#json
find_package(nlohmann_json 3.2.0 REQUIRED)

find_package(PkgConfig REQUIRED)

pkg_check_modules(HYPODERMIC REQUIRED libhypodermic)

		## Enable testing
include(CTest)

if(PACKAGE_TESTS)
    enable_testing()
    add_subdirectory(test)
	

endif()

#  Add Library source files here
find_package(OpenSSL REQUIRED)
add_library(chain_grabber
		src/chainGrabber/MongoDatabase.cpp  include/chainGrabber/ConfigurationManager.h src/chainGrabber/ConfigurationManagerJSON.cpp include/chainGrabber/ConfigurationManagerJSON.h include/chainGrabber/BitcoinAPI.h include/chainGrabber/WhatsOnChainAPI.h src/chainGrabber/WhatsOnChainAPI.cpp include/chainGrabber/certificates.h include/chainLink/ChainLink.h src/chainLink/ChainLink.cpp include/chainLink/messages/BaseMessage.h include/chainLink/messages/MessageHeader.h)
        

include_directories("include")
add_library(chain_link
		src/chainLink/Constants.cpp
		src/chainLink/ChainLink.cpp
		src/chainLink/messages/Payload.cpp
		src/chainLink/NodeServer.cpp
		src/chainLink/Node.cpp
		src/chainLink/messages/VersionPayload.cpp
		src/chainLink/Address.cpp
		src/chainLink/Utils.cpp
		src/chainLink/SVNode.cpp
		src/chainLink/messages/MessageHeader.cpp
		src/chainLink/messages/BaseMessage.cpp
		src/chainLink/messages/RejectPayload.cpp
		src/chainLink/messages/PingPayload.cpp
		src/chainLink/messages/PongPayload.cpp
		src/chainLink/messages/ProtoconfPayload.cpp
		)
add_executable(chain_grabber_main src/main.cpp )
add_executable(chain_grabber_test src/test.cpp)

target_link_libraries(chain_grabber_main chain_link chain_grabber ${LIBMONGOCXX_LIBRARIES} ${Boost_LIBRARIES}  nlohmann_json::nlohmann_json pthread z OpenSSL::SSL  OpenSSL::Crypto)
target_link_libraries(chain_grabber_test chain_link chain_grabber ${LIBMONGOCXX_LIBRARIES} ${Boost_LIBRARIES}  nlohmann_json::nlohmann_json pthread z OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(chain_grabber PUBLIC include chain_link ${HYPODERMIC_INCLUDE_DIRS})


# Set C++ version
target_compile_features(chain_grabber PUBLIC cxx_std_17)
set_target_properties(chain_grabber PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(chain_link PUBLIC cxx_std_17)
set_target_properties(chain_link PROPERTIES CXX_EXTENSIONS OFF)
