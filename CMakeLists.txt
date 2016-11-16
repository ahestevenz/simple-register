cmake_minimum_required(VERSION 2.8)
project(simpleregister)

set(SimpleITK_DIR /opt/SimpleElastix/build/SimpleITK-build)
set(ITK_DIR /opt/SimpleElastix/build/ITK-build)
set(CMAKE_CXX_FLAGS "-fPIC")

set(simpleregister_SRCS apSimpleRegister.cpp main.cpp utils/apExceptions.cpp)

if( NOT SimpleITK_SOURCE_DIR )
  find_package( SimpleITK REQUIRED )
  include( ${SimpleITK_USE_FILE} )

  # TODO: CMake refuses to properly configure the ITK_USE_FILE when
  # called in the SimpleITK_USE_FILE. Here we import ITK manually, but
  # really all dependencies should be resolved by the SimpleITK_USE_FILE.
  find_package( ITK REQUIRED )
  include( ${ITK_USE_FILE} )

  # Add compiler flags needed to use SimpleITK.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SimpleITK_REQUIRED_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SimpleITK_REQUIRED_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${SimpleITK_REQUIRED_LINK_FLAGS}")
else()
  set( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
  include( ${ITK_USE_FILE} )
endif()

find_package(OpenCV)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(utils/)
add_executable(simpleregister ${simpleregister_SRCS})
target_link_libraries( simpleregister ${SimpleITK_LIBRARIES} ${Qt5Core_LIBRARIES} ${OpenCV_LIBS})
install(TARGETS simpleregister RUNTIME DESTINATION bin)

