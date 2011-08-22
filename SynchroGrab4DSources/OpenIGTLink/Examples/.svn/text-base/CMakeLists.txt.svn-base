cmake_minimum_required(VERSION 2.4)

#
# Examples
#


## Imager program isn't supported by QNX

if(NOT OpenIGTLink_PLATFORM_QNX)
  SUBDIRS(
      Tracker
      Imager
      Status
      Receiver
      )
else(NOT OpenIGTLink_PLATFORM_QNX)
  SUBDIRS(
      Tracker
      Status
      Receiver
      )
endif(NOT OpenIGTLink_PLATFORM_QNX)



