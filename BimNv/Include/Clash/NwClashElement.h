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

#ifndef __TNW_CLASHELEMENT_H__
#define __TNW_CLASHELEMENT_H__

#include "NwSavedItemsElement.h"
#include "RxSystemServices.h"
#include "NwExport.h"
#define STL_USING_MAP
#define STL_USING_LIST
#include "OdaSTL.h"

class OdNwModel;

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwModel object pointers.
*/
typedef OdSmartPtr<OdNwModel> OdNwModelPtr;

/** \details
  This class represents a clash element.

  <group OdNw_Classes>
*/
class NWDBEXPORT OdNwClashElement : public OdNwSavedItemsElement
{
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdNwClashElement);
  //DOM-IGNORE-END

public:
  /** \details
    Default constructor.
  */
  OdNwClashElement();

public:

  /** \details
    Gets ignored plugins for ClashElement as std::map.

    \param ignoredPlugins [out] std::map with OdInt32 as values and string descriptions as keys.
    \returns eOk if the ignoredPlugins are retrieved successfully, or an appropriate error code otherwise.
  */
  OdResult getIgnorePlugins(std::map<OdString, OdInt32>& ignoredPlugins) const;

  /** \details
    Gets scene references for ClashElement as OdArray of OdNwModelPtr.

    \param sceneRefs [out] OdArray with OdNwModelPtr as values.
    \returns eOk if the sceneRefs are retrieved successfully, or an appropriate error code otherwise.
  */
  OdResult getSceneRefs(OdArray<OdNwModelPtr>& sceneRefs) const;


  /** \details
    Virtual destructor. Frees allocated resources.
  */
  virtual ~OdNwClashElement();
};

/** \details
  This template class is a specialization of the OdSmartPtr class for OdNwClashElement object pointers.
*/
typedef OdSmartPtr<OdNwClashElement> OdNwClashElementPtr;

#endif //__TNW_CLASHELEMENT_H__
