# Directories
# -------------------------------------------------

set(PLANNERS_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PLANNERS_BASE_SRC_DIR ${PLANNERS_BASE_DIR}/src)
set(PLANNERS_BASE_INCLUDE_DIR ${PLANNERS_BASE_DIR}/include)
set(PLANNERS_BASE_TEST_DIR ${PLANNERS_BASE_DIR}/test)
set(PLANNERS_BASE_PYTHON_DIR ${PLANNERS_BASE_DIR}/python)

set(PLANNERS_BASE_BINARY_DIR ${PLANNERS_BINARY_DIR}/base)

set(PLANNERS_BASE_BINDING_DIR ${PLANNERS_BASE_DIR}/binding)
set(PLANNERS_BASE_BINDING_INCLUDE_DIR ${PLANNERS_BASE_BINDING_DIR}/include)
set(PLANNERS_BASE_BINDING_SRC_DIR ${PLANNERS_BASE_BINDING_DIR}/src)
set(PLANNERS_BASE_BINDING_BINARY_DIR ${PLANNERS_BASE_BINARY_DIR}/binding)
set(PLANNERS_BASE_BINDING_INSTALL_DIR
  ${PLANNERS_BINDING_INSTALL_DIR}/base
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constructs source files.
set(PLANNERS_BASE_SRC

  planner.cc
)

foreach(file ${PLANNERS_BASE_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${PLANNERS_BASE_SRC_DIR}/${file}
    ${PLANNERS_BASE_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${PLANNERS_BASE_INCLUDE_DIR}
  )
endforeach()


# Tests
# -------------------------------------------------

# Simulation tests source files.
set(PLANNERS_BASE_TEST_SRC

  planner_test.cc
)

# Creating the test executables.
foreach(file ${PLANNERS_BASE_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${PLANNERS_BASE_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(planner_test
  PUBLIC
  gtest_main
  trajectory
  planner
)
