CMAKE_MINIMUM_REQUIRED(VERSION 3.1)
PROJECT(plf_list
        VERSION 1.6.9
        LANGUAGES CXX)

IF(NOT CREATE_PACKAGE_VERSION VERSION_GREATER_EQUAL 0.0.4)
  IF(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/create-package/cmake/create-package.cmake")
    MESSAGE(STATUS "Initializing create-package-0.0.4 in git submodule.")
    EXECUTE_PROCESS(COMMAND git submodule --quiet update --init -- "${PROJECT_SOURCE_DIR}/external/create-package"
                    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
  ENDIF()
  INCLUDE("${PROJECT_SOURCE_DIR}/external/create-package/cmake/create-package.cmake")
ENDIF()

CREATE_PACKAGE(AUTHOR         mattreecebentley
               NAME           plf_list
               HEADERS        plf_list.h
               HEADERS_PATH   "."
               NO_HEADERS_PREFIX)

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

  IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    TARGET_COMPILE_OPTIONS(test_plf_list PUBLIC -stdlib=libc++ -ftime-trace --coverage -Wall -Wextra)
    TARGET_LINK_OPTIONS(test_plf_list PUBLIC -Wl,--allow-multiple-definition --coverage)
    TARGET_LINK_LIBRARIES(test_plf_list c++ c++abi)
  ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    TARGET_COMPILE_OPTIONS(test_plf_list PUBLIC -Wall -Wextra)
  ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    TARGET_COMPILE_OPTIONS(test_plf_list PUBLIC /W4)
  ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")

  ENDIF()

  SET_TARGET_PROPERTIES(test_plf_list PROPERTIES
                        CXX_STANDARD          11
                        CXX_STANDARD_REQUIRED YES
                        CXX_EXTENSIONS        NO)
ENDIF()
