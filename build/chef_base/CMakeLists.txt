cmake_minimum_required(VERSION 2.6)

SET(PROJECTNAME chefbase)
SET(LIBRARY_OUTPUT_PATH ${ROOT_DIR}/lib)

FILE(GLOB_RECURSE SOURCES "${ROOT_DIR}/chef_base/*.cc"
    "${ROOT_DIR}/chef_base/*.hpp")
ADD_DEFINITIONS("-g -Wall -Werror -fPIC")
PROJECT(${PROJECTNAME})

ADD_LIBRARY(${PROJECTNAME} SHARED ${SOURCES})
TARGET_LINK_LIBRARIES(${PROJECTNAME} rt pthread libboost_thread.so
        libboost_system.so libboost_date_time.so libboost_chrono.so)
