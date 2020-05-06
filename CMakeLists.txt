cmake_minimum_required(VERSION 3.5)

# Utility functions
# -------------------------------------------------

# Functions to display section headers for status information.
function(print_section_delimiter)
  message("===============")
endfunction()

function(print_section_header HEADER)
  print_section_delimiter()
  message(${HEADER})
  print_section_delimiter()
endfunction()


# Find the python3 version installed.
function(find_python_version out)
  execute_process(COMMAND
    "python3" -c
      "import sys; print(str(sys.version_info[0]) + '.' + str(sys.version_info[1]))"
    OUTPUT_VARIABLE tmp_version
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(${out} ${tmp_version} PARENT_SCOPE)
endfunction()


# Check if a particular version is valid.
function(is_valid_version out version minimum_version)
  if((version VERSION_EQUAL minimum_version) OR
    (version VERSION_GREATER minimum_version))
    set(${out} TRUE PARENT_SCOPE)
  else()
    set(${out} FALSE PARENT_SCOPE)
  endif()
endfunction()


# Find the python site-packages directory.
# This needs to be called after the find_package(Python) call
# as it requires PYTHON_EXECUTABLE to be set
function(find_python_site_packages_dir out)
  execute_process(COMMAND
    "${PYTHON_EXECUTABLE}" -c
      "from distutils.sysconfig import get_python_lib; print(get_python_lib())"
    OUTPUT_VARIABLE tmp_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  # Everything will be installed in a directory given by the project name.
  set(${out} ${tmp_dir}/${MORPHAC_NAME} PARENT_SCOPE)
endfunction()


# Takes in a file name and returns the header name
# by replace the current extension with .h
# If the filename consists of a directory as well, the directory is
# kept as is and the filename extension is replace with .h
function(get_header_name out file)
  get_filename_component(dir ${file} DIRECTORY)
  get_filename_component(header ${file} NAME_WE)
  # If the directory is empty (No directory given), then the
  # return value is just the filename.h
  if("${dir}" STREQUAL "")
    set(${out} ${header}.h PARENT_SCOPE)
  else()
    set(${out} ${dir}/${header}.h PARENT_SCOPE)
  endif()

endfunction()


# Function that takes a list and prepends some given string
# to each element.
# CMake 3.12 has LIST TRANSFORM that can do this but our
# minimum CMake version is 3.5
function(prepend_list out prefix)
  set(tmp_list "")
  foreach(var ${ARGN})
    list(APPEND tmp_list ${prefix}${var})
  endforeach()
  set(${out} ${tmp_list} PARENT_SCOPE)
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

set(BUILD_TESTS ON CACHE BOOL "Build all of the project's test executables")
set(BUILD_WITH_WARNINGS ON CACHE BOOL "Builds the project with -Wall and -Wextra")
set(BUILD_WITH_WARNINGS_AS_ERRORS ON CACHE BOOL "Builds the project with -Werror")
set(BUILD_PYTHON_BINDINGS ON CACHE BOOL "Build all of the python bindings")

# Displaying the list of options that have been set.
message(STATUS "[ BUILD_TESTS has been set to ${BUILD_TESTS} ]")
message(STATUS "[ BUILD_WITH_WARNINGS has been set to ${BUILD_WITH_WARNINGS} ]")
message(STATUS "[ BUILD_WITH_WARNINGS_AS_ERRORS has been set to ${BUILD_WITH_WARNINGS_AS_ERRORS} ]")
message(STATUS "[ BUILD_PYTHON_BINDINGS has been set to ${BUILD_PYTHON_BINDINGS} ]")


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


# Python
# -------------------------------------------------

print_section_header("Python Configuration")

# Minimum python version required.
set(PYTHON_MINIMUM_VERSION 3.5)
# Prefix for compiled python bindings.
set(PYTHON_BINDING_PREFIX "_binding_")

# Find python version
find_python_version(PYTHON_VERSION)

# Make sure that the python version is valid
is_valid_version(is_python_version_valid ${PYTHON_VERSION} ${PYTHON_MINIMUM_VERSION})
if(NOT is_python_version_valid)
  message(FATAL_ERROR "[ Python valid must be >= ${PYTHON_MINIMUM_VERSION} ]")
endif()

# Finding the python executable.
find_package(PythonInterp ${PYTHON_VERSION} REQUIRED)

# Site packages dir for installing bindings.
find_python_site_packages_dir(PYTHON_BINDING_INSTALL_DIR)

message(STATUS "[ Python version: ${PYTHON_VERSION} ]")
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

