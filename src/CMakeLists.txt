cmake_minimum_required(VERSION 3.5)

# Utility functions
# -------------------------------------------------
function(print_section_delimiter)
  message("===============")
endfunction()

function(print_section_header HEADER)
  print_section_delimiter()
  message(${HEADER})
  print_section_delimiter()
endfunction()


# Project details
# -------------------------------------------------
print_section_header("Project Details")

set(MORPHAC_NAME "morphac")
set(MORPHAC_MAJOR_VERSION 1)
set(MORPHAC_MINOR_VERSION 0)
set(MORPHAC_PATCH_VERSION 0)

project(
  ${MORPHAC_NAME}
  VERSION ${MORPHAC_MAJOR_VERSION}.${MORPHAC_MINOR_VERSION}.${MORPHAC_PATCH_VERSION}
  LANGUAGES CXX
)

message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "Project version: ${PROJECT_VERSION}")


# Options (Interface)
# -------------------------------------------------
print_section_header("Build Options")

# Flag to enable/disable testing
option(BUILD_TESTS "Build all of the project's test executables" ON)
option(BUILD_WITH_WARNINGS "Builds the project with -Wall and -Wextra" ON)
option(BUILD_WITH_WARNINGS_AS_ERRORS "Builds the project with -Werror" ON)

# Displaying the list of options that have been set.
message(STATUS "[ BUILD_TESTS has been set to ${BUILD_TESTS} ]")
message(STATUS "[ BUILD_WITH_WARNINGS has been set to ${BUILD_WITH_WARNINGS} ]")
message(STATUS "[ BUILD_WITH_WARNINGS_AS_ERRORS has been set to ${BUILD_WITH_WARNINGS_AS_ERRORS} ]")


# Configuring
# -------------------------------------------------
print_section_header("Build Configuration")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

message(STATUS "[ C++ version: ${CMAKE_CXX_STANDARD} ]")

if (${BUILD_WITH_WARNINGS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(${BUILD_WITH_WARNINGS})

if (${BUILD_WITH_WARNINGS_AS_ERRORS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif(${BUILD_WITH_WARNINGS_AS_ERRORS})

if (${BUILD_TESTS})
  enable_testing()
endif(${BUILD_TESTS})


# Build variables (Internal)
# -------------------------------------------------
set(PYTHON_BINDING_PREFIX "_binding_")

# Python
# -------------------------------------------------
# Finding the python executable and obtaining the site-packages directory
print_section_header("Python Configuration")

find_package(PythonInterp 3.7 REQUIRED)
execute_process(COMMAND
  "${PYTHON_EXECUTABLE}" -c "import site; print(site.getsitepackages()[0])"
  OUTPUT_VARIABLE PYTHON_BINDING_INSTALL_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE
)

if(${PYTHONINTERP_FOUND})
  message(STATUS "[ Python Interpreter found ]")
else(${PYTHONINTERP_FOUND})
  message(STATUS "[ Python Interpreter not found ]")
endif(${PYTHONINTERP_FOUND})

message(STATUS
  "[ Python binding install directory: ${PYTHON_BINDING_INSTALL_DIR} ]"
)


# Third party
# -------------------------------------------------

# Googletest

# Download and unpack googletest at configure time.
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Add googletest directly to the build.
add_subdirectory(
  "${CMAKE_BINARY_DIR}/googletest-src"
  "${CMAKE_BINARY_DIR}/googletest-build"
  EXCLUDE_FROM_ALL
)

# Eigen

set(EIGEN_REPO_DIR ${PROJECT_SOURCE_DIR}/third_party/eigen)
set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/eigen)

# As eigen is used in almost every target, include_directories is used instead
# of having to target_include_directories eigen for each target.
include_directories(${EIGEN_INCLUDE_DIR})

# Pybind11

set(PYBIND11_REPO_DIR ${PROJECT_SOURCE_DIR}/third_party/pybind11)
set(PYBIND11_INCLUDE_DIR ${PYBIND11_REPO_DIR}/include)

add_subdirectory(${PYBIND11_REPO_DIR} third_party/pybind11 EXCLUDE_FROM_ALL)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(morphac)

