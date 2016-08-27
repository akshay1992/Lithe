Lithe
=====

Lithe is a modular synthesizer inspired patching workflow for spatial audio. 

Build instructions:
-------------------

Dependencies (Lithe Core):
* [GoogleTest](https://github.com/google/googletest/archive/master.zip) - For testing (downloaded & built by this project)

Dependencies (Lithe Modules):
* portaudio
* [Gamma](https://github.com/AlloSphere-Research-Group/Gamma) - For sound synthesis/processing
* [allocore-build](https://github.com/akshay1992/allocore-build) - For sound spatialization (downloaded & installed system-wide by this project)
	Ideally this project would depend on [AlloSystem](https://github.com/AlloSphere-Research-Group/AlloSystem), but due to it's install system I've found it easier to amputate just the allocore module binaries from it.
* Lithe Core (built by this project)


-------------------  
Author: Akshay Cadambi (akshay1992)
