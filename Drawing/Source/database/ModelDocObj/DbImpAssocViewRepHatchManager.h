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

#ifndef DbImpAssocViewRepHatchManager_INCLUDED_
#define DbImpAssocViewRepHatchManager_INCLUDED_ /*!DOM*/

#include "DbAssocViewRepHatchManager.h"
#include "DbImpAssocActionParam.h"

#include "TD_PackPush.h"

typedef OdArray<OdInt32,  OdMemoryAllocator<OdInt32> >  OdInt32dArray;
typedef OdArray<OdUInt64, OdMemoryAllocator<OdUInt64> > OdUInt64dArray;

/** \details
  This class implements the view hatch action manager.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class SYNERGYOBJDPW_EXPORT OdDbImpAssocViewRepHatchManager : public OdDbImpAssocCompoundActionParam
{
public:     
  /** \details
    Constructor creates an instance of this class.
  */
  OdDbImpAssocViewRepHatchManager();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdDbImpAssocViewRepHatchManager();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdDbDwgFiler* pFiler, OdDbObjectId objectId);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdDbDwgFiler* pFiler, OdDbObjectId objectId) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdDbDxfFiler* pFiler, OdDbObjectId objectId);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdDbDxfFiler* pFiler, OdDbObjectId objectId) const;

protected:

  OdUInt16          m_nVersion;                     // = 0 - version

  mutable OdInt32   m_Count_ActionParam;            // size of array DbAssocViewRepHatchActionParam

  OdUInt64dArray    m_Unknown2;                     // 2, 3, 4 ...
  OdUInt64dArray    m_Unknown3;                     // 2, 3, 4 ...
  OdInt32dArray     m_Unknown4;                     // = 1 also
  OdDbObjectIdArray m_AssocViewRepHatchActionParam; // DbAssocViewRepHatchActionParam

  //  OdDbObjectId* m_AssocViewRepHatchActionParam; // DbAssocViewRepHatchActionParam x402

  friend class OdDbAssocViewRepHatchManager;
};

#include "TD_PackPop.h"

#endif // DbImpAssocViewRepHatchManager_INCLUDED_
