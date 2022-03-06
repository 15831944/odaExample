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

#ifndef _PRCMARKUPTESS_INCLUDED_
#define _PRCMARKUPTESS_INCLUDED_ 
 

#include "PrcBaseTessData.h"
#include "PrcFileStructure.h"
#include "PrcMarkupTessBufBase.h"

/** \details 
<group PRC_Tessellation_Classes> 

Class stores information about the behavior of a tessellation related to a markup.
*/
class PRC_TOOLKIT OdPrcMarkupTess: public OdPrcBaseTessData
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_TESS(OdPrcMarkupTess);
  //DOM-IGNORE-END

  /** \details
  Returns the current array of markup entity codes.
  The markup entity codes array is returned as a reference to an OdUInt32Array object, therefore it can be used to set new markup entity codes.
  */
  OdUInt32Array &codes();
  
  /** \details
  Returns the current array of markup entity codes.
  */
  const OdUInt32Array &codes() const;
  
  /** \details
  Returns the current array of markup entity text strings.
  The markup entity text strings array is returned as a reference to an OdStringArray object, therefore it can be used to set new markup entity text strings.
  */
  OdStringArray &text();
  
  /** \details
  Returns the current array of markup entity text strings.
  */
  const OdStringArray &text() const;
  
  /** \details
  Returns the current array of the tessellation data coordinates.
  The coordinates array is returned as a reference to an OdFloatArray object, therefore it can be used to set new coordinates.
  */
  OdFloatArray &coordinates();
  
  /** \details
  Returns the current array of the tessellation data coordinates.
  */
  const OdFloatArray &coordinates() const;
  
  /** \details
  Sets a new tessellation label.

  \param label [in] New tessellation label text to be set.
  */
  void setLabel(const OdString &label);
  
  /** \details
  Returns the current tessellation label text.
  */
  OdString label() const;
  
  /** \details
  Sets a new graphical behavior of the tessellation.

  \param behaviour [in] New graphical behavior of the tessellation to be set.
  */
  void setBehaviour(OdInt8 behaviour);
  
  /** \details
  Returns the current graphical behavior of the tessellation.
  */
  OdInt8 behaviour() const;

  /** \details
    Returns the head of markup tessellation objects for the specified file structure.
    Tessellation objects are organized as a single link list of instances of classes derived from OdPrcMarkupTessBuf.

    \param pMkpTessBuf  [out] A reference to a pointer of an OdPrcMarkupTessBuf object which should be filled with pointers to markup tessellation objects. 
    \param pFs          [in]  A constant reference to a .prc file structure object, for which the tessellation buffer should be returned. 


    \returns Returns a value of OdResult type. If eOk value is returned, the markup tessellation object list was successfully built and returned. 
  
    \remarks
    Object of classes listed below can be added to the markup tessellation buffer:
    * OdPrcMarkupTessBufBlock
    * OdPrcMarkupTessBufPolyline
    * OdPrcMarkupTessBufMatrix
    * OdPrcMarkupTessBufTriangles
    * OdPrcMarkupTessBufFrame
    * OdPrcMarkupTessBufFixedSize
    * OdPrcMarkupTessBufSymbol
    * OdPrcMarkupTessBufCylinder
    * OdPrcMarkupTessBufColor
    * OdPrcMarkupTessBufFont
    * OdPrcMarkupTessBufText
    * OdPrcMarkupTessBufPoints
    * OdPrcMarkupTessBufPolygon
  
    Markup Extra Data types listed below are not supported yet:
    * PRC_MARKUP_ExtraDataType_Pattern
    * PRC_MARKUP_ExtraDataType_Picture
    * PRC_MARKUP_ExtraDataType_Quads
    * PRC_MARKUP_ExtraDataType_FaceViewMode
    * PRC_MARKUP_ExtraDataType_LineStipple
    * PRC_MARKUP_ExtraDataType_LineWidth
  */
  OdResult getOdPrcMarkupTessBuf(OdPrcMarkupTessBufPtr &pMkpTessBuf, const OdPrcFileStructure &pFs) const;

  /** \details
    Set a new markup tessellation buffer.
    A tessellation object buffer is a single link list of instances of classes derived from OdPrcMarkupTessBuf.

    \param pMkpTessBuf  [in]  A constant reference to a pointer of an OdPrcMarkupTessBuf object which should be set as a new markup tessellation buffer. 
    \param pFs          [out] A reference to a .prc file structure object, for which a new tessellation buffer should be set. 

    \returns Returns eOk value if a new tessellation buffer was successfully set. 
  */
  OdResult setFromOdPrcMarkupTessBuf(const OdPrcMarkupTessBufPtr &pMkpTessBuf, OdPrcFileStructure &pFs);
};

SMARTPTR(OdPrcMarkupTess);

#endif // _PRCMARKUPTESS_INCLUDED_

