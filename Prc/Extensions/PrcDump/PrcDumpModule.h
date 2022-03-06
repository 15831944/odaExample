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

#ifndef _ODPRCDUMPMODULEIMPL_INCLUDED_
#define _ODPRCDUMPMODULEIMPL_INCLUDED_

#include "RxDynamicModule.h"
#include "PrcDumpExportDef.h"
#include "PrcUniqueId.h"
#include "OdBinaryData.h"
#include "Prc3dTess.h"
#include "Prc3dWireTess.h"
#include "PrcMarkupTess.h"
#include "PrcBrepModel.h"
#include "PrcWireCurve.h"
#include "PrcDirection.h"
#include "PrcConstructionPlane.h"
#include "PrcPointSet.h"
#include "PrcPolyBrepModel.h"
#include "PrcPolyWire.h"
#include "PrcSet.h"
#include "PrcCoordinateSystem.h"
#include "PrcTransformation3d.h"
#include "PrcRepresentationItemContent.h"
#include "PrcAnnotationItem.h"
#include "PrcAnnotationSet.h"
#include "PrcAnnotationReference.h"
#include "PrcMaterialGeneric.h"
#include "PrcTextureApplication.h"
#include "PrcDottingPattern.h"
#include "PrcHatchingPattern.h"
#include "PrcSolidPattern.h"
#include "PrcPicturePattern.h"
//#include "PrcHighlyCompressed3dTess.h"
#include "PrcBlend02Boundary3d.h"
#include "PrcNurbsCurve3d.h"
#include "PrcNurbsCurve2d.h"
#include "PrcCircle3d.h"
#include "PrcCircle2d.h"
#include "PrcCompositeCurve3d.h"
#include "PrcCompositeCurve2d.h"
#include "Prc2dCurveOnSurfaceCurve3d.h"
#include "PrcEllipse3d.h"
#include "PrcEllipse2d.h"
#include "PrcEquationCurve3d.h"
#include "PrcEquationCurve2d.h"
#include "PrcHelixType0Curve.h"
#include "PrcHelixType1Curve.h"
#include "PrcHyperbola3d.h"
#include "PrcHyperbola2d.h"
#include "PrcIntersectionCurve3d.h"
#include "PrcLine3d.h"
#include "PrcLine2d.h"
#include "PrcOffsetCurve3d.h"
#include "PrcParabola3d.h"
#include "PrcParabola2d.h"
#include "PrcPolyLine3d.h"
#include "PrcPolyLine2d.h"
#include "PrcTransformedCurve3d.h"
#include "PrcTransformedCurve2d.h"
#include "PrcAuditInfo.h"
#include "PrcBlend01Surface.h"
#include "PrcBlend02Surface.h"
#include "PrcBlend03Surface.h"
#include "PrcNurbsSurface.h"
#include "PrcCone.h"
#include "PrcCylinder.h"
#include "PrcCylindricalSurface.h"
#include "PrcOffsetSurface.h"
#include "PrcPlane.h"
#include "PrcRuledSurface.h"
#include "PrcSphere.h"
#include "PrcRevolutionSurface.h"
#include "PrcExtrusionSurface.h"
#include "PrcFromCurvesSurface.h"
#include "PrcTorus.h"
#include "PrcTransformedSurface.h"
#include "PrcSingleWireBody.h"
#include "PrcBrepData.h"
#include "PrcWireEdge.h"
#include "PrcConnex.h"
#include "PrcShell.h"
#include "PrcFace.h"
#include "PrcLoop.h"
#include "PrcCoEdge.h"
#include "PrcEdge.h"
#include "PrcUniqueVertex.h"
#include "PrcMultipleVertex.h"
#include "PrcMath1dArcTanCos.h"
#include "PrcMath1dCombination.h"
#include "PrcMath1dFraction.h"
#include "PrcMath1dPolynom.h"
#include "PrcMath1dTrigonometric.h"
#include "PrcMath3dLinear.h"
#include "PrcMath3dNonLinear.h"
#include "PrcDirectionalLight.h"
#include "PrcPointLight.h"
#include "PrcSpotLight.h"

//DOM-IGNORE-BEGIN
/************************************************************************/
/* This class is the base class for all entity dumpers                  */
/************************************************************************/
//DOM-IGNORE-END

/** \details 
Abstract class for any entity dumper. Contains an interface for dumping values of base PRC data types.
<group PRC_Protocol_Extensions_Classes>
*/
class ODPRCEXPORT_DLL OdPrcListener
{
public:

  /** \details 
  Dumps a specified signed byte value. 
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpInt8(const OdChar *pName, OdInt8 value) const = 0;
  
  /** \details 
  Dumps a specified signed integer value. 
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpInt32(const OdChar *pName, OdInt32 value) const = 0;
  
  /** \details 
  Dumps a specified unsigned integer value. 
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpUInt8(const OdChar *pName, OdUInt8 value) const = 0;
  
  /** \details 
  Dumps a specified unsigned short value. 
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpUInt16(const OdChar *pName, OdUInt16 value) const = 0;
  
  /** \details 
  Dumps a specified unsigned integer value. 
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpUInt32(const OdChar *pName, OdUInt32 value) const = 0;
  
  /** \details 
  Dumps a hexadecimal representation of a specified unsigned integer value.
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpUInt32Hex(const OdChar *pName, OdUInt32 value) const = 0;
  
  /** \details 
  Dumps a unique entity identifier value.
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpUniqueId(const OdChar *pName, OdPrcUniqueId value) const = 0;
  
  /** \details 
  Dumps an entity object identifier value.
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpObjectId(const OdChar *pName, OdPrcObjectId value) const = 0;
  
  /** \details 
  Dumps an uncompressed binary data block.
  \param pName [in] A property name to be dumped.
  \param value [in] A binary data block to be dumped.
  */
  virtual void dumpUncompressedBlock(const OdChar *pName, OdBinaryData value) const = 0;
  
  /** \details 
  Dumps a boolean value.
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpBoolean(const OdChar *pName, OdBool value) const = 0;
  
  /** \details 
  Dumps a double value.
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpDouble(const OdChar *pName, OdDouble value) const = 0;
  
  /** \details 
  Dumps a float value.
  \param pName [in] A property name to be dumped.
  \param value [in] A property value to be dumped.
  */
  virtual void dumpFloat(const OdChar *pName, float value) const = 0;
  
  /** \details 
  Dumps a bit field value.
  \param pName [in] A property name to be dumped.
  \param data  [in] A binary data to be dumped.
  */
  virtual void dumpBits(const OdChar *pName, const OdBitBinaryData &data) const = 0;
  
  /** \details 
  Dumps an ANSI string value.
  \param pName  [in] A property name to be dumped.
  \param str    [in] A string value to be dumped.
  */
  virtual void dumpAnsiString(const OdChar *pName, OdAnsiString str) const = 0;
  
  /** \details 
  Dumps a string value.
  \param pName  [in] A property name to be dumped.
  \param str    [in] A string value to be dumped.
  */
  virtual void dumpString(const OdChar *pName, OdString str) const = 0;
};

/** \details 
A class that implements entity dumping functionality. 
<group PRC_Protocol_Extensions_Classes>
*/
class ODPRCEXPORT_DLL OdPrcEntity_Dumper : public OdRxObject
{
public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcEntity_Dumper);
  //DOM-IGNORE-END

  /** \details 
  Dumps a specified entity's content.
  \param pObj       [in] A pointer to an entity to be dumped.
  \param pListener  [in] A pointer to a dumper used for dumping an entity's content.
  
  \remarks
  Current implementation does nothing. 
  */
  virtual void dump(const OdRxObject *pObj, const OdPrcListener* pListener) const;

  /** \details 
  Returns the object's sub elements array.
  \param pObj [in] A pointer to an object.
  */
  virtual OdRxObjectPtrArray subElements( const OdRxObject *pObj ) const
  {
    return OdRxObjectPtrArray();
  }
  
  /** \details 
  Returns the object's name.
  \param pObj [in] A pointer to an object.
  */
  virtual OdString getName( const OdRxObject *pObj ) const
  {
    if (pObj)
    {
      OdString s;
      s.format(L"<%ls>", pObj->isA()->name().c_str());
      return s;
    }

    return OdString::kEmpty;
  }
};
SMARTPTR(OdPrcEntity_Dumper);

class Dumpers;

/** \details
Implements dumping functionality for .prc content.
<group PRC_Protocol_Extensions_Classes>
*/
class ODPRCEXPORT_DLL OdPrcDumpModule : public OdRxModule
{
  Dumpers* m_pDumpers;
public:

  /** \details
  Creates a dumping module for .prc content.
  */
  OdPrcDumpModule();

  /** \details 
  Destroys the dumping module for .prc content.
  */
  virtual ~OdPrcDumpModule();

  /** \details 
  Registers the OdDbEntity_Dumper class in ODA Platform, creates dumpers for supported entities and adds protocol extensions for them.
  */
  virtual void initApp();

  /** \details 
  Deletes protocol extensions for entities available for dumping, unregisters the OdDbEntity_Dumper class, and destroys dumpers. 
  */
  virtual void uninitApp();
};

SMARTPTR(OdPrcDumpModule);

#endif //_ODPRCDUMPMODULEIMPL_INCLUDED_
