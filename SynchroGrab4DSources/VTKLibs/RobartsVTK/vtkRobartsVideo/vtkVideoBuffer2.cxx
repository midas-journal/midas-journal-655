/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkVideoBuffer2.cxx,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

  Author: Danielle Pace
          Robarts Research Institute and The University of Western Ontario

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information. 

=========================================================================*/
#include "vtkVideoBuffer2.h"
#include "vtkObjectFactory.h"
#include "vtkVideoFrame2.h"
#include "vtkDoubleArray.h"
#include "vtkCriticalSection.h"

vtkCxxRevisionMacro(vtkVideoBuffer2, "$Revision: 1.4 $");
vtkStandardNewMacro(vtkVideoBuffer2);

//----------------------------------------------------------------------------
vtkVideoBuffer2::vtkVideoBuffer2()
{
  this->FrameArray = 0;
  this->TimeStampArray = vtkDoubleArray::New();
  this->FrameFormat = vtkVideoFrame2::New();
  this->Mutex = vtkCriticalSection::New();
  this->BufferSize = 0;
  this->NumberOfItems = 0;
  this->CurrentIndex = 0;
  this->CurrentTimeStamp = 0.0;

  // serves to instantiate the frame array and the time stamp array
  this->SetBufferSize(30);
}

//----------------------------------------------------------------------------
vtkVideoBuffer2::~vtkVideoBuffer2()
{ 
  this->SetBufferSize(0);
  this->NumberOfItems = 0;

  if (this->FrameArray)
    {
    delete [] this->FrameArray;
    }

  if (this->TimeStampArray)
    {
    this->TimeStampArray->Delete();
    }

  this->FrameFormat->Delete();
  this->Mutex->Delete();
}

//----------------------------------------------------------------------------
void vtkVideoBuffer2::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os,indent);

  os << indent << "BufferSize: " << this->BufferSize << "\n";
  os << indent << "NumberOfItems: " << this->NumberOfItems << "\n";
  os << indent << "CurrentTimeStamp: " << this->CurrentTimeStamp << "\n";
  if (this->FrameFormat)
    {
    os << indent << "FrameFormat:\n";
    this->FrameFormat->PrintSelf(os, indent.GetNextIndent());
    }
  if (this->TimeStampArray)
    {
    os << indent << "TimeStampArray:\n";
    this->TimeStampArray->PrintSelf(os, indent.GetNextIndent());
    }
}

//----------------------------------------------------------------------------
void vtkVideoBuffer2::Lock()
{
  this->Mutex->Lock();
}

//----------------------------------------------------------------------------
void vtkVideoBuffer2::Unlock()
{
  this->Mutex->Unlock();
}

//----------------------------------------------------------------------------
// Sets the buffer size, and copies the maximum number of the most current old
// frames and timestamps
void vtkVideoBuffer2::SetBufferSize(int bufsize)
{
  int i;
  vtkVideoFrame2 **framearray;
  vtkDoubleArray* timestamps;

  if (bufsize < 0)
    {
    vtkErrorMacro("SetBufferSize: invalid buffer size");
    return;
    }

  if (bufsize == this->BufferSize && bufsize != 0)
    {
    return;
    }

  // if we don't have a frame array, we'll make one
  if (this->FrameArray == 0)
    {
    if (bufsize > 0)
      {
      this->CurrentIndex = 0;
      this->NumberOfItems = 0;
      this->CurrentTimeStamp = 0.0;
      this->FrameArray = new vtkVideoFrame2 *[bufsize];
      this->BufferSize = bufsize;
      this->TimeStampArray->SetNumberOfValues(this->BufferSize);
      for (i = 0; i < bufsize; i++)
        {
        this->FrameArray[i] = this->FrameFormat->MakeObject();
        this->TimeStampArray->SetValue(i, 0.0);
        } 
      this->Modified();
      }
    }
  // if we already have a frame array and are changing its buffer size
  else 
    {
    if (bufsize > 0)
      {
      framearray = new vtkVideoFrame2 *[bufsize];
      timestamps = vtkDoubleArray::New();
      timestamps->SetNumberOfValues(bufsize);
      }
    else
      {
      framearray = NULL;
      timestamps = NULL;
      this->NumberOfItems = 0;
      this->CurrentTimeStamp = 0.0;
      }

    int index = this->CurrentIndex;

    // if the new buffer is smaller than the old buffer
    if (this->BufferSize > bufsize)
      {
      // copy the most recent frames and timestamps
      for (i = 0; i < bufsize; i++)
        {
        framearray[i] = this->FrameArray[index];
        timestamps->SetValue(i, this->TimeStampArray->GetValue(index));
        index = (index + 1) % this->BufferSize;
        if (index < 0)
          {
          // because '%' can give negative results on some platforms
          index = index + this->BufferSize;
          }
        }
      // delete the older frames and timestamps that won't fit in the new buffer
      for (i = 0; i < this->BufferSize - bufsize; i++)
        {
         this->FrameArray[index]->Delete();
         this->TimeStampArray->SetValue(index, 0.0);
         index = (index + 1) % this->BufferSize;
         if (index < 0)
            {
          // because '%' can give negative results on some platforms
          index = index + this->BufferSize;
            }
        }
      // set the current index
      this->CurrentIndex = 0;
      }
    // if the new buffer is bigger than the old buffer
    else if (bufsize > this->BufferSize)
      {
      // create new frames and timestamps
      for (i = 0; i < bufsize - this->BufferSize; i++)
        {
        framearray[i] = this->FrameFormat->MakeObject();
        timestamps->SetValue(i, 0.0);
        }
      // copy the old frames and timestamps
      for (i = bufsize-this->BufferSize; i < bufsize; i++)
        {
        framearray[i] = this->FrameArray[index];
        timestamps->SetValue(i, this->TimeStampArray->GetValue(index));
        index = (index + 1) % this->BufferSize;
        if (index < 0)
          {
          // because '%' can give negative results on some platforms
          index = index + this->BufferSize;
          }
        }
      // set the current index
      this->CurrentIndex = bufsize - this->BufferSize;
      }

    // fix the current index if it is out of range
    if (this->CurrentIndex < 0)
      {
      this->CurrentIndex = 0;
      }

    // update the frame array and the time stamp array
    if (this->FrameArray)
      {
      delete [] this->FrameArray;
      }
    this->FrameArray = framearray;
    if (this->TimeStampArray)
      {
        this->TimeStampArray->Delete();
      }
    this->TimeStampArray = timestamps;

    // update the buffer size and the number of items
    this->BufferSize = bufsize;
    if (this->NumberOfItems > this->BufferSize)
      {
      this->NumberOfItems = this->BufferSize;
      }

    this->Modified();
    }
}

//----------------------------------------------------------------------------
// Sets the frame format.  If the format is different from the old format,
// deletes all of the old frames and fills the buffer with new frames of the
// new format
void vtkVideoBuffer2::SetFrameFormat(vtkVideoFrame2 *format)
{
  // if the new format matches the old format, we don't need to do anything
  if (format)
    {
    int frameSize[3];
	int frameExtent[6];
	int frameFormatSize[3];
	int frameFormatExtent[6];
    format->GetFrameSize(frameSize);
    format->GetFrameExtent(frameExtent);
    this->FrameFormat->GetFrameSize(frameFormatSize);
    this->FrameFormat->GetFrameExtent(frameFormatExtent);
    
    if (frameSize[0] == frameFormatSize[0] &&
      frameSize[1] == frameFormatSize[1] &&
      frameSize[2] == frameFormatSize[2] &&
      frameExtent[0] == frameFormatExtent[0] &&
      frameExtent[1] == frameFormatExtent[1] &&
      frameExtent[2] == frameFormatExtent[2] &&
      frameExtent[3] == frameFormatExtent[3] &&
      frameExtent[4] == frameFormatExtent[4] &&
      frameExtent[5] == frameFormatExtent[5] &&
      format->GetPixelFormat() == this->FrameFormat->GetPixelFormat() &&
      format->GetBitsPerPixel() == this->FrameFormat->GetBitsPerPixel() &&
      format->GetRowAlignment() == this->FrameFormat->GetRowAlignment() &&
      format->GetTopDown() == this->FrameFormat->GetTopDown() &&
      format->GetBytesInFrame() == this->FrameFormat->GetBytesInFrame() &&
      format->GetOpacity() == this->FrameFormat->GetOpacity() &&
	  format->GetCompression() == this->FrameFormat->GetCompression() &&
	  format->GetFrameGrabberType() == this->FrameFormat->GetFrameGrabberType() )
      {
      return;
      }
    }

  // set the new frame format
  if (this->FrameFormat)
    {
    this->FrameFormat->Delete();
    }
  if (format)
    {
    format->Register(this);
    this->FrameFormat = format;
    }
  else
    {
    this->FrameFormat = vtkVideoFrame2::New();
    }

  this->Modified();

  // replace all the frames with ones in the new format
  for (int i = 0; i < this->BufferSize; i++)
    {
    this->FrameArray[i]->Delete();
    this->FrameArray[i] = this->FrameFormat->MakeObject();
    this->TimeStampArray->SetValue(i, 0.0);
    }

  this->CurrentIndex = 0;
  this->NumberOfItems = 0;
  this->CurrentTimeStamp = 0.0;
}

//----------------------------------------------------------------------------
void vtkVideoBuffer2::AddItem(vtkVideoFrame2* frame, double time)
{
  if (time <= this->CurrentTimeStamp)
    {
    return;
    }

  // don't add a frame if it doesn't match the buffer frame format
  int frameSize[3];
  int frameExtent[6];
  int frameFormatSize[3];
  int frameFormatExtent[6];
  frame->GetFrameSize(frameSize);
  frame->GetFrameExtent(frameExtent);
  this->FrameFormat->GetFrameSize(frameFormatSize);
  this->FrameFormat->GetFrameExtent(frameFormatExtent);
  if (frameSize[0] != frameFormatSize[0] ||
    frameSize[1] != frameFormatSize[1] ||
    frameSize[2] != frameFormatSize[2] ||
    frameExtent[0] != frameFormatExtent[0] ||
    frameExtent[1] != frameFormatExtent[1] ||
    frameExtent[2] != frameFormatExtent[2] ||
    frameExtent[3] != frameFormatExtent[3] ||
    frameExtent[4] != frameFormatExtent[4] ||
    frameExtent[5] != frameFormatExtent[5] ||
    frame->GetPixelFormat() != this->FrameFormat->GetPixelFormat() ||
    frame->GetBitsPerPixel() != this->FrameFormat->GetBitsPerPixel() ||
    frame->GetRowAlignment() != this->FrameFormat->GetRowAlignment() ||
    frame->GetTopDown() != this->FrameFormat->GetTopDown() ||
    frame->GetOpacity() != this->FrameFormat->GetOpacity() ||
	frame->GetCompression() != this->FrameFormat->GetCompression() ||
	frame->GetFrameGrabberType() != this->FrameFormat->GetFrameGrabberType() )
    {
    return;
    }

  // add the frame and timestamp, and update buffer
  this->CurrentTimeStamp = time;
  this->FrameArray[this->CurrentIndex] = frame;
  this->TimeStampArray->SetValue(this->CurrentIndex, time);
  this->NumberOfItems++;
  if (this->NumberOfItems > this->BufferSize)
    {
    this->NumberOfItems = this->BufferSize;
    }

  this->Modified();
}

//----------------------------------------------------------------------------
void vtkVideoBuffer2::Seek(int n)
{
  if (this->BufferSize <= 0)
    {
    return;
    }
 
  int i = (this->CurrentIndex - n) % this->BufferSize;
  while (i < 0) 
    { // because '%' can give negative results on some platforms
    i += this->BufferSize;
    }
  this->CurrentIndex = i;

  this->Modified();
}

//----------------------------------------------------------------------------
vtkVideoFrame2* vtkVideoBuffer2::GetFrame(int frame)
{
  if (this->BufferSize <= 0)
    {
    return 0;
    }

  int index = (this->CurrentIndex - frame) % this->BufferSize;
  while (index < 0)
    { // because '%' can give negative results on some platforms
    index += this->BufferSize;
    }

  return this->FrameArray[index];
}

//----------------------------------------------------------------------------
double vtkVideoBuffer2::GetTimeStamp(int frame)
{ 
  if (this->BufferSize <= 0)
    {
    return 0.0;
    }

  int index = (this->CurrentIndex - frame) % this->BufferSize;
  while (index < 0)
    { // because '%' can give negative results on some platforms
    index += this->BufferSize;
    }

  return this->TimeStampArray->GetValue(index);
}

//----------------------------------------------------------------------------
// do a simple divide-and-conquer search for the transform
// that best matches the given timestamp
int vtkVideoBuffer2::GetIndexFromTime(double time)
{
  int lo = 1; // index of minimum time
  int hi = this->BufferSize; // index of maximum time
  double tlo = this->GetTimeStamp(lo); // minimum time
  double thi = this->GetTimeStamp(hi); // maximum time

  if (time <= tlo)
    {
	//std::cout << "warning - returning lo" << std::endl; // TODO put back
    return lo;
    }
  else if (time >= thi)
    {
	//std::cout << "warning - returning hi" << std::endl; // TODO put back
    return hi;
    }

  for (;;)
    {
    if (hi-lo == 1)
      {
      if (time - tlo > thi - time)
        {
        return hi;
        }
      else
        {
        return lo;
        }
      }

    int mid = (lo+hi)/2;
    double tmid = this->GetTimeStamp(mid);

    if (time < tmid)
      {
      hi = mid;
      thi = tmid;
      }
    else
      {
      lo = mid;
      tlo = tmid;
      }
    }
}
