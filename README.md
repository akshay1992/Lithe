Lithe
=====

Lithe is a modular synthesizer-inspired patching workflow for spatial audio. 

Lithe is split into two libraries: 
* lithe_core
* lithe_modules

_Core_ provides all the basic frameworks for patching and processing an audio graph. _Modules_ contains modules built using the _Core_ framework that can be used to directly produce sound.

Lithe intentionally does not include a built in GUI, which allows it to be used with any GUI framework or application. 

Build instructions:
-------------------
Note: All builds require CMake

Lithe dependencies:
* [AlloSystem](https://github.com/akshay1992/AlloSystem) - For sound spatialization,
* [Gamma](https://github.com/AlloSphere-Research-Group/Gamma) - For sound synthesis/DSP
* [cuttlebone](https://github.com/rbtsx/cuttlebone) - a required dependency of AlloSystem 

The following steps describe how to build Lithe along with its dependencies.

##### Building and installing AlloSystem 
Note: Gamma and cuttlebone are automatically built by AlloSystem if found alongside it. Therefore, building AlloSystem with in this way will also cover Lithe's dependencies.

Clone AlloSystem, Gamma, and cuttlebone into the same directory using the following commands:

        git clone git@github.com:akshay1992/AlloSystem 
        git clone git@github.com:AlloSphere-Research-Group/Gamma.git 
        git clone git@github.com:rbtsx/cuttlebone.git

Build and install AlloSystem using the following commands (it automatically finds Gamma and cuttlebone). 

        cd AlloSystem
        mkdir build
        cd build
        cmake ..
        make
        make install

##### Building and installing Lithe

Clone Lithe from the git repo  

    git clone git@github.com:akshay1992/Lithe

Build and install Lithe

    cd Lithe
    mkdir build
    cd build
    cmake ..
    make
    make install
    
Lithe will be installed by default in `/usr/local/`. To specify a different install location, specify it during the install step as follows: 

        make install <path_to_install_directory>

##### Building and running tests
To build and run the tests run this command from within the `Lithe/build/` directory created in the above build step:
    make check
    
Note: Lithe uses [GoogleTest](https://github.com/google/googletest/archive/master.zip) for testing. It automatically downloads and builds it when testing. Therefore, be sure to be connected to the internet while building the test cases (at least the first time).

-------------------  
Author: Akshay Cadambi  
Graduate student in the _Media, Arts, and Technology_ program  
at the _University of California, Santa Barbara_

