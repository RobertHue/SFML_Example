# Author:	Robert Huemmer
cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

# Define the project name
set(PROJECT_NAME "SFML sprite example")
project($PROJECT_NAME VERSION 0.1 LANGUAGES CXX)

message(STATUS "~~~ ${PROJECT_NAME} v${PROJECT_VERSION} ~~~")
message(STATUS "Target: ${CMAKE_SYSTEM_PROCESSOR} (${CMAKE_SYSTEM_NAME})")
message(STATUS "Build Type : ${CMAKE_BUILD_TYPE}")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

########################################
# set some compiler flags
SET(COMPILER_FLAGS
	"-std=c++11 -g3 -Wall"
)
SET(LINKER_FLAGS
	""
)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINKER_FLAGS}" )

########################################
# Add a given directory to those the compiler uses to search for include files
include_directories( . )
include_directories (${Boost_INCLUDE_DIRS})



########################################
# configure and find BOOST
set(Boost_USE_STATIC_LIBS        ON) 	# only find static libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.69.0 REQUIRED COMPONENTS system filesystem unit_test_framework serialization)

########################################
# configure and find Qt5 (uncomment when used)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)	# Find includes in corresponding build directories
#set(CMAKE_AUTOMOC ON)	# Instruct CMake to run moc automatically when needed.
#find_package(Qt5 REQUIRED COMPONENTS Widgets)

# Detect and add SFML 
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED system window graphics network audio)


set(EXECUTABLE_NAME "Test.exe")

########################################
########################################
########################################
if( Boost_FOUND AND SFML_FOUND)
	message(STATUS "boost-include-dirs : ${Boost_INCLUDE_DIRS}")
	message(STATUS "sfml-include-dirs : ${SFML_INCLUDE_DIR}")
	message(STATUS "sfml-exe-name : ${EXECUTABLE_NAME}")
	message(STATUS "sfml-libraries : ${SFML_LIBRARIES}")
	message(STATUS "sfml-dependencies : ${SFML_DEPENDENCIES}")
	message(STATUS "Boost_LIBRARIES : ${Boost_LIBRARIES}")
	
	include_directories(${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})	
	add_executable( ${EXECUTABLE_NAME} SFML.cpp	)	
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Boost_LIBRARIES})
endif()
########################################
########################################
########################################