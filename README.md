Lithe
=====

Lithe is a modular synthesizer-inspired patching workflow for spatial audio. 

This repository builds a static library `lithe_core` and contains a framework for patching and processing a spatial audio graph. It also has utilities for processing spatial 'signals'. It's intended use is for creating effects for object-based spatial audio.

Lithe can be installed as a static library from this repo. It doesn't have any dependencies. 

Build instructions:
-------------------
Note: All builds require CMake

### Building and installing Lithe

Clone Lithe from the git repo  

        git clone git@github.com:akshay1992/Lithe

To build Lithe  

        cd Lithe
        mkdir build
        cd build
        cmake ..
        make

To install  

        make install

Note that the above command will will install in the default location (usually `/usr/local/`). To specify a different install location, you can manually specify install directory in the last command:
    
        make install <path_to_install_directory>

Note: The install and uninstall scripts are provided as a shorthand. `install.sh` installs in the default directory `/usr/local/` and `uninstall.sh` removes Lithe from those locations (if found).

### Building and running tests
To build and run the tests run this command from within the `Lithe/build/` directory created in the above build step:

    make check
    
Note: Lithe uses [GoogleTest](https://github.com/google/googletest/archive/master.zip) for testing. It automatically downloads and builds it when testing. Therefore, be sure to be connected to the internet while building the test cases (at least the first time).

### Documentation
To generate the documentation, from within the `Lithe/build/` directory created in the above build step, run the following command:

    make docs

The documentation can be found within `Lithe/docs` in html and latex forms. 
    
Note: Lithe uses [Doxygen](http://www.stack.nl/~dimitri/doxygen/index.html) for generating documentation. First make sure Doxygen is installed before running the above command.

-------------------  
Author: Akshay Cadambi  
Email: akshay19.92@gmail.com
