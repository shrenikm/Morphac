cmake_minimum_required(VERSION 3.5)

# Project details
# -------------------------------------------------

set(MORPHAC_NAME "morphac")
set(MORPHAC_MAJOR_VERSION 1)
set(MORPHAC_MINOR_VERSION 0)
set(MORPHAC_PATCH_VERSION 0)

project(
  ${MORPHAC_NAME}
  VERSION ${MORPHAC_MAJOR_VERSION}.${MORPHAC_MINOR_VERSION}.${MORPHAC_PATCH_VERSION}
  LANGUAGES CXX
)


# Options
# -------------------------------------------------

# Flag to enable/disable testing
option(BUILD_TESTS "Build all of the project's test executables" ON)
option(BUILD_WITH_WARNINGS "Builds the project with -Wall and -Wextra" ON)
option(BUILD_WITH_WARNINGS_AS_ERRORS "Builds the project with -Werror" ON)

# Displaying the list of options that have been set.
message("Morphac Options")
message("---------------")
message("[ BUILD_TESTS has been set to ${BUILD_TESTS} ]")
message("[ BUILD_WITH_WARNINGS has been set to ${BUILD_WITH_WARNINGS} ]")
message("[ BUILD_WITH_WARNINGS_AS_ERRORS has been set to ${BUILD_WITH_WARNINGS_AS_ERRORS} ]")
message("---------------")


# Configuring
# -------------------------------------------------

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (${BUILD_WITH_WARNINGS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(${BUILD_WITH_WARNINGS})

if (${BUILD_WITH_WARNINGS_AS_ERRORS})
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif(${BUILD_WITH_WARNINGS_AS_ERRORS})

if (${BUILD_TESTS})
  enable_testing()
endif(${BUILD_TESTS})


# Third party
# -------------------------------------------------

# Download and unpack googletest at configure time.
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
)

# Add googletest directly to the build.
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(morphac)

