# Directories
# -------------------------------------------------

set(NUMERIC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NUMERIC_SRC_DIR ${NUMERIC_DIR}/src)
set(NUMERIC_INCLUDE_DIR ${NUMERIC_DIR}/include)
set(NUMERIC_TEST_DIR ${NUMERIC_DIR}/test)
set(NUMERIC_BINDING_DIR ${NUMERIC_DIR}/binding)
set(NUMERIC_BINDING_INCLUDE_DIR ${NUMERIC_BINDING_DIR}/include)
set(NUMERIC_BINDING_SRC_DIR ${NUMERIC_BINDING_DIR}/src)
set(NUMERIC_BINARY_DIR ${NUMERIC_BINARY_DIR}/models)
set(NUMERIC_BINDING_BINARY_DIR ${NUMERIC_BINARY_DIR}/binding)
set(NUMERIC_BINDING_INSTALL_DIR
  ${MATH_BINDING_INSTALL_DIR}/integration
)


# Adding subdirectories
# -------------------------------------------------

add_subdirectory(binding)

# Libraries
# -------------------------------------------------

# Models source files.
set(NUMERIC_SRC

  integrator.cc
  euler_integrator.cc
)

foreach(file ${NUMERIC_SRC})
  get_filename_component(lib_name
    ${file} NAME_WE
  )

  get_header_name(header_name ${file})

  add_library(${lib_name}
    SHARED
    ${NUMERIC_SRC_DIR}/${file}
    ${NUMERIC_INCLUDE_DIR}/${header_name}
  )

  target_include_directories(${lib_name}
    PUBLIC
    ${NUMERIC_INCLUDE_DIR}
  )
endforeach()

# Adding library dependencies.
target_link_libraries(integrator
  PUBLIC
  kinematic_model
)

target_link_libraries(euler_integrator
  PUBLIC
  integrator kinematic_model
)



