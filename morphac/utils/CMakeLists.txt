# Directories
# -------------------------------------------------

set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(UTILS_SRC_DIR ${UTILS_DIR}/src)
set(UTILS_INCLUDE_DIR ${UTILS_DIR}/include)
set(UTILS_TEST_DIR ${UTILS_DIR}/test)
set(UTILS_PYTHON_DIR ${UTILS_DIR}/python)

set(UTILS_BINARY_DIR ${MORPHAC_BINARY_DIR}/utils)

set(UTILS_BINDING_DIR ${UTILS_DIR}/binding)
set(UTILS_BINDING_INCLUDE_DIR ${UTILS_BINDING_DIR}/include)
set(UTILS_BINDING_SRC_DIR ${UTILS_BINDING_DIR}/src)
set(UTILS_BINDING_MODULES_DIR
  ${UTILS_BINDING_DIR}/modules
)
set(UTILS_BINDING_BINARY_DIR ${UTILS_BINARY_DIR}/binding)

# Directories to install the bindings to.
set(UTILS_PACKAGE_DIR
  ${MORPHAC_PACKAGE_MODULE_DIR}/utils
)
set(UTILS_SITE_PACKAGES_DIR
  ${PYTHON_BINDING_INSTALL_DIR}/utils
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)


# Libraries
# -------------------------------------------------

# Utils source files.
set(UTILS_SRC

  angle_utils.cc
  integrator_utils.cc
  numeric_utils.cc
  points_utils.cc
)

morphac_add_libraries(
  ${UTILS_INCLUDE_DIR}
  ${UTILS_SRC_DIR}
  ${UTILS_SRC}
)

# Adding library dependencies.
morphac_link_libraries(integrator_utils
  integrator
  euler_integrator
  mid_point_integrator
  rk4_integrator
  kinematic_model
)


# Tests
# -------------------------------------------------

# Utils test source files.
set(UTILS_TEST_SRC

  angle_utils_test.cc
  integrator_utils_test.cc
  numeric_utils_test.cc
  points_utils_test.cc
)

# Creating the test executables.
foreach(file ${UTILS_TEST_SRC})
  get_filename_component(test_name
    ${file} NAME_WE
  )

  add_executable(
    ${test_name}
    ${UTILS_TEST_DIR}/${file}
  )

  add_test(NAME ${test_name}
    COMMAND ${test_name}
  )
endforeach()

# Linking depending libraries.
target_link_libraries(angle_utils_test
  PUBLIC
  gtest_main
  angle_utils
)

target_link_libraries(integrator_utils_test
  PUBLIC
  gtest_main
  integrator_utils
  integrator
  diffdrive_model
)

target_link_libraries(numeric_utils_test
	PUBLIC
	gtest_main
	numeric_utils
)

target_link_libraries(points_utils_test
  PUBLIC
  gtest_main
  points_utils
)


# Python files
# -------------------------------------------------

# List of python files.
set(UTILS_PYTHON_FILES
  canvas_utils.py
  decorator_utils.py
  mechanics_utils.py
  python_utils.py
  pytest_utils.py
)

# Appending the directory of the python files.
prepend_list(UTILS_PYTHON_FILES
  ${UTILS_PYTHON_DIR}/
  ${UTILS_PYTHON_FILES}
)

morphac_package_files(
  ${UTILS_PACKAGE_DIR}
  ${UTILS_SITE_PACKAGES_DIR}
  # Files
  ${UTILS_PYTHON_FILES}
)

