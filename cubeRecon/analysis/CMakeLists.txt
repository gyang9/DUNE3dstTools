cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)

# Set the project name and version
project(cube-analysis)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

message("Cube Reconstruction Display -- ${VERSION}")

# Set the default verbosity of the compilation...
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# Configure the dependencies
find_package(ROOT REQUIRED)
if(ROOT_FOUND)
  include(${ROOT_USE_FILE})
endif(ROOT_FOUND)

if(ROOT_Eve_LIBRARY)
  message("Building the cube-analysis event analysislay")
else(ROOT_Eve_LIBRARY)
  message("NOT BUILDING THE EVENT DISPLAY: eve not found")
  return()
endif(ROOT_Eve_LIBRARY)

if (EDEPSIM_LIBRARY)
	set(show_edepsim_source TG4HitChangeHandler.cxx TTrajectoryChangeHandler.cxx)
  set(show_edepsim_includesTTrajectoryChangeHandler.hxx)
endif (EDEPSIM_LIBRARY)

# Define the source and include files that should be used for the analysislay.
set(source
  TEventAnalysis.cxx 
  TReconTrackElement.cxx
  TReconShowerElement.cxx
  TReconClusterElement.cxx
  ${show_edepsim_source}
  )

set(includes
  TEventAnalysis.hxx
  TReconTrackElement.hxx 
  TReconShowerElement.hxx
  TReconClusterElement.hxx
  TTrajectoryHandler.hxx
  TG4HitHandler.hxx
  ${show_edepsim_includes}
  )

# Make sure the current directories are available for the root
# dictionary generation.
include_directories(${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/../io
  ${CMAKE_CURRENT_SOURCE_DIR}/../src
  ${CMAKE_CURRENT_SOURCE_DIR}/../tools)

# Build the dictionary for the i/o classes.
ROOT_GENERATE_DICTIONARY(G__cubeanalysis
  OPTIONS -inlineInputHeader
  LINKDEF cubeanalysis_LinkDef.h)

# Build the library.
add_library(cubeanalysis SHARED
  ${source}
  G__cubeanalysis.cxx)
target_include_directories(cubeanalysis PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cubeanalysis PUBLIC cuberecon_io cuberecon_tools ${ROOT_LIBRARIES})
install(TARGETS cubeanalysis LIBRARY DESTINATION lib)

# Build the analysislay
add_executable(cube-analysis analysis.cxx)
target_link_libraries(cube-analysis LINK_PUBLIC cubeanalysis)
install(TARGETS cube-analysis RUNTIME DESTINATION bin)

# If this is ROOT6 or later, then install the rootmap and pcm files.
if(${ROOT_VERSION} VERSION_GREATER 6)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libcubeanalysis.rootmap
    DESTINATION lib)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libcubeanalysis_rdict.pcm
    DESTINATION lib)
endif(${ROOT_VERSION} VERSION_GREATER 6)
