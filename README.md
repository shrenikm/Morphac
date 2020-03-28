# Morphac

Morphac (Mobile Robot Playground for Planning and Control) is an open source motion planning and control library for mobile robots. [Currently under development].

The library is written in C++ and will have python bindings for all functionality.

## Build status
Platform | Status
---------|-------
Ubuntu (16.04) | [![Build Status](https://travis-ci.com/shrenikm/Morphac.svg?branch=master)](https://travis-ci.com/shrenikm/Morphac)

## Installation

### Requirements
* Ubuntu 16.04 (It has only been tested on Ubuntu 16.04 but it should build on any linux distro)
* CMake version >= 3.5
* GCC version >= 5
* Python version >= 3.7

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
Tests may be run using:<br/>
`make test`<br/><br/>
To disable building tests, the CMake `BUILD_TESTS` option can be set to `OFF`.

-------

## License

[MIT License](LICENSE)


