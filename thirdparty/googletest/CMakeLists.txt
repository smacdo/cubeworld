find_package(Threads REQUIRED)


include_directories(include)
add_library(googletest STATIC googletest-all.cpp)
set_target_properties(googletest
    PROPERTIES
    LINK_FLAGS ${CMAKE_THREAD_LIBS_INIT})
