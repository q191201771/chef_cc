cmake_minimum_required(VERSION 2.6)

SET(PROJECTNAME chefbase)
SET(LIBRARY_OUTPUT_PATH ${ROOT_DIR}/lib)

FILE(GLOB_RECURSE SOURCES "${ROOT_DIR}/chef_base/*.cc")
ADD_DEFINITIONS("-g -Wall -fPIC")
PROJECT(${PROJECTNAME})

ADD_LIBRARY(${PROJECTNAME} STATIC ${SOURCES})
TARGET_LINK_LIBRARIES(${PROJECTNAME} pthread libboost_thread.a libboost_system.a libboost_date_time.a)
