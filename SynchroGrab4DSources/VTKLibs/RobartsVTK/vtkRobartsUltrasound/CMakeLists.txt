PROJECT(ROBARTSULTRASOUND)

SET(KIT RobartsUltrasound)
SET(UKIT ROBARTSULTRASOUND)
SET(KIT_LIBS vtkFiltering vtkHybrid vtkAtamaiTracking vtkRobartsECG vtkRobartsVideo)
SET(KIT_EXTRA_LIBS)

SET (Kit_SRCS ${Kit_SRCS} )

SET ( Kit_SRCS ${Kit_SRCS}
  vtkFreehandUltrasound2.cxx
  vtkFreehandUltrasound2Dynamic.cxx
#  vtkTaggedImageFilter.cxx
#  vtkUltrasoundCalibFileReader.cxx
)

INCLUDE_DIRECTORIES(${ATAMAITRACKING_SOURCE_DIR}
                    ${ATAMAITRACKING_BINARY_DIR}
                    ${ROBARTSECG_SOURCE_DIR}
                    ${ROBARTSECG_BINARY_DIR}
                    ${ROBARTSVIDEO_BINARY_DIR}
                    ${ROBARTSVIDEO_SOURCE_DIR} )

SET(Kit_EXTRA_SRCS)
SET(Kit_EXTRA_CMDS)
SET(Kit_TCL_EXTRA_SRCS)
SET(Kit_PYTHON_EXTRA_SRCS)
SET(Kit_JAVA_EXTRA_SRCS)

# -----------------------------------------------------------------

# Include the common setting file
INCLUDE(${SYNCHROGRAB4D_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
