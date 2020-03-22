# Bindings
# -------------------------------------------------

set(CONSTRUCTS_BINDING_SRC

  pose_binding.cc
)

foreach(file ${CONSTRUCTS_BINDING_SRC})
  get_filename_component(binding_name ${file} NAME_WE)
  pybind11_add_module(${binding_name} SHARED ${CONSTRUCTS_BINDING_DIR}/${file})
  target_include_directories(${binding_name} PRIVATE ${PYBIND11_INCLUDE_DIR})
endforeach()

# Adding library dependencies.
target_link_libraries(pose_binding PUBLIC pose)

