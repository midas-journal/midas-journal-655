MESSAGE(STATUS "Loading ${VTK_DIR}/CMakeCache.txt")

LOAD_CACHE(${VTK_DIR} READ_WITH_PREFIX TEMP_
  VTK_USE_SYSTEM_EXPAT
  VTKEXPAT_SOURCE_DIR
  EXPAT_INCLUDE_DIR
  EXPAT_LIBRARY
  VTK_USE_SYSTEM_JPEG
  VTKJPEG_SOURCE_DIR
  JPEG_INCLUDE_DIR
  JPEG_LIBRARY
  VTK_USE_SYSTEM_PNG
  VTKPNG_SOURCE_DIR
  PNG_INCLUDE_DIR
  PNG_LIBRARY
  VTK_USE_SYSTEM_TIFF
  VTKTIFF_SOURCE_DIR
  TIFF_INCLUDE_DIR
  TIFF_LIBRARY
  VTK_USE_SYSTEM_ZLIB
  VTKZLIB_SOURCE_DIR
  ZLIB_INCLUDE_DIR
  ZLIB_LIBRARY
)

# EXPAT
IF(TEMP_VTK_USE_SYSTEM_EXPAT)
  SET(EXPAT_INCLUDE_DIR ${TEMP_VTKEXPAT_INCLUDE_DIR})
  SET(EXPAT_LIBRARY ${TEMP_EXPAT_LIBRARY})
ELSE(TEMP_VTK_USE_SYSTEM_EXPAT)
  SET(EXPAT_INCLUDE_DIR ${TEMP_VTKEXPAT_SOURCE_DIR})
  SET(EXPAT_LIBRARY vtkexpat)
ENDIF(TEMP_VTK_USE_SYSTEM_EXPAT)

# JPEG
IF(TEMP_VTK_USE_SYSTEM_JPEG)
  SET(JPEG_INCLUDE_DIR ${TEMP_VTKJPEG_INCLUDE_DIR})
  SET(JPEG_LIBRARY ${TEMP_JPEG_LIBRARY})
ELSE(TEMP_VTK_USE_SYSTEM_JPEG)
  SET(JPEG_INCLUDE_DIR ${TEMP_VTKJPEG_SOURCE_DIR})
  SET(JPEG_LIBRARY vtkjpeg)
ENDIF(TEMP_VTK_USE_SYSTEM_JPEG)

# PNG
IF(TEMP_VTK_USE_SYSTEM_PNG)
  SET(PNG_INCLUDE_DIR ${TEMP_VTKPNG_INCLUDE_DIR})
  SET(PNG_LIBRARY ${TEMP_PNG_LIBRARY})
ELSE(TEMP_VTK_USE_SYSTEM_PNG)
  SET(PNG_INCLUDE_DIR ${TEMP_VTKPNG_SOURCE_DIR})
  SET(PNG_LIBRARY vtkpng)
ENDIF(TEMP_VTK_USE_SYSTEM_PNG)

# TIFF
IF(TEMP_VTK_USE_SYSTEM_TIFF)
  SET(TIFF_INCLUDE_DIR ${TEMP_VTKTIFF_INCLUDE_DIR})
  SET(TIFF_LIBRARY ${TEMP_TIFF_LIBRARY})
ELSE(TEMP_VTK_USE_SYSTEM_TIFF)
  SET(TIFF_INCLUDE_DIR ${TEMP_VTKTIFF_SOURCE_DIR})
  SET(TIFF_LIBRARY vtktiff)
ENDIF(TEMP_VTK_USE_SYSTEM_TIFF)

# ZLIB
IF(TEMP_VTK_USE_SYSTEM_ZLIB)
  SET(ZLIB_INCLUDE_DIR ${TEMP_VTKZLIB_INCLUDE_DIR})
  SET(ZLIB_LIBRARY ${TEMP_ZLIB_LIBRARY})
ELSE(TEMP_VTK_USE_SYSTEM_ZLIB)
  SET(ZLIB_INCLUDE_DIR ${TEMP_VTKZLIB_SOURCE_DIR})
  SET(ZLIB_LIBRARY vtkzlib)
ENDIF(TEMP_VTK_USE_SYSTEM_ZLIB)