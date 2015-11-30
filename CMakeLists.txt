cmake_minimum_required(VERSION 2.8)
project(gazebo2ice)

### Dependencies
find_package(GAZEBO 5.1 REQUIRED)

find_package(Boost COMPONENTS system REQUIRED)

## FindIce
set(Ice_LIBRARIES "-lIce -lIceUtil")

## FindJdeRobotInterfaces
#set(JdeRobot_Interfaces_BUILD_DIR ${CMAKE_BINARY_DIR}/../JdeRobot/src/stable/interfaces)
set(JdeRobot_Interfaces_INCLUDE_DIRS /usr/local/include/jderobot)
set(JdeRobot_Interfaces_LIBRARY_DIRS /usr/local/lib/jderobot)
set(JdeRobot_Interfaces_LIBRARIES "JderobotInterfaces")


include_directories(
	${GAZEBO_INCLUDE_DIRS}
	${JdeRobot_Interfaces_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

link_directories(
	${GAZEBO_LIBRARY_DIRS}
	${JdeRobot_Interfaces_LIBRARY_DIRS}
	${Boost_LIBRARY_DIRS}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

### Project config
include_directories(include)


set(SOURCES_COMMON
	src/core/gazebotools.cpp
	src/core/icemanager.cpp
	src/core/globalicemanager.cpp
	include/gazebo2ice/gazebotools.h
	include/gazebo2ice/icemanager.h
	include/gazebo2ice/globalicemanager.h
)
set_property(SOURCE src/core/icemanager.cpp PROPERTY COMPILE_FLAGS "-std=c++0x")

set(SOURCES_CORE
	${SOURCES_COMMON}
)

set(LIBRARIES
	${Ice_LIBRARIES}
	${JdeRobot_Interfaces_LIBRARIES}
	${GAZEBO_LIBRARIES}
	${Boost_LIBRARIES}
)

## core
add_library(gazebo_icecore SHARED ${SOURCES_CORE})
target_link_libraries(gazebo_icecore ${LIBRARIES})
set(LIBRARIES ${LIBRARIES} gazebo_icecore)

## model (bootstap model)
add_library(gazebo_icecore_model SHARED src/plugins/modelplugin.cc)
target_link_libraries(gazebo_icecore_model ${LIBRARIES})

## system (take args)
add_library(gazebo_icecore_args SHARED src/plugins/systemplugin.cc)
target_link_libraries(gazebo_icecore_args ${LIBRARIES})


## pose3d
add_library(gazebo_pose3d2ice SHARED src/plugins/pose3dplugin.cc)
target_link_libraries(gazebo_pose3d2ice ${LIBRARIES})

## test
add_executable(test src/tests/test.cc)
target_link_libraries(test ${LIBRARIES})

#add_library(gazebo_icecore-obj OBJECT ${SOURCES_CORE})
#set_property(TARGET gazebo_icecore-obj PROPERTY POSITION_INDEPENDENT_CODE 1)

#add_library(gazebo_icecore-embedded STATIC $<TARGET_OBJECTS:gazebo_icecore-obj>)
#set_property(TARGET gazebo_icecore-embedded PROPERTY POSITION_INDEPENDENT_CODE 1)

#add_library(gazebo_icecore SHARED $<TARGET_OBJECTS:gazebo_icecore-obj>)
#target_link_libraries(gazebo_icecore
#	${JdeRobot_Interfaces_LIBRARIES}
#)


#add_library(gazebo_icecore-static STATIC ${SOURCES_CORE})
#target_link_libraries(gazebo_icecore-static ${LIBRARIES})
#set_property(TARGET gazebo_icecore-static PROPERTY POSITION_INDEPENDENT_CODE 1)
#add_library(gazebo_icecore SHARED src/icemodelplugin.cc)
#target_link_libraries(gazebo_icecore gazebo_icecore-static)

