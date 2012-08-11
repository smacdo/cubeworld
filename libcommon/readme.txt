LIBCOMMON README
VERSION 0.1

Summary
=========================================================================
LIBCOMMON is Scott's collection of re-usable C++ programming libraries.
The supplied libraries are built to encapsulate common application,
graphics and game play functionality that is not supported by STL or
boost. These libraries have minimal external dependencies, are built with
modern STL in mind and haveing continually increasing unit test coverage.

All of the libraries are licensed under the Apache 2.0, which is an open
source license that allows for modification and redistribution. Please see
the license text for additional details.

Breakdown
=========================================================================
    libcommon/common:

    libcommon/app:

    libcommon/entity:

    libcommon/game3d:

    libcommon/game2d:

    libcommon/platform:

    libcommon/string:

Requirements
=========================================================================
$APPLICATION$ has the following requirements prior to installation

1. CMake version 2.6+
2. Modern C++ compiler (GCC 4.2+, Visual C++ 2010)
3. ???
4. Profit!

Installation
=========================================================================
(Please make sure you are currently in the project's root directory)

1. mkdir build
2. cd build
3. cmake ../
4. make
5. make install

Running
=========================================================================
If you installed the application via make install, simply type in the
name of the executable. Otherwise, if you only ran 'make' then the binary
will be located in the build/src/ directory.

The format for running $APPLICATION$ is:
  $APPBIN$ option ...

$APPLICATION$ supports the following options:
  --help
  -h               Print an informative help message on stanrd output

  --version
  -v               Print the program's name, version and build info.

Feedback
=========================================================================
Submit bug reports, feedback, comments, criticisms, love notes or whatnot
to $AUTHOR$ $EMAIL$.

Don't be shy - devs love feedback! Even if its "hey, I just tried out your
application!" or "it sucks!". :)

Reporting Bugs
=========================================================================
To report bugs or suggest enhancements, please send e-mail to
$BUGEMAIL$

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
