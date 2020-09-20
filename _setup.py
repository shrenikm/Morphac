#!/usr/bin/env python3
"""Morphac is a planning and control library for mobile robots.

Key highlights:

* The library focuses exclusively on mobile robots.
* It provides implementations of standard planning and control algorithms.
* It provides a framework to facilitate the development of new algorithms easily.
* Its modular and intuitive design enables quick prototyping and testing of new ideas.
* The framework and algorithms are written in C++ with python bindings for each functionality.

Even though the library is written primarily using C++, its real-time performance cannot be guaranteed.
Morphac will primarily be a research focussed library.
"""

import setuptools
import yaml

# Read the config file.
def parse_morphac_config_file():
    with open("morphac_config.yaml", "r") as f:
        try:
            morphac_config = yaml.safe_load(f)
        except yaml.YAMLError as ex:
            print(ex)

    return morphac_config


NAME = parse_morphac_config_file()["name"]

VERSION = ".".join(
    list(
        map(
            str,
            [
                parse_morphac_config_file()["major_version"],
                parse_morphac_config_file()["minor_version"],
                parse_morphac_config_file()["patch_version"],
                parse_morphac_config_file()["version_suffix"],
            ],
        )
    )
)

CLASSIFIERS = [
    "Development Status :: 3 - Alpha",
    "Intended Audience :: Science/Research",
    "License :: OSI Approved :: MIT License",
    "Natural Language :: English",
    "Operating System :: POSIX :: Linux",
    "Programming Language :: C++",
    "Programming Language :: Python :: 3.6",
    "Programming Language :: Python :: 3.7",
    "Programming Language :: Python :: 3.8",
    "Topic :: Scientific/Engineering",
    "Topic :: Scientific/Engineering :: Artificial Intelligence",
]

DOC = __doc__.split("\n")
DESCRIPTION = DOC[0]
LONG_DESCRIPTION = "\n".join(DOC[2:])

INSTALL_REQUIRES = [
    "attrs==20.2.0",
    "msgpack==1.0.0",
    "numpy==1.19.2",
    "opencv-python==4.4.0.42",
    "pytest==6.0.2",
]

DESCRIPTION = "Morphac is a planning and control library for mobile robots."

setuptools.setup(
    name=NAME,
    version=VERSION,
    author="Shrenik",
    author_email="shrenik95@gmail.com",
    classifiers=CLASSIFIERS,
    description=DESCRIPTION,
    long_description=LONG_DESCRIPTION,
    install_requires=INSTALL_REQUIRES,
    keywords="robotics mobile_robots motion_planning planning control",
    license="MIT",
    url="https://github.com/shrenikm/Morphac",
    # TODO: project_urls
    packages=setuptools.find_packages(include=["morphac", "morphac.*"]),
    # Look at MANIFEST.in to see what gets included.
    include_package_data=True,
    python_requires=">=3.6",
)

