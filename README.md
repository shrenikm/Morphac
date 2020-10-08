# Morphac

Morphac (Mobile Robot Playground for Planning and Control) is an open source motion planning and control library for mobile robots.

The library is written in C++ and will have python bindings for all functionality.

## Build status
| Type         | OS             | Python        | Status                                                                                                                                |
| ------------ | -------------- | ------------- | ------------------------------------------------------------------------------------------------------------------------------------- |
| Source build | Ubuntu (18.04) | 3.6, 3.7, 3.8 | [![Build Status](https://travis-ci.com/shrenikm/Morphac.svg?branch=master)](https://travis-ci.com/shrenikm/Morphac)                   |
| PyPI package | Ubuntu (16.04) | 3.6, 3.7, 3.8 | [![shrenikm](https://circleci.com/gh/shrenikm/Morphac.svg?style=shield)](https://app.circleci.com/pipelines/github/shrenikm/Morphac) |



## Installation

### Requirements
* Ubuntu 16.04/18.04 (It has only been tested on these platforms)
* CMake version >= 3.5
* GCC version >= 5
* Python version >= 3.6

### Building from source
Clone the repository
```bash
git clone https://github.com/shrenikm/Morphac.git
```
Initialize and update submodules
```bash
git submodule update --init --recursive
```
Build using CMake
```bash
mkdir build && cd build
cmake .. && make
```
Install the library and python modules
```bash
make install
```
C++ tests may be run using
```bash
make test
```
Python tests using
```bash
pytest morphac
```

Available CMake configuration options:
| Option                        | Description                                          | Default |
| ----------------------------- | ---------------------------------------------------- | ------- |
| BUILD_TESTS                   | Build C++ tests or not                               | ON      |
| BUILD_WITH_WARNINGS           | Build source code with `-Wall` and `-Wextra`         | ON      |
| BUILD_WITH_WARNINGS_AS_ERRORS | Build source code with `-Werror`                     | ON      |
| INSTALL_PYTHON_PACKAGE        | Install the python package into site-packages or not | ON      |

<br/>

Note that the build creates a `packages/` directory under the project source path, irrespective of the status of the `INSTALL_PYTHON_PACKAGE` option.
The directory contains all of the necessary bindings and files required to create a package (Including the setup file).


### Installing through PyPI

If only the python package is required, it may be installed using
```bash
pip install morphac
```
For a specifc version, use
```bash
pip install morphac==<version>
```

Or grab and install a package from one of the [releases](https://github.com/shrenikm/Morphac/releases)

<br/>

## Post installation

After the library is installed, verify the install by running
```python
import morphac
print(morphac.__version__)
morphac.run_all_tests()
```

Examples can also be run using
```python
import morphac
morphac.run_constant_controller_example()
```

<br/>

## Known issues

* `opencv-python` is installed as a dependency, but there might some issues with the GUI if installed through a conda environment. In this case, it is advisable to build opencv from source.

<br/>

-------

## License

[MIT License](LICENSE)


