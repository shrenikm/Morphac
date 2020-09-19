cmake_minimum_required(VERSION 3.5)

# Pre build checks
# -------------------------------------------------

# Disable builds in the source directory.
if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "Please create a separate directory for the build.")
endif()


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
  set(${out} ${tmp_dir} PARENT_SCOPE)
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


# Function that takes a list and prepends some given string to each element.
# CMake 3.12 has LIST TRANSFORM that can do this but our minimum CMake version is 3.5
function(prepend_list out prefix)
  set(tmp_list "")
  foreach(element ${ARGN})
    list(APPEND tmp_list ${prefix}${element})
  endforeach()
  set(${out} ${tmp_list} PARENT_SCOPE)
endfunction()

# Function that takes a list and appends some given string to each element.
# CMake 3.12 has LIST TRANSFORM that can do this but our minimum CMake version is 3.5
function(append_list out suffix)
  set(tmp_list "")
  foreach(element ${ARGN})
    list(APPEND tmp_list ${element}${suffix})
  endforeach()
  set(${out} ${tmp_list} PARENT_SCOPE)
endfunction()



# Function that takes in a target name and converts it to a static target name.
# The string defined in STATIC_TARGET_SUFFIX is appended to the target name.
function(get_static_target_name out target_name)
  set(${out} ${target_name}${STATIC_TARGET_SUFFIX} PARENT_SCOPE)
endfunction()


# Function that takes in a target name and converts it to a python target
# name. The string defined in PYTHON_TARGET_SUFFIX is appended to the target name.
# These are used on the cpp src files that builds some python module.
function(get_python_target_name out target_name)
  set(${out} ${target_name}${PYTHON_TARGET_SUFFIX} PARENT_SCOPE)
endfunction()


# Function that calls add_library and creates shared (and optionally static) libraries.
function(morphac_add_libraries include_dir src_dir)
  foreach(file ${ARGN})
    get_filename_component(lib_name
      ${file} NAME_WE
    )

    get_header_name(header_name ${file})

    # Regular shared library.
    add_library(${lib_name}
      SHARED
      ${src_dir}/${file}
      ${include_dir}/${header_name}
    )

    target_include_directories(${lib_name}
      PUBLIC
      ${include_dir}
    )

    # Static library for the python bindings.
    get_static_target_name(static_lib_name ${lib_name})
    if(BUILD_PYTHON_BINDINGS)
      add_library(${static_lib_name}
        STATIC
        ${src_dir}/${file}
        ${include_dir}/${header_name}
      )

      target_include_directories(${static_lib_name}
        PUBLIC
        ${include_dir}
      )
    endif()
  endforeach()
endfunction()


# Function that links static libraries to a static target.
# The library names are assumed to be non-static and will be suffixed
# with STATIC_TARGET_SUFFIX. Note that the target name will be used as is.
# This is because this function is used to link static libraries to 
# python bindings targets which won't have the static suffix.
function(morphac_link_static_libraries target)
  append_list(static_libraries ${STATIC_TARGET_SUFFIX} ${ARGN})
  target_link_libraries(${target}
    PUBLIC
    ${static_libraries}
  )
endfunction()


# Function that links libraries to the target.
# Also links the static libraries if required (for the bindings).
function(morphac_link_libraries target)
  set(libraries ${ARGN})
  target_link_libraries(${target}
    PUBLIC
    ${libraries}
  )

  # If we build python bindings, we link the static libraries as well.
  if(BUILD_PYTHON_BINDINGS)
    get_static_target_name(static_target ${target})
    morphac_link_static_libraries(${static_target} ${libraries})
  endif()
endfunction()


# Function that installs the python bindings into directories to create the package.
function(morphac_install_python_package packages_dir site_packages_dir)
  # First install in the packages directory that resides in the main cmake source directory.
  install(FILES
    ${ARGN}
    DESTINATION
    ${packages_dir}
  )

  # Now install into the site-packages directory depending on whether the INSTALL_PYTHON_PACKAGE
  # flag is set.
  if(INSTALL_PYTHON_PACKAGE)
    install(FILES
      ${ARGN}
      DESTINATION
      ${site_packages_dir}
    )
  endif()
endfunction()


# Function that installs a single file into the packages directories. Also has an option to rename the file.
# The third argument is the file and an optional fourth argument may be given if the file needs to be renamed.
function(morphac_install_python_file packages_dir site_packages_dir)
  if(${ARGC} EQUAL 4)
    # File needs to be renamed.
    set(filename ${ARGV3})
  else()
    # File doesn't need to be renamed.
    set(filename ${ARGV2})
  endif()
  install(FILES
    ${ARGV2}
    DESTINATION
    ${packages_dir}
    RENAME
    ${filename}
  )

  # Install into site-packages depending on whether the INSTALL_PYTHON_PACKAGE flag is set.
  if(INSTALL_PYTHON_PACKAGE)
    install(FILES
      ${ARGV2}
      DESTINATION
      ${site_packages_dir}
      RENAME
      ${filename}
    )
  endif()
endfunction()


# Project details
# -------------------------------------------------

print_section_header("Project Details")

# Read the project name and version details from the yaml configuration.
set(MORPHAC_CONFIG_FILE ${CMAKE_SOURCE_DIR}/morphac_config.yaml)
FILE(READ ${MORPHAC_CONFIG_FILE} morphac_config_file_contents)

# Extract config information.
string(REGEX MATCH "name: ([A-Za-z0-9]*)" _ ${morphac_config_file_contents})
set(MORPHAC_NAME ${CMAKE_MATCH_1})
string(REGEX MATCH "major_version: ([A-Za-z0-9]*)" _ ${morphac_config_file_contents})
set(MORPHAC_MAJOR_VERSION ${CMAKE_MATCH_1})
string(REGEX MATCH "minor_version: ([A-Za-z0-9]*)" _ ${morphac_config_file_contents})
set(MORPHAC_MINOR_VERSION ${CMAKE_MATCH_1})
string(REGEX MATCH "patch_version: ([A-Za-z0-9]*)" _ ${morphac_config_file_contents})
set(MORPHAC_PATCH_VERSION ${CMAKE_MATCH_1})

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
set(BUILD_PYTHON_BINDINGS ON CACHE BOOL "Build and creates a package directory with all of the python binding modules")
set(INSTALL_PYTHON_PACKAGE ON CACHE BOOL "Installs the package created by the bindings into site packages.")

# Displaying the list of options that have been set.
message(STATUS "[ BUILD_TESTS has been set to ${BUILD_TESTS} ]")
message(STATUS "[ BUILD_WITH_WARNINGS has been set to ${BUILD_WITH_WARNINGS} ]")
message(STATUS "[ BUILD_WITH_WARNINGS_AS_ERRORS has been set to ${BUILD_WITH_WARNINGS_AS_ERRORS} ]")
message(STATUS "[ BUILD_PYTHON_BINDINGS has been set to ${BUILD_PYTHON_BINDINGS} ]")
message(STATUS "[ INSTALL_PYTHON_PACKAGE has been set to ${INSTALL_PYTHON_PACKAGE} ]")


# Configuring
# -------------------------------------------------

print_section_header("Build Configuration")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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


# Target and library configuration
# -------------------------------------------------

# Postfix for building static library targets (To be linked to python bindings)
set(STATIC_TARGET_SUFFIX "_static")


# Python
# -------------------------------------------------

print_section_header("Python Configuration")

# Minimum python version required.
set(PYTHON_MINIMUM_VERSION 3.5)
# Prefix for compiled python bindings.
set(PYTHON_BINDING_PREFIX "_binding_")
# Suffix for python targets.
set(PYTHON_TARGET_SUFFIX "_python")

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
find_python_site_packages_dir(PYTHON_SITE_PACKAGES_DIR)
set(PYTHON_BINDING_INSTALL_DIR ${PYTHON_SITE_PACKAGES_DIR}/${MORPHAC_NAME})

# Python package directory. Note that this is different from the python bindings
# install directory. This directory includes all of the compiled objects that make
# up the pip installation package.
set(MORPHAC_PYTHON_PACKAGE_DIR ${CMAKE_SOURCE_DIR}/packages/${MORPHAC_NAME})

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

