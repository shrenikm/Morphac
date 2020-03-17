message(${PYBIND11_INCLUDE_DIR})
pybind11_add_module(binding_pose binding_pose.cc)
target_include_directories(binding_pose PRIVATE ${PYBIND11_INCLUDE_DIR})
