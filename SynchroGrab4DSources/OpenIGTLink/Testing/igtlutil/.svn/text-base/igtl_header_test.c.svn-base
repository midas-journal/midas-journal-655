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

#include "igtl_header.h"
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

int main( int argc, char * argv [] )
{

  igtl_header  header;

  header.version = 1;
  strncpy( header.name, "Name", 8 );
  strncpy( header.device_name, "DeviceName", 20 );
  header.timestamp = 12345;
  header.body_size = 234567;
  header.crc = 1343143;

  igtl_header_convert_byte_order( &header );

  //
  // FIXME: Test the outcome of the 
  // byte order conversion for correctness.
  // until then, we mark this test as failing.
  //

  return EXIT_SUCCESS;
}
