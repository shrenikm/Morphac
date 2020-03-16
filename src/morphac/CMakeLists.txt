# Third party dependencies
# -------------------------------------------------

# Third party include directories
set(EIGEN_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/eigen)
set(PYBIND11_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/third_party/pybind11)

#include_directories(${PROJECT_SOURCE_DIR}/third_party/eigen)
add_subdirectory(${EIGEN_INCLUDE_DIR} third_party/eigen)
add_subdirectory(${PYBIND11_INCLUDE_DIR} third_party/pybind11)


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

