/*=========================================================================

  Program:   Open ITK Link Library
  Module:    $HeadURL$
  Language:  C
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#ifndef __IGTL_UTIL_H
#define __IGTL_UTIL_H

#include "igtl_win32header.h"
#include "igtl_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Byte order conversion macros
 *
 */

#define BYTE_SWAP_INT16(S) (((S) & 0xFF) << 8 \
                            | (((S) >> 8) & 0xFF))
#define BYTE_SWAP_INT32(L) ((BYTE_SWAP_INT16 ((L) & 0xFFFF) << 16) \
                            | BYTE_SWAP_INT16 (((L) >> 16) & 0xFFFF))
#define BYTE_SWAP_INT64(LL) ((BYTE_SWAP_INT32 ((LL) & 0xFFFFFFFF) << 32) \
                             | BYTE_SWAP_INT32 (((LL) >> 32) & 0xFFFFFFFF))

/*
 * Test endian of the host
 */
int igtl_export igtl_is_little_endian();
igtl_uint64 igtl_export crc64(unsigned char *data, int len, igtl_uint64 crc);


/*
 * Convert nanosecond to fraction / fraction to nanosec
 */

igtl_uint32 igtl_export igtl_nanosec_to_frac(igtl_uint32 nanosec);
igtl_uint32 igtl_export igtl_frac_to_nanosec(igtl_uint32 frac);

#ifdef __cplusplus
}
#endif

#endif  /*__IGTL_UTIL_H*/

