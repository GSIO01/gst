cmake_minimum_required(VERSION 3.11)
project(gst)

# c++17 is required
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# public header files
set(SRC_PUBLIC_HEADERS
				src/event/events.h
				src/event/listener.h
				src/event/manager.h
				src/event/parameter.h
				src/event/qevent.h
				src/fsm/fevent.h
				src/fsm/fsm.h
				src/fsm/machine.h
				src/fsm/parameter.h
				src/fsm/transition.h
				src/types/property.hpp)

# source files and private header files
set(SRC_FILES
				${SRC_PUBLIC_HEADERS}
				src/fsm/fevent.cpp
				src/fsm/mashine.cpp
				src/fsm/parameter.cpp)

# the library
add_library(gst SHARED ${SRC_FILES})
add_library(gstStatic STATIC ${SRC_FILES})

target_include_directories(gst PUBLIC src)
target_include_directories(gstStatic PUBLIC src)

# examples
add_executable(event_example examples/event/main.cpp examples/event/TestClass.h examples/event/TestClass.cpp)
target_link_libraries(event_example gstStatic)
target_include_directories(event_example PUBLIC src)

add_executable(fsm_example examples/fsm/main.cpp examples/fsm/test_fsm.h examples/fsm/test_fsm.cpp)
target_link_libraries(fsm_example gstStatic)
target_include_directories(fsm_example PUBLIC src)
