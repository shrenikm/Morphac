# Bindings
# -------------------------------------------------

# If BUILD_PYTHON_BINDINGS is OFF, we don't need to proceed.
if(NOT BUILD_PYTHON_BINDINGS)
  return()
endif()

# Src file that creates the python module.
set(MODELS_MODULE_FILE

  models.cc
)

# Individual binding files called by the src module file.
# They are split up into different files so that compilation is more efficient.
set(MODELS_BINDING_FILES

  kinematic_model_binding.cc
  diffdrive_model_binding.cc
  dubin_model_binding.cc
  tricycle_model_binding.cc
)

# Prepending the directory to the files.
prepend_list(MODELS_BINDING_FILES
  ${MODELS_BINDING_SRC_DIR}/
  ${MODELS_BINDING_FILES}
)

# Adding the module as a library.
get_filename_component(module_name
  ${MODELS_MODULE_FILE} NAME_WE
)

## Get python target name. This is to prevent clashes with similar named cpp
## non binding targets.
get_python_target_name(python_target ${module_name})

pybind11_add_module(${python_target}
  SHARED
  ${MODELS_BINDING_DIR}/${MODELS_MODULE_FILE}
  ${MODELS_BINDING_FILES}
)

target_include_directories(${python_target}
  PUBLIC
  ${PYBIND11_INCLUDE_DIR}
  ${MODELS_BINDING_DIR}/include
)

# Adding library dependencies.
target_link_libraries(${python_target}
  PUBLIC
  kinematic_model
  state
  input
  diffdrive_model
  dubin_model
  tricycle_model
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

# Installing compiled bindings.
install(FILES
  ${MODELS_BINDING_BINARY_DIR}/${binding_install_file_name}
  DESTINATION ${MODELS_BINDING_INSTALL_DIR}
)

# Installing __init__ files.
install(FILES
  ${MODELS_BINDING_DIR}/__init__.py
  DESTINATION ${MODELS_BINDING_INSTALL_DIR}
)
