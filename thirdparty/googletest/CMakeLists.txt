#find_package(Threads REQUIRED)

#if(NOT THREADS_FOUND)
#	message(FATAL_ERROR "Failed to find a threads package")
#endif()

include_directories(include)
add_library(gtest STATIC googletest-all.cpp)
add_definitions(gtest -DGTEST_HAS_PTHREAD=0)
#set_target_properties(gtest PROPERTIES
#    LINK_FLAGS ${CMAKE_THREAD_LIBS_INIT})
