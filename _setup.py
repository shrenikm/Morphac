import setuptools
import yaml

# Read the config file.
with open("morphac_config.yaml", "r") as f:
    try:
        morphac_config = yaml.safe_load(f)
    except yaml.YAMLError as ex:
        print(ex)

setuptools.setup(
    name=morphac_config["name"],
    version=".".join(
        list(
            map(
                str,
                [
                    morphac_config["major_version"],
                    morphac_config["minor_version"],
                    morphac_config["patch_version"],
                    morphac_config["version_suffix"],
                ],
            )
        )
    ),
    author="Shrenik",
    author_email="shrenik95@gmail.com",
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: MIT License",
        "Natural Language :: English",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: C++",
        "Programming Language :: Python :: 3.5",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Artificial Intelligence",
    ],
    description="A planning and control library for mobile robots.",
    install_requires=[
        "attrs==19.3.0",
        "msgpack==1.0.0",
        "numpy==1.18.1",
        "pytest==5.4.1",
    ],
    keywords="robotics mobile_robots motion_planning planning control",
    # TODO: long_description.
    license="MIT",
    url="https://github.com/shrenikm/Morphac",
    # TODO: project_urls
    packages=setuptools.find_packages(include=["morphac", "morphac.*"]),
    include_package_data=True,
    # data_files=
    # packages=["morphac"],
    python_requires=">=3.5",
)

