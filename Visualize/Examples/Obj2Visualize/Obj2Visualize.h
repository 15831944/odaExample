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


#ifndef OBJ2VISUALIZE_H
#define OBJ2VISUALIZE_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

// Visualize SDK
#include "TvVisualizeFiler.h"
#include "TvFactory.h"

#define STL_USING_MAP
#include "OdaSTL.h"

#include "OBJToolkit.h"

/** \details
Structure for collecting the statistic information for the group in obj file
*/
struct OdTvVisualizeObjFilerGroupInfo
{
  OdTvVisualizeObjFilerGroupInfo() : m_nShells(0), m_nFaces(0), m_nVertices(0), m_nPoints(0), m_nNurbs(0), m_nPolylines(0), m_nPointObjects(0), m_nBReps(0)
  {}

  OdUInt32 m_nShells;
  OdUInt32 m_nBReps;
  OdUInt32 m_nNurbs;
  OdUInt32 m_nPolylines;
  OdUInt32 m_nPointObjects;
  OdUInt32 m_nFaces;
  OdUInt32 m_nVertices;
  OdUInt32 m_nPoints;
};

/** \details
Map for storing the connection between group and it's info structure
*/
typedef std::map<OdUInt64, OdTvVisualizeObjFilerGroupInfo> GroupInfoMap;    //here we can NOT TO use the pointers since the number of groups is small and here it is not strongly think about the performance

/** \details
Map for storing the connection between group and it's Visualize representation
*/
typedef std::map<OdUInt64, OdTvEntityId> GroupTvMap;


void odrxSetMemberConstructor(OdRxClass* pClass, OdRxMemberCollectionConstructorPtr pc, void* data = 0);

namespace OBJToolkit {
  /** \details
  This class implements the properties of the obj loader
  */
  class OdTvVisualizeObjFilerProperties : public OdRxDispatchImpl<>
  {
    enum ParamFlags
    {
      kDirectlyFromFile           = 1,  // parse obj directly from file, without copy it in memory firstly
      kBrepFlipUVCoordinates      = 2,  // some applications UV coordinate system of BReps in OBJ is different from CS of ODA Platform
      kCalculateNormals           = 4,  // some .obj files don't have vertex normals
      kNeedCDATree                = 8,  // Need create CDA tree 
      kImportBrepAsBrep           = 16  // Need for import brep as OdTvBrepData
    };

  public:
    OdTvVisualizeObjFilerProperties();
    virtual ~OdTvVisualizeObjFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeObjFilerProperties);
    static OdRxDictionaryPtr createObject();

    void     setDefaultColor(OdIntPtr pDefColor);
    OdIntPtr getDefaultColor() const;

    void     setDirectlyFromFile(bool directlyFromFile) { SETBIT(m_flags, kDirectlyFromFile, directlyFromFile); }
    bool     getDirectlyFromFile() const { return GETBIT(m_flags, kDirectlyFromFile); }

    void     setBrepFlipUVCoordinates(bool brepFlipUVCoordinates) { SETBIT(m_flags, kBrepFlipUVCoordinates, brepFlipUVCoordinates); }
    bool     getBrepFlipUVCoordinates() const { return GETBIT(m_flags, kBrepFlipUVCoordinates); }

    void     setCalculateVertexNormals(bool calculateNormals) { SETBIT(m_flags, kCalculateNormals, calculateNormals); }
    bool     getCalculateVertexNormals() const { return GETBIT(m_flags, kCalculateNormals); }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void setImportBrepAsBrep(bool bSet) { SETBIT(m_flags, kImportBrepAsBrep, bSet); }
    bool getImportBrepAsBrep() const { return GETBIT(m_flags, kImportBrepAsBrep); }

    void      setDefaultUnits(OdUInt8 units) { m_defaultUnits = units; }
    OdUInt8   getDefaultUnits() const { return m_defaultUnits; }

  protected:

    ODCOLORREF  m_defaultColor;           // default color which is set to the entity
    OdUInt8     m_flags;                  // Different options
    OdTvMatrix  m_appendTransform;        // Transform for the append
    OdUInt8     m_defaultUnits;           // default units
  };
  typedef OdSmartPtr<OdTvVisualizeObjFilerProperties> OdTvVisualizeObjFilerPropertiesPtr;
}


/** \details
This class is rcs loader (to the Visualize database)
*/
class OdTvVisualizeObjFiler : public OdTvVisualizeFiler
{
  OdTvMaterialId importMaterial(OdTvDatabasePtr pDb, OBJToolkit::OdMtlPtr mtl) const;

public:

  OdTvVisualizeObjFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString& filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:

  struct LoadObjOptions
  {
    enum Type
    {
      kFilePath,
      kBuffer
    };

    OdString      m_filePath;
    OdStreamBuf*  m_pBuffer;
    Type          m_type;

    LoadObjOptions(const OdString& filePath) : m_filePath(filePath), m_type(kFilePath), m_pBuffer(NULL) {}
    LoadObjOptions(OdStreamBuf* pBuffer) : m_pBuffer(pBuffer), m_type(kBuffer) {}
  };

  bool importObj(OdTvDatabaseId& databaseId, OdTvModelId& tvModelId, const LoadObjOptions& opt, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  OdTvGeometryDataId createShell(OdTvEntityId& entityId, OdGePoint3dArray& vertices, OdGePoint2dArray& texCoo, OdGeVector3dArray& normals, OdUInt32Array& faces) const;
  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, const GroupInfoMap& groupInfos, const GroupTvMap& groupTvConnect) const;

  OBJToolkit::OdTvVisualizeObjFilerPropertiesPtr m_properties;
};


/** \details
This class is obj loader module implementation
*/
class OdTvVisualizeObjFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  static OdArray<OdRxMemberPtr> properties;

  static void constructOdObjDatabaseProperties(OdRxMemberCollectionBuilder& b, void*);

  void initApp();
  void uninitApp();

private:
  OdRxObjectPtr m_pModule;
};
typedef OdSmartPtr<OdTvVisualizeObjFilerModule> OdTvVisualizeObjFilerModulePtr;

OdArray<OdRxMemberPtr> OdTvVisualizeObjFilerModule::properties;

#include "TD_PackPop.h"

#endif // OBJ2VISUALIZE_H

