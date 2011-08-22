--- base classes / helper classes
vtkVideoFrame2
vtkVideoBuffer2
vtkVideoSource2

--- for Matrox:
vtkMILVideoSource <-- should sub into VTK Hybrid, improved class
vtkMILVideoSource2 <-- refactored class for SynchroGrab4D

--- for Video-for-Windows (untested):
vtkWin32VideoSource2

--- for Linux:
vtkV4L2VideoSource <-- still needs to be refactored for use with SynchroGrab4D

--- for Sonix RP:
vtkSonixVideoSource <-- still needs to be refactored for use with SynchroGrab4D