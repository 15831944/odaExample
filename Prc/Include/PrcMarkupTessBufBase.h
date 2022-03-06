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

#ifndef _PRCMARKUPTESSBUFBASE_INCLUDED_
#define _PRCMARKUPTESSBUFBASE_INCLUDED_ 
 

class OdPrcMarkupTessBuf;
typedef OdSmartPtr<OdPrcMarkupTessBuf> OdPrcMarkupTessBufPtr;

/** \details 
<group PRC_Markup_Classes> 

Markup tessellation buffer is a base class for storing markup tessellation entities. It is implemented as a single linked list. 
*/
class PRC_TOOLKIT OdPrcMarkupTessBuf : public OdRxObject
{
private:
  OdPrcMarkupTessBufPtr m_pNext;   // Smart pointer to another instance for attaching in a sequence

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcMarkupTessBuf);
  //DOM-IGNORE-END

  /** \details 
  Destroys the markup tessellation buffer.
  */
  virtual ~OdPrcMarkupTessBuf();

  /** \details 
  Returns a pointer to the next markup tessellation entity.
  */
  OdPrcMarkupTessBufPtr next() const;

  /** \details 
  Sets the next markup tessellation entity.

  \param pMkpTessBuf [in] A pointer to the next markup tessellation buffer. 
  */
  OdPrcMarkupTessBufPtr setNext(OdPrcMarkupTessBuf* pMkpTessBuf);
};

#endif // _PRCMARKUPTESSBUFBASE_INCLUDED_

