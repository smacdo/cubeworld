CubeWorld README
VERSION 0.1

Summary
=========================================================================
You have mysteriously awoken to find yourself in a strange and fantastic
world of cubes. You must explore the landscape to survive, discover
incredible interactions with the environment, explore dangerous above and
below ground lairs and create a stronghold that stands the test of time.

Can you learn and survive, perhaps even prosper, in Cube World?

Requirements
=========================================================================
CubeWorld has the following requirements prior to installation

1. CMake version 2.6+
2. Modern C++ compiler (GCC 4.2+, Visual C++ 2010)
3. Hardware OpenGL 2.0 support
    - NVidia 6xxx series or ATI 2xxx series or newer
    - Recommended that you have at least 256MB of video RAM
4. Profit!

Building / Running
=========================================================================
(Please make sure you are currently in the project's root directory)

Linux
--------------
1. mkdir build
2. cd build
3. cmake ../
4. make
5. make install

Windows
---------------
1. Download API.7z, extract to C:\APIs
2. Follow instructions in C:\APIs\readme.txt
3. Start CMake-GUI
	- Specify source code dir as this directory
	- Specify build dir as this directory\build
	- Click "configure"
	- Click "Generate"
4. Start Visual Studio, open build\cubeworld.sln
5. Right click "cubeworldclient", click "set as start up project"
6. Click run, you're good to go!

Running
=========================================================================
If you installed the application via make install, simply type in the
name of the executable. Otherwise, if you only ran 'make' then the binary
will be located in the build/src/ directory.

The format for running cubeworld is:
  ./forgeclient option ...

Cubeworld supports the following options:
  --help
  -h               Print an informative help message on stanrd output

  --version
  -v               Print the program's name, version and build info.

Feedback
=========================================================================
Submit bug reports, feedback, comments, criticisms, love notes or whatnot
to Scott MacDonald <scott@whitespaceconsideredharmful.com>

Don't be shy - devs love feedback! Even if its "hey, I just tried out your
application!" or "it sucks!". :)

Reporting Bugs
=========================================================================
To report bugs or suggest enhancements, please send e-mail to
forgebugs@whitespaceconsideredharmful.com

When reporting bugs, please try to include enough information for the
maintainers to reproduce your problem. This should include:
    1. The application's version number
    2. Hardware and operating system names and versions
    3. Contents of any input files needed to reproduce the bug
    4. The expected behavior and/or output
    5. A description of the problem and samples of erroneous output
    6. Options you gave to configure
    7. Anything else that you think would be helpful

When in doubt, include it. It's always better to include too much
information rather than too little and risk leaving something important
out.

Patches
=========================================================================
Patches are always welcome. Please send a diff (diff -c), and a detailed
changelog listing your changes. Additionally, please follow the project's
coding style or we may have to (sadly) reject your patch.
