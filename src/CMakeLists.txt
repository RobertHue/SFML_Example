
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
	
	file(GLOB_RECURSE dependencies
		"../include/*.h"
		"*.cpp"
	)
	
	include_directories(${Boost_INCLUDE_DIRS} ${SFML_INCLUDE_DIR})	
	add_executable( ${EXECUTABLE_NAME} ${dependencies}	)	
	target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Boost_LIBRARIES})
endif()
########################################
########################################
########################################