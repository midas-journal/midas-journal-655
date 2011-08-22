PROJECT(ROBARTSVIDEO)

SET(KIT RobartsVideo)
SET(UKIT RobartsVideo)
SET(KIT_LIBS vtkHybrid)
SET(KIT_EXTRA_LIBS)

SET (Kit_SRCS ${Kit_SRCS}
  vtkVideoBuffer2.cxx
  vtkVideoFrame2.cxx
  vtkVideoSource2.cxx
)

## Needs to be added back in when refactored

#OPTION(USE_SONIX_VIDEO "Use Sonix ultrasound device." OFF)
#IF(USE_SONIX_VIDEO)
#  SET (Kit_SRCS ${Kit_SRCS}
#    vtkSonixVideoSource2.cxx
#  )
#ENDIF(USE_SONIX_VIDEO)

IF (WIN32)

  SET (KIT_EXTRA_LIBS ${KIT_EXTRA_LIBS} ws2_32.lib)

  IF (VTK_VFW_SUPPORTS_CAPTURE)
    SET (Kit_SRCS ${Kit_SRCS} vtkWin32VideoSource2.cxx)
  ENDIF (VTK_VFW_SUPPORTS_CAPTURE)

  IF (VTK_USE_MATROX_IMAGING)
    SET(KIT_LIBS ${KIT_LIBS} ${MIL_LIBRARY})
    IF (MIL_INCLUDE_PATH)
    ELSE (MIL_INCLUDE_PATH)
    FIND_PATH(MIL_INCLUDE_PATH mil.h "C:/Program Files/Matrox Imaging/mil/include" )
    ENDIF (MIL_INCLUDE_PATH)
    INCLUDE_DIRECTORIES( ${MIL_INCLUDE_PATH})
    SET (Kit_SRCS ${Kit_SRCS} vtkMILVideoSource2.cxx)
    # Include directory needed for vtkMILVideoSource.cxx.
  ENDIF (VTK_USE_MATROX_IMAGING)

#ELSE (WIN32)

## needs to be added back in when refactored

#  OPTION(USE_LINUX_VIDEO "Use Linux video source" ON)
#  IF(USE_LINUX_VIDEO)
#  SET (Kit_SRCS ${KIT_SRCS}
#    vtkV4L2VideoSource2.cxx
#  )
#  ENDIF(USE_LINUX_VIDEO)

ENDIF (WIN32)

SET(Kit_EXTRA_SRCS)
SET(Kit_EXTRA_CMDS)
SET(Kit_TCL_EXTRA_SRCS)
SET(Kit_PYTHON_EXTRA_SRCS)
SET(Kit_JAVA_EXTRA_SRCS)

# -----------------------------------------------------------------

# Include the common setting file
INCLUDE(${SYNCHROGRAB4D_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
