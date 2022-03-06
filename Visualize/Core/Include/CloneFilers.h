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




#ifndef OD_CLONEFILERS_INCLUDED
#define OD_CLONEFILERS_INCLUDED

#include "DbFiler.h"
#include "IdArrays.h"

class OdTvDbIdMapping;

class OdTvDbDeepCloneFiler;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbDeepCloneFiler object pointers.
*/
typedef OdSmartPtr<OdTvDbDeepCloneFiler> OdTvDbDeepCloneFilerPtr;

/** \details
    This class is the base class for classes that are used for DeepClone file I/O operations utilizing .dwg 
    and .dxf file formats.
    Corresponding C++ library: TD_Db
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbDeepCloneFiler : public OdTvDbDwgFiler
{
protected:
  OdTvDbDeepCloneFiler() {}

public:
  ODRX_DECLARE_MEMBERS(OdTvDbDeepCloneFiler);

  /** \details
    Creates a DeepCloneFiler object with the specified ID Mapping.
    \param pIdMapping [in]  Pointer to the ID Mapping. 
  */
  static OdTvDbDeepCloneFilerPtr createObject(OdTvDbIdMapping* pIdMapping);

  // Protocol specific to clone filers

  /** \details
    Sets this DeepCloneFiler object to reference the Object ID that it would normally reference first.

    \remarks
    Allows multiple traversals of the ID Mapping.
  */
    virtual void start() = 0;
  /** \details
    Sets this DeepCloneFiler object to reference the Object ID following the current Object ID referenced.
    
    \param objectId [out]  Receives the next referenced Object ID.
  */
    virtual bool nextReference(OdTvDbObjectId& objectId) = 0;

  /** \details
    Returns the ID Mapping for this DeepCloneFiler object.
  */
  virtual OdTvDbIdMapping& idMapping() = 0;

  /** \details
    Processes the objects in the ID Mapping of this DeepCloneFiler object.
  */
  virtual void defaultProcessReferences() = 0;
};

class OdTvDbWblockCloneFiler;
/** \details
    This template class is a specialization of the OdSmartPtr class for OdTvDbWblockCloneFiler object pointers.
*/
typedef OdSmartPtr<OdTvDbWblockCloneFiler> OdTvDbWblockCloneFilerPtr;

/** \details
    This class is the base class for classes that are used for Wblock file I/O operations utilizing .dwg
    and .dxf file formats.
    Library Db
    <group OdTvDb_Classes>
*/
class TOOLKIT_EXPORT OdTvDbWblockCloneFiler : public OdTvDbDeepCloneFiler
{
protected:
  OdTvDbWblockCloneFiler() {}

public:
  ODRX_DECLARE_MEMBERS(OdTvDbWblockCloneFiler);

  /** \details
    Creates a WblockCloneFiler object with the specified ID Mapping.
    \param pIdMapping [in]  Pointer to the ID Mapping. 
  */
  static OdTvDbWblockCloneFilerPtr createObject(OdTvDbIdMapping* pIdMapping);
};

#endif //OD_CLONEFILERS_INCLUDED
