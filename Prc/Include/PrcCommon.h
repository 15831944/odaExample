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

#ifndef _PRCCOMMON_INCLUDED_
#define _PRCCOMMON_INCLUDED_ 
 

#include "OdaCommon.h"

#include "RxObject.h"
#include "RxObjectImpl.h"
#include "SmartPtr.h"
#include "StringArray.h"
#include "OdStreamBuf.h"
#include "UInt32Array.h"
#include "UInt16Array.h"
#include "UInt8Array.h"
#include "Int16Array.h"
#include "Int32Array.h"
#include "BoolArray.h"
#include "Int8Array.h"
#include "Ge/GePoint3d.h"

typedef OdArray<OdGePoint3dArray> OdGePoint3dArrayArray;
typedef OdArray<float, OdMemoryAllocator<float> > OdFloatArray;

#include "DoubleArray.h"
#include "Ge/GeVector3dArray.h"
#include "Ge/GeVector2dArray.h"
#include "Ge/GePoint3dArray.h"
#include "Ge/GePoint2dArray.h"
#include "Ge/GeDoubleArray.h"
#include "PrcDefines.h"
#include "PrcToolkitExportDef.h"
#include "PrcModuleNames.h"

//DOM-IGNORE-BEGIN
#define PRC_DECLARE(className)\
public:\
  className();\
public:

#define PRC_DECLARE_UIO(className)\
  PRC_DECLARE(className)\
public:\
  void prcOut(OdPrcUncompressedFiler *pStream);\
  void prcIn(OdPrcUncompressedFiler *pStream);

#define PRC_DECLARE_CIO(className)\
  PRC_DECLARE(className)\
public:\
  void prcOut(OdPrcCompressedFiler *pStream);\
  void prcIn(OdPrcCompressedFiler *pStream);

#define SMARTPTR(classname) class classname; typedef OdSmartPtr<classname> classname##Ptr; typedef OdArray<classname##Ptr> classname##PtrArray;

#define ODPRC_DECLARE_MEMBERS_PRCBASE(className)\
protected:\
  className();\
  className(OdPrcBaseImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS(className)\
protected:\
  className();\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_BODY(className)\
protected:\
  className();\
  className(OdPrcBodyImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_TESS(className)\
protected:\
  className();\
  className(OdPrcBaseTessDataImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_SURF(className)\
protected:\
  className();\
  className(OdPrcSurfaceImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_TOPO(className)\
protected:\
  className();\
  className(OdPrcTopoItemImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_MATH(className)\
protected:\
  className();\
  className(OdPrcMathImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_CRV(className)\
protected:\
  className();\
  className(OdPrcCurveImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_COMPRESSED_CRV(className)\
protected:\
  className();\
  className(OdPrcCompressedCurveImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_COMPRESSED_FACE(className)\
protected:\
  className();\
  className(OdPrcCompressedFaceImpl *pImpl);\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(className);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRCRX_DECLARE(class)\
protected:\
  class();\
  ODRX_DECLARE_MEMBERS(class);

#define ODPRCRX_DECLARE_CRV(class)\
protected:\
  class();\
  class(OdPrcCurveImpl *pImpl);\
  ODRX_DECLARE_MEMBERS(class);

#define ODPRCRX_DECLARE_BASE(classname)\
  ODPRCRX_DECLARE(classname);\
  private:\
  friend class OdPrcSystemInternals;\
  friend class classname##Impl;\
  classname##Impl *m_pImpl;\
  public:

#define ODPRC_DECLARE_MEMBERS_NOTYPE(class)\
  ODPRCRX_DECLARE(class);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_NOTYPE_PRCBASE(class)\
  ODPRCRX_DECLARE(class);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);\
  protected:\
  class(OdPrcBaseImpl *pImpl);\
  public:

#define ODPRCRX_DECLARE_BASE_NOTYPE(classname)\
  ODPRC_DECLARE_MEMBERS_NOTYPE(classname);\
  private:\
  friend class OdPrcSystemInternals;\
  friend class classname##Impl;\
  classname##Impl *m_pImpl;\
  public:

#define ODPRC_DECLARE_MEMBERS_BASE_NOTYPE(classname)\
  private:\
  friend class OdPrcSystemInternals;\
  friend class classname##Impl;\
  classname##Impl *m_pImpl;\
  ODPRCRX_DECLARE(classname);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

#define ODPRC_DECLARE_MEMBERS_IMPL_NO_CONS(classname)\
  private:\
  friend class OdPrcSystemInternals;\
  friend class classname##Impl;\
  classname##Impl *m_pImpl;\
  public: \
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);


#define ODPRC_DECLARE_BASE_MEMBERS(classname)\
private:\
friend class OdPrcSystemInternals;\
friend class classname##Impl;\
classname##Impl *m_pImpl;\
protected:\
classname();\
public:\
  virtual OdUInt32 prcType() const;\
  ODRX_DECLARE_MEMBERS(classname);\
  virtual void  prcOut(OdPrcCompressedFiler *pStream);\
  virtual void  prcIn(OdPrcCompressedFiler *pStream);

class OdPrcCompressedFiler;
//DOM-IGNORE-END

/** \details
Enumerator implements types of orientation.
*/
enum Orientation
{
  /** Opposite orientation.*/
  kOpposite = 0,  
  /** Same orientation.*/
  kSame     = 1,      
  /** Unknown orientation.*/
  kUnknown  = 2    
};

#endif // _PRCCOMMON_INCLUDED_

