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

