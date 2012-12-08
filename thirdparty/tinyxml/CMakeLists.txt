###########################################################################
# Custom TinyXML CMake script
# Author: Scott MacDonald
###########################################################################
project(tinyxml)

# TinyXML expects its header files to be in the same directory as the source
# files, even though I've separated them out
include_directories( include/tinyxml )

# TinyXML has some special definitions that we need to add in order to build
# it with proper STL support
add_definitions( -DTIXML_USE_STL )

# This is prety straight forward, just create a small static lib that we 
# can import elsewhere
add_library( tinyxml STATIC src/tinyxml.cpp
                            src/tinyxmlerror.cpp
                            src/tinyxmlparser.cpp )
