PROJECT(ROBARTSECG)

SET(KIT RobartsECG)
SET(UKIT ROBARTSECG)
SET(KIT_LIBS vtkHybrid)
SET(KIT_EXTRA_LIBS)

SET ( Kit_SRCS ${Kit_SRCS}
    vtkSignalBox.cxx)

OPTION (VTK_USE_HEARTSIGNALBOX "Enable Heart Signal Box" OFF)
  IF (VTK_USE_HEARTSIGNALBOX)
    SET (Kit_SRCS ${Kit_SRCS}
         vtkHeartSignalBox.cxx
        )
  SET (KIT_EXTRA_LIBS ${KIT_EXTRA_LIBS} ${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/RobartsVTK/vtkRobartsECG/inpout32.lib)
  #LINK_DIRECTORIES(${SYNCHROGRAB4D_SOURCE_DIR}/vtkRobartsECG/Inpout)
ENDIF (VTK_USE_HEARTSIGNALBOX)

OPTION (VTK_USE_USBECGBOX "Enable USB ECG Signal Box" OFF)
IF (VTK_USE_USBECGBOX)
  SET ( Kit_SRCS ${Kit_SRCS}
        vtkUSBECGBox.cxx
      )
  SET (KIT_EXTRA_LIBS ${KIT_EXTRA_LIBS}	${SYNCHROGRAB4D_SOURCE_DIR}/VTKLibs/RobartsVTK/vtkRobartsECG/cbw32.lib )
  #LINK_DIRECTORIES(${SYNCHROGRAB4D_SOURCE_DIR}/vtkRobartsECG/cbw)
ENDIF (VTK_USE_USBECGBOX)

SET(Kit_EXTRA_SRCS)
SET(Kit_EXTRA_CMDS)
SET(Kit_TCL_EXTRA_SRCS)
SET(Kit_PYTHON_EXTRA_SRCS)
SET(Kit_JAVA_EXTRA_SRCS)

# -----------------------------------------------------------------

# Include the common setting file
INCLUDE(${SYNCHROGRAB4D_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
