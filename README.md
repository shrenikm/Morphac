# Morphac

Morphac (Mobile Robot Playground for Planning and Control) is an open source motion planning and control library for mobile robots. **[Currently under development]**.

The library is written in C++ and will have python bindings for all functionality.

## Build status
OS | Python | Status
---------|--------|-------
Ubuntu (18.04) | 3.5, 3.6, 3.7, 3.8 | [![Build Status](https://travis-ci.com/shrenikm/Morphac.svg?branch=master)](https://travis-ci.com/shrenikm/Morphac)

## Installation

### Requirements
* Ubuntu 16.04/18.04 (It has only been tested on these platforms)
* CMake version >= 3.5
* GCC version >= 5
* Python version >= 3.5

### Building
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
BUILD_PYTHON_BINDINGS | Build python bindings or not | ON


-------

## License

[MIT License](LICENSE)


