# Include dependencies
include_directories(${PROJECT_SOURCE_DIR}/third_party)

# Including the base morphac directory for relative cpp imports
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Adding the individual core subdirectories
add_subdirectory(constructs)
add_subdirectory(environments)
add_subdirectory(mechanics)
add_subdirectory(robot)
