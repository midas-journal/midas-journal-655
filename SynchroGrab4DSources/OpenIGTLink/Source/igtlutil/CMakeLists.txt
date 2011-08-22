SET(IGTL_UTIL_PROTOCOL_VERSION "1")

if(OpenIGTLink_BUILD_SHARED_LIBS)
  set(igtlutil_BUILD_SHARED_LIBS ${OpenIGTLink_BUILD_SHARED_LIBS})
  
endif(OpenIGTLink_BUILD_SHARED_LIBS)

if(OpenIGTLink_BUILD_GENERATE_PIC)
  set(igtlutil_BUILD_GENERATE_PIC ${OpenIGTLink_BUILD_GENERATE_PIC})
  set(IGTLSTATIC 1)
endif(OpenIGTLink_BUILD_GENERATE_PIC)

SET(igtlutil_HEADS
  igtl_header.h
  igtl_image.h
  igtl_transform.h
  igtl_util.h
  igtl_types.h
  igtl_position.h
  )

SET(igtlutil_SOURCES
  igtl_header.c
  igtl_image.c
  igtl_transform.c
  igtl_util.c
#  igtl_position.c
  )       

ADD_LIBRARY(igtlutil
  ${igtlutil_SOURCES}
)

SET_TARGET_PROPERTIES(igtlutil PROPERTIES
  VERSION ${OpenIGTLink_VERSION_MAJOR}.${OpenIGTLink_VERSION_MINOR}.${OpenIGTLink_VERSION_PATCH}
  SOVERSION ${OpenIGTLink_VERSION_MAJOR}
)

#TARGET_LINK_LIBRARIES(igtlutil
#  ${LIBS}
#  )
