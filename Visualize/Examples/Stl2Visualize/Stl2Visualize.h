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


#ifndef STL2VISUALIZE_H
#define STL2VISUALIZE_H

#include "TD_PackPush.h"
#include "RxDispatchImpl.h"

#include "TvVisualizeFiler.h"

void odrxSetMemberConstructor(OdRxClass* pClass, OdRxMemberCollectionConstructorPtr pc, void* data = 0);

namespace STL2Visualize {
  /** \details
  This class implements the properties of the stl loader
  */
  class OdTvVisualizeStlFilerProperties : public OdRxDispatchImpl<>
  {
    enum PropertiesFlags
    {
      kFixNormals                 = 1,
      kUnifyDuplicatedVertices    = 2,
      kCalcNormalsAtVertices      = 4,
      kNeedCDATree                = 8  // Need create CDA tree. Since the number of properties is small, we always will collect properties
    };

  public:
    OdTvVisualizeStlFilerProperties();
    virtual ~OdTvVisualizeStlFilerProperties();

    ODRX_DECLARE_DYNAMIC_PROPERTY_MAP(OdTvVisualizeStlFilerProperties);
    static OdRxDictionaryPtr createObject();

    void     setDefaultColor(OdIntPtr pDefColor);
    OdIntPtr getDefaultColor() const;

    void setFixNormals(bool bFix) { SETBIT(m_flags, kFixNormals, bFix); }
    bool getFixNormals() const { return GETBIT(m_flags, kFixNormals); }

    void setUnifyDuplicatedVertices(bool bUnify) { SETBIT(m_flags, kUnifyDuplicatedVertices, bUnify); }
    bool getUnifyDuplicatedVertices() const { return GETBIT(m_flags, kUnifyDuplicatedVertices); }

    void setCalcNormalsAtVertices(bool bCalc) { SETBIT(m_flags, kCalcNormalsAtVertices, bCalc); }
    bool getCalcNormalsAtVertices() const { return GETBIT(m_flags, kCalcNormalsAtVertices); }

    void      setAppendTransform(OdIntPtr pTransform);
    OdIntPtr  getAppendTransform() const;

    void setNeedCDATree(bool bSet) { SETBIT(m_flags, kNeedCDATree, bSet); }
    bool getNeedCDATree() const { return GETBIT(m_flags, kNeedCDATree); }

    void      setDefaultUnits(OdUInt8 units) { m_defaultUnits = units; }
    OdUInt8   getDefaultUnits() const { return m_defaultUnits; }

  protected:

    ODCOLORREF m_defaultColor;    // default color which is set to the entity
    OdUInt8    m_flags;           // store set of options
    OdTvMatrix m_appendTransform; // Transform for the append
    OdUInt8    m_defaultUnits;    // default units
  };
  typedef OdSmartPtr<OdTvVisualizeStlFilerProperties> OdTvVisualizeStlFilerPropertiesPtr;
}

/** \details
This class is rcs loader (to the Visualize database)
*/
class OdTvVisualizeStlFiler : public OdTvVisualizeFiler
{
public:

  OdTvVisualizeStlFiler();

  virtual OdRxDictionaryPtr properties() { return m_properties; }
  virtual OdTvDatabaseId loadFrom(OdDbBaseDatabase* pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(OdStreamBuf* pBuffer,        OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId loadFrom(const OdString& filePath,    OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvDatabaseId generate(OdTvFilerTimeProfiling* pProfileRes = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdDbBaseDatabase*  pDatabase, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, OdStreamBuf*       pBuffer, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;
  virtual OdTvModelId    appendFrom(const OdTvDatabaseId& databaseId, const OdString&    filePath, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;

private:
  void createCommonDataAccessTree(OdTvDatabasePtr pTvDb, OdDbBaseDatabase *pDatabase, const OdString& strTreeName, OdTvEntityId entId, OdTvGeometryDataId geomId) const;

  struct LoadStlOptions
  {
    enum Type
    {
      kFilePath,
      kBuffer
    };

    OdString      m_filePath;
    OdStreamBuf* m_pBuffer;
    Type          m_type;

    LoadStlOptions(const OdString& filePath) : m_filePath(filePath), m_type(kFilePath), m_pBuffer(NULL) {}
    LoadStlOptions(OdStreamBuf* pBuffer) : m_pBuffer(pBuffer), m_type(kBuffer) {}
  };

  bool importStl(OdTvDatabaseId& databaseId, OdTvModelId& tvModelId, const LoadStlOptions& opt, OdTvFilerTimeProfiling* pProfileRes = NULL, OdTvResult* rc = NULL) const;


  STL2Visualize::OdTvVisualizeStlFilerPropertiesPtr m_properties;
};


/** \details
This class is stl loader module implementation
*/
class OdTvVisualizeStlFilerModule : public OdTvVisualizeFilerModule
{
public:
  virtual OdTvVisualizeFilerPtr getVisualizeFiler() const;

  static OdArray<OdRxMemberPtr> properties;
  static void constructOdStlImportProperties(OdRxMemberCollectionBuilder& b, void*);

  void initApp();
  void uninitApp();
private:
  OdRxObjectPtr m_pModule;
};
OdArray<OdRxMemberPtr> OdTvVisualizeStlFilerModule::properties;

#include "TD_PackPop.h"

#endif // STL2VISUALIZE_H

