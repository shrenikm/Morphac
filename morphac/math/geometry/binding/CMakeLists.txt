# Bindings
# -------------------------------------------------

# Src file that creates the python module.
set(GEOMETRY_MODULE_FILE

  geometry.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(GEOMETRY_BINDING_FILES

  lines_binding.cc
  polygons_binding.cc
  shapes_binding.cc
)

# Prepending the directory to the files.
prepend_list(GEOMETRY_BINDING_FILES
  ${GEOMETRY_BINDING_SRC_DIR}/
  ${GEOMETRY_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${GEOMETRY_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${GEOMETRY_BINDING_DIR}/${GEOMETRY_MODULE_FILE}
  ${GEOMETRY_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${GEOMETRY_BINDING_DIR}/include
)

# Adding library dependencies.
morphac_link_static_libraries(${python_target}
  lines
  polygons
  shapes
)

# Setting binding target properties.
# Target prefix.
set_target_properties(${python_target}
  PROPERTIES
  PREFIX ${PYTHON_BINDING_PREFIX}
)


# Installing
# -------------------------------------------------

# Get target suffix
get_target_property(binding_suffix
  ${python_target} SUFFIX
)

# Full name of the built target (.so file that needs to be installed).
set(binding_install_file_name
  ${PYTHON_BINDING_PREFIX}${python_target}${binding_suffix}
)

morphac_package_files(
  ${GEOMETRY_PACKAGE_DIR}
  ${GEOMETRY_SITE_PACKAGES_DIR}
  # Files
  ${GEOMETRY_BINDING_DIR}/__init__.py
  ${GEOMETRY_BINDING_BINARY_DIR}/${binding_install_file_name}
)

