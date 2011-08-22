/*=========================================================================

  Program:   Open ITK Link Library
  Module:    $RCSfile: $
  Language:  C
  Date:      $Date: $
  Version:   $Revision: $

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "igtl_image.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main( int argc, char * argv [] )
{
  typedef long long LongType;
  float spacing[3];
  float origin[3];
  float norm_i[3];
  float norm_j[3];
  float norm_k[3];
  unsigned long crc;
  char * image;

  igtl_image_header  header;

  LongType size = igtl_image_get_data_size( &header );

  igtl_image_get_matrix(spacing, origin, norm_i, norm_j, norm_k, & header);
  igtl_image_convert_byte_order( & header);

  // FIXME: verify the outcome

  
  //crc = igtl_image_get_crc( &header, (void*) image);

  // FIXME: verify the outcome


  return EXIT_SUCCESS;
}
