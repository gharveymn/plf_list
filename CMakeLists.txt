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

  SET(TEST_NAME plf_list)
  SET(SOURCE_FILES plf_list_test_suite.cpp)

  SET(TARGET_VERSIONS 98 11 14 17 20)

  if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(COMPILE_OPTS -stdlib=libc++ -ftime-trace --coverage -Wall -Wextra)
    SET(LINK_OPTS -Wl,--allow-multiple-definition --coverage)
    SET(LINK_LIBS c++ c++abi)
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    SET(COMPILE_OPTS -Wall -Wextra)
    SET(LINK_OPTS )
    SET(LINK_LIBS )
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    SET(COMPILE_OPTS /W4)
    SET(LINK_OPTS )
    SET(LINK_LIBS )
  elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    SET(COMPILE_OPTS )
    SET(LINK_OPTS )
    SET(LINK_LIBS )
  endif()

  IF (UNIX AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    LIST(APPEND COMPILE_OPTS -fsanitize=address)
    LIST(APPEND LINK_OPTS -fsanitize=address)
  ENDIF()

  FOREACH(version ${TARGET_VERSIONS})
    SET(target_name test.${TEST_NAME}.c++${version})
    ADD_EXECUTABLE(${target_name} ${SOURCE_FILES})

    TARGET_COMPILE_OPTIONS(${target_name} PUBLIC ${COMPILE_OPTS})
    TARGET_LINK_OPTIONS   (${target_name} PUBLIC ${LINK_OPTS})
    TARGET_LINK_LIBRARIES (${target_name} ${PACKAGE_NAME} ${LINK_LIBS})

    SET_TARGET_PROPERTIES(${target_name} PROPERTIES
                          CXX_STANDARD          ${version}
                          CXX_STANDARD_REQUIRED NO
                          CXX_EXTENSIONS        NO)
  ENDFOREACH()
ENDIF()
