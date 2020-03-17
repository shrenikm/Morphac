# Third party dependencies
# -------------------------------------------------

# Third party include directories
set(EIGEN_REPO_DIR ${PROJECT_SOURCE_DIR}/third_party/eigen)
set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/eigen)

set(PYBIND11_REPO_DIR ${PROJECT_SOURCE_DIR}/third_party/pybind11)
set(PYBIND11_INCLUDE_DIR ${PYBIND11_REPO_DIR}/include)

# Eigen
# As eigen is used in almost every target, include_directories is used instead
# of having to target_include_directories eigen for each target.
include_directories(${EIGEN_INCLUDE_DIR})

add_subdirectory(${PYBIND11_REPO_DIR} third_party/pybind11)
#include_directories(${PYBIND11_INCLUDE_DIR})


# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports
set(MORPHAC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_INCLUDE_DIR})

# Adding the individual core subdirectories
add_subdirectory(constructs)
add_subdirectory(environments)
add_subdirectory(mechanics)
add_subdirectory(robot)

