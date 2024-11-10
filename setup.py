# setup.py
from setuptools import setup, Extension
from pybind11.setup_helpers import Pybind11Extension, build_ext

ext_modules = [
    Pybind11Extension(
        "PChess",
        ["bindings.cpp", "piece.cpp"],  # Fichiers sources
    ),
]

setup(
    name="PChess",
    version="0.1",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
)

