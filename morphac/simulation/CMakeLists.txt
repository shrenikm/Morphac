# Directories
# -------------------------------------------------

set(SIMULATION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SIMULATION_SRC_DIR ${SIMULATION_DIR}/src)
set(SIMULATION_INCLUDE_DIR ${SIMULATION_DIR}/include)
set(SIMULATION_TEST_DIR ${SIMULATION_DIR}/test)

set(SIMULATION_BINARY_DIR ${MORPHAC_BINARY_DIR}/simulation)

set(SIMULATION_BINDING_DIR ${SIMULATION_DIR}/binding)
set(SIMULATION_BINDING_INCLUDE_DIR ${SIMULATION_BINDING_DIR}/include)
set(SIMULATION_BINDING_SRC_DIR ${SIMULATION_BINDING_DIR}/src)
set(SIMULATION_BINDING_BINARY_DIR ${SIMULATION_BINARY_DIR}/binding)
set(SIMULATION_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/simulation
)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constructs source files.
set(SIMULATION_SRC

  playground.cc
  playground_state.cc
)

foreach(file ${SIMULATION_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${SIMULATION_SRC_DIR}/${file}
    ${SIMULATION_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${SIMULATION_INCLUDE_DIR}
  )
endforeach()

# Adding library dependencies.
target_link_libraries(playground_state
  PUBLIC
  state
  map
  robot
)

target_link_libraries(playground
  PUBLIC
  input
  state
  playground_state
  robot
  pilot
  integrator
  integrator_utils
)


# Tests
# -------------------------------------------------

# Simulation tests source files.
set(SIMULATION_TEST_SRC

  playground_state_test.cc
)

# Creating the test executables.
foreach(file ${SIMULATION_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${SIMULATION_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(playground_state_test
  PUBLIC
  gtest_main
  diffdrive_model
  playground_state
)

