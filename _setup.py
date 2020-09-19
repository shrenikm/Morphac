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
                ],
            )
        )
    ),
    author="Shrenik",
    author_email="shrenik95@gmail.com",
    description="A planning anc control library for mobile robots.",
    # TODO: Long description.
    long_description="",
    long_description_content_type="text/markdown",
    url="https://github.com/shrenikm/Morphac",
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Science/Research",
        "License :: OSI Approved :: MIT License",
        "Natural Language :: English",
        "Operating System :: POSIX :: Linux",
        "Programming Language :: C++",
        "Programming Language :: Python :: 3",
        "Topic :: Scientific/Engineering",
        "Topic :: Scientific/Engineering :: Artificial Intelligence",
    ],
    python_requires=">=3.5",
)

