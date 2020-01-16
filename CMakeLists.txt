CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(plf_list
        VERSION 1.6.9
        LANGUAGES CXX)

EXECUTE_PROCESS(COMMAND "git submodule update --init -- \"external/create-package\""
                WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

INCLUDE("${PROJECT_SOURCE_DIR}/external/create-package/cmake/create-package.cmake" OPTIONAL)

CREATE_PACKAGE(AUTHOR       mattreecebentley
               NAME         plf_list
               HEADERS      plf_list.h
               HEADERS_PATH ".")

# Options
IF(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  OPTION(PLF_LIST_BUILD_TESTS "Set to ON to build tests" ON)
ELSE()
  OPTION(PLF_LIST_BUILD_TESTS "Set to ON to build tests" OFF)
ENDIF()

# Only include tests if we are at the top level
IF(PLF_LIST_BUILD_TESTS)
  SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
  ADD_EXECUTABLE(test_plf_list plf_list_test_suite.cpp)
  TARGET_LINK_LIBRARIES(test_plf_list plf_list)

  SET_TARGET_PROPERTIES(test_plf_list PROPERTIES
                        CXX_STANDARD          20
                        CXX_STANDARD_REQUIRED YES
                        CXX_EXTENSIONS        NO)
ENDIF()
