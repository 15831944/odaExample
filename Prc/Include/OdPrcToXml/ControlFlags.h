/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2022, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Open Design Alliance software pursuant to a license 
//   agreement with Open Design Alliance.
//   Open Design Alliance Copyright (C) 2002-2022 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef _CONTROLFLAGS_INCLUDED_
#define _CONTROLFLAGS_INCLUDED_ 

 

#include "PrcToXmlExportDef.h"

/** \details 
<group PRC_Export_Import_Classes> 
Class implements a set of flags determining the options for exporting PRC data to an .xml file.
*/
class PRCTOXML_TOOLKIT ControlFlags
{
public:
  /** \details 
  Enumerator representing options for exporting PRC data to an .xml file.
  */
  enum ControlFlagsEnum
  {
    /** No options for XML output are used.*/
    kDisabled                                  = 0x00000000, 
    /** Proceed with an audit of PRC data during the writing of it to the .xml file.*/
    kWithAudit                                 = 0x00000001, 
    /** Trace tell method for the filer object.*/
    kTraceTell                                 = 0x00000002, 
    /** Write data of the dump arrays to the .xml file.*/
    kDumpArraysToXml                           = 0x00000004, 
    /** Write PRC data to the .xml file with all options switched on.*/
    kFullOutput                                = 0xFFFFFF00, 
    /** Trace writing uncompressed unsigned integer data.*/
    kTraceUncompressedUnsignedInteger          = 0x00000100, 
    /** Trace reading uncompressed block.*/
    kTraceReadUncompressedBlock                = 0x00000200, 
    /** Trace writing bit data.*/
    kTraceBits                                 = 0x00000400, 
    /** Trace writing unsigned integer data represented with a variable bit number.*/
    kTraceUnsignedIntegerWithVariableBitNumber = 0x00000800, 
    /** Trace the bits number while writing unsigned integer data.*/
    kTraceNumberOfBitsThenUnsignedInteger      = 0x00001000, 
    /** Trace writing unsigned integer data.*/
    kTraceUnsignedInteger                      = 0x00002000, 
    /** Trace writing integer data.*/
    kTraceInteger                              = 0x00004000, 
    /** Trace writing double precision data.*/
    kTraceDouble                               = 0x00008000, 
    /** Trace writing string data.*/
    kTraceString                               = 0x00010000, 
    /** Trace writing boolean data.*/
    kTraceBoolean                              = 0x00020000, 
    /** Trace writing two-dimensional vector data.*/
    kTraceVector2d                             = 0x00040000, 
    /** Trace writing three-dimensional vector data.*/
    kTraceVector3d                             = 0x00080000, 
    /** Trace writing two-dimensional point data.*/
    kTracePoint2d                              = 0x00800000, 
    /** Trace writing three-dimensional point data.*/
    kTracePoint3d                              = 0x80000000, 
    /** Trace writing character data.*/
    kTraceCharacter                            = 0x00100000, 
    /** Trace writing entity type data.*/
    kTraceEntityType                           = 0x00200000, 
    /** Trace writing compressed entity type data.*/
    kTraceCompressedEntityType                 = 0x00400000, 
    /** Trace writing double precision data represented with a variable bit number.*/
    kTraceDoubleWithVariableBitNumber          = 0x01000000, 
    /** Trace writing three-dimensional point data represented with a variable bit number.*/
    kTracePoint3DWithVariableBitNumber         = 0x02000000, 
    /** Trace writing compressed integer array data.*/
    kTraceCompressedIntegerArray               = 0x04000000, 
    /** Trace writing compressed character array data.*/
    kTraceCharacterArray                       = 0x08000000, 
    /** Trace writing integer data represented with a variable bit number.*/
    kTraceIntegerWithVariableBitNumber         = 0x10000000, 
    /** Trace reading short integer array data.*/
    kTraceReadShortArray                       = 0x20000000, 
    /** Trace writing compressed indice array data.*/
    kTraceCompressedIndiceArray                = 0x40000000, 
    /** Default mode.*/
    kDefaultMode                               = kFullOutput, 
    /** Dump compressed Arrays data.*/
    kDumpCompressedArrays                      = kDumpArraysToXml | kTraceCompressedIntegerArray | kTraceCharacterArray | kTraceReadShortArray | kTraceCompressedIndiceArray
  };

  /** \details
  Creates an instance of ControlFlags class with default flags set (all flags are switched on).
  */  
  ControlFlags()
    : m_Flags(kDefaultMode)
  {
  }

  /** \details
  Creates an instance of the ControlFlags class with specified flags set.
  \param flags [in] A set of flag values to be used for creating a class instance.
  */
  ControlFlags(ControlFlagsEnum flags)
    : m_Flags(flags)
  {
  }

  /** Current set of options for exporting PRC data to an .xml file.*/
  ControlFlagsEnum m_Flags;

  /** \details 
  Returns the current value of the flag that determines trace writing of uncompressed, unsigned integer data.*/
  bool uncompressedUnsignedInteger         () const { return GETBIT(m_Flags, kTraceUncompressedUnsignedInteger         ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of uncompressed block data.*/
  bool readUncompressedBlock               () const { return GETBIT(m_Flags, kTraceReadUncompressedBlock               ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of bit data.*/
  bool bits                                () const { return GETBIT(m_Flags, kTraceBits                                ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of integer data with variable bit numbers.*/
  bool unsignedIntegerWithVariableBitNumber() const { return GETBIT(m_Flags, kTraceUnsignedIntegerWithVariableBitNumber); }
  
  /** \details 
  Returns the current value of the flag that determines whether the bit numbers are traced when writing unsigned integer data.*/
  bool numberOfBitsThenUnsignedInteger     () const { return GETBIT(m_Flags, kTraceNumberOfBitsThenUnsignedInteger     ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of unsigned integer data.*/
  bool unsignedInteger                     () const { return GETBIT(m_Flags, kTraceUnsignedInteger                     ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of integer data.*/
  bool integer                             () const { return GETBIT(m_Flags, kTraceInteger                             ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of double precision data.*/
  bool doubleEnabled                       () const { return GETBIT(m_Flags, kTraceDouble                              ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of string data.*/
  bool string                              () const { return GETBIT(m_Flags, kTraceString                              ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of boolean data.*/
  bool boolean                             () const { return GETBIT(m_Flags, kTraceBoolean                             ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of two-dimensional vector data.*/
  bool vector2d                            () const { return GETBIT(m_Flags, kTraceVector2d                            ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of three-dimensional vector data.*/
  bool vector3d                            () const { return GETBIT(m_Flags, kTraceVector3d                            ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of two-dimensional point data.*/
  bool point2d                             () const { return GETBIT(m_Flags, kTracePoint2d                             ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of three-dimensional point data.*/
  bool point3d                             () const { return GETBIT(m_Flags, kTracePoint3d                             ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of character data.*/
  bool character                           () const { return GETBIT(m_Flags, kTraceCharacter                           ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of entity type data.*/
  bool entityType                          () const { return GETBIT(m_Flags, kTraceEntityType                          ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of compressed entity type data.*/
  bool compressedEntityType                () const { return GETBIT(m_Flags, kTraceCompressedEntityType                ); }
  
  /** \details 
  Returns the current value of the flag that determines whether the tell() method is traced.*/
  bool tell                                () const { return GETBIT(m_Flags, kTraceTell                                ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of double data with variable bit numbers.*/
  bool doubleWithVariableBitNumber         () const { return GETBIT(m_Flags, kTraceDoubleWithVariableBitNumber         ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of three-dimensional point data with variable bit numbers.*/
  bool point3DWithVariableBitNumber        () const { return GETBIT(m_Flags, kTracePoint3DWithVariableBitNumber        ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of compressed integer array data.*/
  bool compressedIntegerArray              () const { return GETBIT(m_Flags, kTraceCompressedIntegerArray              ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of character array data.*/
  bool characterArray                      () const { return GETBIT(m_Flags, kTraceCharacterArray                      ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of integer data with variable bit numbers.*/
  bool integerWithVariableBitNumber        () const { return GETBIT(m_Flags, kTraceIntegerWithVariableBitNumber        ); }
  
  /** \details 
  Returns the current value of the flag that determines trace reading of short integer array data.*/
  bool readShortArray                      () const { return GETBIT(m_Flags, kTraceReadShortArray                      ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of compressed indice array data.*/
  bool compressedIndiceArray               () const { return GETBIT(m_Flags, kTraceCompressedIndiceArray               ); }
  
  /** \details 
  Returns the current value of the flag that determines trace writing of tesselation array data.*/
  bool dumpTessArrays                      () const { return GETBIT(m_Flags, kDumpArraysToXml                          ); }
  
  /** \details
  Returns the current value of the flag that determines whether an audit is processed. 
  */
  bool audit() const { return GETBIT(m_Flags, kWithAudit); }
};

#endif // _CONTROLFLAGS_INCLUDED_

