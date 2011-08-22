INCLUDE_DIRECTORIES(${ULTERIUS_INCLUDE_DIR})

ADD_EXECUTABLE(4DUltrasound
  4DUltrasound.cxx 
  #vtkDataCollector.cxx 
  vtkDataProcessor.cxx
  vtkDataSender.cxx
  vtkInstrumentTracker.cxx
  )

#Use tracker device
TARGET_LINK_LIBRARIES(
  4DUltrasound 
  OpenIGTLink
  igtlutil
  ##12/1/08
  ## NH commented out for compilation in Mac OS
  #ws2_32
  #wsock32
  #vtkOpenIGTUltrasound 
  vtkAtamaiTracking
  vtkRobartsECG
  vtkRobartsVideo
  vtkRobartsUltrasound
  #vtkIO
  #ndicapi
  #${NDIOAPI_LIBRARY} 
)

