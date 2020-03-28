# Utility functions
# -------------------------------------------------

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


# Morphac setup
# -------------------------------------------------

# Including the base morphac directory for relative cpp imports.
set(MORPHAC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${MORPHAC_INCLUDE_DIR})

# Base morphac binary directory.
set(MORPHAC_BASE_BINARY_DIR ${CMAKE_BINARY_DIR}/morphac)

# Adding subdirectories
# -------------------------------------------------

add_subdirectory(constructs)
add_subdirectory(environments)
add_subdirectory(mechanics)
add_subdirectory(robot)

