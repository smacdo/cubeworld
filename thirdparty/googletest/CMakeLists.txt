find_package(Threads REQUIRED)


include_directories(include)
add_library(gtest STATIC googletest-all.cpp)
set_target_properties(gtest
    PROPERTIES
    LINK_FLAGS ${CMAKE_THREAD_LIBS_INIT})
