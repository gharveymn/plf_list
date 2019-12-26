CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(plf_list
        VERSION 1.6.9
        LANGUAGES CXX)

INCLUDE(cmake/create-package.cmake)

CREATE_HEADER_ONLY_PACKAGE(AUTHOR       mattreecebentley
                           NAME         plf_list
                           HEADERS      plf_list.h
                           INCLUDE_PATH ".")

# Options
OPTION(PLF_LIST_BUILD_TESTS "Set to ON to build tests" ON)

# Only include tests if we are at the top level
IF(PLF_LIST_BUILD_TESTS AND (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
  ADD_EXECUTABLE(test plf_list_test_suite.cpp)
  TARGET_LINK_LIBRARIES(test plf_list)
ENDIF()
