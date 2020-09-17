# Directories
# -------------------------------------------------

set(CONSTANTS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CONSTANTS_SRC_DIR ${CONSTANTS_DIR}/src)
set(CONSTANTS_INCLUDE_DIR ${CONSTANTS_DIR}/include)
set(CONSTANTS_TEST_DIR ${CONSTANTS_DIR}/test)
set(CONSTANTS_PYTHON_DIR ${CONSTANTS_DIR}/python)

set(CONSTANTS_BINARY_DIR ${MORPHAC_BINARY_DIR}/constants)

set(CONSTANTS_BINDING_DIR ${CONSTANTS_DIR}/binding)
set(CONSTANTS_BINDING_INCLUDE_DIR ${CONSTANTS_BINDING_DIR}/include)
set(CONSTANTS_BINDING_SRC_DIR ${CONSTANTS_BINDING_DIR}/src)
set(CONSTANTS_BINDING_MODULES_DIR
  ${CONSTANTS_BINDING_DIR}/modules
)
set(CONSTANTS_BINDING_BINARY_DIR ${CONSTANTS_BINARY_DIR}/binding)
set(CONSTANTS_BINDING_INSTALL_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/constants
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Constants source files.
set(CONSTANTS_SRC

  environment_constants.cc
  mechanics_constants.cc
)

foreach(file ${CONSTANTS_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  # Regular shared library.
  add_library(${lib_name}
    SHARED
    ${CONSTANTS_SRC_DIR}/${file}
    ${CONSTANTS_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${CONSTANTS_INCLUDE_DIR}
  )

  # Static library for the python bindings.
  add_library(${lib_name}${STATIC_TARGET_SUFFIX}
    STATIC
    ${CONSTANTS_SRC_DIR}/${file}
    ${CONSTANTS_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}${STATIC_TARGET_SUFFIX}
    PUBLIC
    ${CONSTANTS_INCLUDE_DIR}
  )

endforeach()


# Tests
# -------------------------------------------------

# Constants tests source files.
set(CONSTANTS_TEST_SRC

  environment_constants_test.cc
  mechanics_constants_test.cc
)

# Creating the test executables.
foreach(file ${CONSTANTS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${CONSTANTS_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(environment_constants_test
  PUBLIC
  gtest_main
  environment_constants
)

target_link_libraries(mechanics_constants_test
  PUBLIC
  gtest_main
  mechanics_constants
)


# Python files
# -------------------------------------------------

# List of python files.
set(CONSTANTS_PYTHON_FILES
  colors.py
)

# Appending the directory of the python files.
prepend_list(CONSTANTS_PYTHON_FILES
  ${CONSTANTS_PYTHON_DIR}/
  ${CONSTANTS_PYTHON_FILES}
)

# Install the python files.
install(FILES
  ${CONSTANTS_PYTHON_FILES}
  DESTINATION
  ${CONSTANTS_BINDING_INSTALL_DIR}
)
