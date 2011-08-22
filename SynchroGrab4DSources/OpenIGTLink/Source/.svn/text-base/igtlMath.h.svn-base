/*=========================================================================

  Program:   Open IGT Link Library
  Module:    $HeadURL$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __igtlMath_h
#define __igtlMath_h

#include "igtlWin32Header.h"

namespace igtl
{

typedef float  Matrix4x4[4][4];

void IGTLCommon_EXPORT PrintMatrix(igtl::Matrix4x4 &matrix);
void IGTLCommon_EXPORT QuaternionToMatrix(float* q, Matrix4x4& m);
void IGTLCommon_EXPORT MatrixToQuaternion(Matrix4x4& m, float* q);
void IGTLCommon_EXPORT Cross(float *a, float *b, float *c);
void IGTLCommon_EXPORT IdentityMatrix(igtl::Matrix4x4 &matrix);

}

#endif // __igtlMath_h



