SynchroGrab4D, version 1.0

*** Note that SynchroGrab4D will be maintained at:
http://svn.na-mic.org/NAMICSandBox/trunk/4DUltrasound-WithGating

Authors:
Danielle Pace,
David Gobbi,
Chris Wedlake,
Jan Gumprecht,
Jonathan Boisvert

Contact Information:
Danielle Pace, dpace@imaging.robarts.ca

-------

Building Slicer - Assuming you are building the 3.4 release:

1) Requires OpenIGTLink library from Slicer3 trunk, so in slicer_variables.tcl change
set ::OpenIGTLink_TAG "http://svn.na-mic.org/NAMICSandBox/branches/OpenIGTLink-1-0"
to
set ::OpenIGTLink_TAG "http://svn.na-mic.org/NAMICSandBox/trunk/OpenIGTLink"
- Code tested with OpenIGTLink trunk revision 4632

2) Check out OpenIGTLink IF module from Slicer3 trunk instead of the 3.4 release

3) Check out FourDImage module from Slicer3 trunk and add it to the list of modules Slicer3/Modules/CMakeLists

4) If you want to use Matrox frame grabbing, set VTK_USE_MATROX_IMAGING ON when building Slicer's VTK
MIL_INCLUDE_PATH something like C:/Program Files/Matrox Imaging/Mil/Include
MIL_LIBARY something like C:/Program Files/Matrox Imaging/Mil/mil.lib
We have included an updated version of vtkMILVideoSource.h and vtkMILVideoSource2.cxx (in SynchroGrab4DSources/VTKLibs/RobartsVTK) and recommend that you sub this into Slicer's source code

-------

Equipment-specific libraries

- Sonix video needs Sonix RP headers
- Heart signal box needs inpout32.lib/inpout32.dll within SynchroGrab4DSources\VTKLibs\RobartsVTK\vtkRobartsECG
- May need to change hard-coded base port number in SynchroGrab4DSources\VTKLibs\RobartsVTK\vtkRobartsECG\vtkHeartSignalBox.cpp
- USB signal box needs cbw32.lib/cbw32.dll within SynchroGrab4DSources\VTKLibs\RobartsVTK\vtkRobartsECG

-------

Building SynchroGrab4D:

1)  Run CMake, using SynchroGrab4DSources as the source directory

- VTK_DIR = VTK-build directory from Slicer3
- OpenIGTLink_DIR = OpenIGTLink-build directory from Slicer3
*** make sure that you select the correct VTK and OpenIGTLink
directories if you have more than one version on your system
- Options for building video sources:
  Matrox = see step 4 above
- Options for building tracking systems:
  Aurora/Polaris = VTK_USE_POLARIS
  Certus = VTK_USE_CERTUS
  Flock of Birds = VTK_USE_FLOCK
  Micron tracker = VTK_USE_MICRONTRACKER
- Options for building ECG systems:
  Heart box (requires 5V signal at each R-wave) = VTK_USE_HEARTSIGNALBOX
  USB box (user-defined threshold on incoming USB signal) = VTK_USE_USBECGBOX

2)  Add your equivalent of the following paths to your environment:

OPENIGTLINK
E:\Slicer-3-4\winbin\Slicer3-lib\OpenIGTLink-build\bin\Debug

VTKBUILD
E:\Slicer-3-4\winbin\Slicer3-lib\VTK-build\bin\Debug

If using heart signal box or USB signal box:
ROBARTSECG
E:\SynchroGrab4D\SynchroGrab4DSources\VTKLibs\RobartsVTK\vtkRobartsECG

PATH
%OPENIGTLINK%; %VTKBUILD%; %ROBARTSECG%

-------

Running SynchroGrab4D:

To setup Slicer to receive the incoming images and transforms, configure OpenIGTLink IF module as follows:
For images:
Connector 1 -- Server -- Port 18944 -- Active
For transforms (if you choose to):
Connector 2 -- Server -- Port 18945 -- Active

Run 4DUltrasound.exe to get  list of command-line options (only the calibration file is required)

Then simply run 4DUltrasound.exe with your particular choice of options, and it will automatically perform the 3D or 4D ultrasound reconstruction and send the results to 3D Slicer.  For example:
./4DUltrasound.exe -c ../../../SynchroGrab4DSources/freehand_summary.xml
or
./4DUltrasound.exe -c ../../../SynchroGrab4DSources/freehand_summary.xml -isp 10 -stm -tsr 5

EXAMPLE demo:  Using a fake tracker that rotates in a circle, noisy input images and a gating simulator with two phases that operates at 1 cycle/sec.
- use freehand_summary.xml calibration file, located in SynchroGrab4D sources
- use NOISE video source
- use FAKE tracker with the tracker port set to 1
- use FAKE signal box, or no triggering at all
(This will send simulated volumes to Slicer)
- To view the volumes in 3D Slicer:  Use "fit to window" to align the three planes through the volume, adjust the window/level, and slice through the volume using the sliders above the red/yellow/green windows.

-------

Practical acquistion issues:

- All output volumes are allocated in memory at the beginning of the reconstruction, so make sure that you have enough memory for the number and size of output volumes that you want
- When reconstructing with compounding turned on, an accumulation buffer is assocated with each output volume, increasing the risk of not having enough memory
- SynchroGrab4D will drop frames if it doesn't have time to insert a frame into its output volume before the next frame of interest comes along
- Saving inserted 2D images as .bmp files also occurs in real-time, and therefore increases the risk of dropping frames

-------

Testing:

Tested:
- no triggering + fake video source + fake tracker
- fake signal box + fake video source + fake tracker
- heart signal box + MIL video + Aurora tracker
- USB signal box + MIL video + Aurora tracker

Untested with reconstruction code, but tested previously:
- Flock tracker
- Micron tracker
- Certus tracker
- Polaris tracker
(feedback from users with these trackers is appreciated!)

Pretty much completely untested, but "theoretically" should work:
- Win32 video source 2
(feedback from users with this frame grabber is appreciated!)

-------

Known bugs (to be fixed shortly!):
- (Minor) Timestamp in tracking simulator not correct

Additional features to be added:
- Support for Linux and Sonix RP video input - need to refactor classes to videoSource2-style
- GUI within Slicer to control user parameters / enable start-stop behavior, etc
- Python/Tcl/Java wrapping currently not supported/tested
- Other output volume formats besides .vtk
- Clipping rectangle to specify region of interest in 2D US frames
- Offline reconstruction (i.e. not real-time) not currently supported for gated 4D reconstruction
  (exists but is relatively untested for non-gated 3D reconstruction)


