# Morphac

Morphac (Mobile Robot Playground for Planning and Control) is an open source motion planning and control library for mobile robots.

The library is written in C++ and will have python bindings for all functionality.

## Build status
OS | Python | Status
---------|--------|-------
Ubuntu (18.04) | 3.6, 3.7, 3.8 | [![Build Status](https://travis-ci.com/shrenikm/Morphac.svg?branch=master)](https://travis-ci.com/shrenikm/Morphac)


## Installation

### Requirements
* Ubuntu 16.04/18.04 (It has only been tested on these platforms)
* CMake version >= 3.5
* GCC version >= 5
* Python version >= 3.6

### Building from source
Clone the repository:<br/>
`git clone https://github.com/shrenikm/Morphac.git`<br/><br/>
Initialize and update submodules:<br/>
`git submodule update --init --recursive`<br/><br/>
Build using CMake:<br/>
`mkdir build && cd build`<br/>
`cmake .. && make`<br/><br/>
Install the library and python modules:<br/>
`make install`<br/><br/>
C++ tests may be run using:<br/>
`make test`<br/><br/>
Python tests using:<br/>
`pytest morphac`<br/><br/>

Available CMake configuration options:
Option | Description | Default
-------|-------------|--------
BUILD_TESTS | Build C++ tests or not | ON
BUILD_WITH_WARNINGS | Build source code with `-Wall` and `-Wextra` | ON
BUILD_WITH_WARNINGS_AS_ERRORS | Build source code with `-Werror` | ON
INSTALL_PYTHON_PACKAGE | Install the python package into site-packages or not | ON

<br/><br/>

Note that the build creates a `packages/` directory under the project source path, irrespective of the status of the `INSTALL_PYTHON_PACKAGE` option.
The directory contains all of the necessary bindings and files required to create a package file (Including the setup file).


## Post installation

After the library is installed, verify the install by running:
```python
import morphac
print(morphac.__version__)
morphac.run_all_tests()
```

Examples can also be run using:
```python
import morphac
morphac.run_constant_controller_example()
```

## Known issues

* `opencv-python` is installed as a dependency, but there might some issues with the GUI if installed through a conda environment. In this case, it is advisable to build opencv from source.


-------

## License

[MIT License](LICENSE)


