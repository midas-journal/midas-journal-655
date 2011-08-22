CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

#
# Set the project name.
#

PROJECT (SYNCHROGRAB4D)

#
# Load CMake commands to e.g. bring VTK and ITK into the project
#

INCLUDE (${SYNCHROGRAB4D_SOURCE_DIR}/CMakeOptions.cmake)

#
# Avoid dev warnings in CMake 2.6
#

IF(COMMAND CMAKE_POLICY)
  CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

#
# Little configuration to force OpenIGTLink to compile statically
#
ADD_DEFINITIONS(-DIGTLSTATIC=1)

#
# Enable / Disable Hardware Simulators
#
#OPTION(USE_ULTRASOUND_DEVICE "Use Ultrasound Device." OFF)

# 
# Whether to build with shared libs: define our own symbol
#

OPTION(BUILD_SHARED_LIBS "Build shared libraries." OFF)
SET(SYNCHROGRAB4D_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

#
# Initialize configuration
#

# Kits
SET(SynchroGrab4D_KITS)

# Libraries
SET(SynchroGrab4D_LIBRARIES)

# Include directories
SET(SynchroGrab4D_INCLUDE_DIRS)

#
# Here is where the sub-directories for the SynchroGrab4D classes are.
#

SUBDIRS (
#  Utilities
  VTKLibs
  Applications
#  ITKLibs
)

#
# Include paths go here
#
INCLUDE_DIRECTORIES(
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/RobartsVTK
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/RobartsVTK/vtkRobartsUltrasound
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/RobartsVTK/vtkRobartsECG
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/RobartsVTK/vtkRobartsVideo
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/AtamaiVTK/vtkAtamaiTracking
  ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/AtamaiVTK/vtkAtamaiTrackingUtils/ndicapi
##  ${SYNCHROGRAB4D_SOURCE_DIR}/Utilities/ndicapi
##  ${SYNCHROGRAB4D_SOURCE_DIR}/Utilities/igtl
##  ${SYNCHROGRAB4D_SOURCE_DIR}/Utilities/igtl/igtlutils
  ${OpenIGTLink_SOURCE_DIR}
  ${OpenIGTLink_SOURCE_DIR}/Source
  ${OpenIGTLink_SOURCE_DIR}/Source/igtlutil
)

#
# Common configuration settings
#

CONFIGURE_FILE(
  ${SYNCHROGRAB4D_SOURCE_DIR}/QueensOpenIGTLibsConfigure.h.in
  ${SYNCHROGRAB4D_BINARY_DIR}/QueensOpenIGTLibsConfigure.h
)

CONFIGURE_FILE(
  ${SYNCHROGRAB4D_SOURCE_DIR}/SynchroGrabConfigure.h.in
  ${SYNCHROGRAB4D_BINARY_DIR}/SynchroGrabConfigure.h
)


##################

#CONFIGURE_FILE(${SYNCHROGRAB4D_SOURCE_DIR}/igtlConfigure.h.in 
#  ${SYNCHROGRAB4D_BINARY_DIR}/igtlConfigure.h)

#CONFIGURE_FILE(${SYNCHROGRAB4D_SOURCE_DIR}/igtl_typeconfig.h.in 
#  ${SYNCHROGRAB4D_BINARY_DIR}/igtl_typeconfig.h)
  
#CONFIGURE_FILE(${SYNCHROGRAB4D_SOURCE_DIR}/igtlTypeConfig.h.in 
#  ${SYNCHROGRAB4D_BINARY_DIR}/igtlTypeConfig.h)
  
###########

INCLUDE_DIRECTORIES(${SYNCHROGRAB4D_BINARY_DIR})
