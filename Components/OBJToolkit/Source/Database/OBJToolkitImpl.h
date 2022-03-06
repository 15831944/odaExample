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

#ifndef OBJTOOLKITIMPL_H
#define OBJTOOLKITIMPL_H

#include "OBJToolkit.h"

#include "SharedPtr.h"
#include "RxVariant.h"
#include "RxObjectImpl.h"
#include "OdString.h"
#include "OdDToStr.h"
#include "DbBaseHostAppServices.h"

#include "OBJParseRules.h"
#include "FileOps.h"

#define STL_USING_VECTOR
#define STL_USING_LIST
#define STL_USING_MAP
#include "OdaSTL.h"
#include "OdObjBrFile.h"
#include "OdObjBrBrep.h"
#include "OdObjBrComplex.h"
#include "OdObjBrShell.h"
#include "OdObjBrFace.h"
#include "OdObjBrCoedge.h"
#include "OdObjBrEdge.h"
#include "OdObjBrVertex.h"
#include "OdObjBrLoop.h"

namespace OBJToolkit {

#define _OD_MTL_PLAIN_WHITE OD_T("Default_Plain_White")

enum eMtlEntityType {
  eMtlMapKa           = 0
};

struct OdObjVertex
{
  double m_x;
  double m_y;
  double m_z;
  double m_w;

  OdObjVertex()
    : m_x(0.), m_y(0.), m_z(0.), m_w(1.) {};

  OdObjVertex(double x, double y, double z, double w = 1.)
    : m_x(x), m_y(y), m_z(z), m_w(w) {};
};

struct OdObjVertexPoint
{
  double m_u;
  double m_v;
  double m_w;

  OdObjVertexPoint()
    : m_u(0.), m_v(0.), m_w(1.) {};

  OdObjVertexPoint(double u, double v, double w = 1.)
    : m_u(u), m_v(v), m_w(w) {};
};

struct OdMtlOptionsImpl : public OdMtlOptions
{
public:
  ODRX_DECLARE_MEMBERS(OdMtlOptionsImpl);

  std::map<OdMtlOptVal, OdVariant> opts;

public:

  virtual   ~OdMtlOptionsImpl();
  bool      setOption(OdMtlOptVal optVal, OdString &sVal);
  OdVariant getOption(OdMtlOptVal optVal);

};
typedef OdSmartPtr<OdMtlOptionsImpl> OdMtlOptionsImplPtr;

/** \details
Class which implements material according to MTL format
*/
class OdMtlImpl : public OdMtl
{
public:
  ODRX_DECLARE_MEMBERS(OdMtlImpl);

  struct OdMtlFilter
  {
    eMtlDataType            m_type;
    double                  m_param1, m_param2, m_param3;
    OdString                m_mapFilename;
    double                  m_factor;

    OdMtlFilter()
      : m_type(eMtlUndef)
      , m_param1(1.)
      , m_param2(1.)
      , m_param3(1.)
      , m_factor(0.)
    {}
  };

  OdString                m_path;
  OdString                m_name;

  std::map<OdMtlTokens, OdVariant>            m_properties;
  std::map<OdMtlTokens, OdMtlOptionsImplPtr>  m_options;

  OdMtlFilter             m_ka; // Ambient reflectivity
  OdMtlFilter             m_kd; // Diffuse reflectivity
  OdMtlFilter             m_ks; // Specular reflectivity
  OdMtlFilter             m_tf; // Transmission filter

public:

  void            init(OdString &_name, OdString &_path);
  bool            setOptions(OdMtlTokens t, OdMtlOptions *pOptions);
  bool            setValue(OdMtlTokens t, void *);
  bool            setValue(OdMtlTokens t, OdMtlVal o, void *val);
  void            setName(OdString name);

  OdString        getName() const;
  OdString        getPath() const;

  double          getNs();
  bool            hasNs() { return m_properties.find(mtNs) != m_properties.end(); };

  OdUInt16        getSharpness();
  bool            hasSharpness() { return m_properties.find(mtSharpness) != m_properties.end(); };

  bool            getAntiAliasing();
  bool            hasAntiAliasing() { return m_properties.find(mtMapAat) != m_properties.end(); };

  double          getNi();
  bool            hasNi() { return m_properties.find(mtNi) != m_properties.end(); };

  double          getD();
  bool            hasD() { return m_properties.find(mtD) != m_properties.end(); };

  bool            getDHalo();
  bool            hasDHalo() { return m_properties.find(mtDHalo) != m_properties.end(); };

  double          getTr();
  bool            hasTr() { return m_properties.find(mtTr) != m_properties.end(); };

  double          getOpacity(); // calculation based on D and Tr
  bool            hasOpacity() { return hasD() || hasTr(); };

  OdUInt8         getIllumination();
  bool            hasIllumination() { return m_properties.find(mtIllum) != m_properties.end(); };;

  OdMtlOptionsPtr getOptions(OdMtlTokens optionsGroup);

  eMtlDataType    getAmbientReflectivity(double &Ka1, double &Ka2, double &Ka3, OdString &mapKaRflFilename, double &KaFactor);
  eMtlDataType    getDiffuseReflectivity(double &Kd1, double &Kd2, double &Kd3, OdString &map_Kd_rfl_filename, double &KdFactor);
  eMtlDataType    getSpecularReflectivity(double &Ks1, double &Ks2, double &Ks3, OdString &mapKsRflFilename, double &KsFactor);
  eMtlDataType    getTransmissionFilter(double &Tf1, double &Tf2, double &Tf3, OdString &mapTfRflFilename, double &TfFactor);

};
typedef OdSmartPtr<OdMtlImpl> OdMtlImplPtr;

  /** \details
Class which implements amterials (MTL) of OBJ file
*/
class OdMtlDbImpl : public OdMtlDb
{
public:
  ODRX_DECLARE_MEMBERS(OdMtlDbImpl);

  OdString                          m_sPath;
  std::map<OdString, OdMtlImplPtr>  m_materials;
  OdMtlImplPtr                      m_pMtlCur;
  std::map<OdDbStub*, OdMtlPtr>     m_mapMaterials;

public:

  OdMtlDbImpl();

  void              setRasterImage(OdGiRasterImage *pImg);
  void              setPath(OdString &path);
  OdMtlImplPtr      addMaterial(OdString &material_name, OdString &material_path);
  OdUInt32          appendMaterials(OdMtlDbImpl *pMtlDB);
  OdMtlPtr          createMaterial(OdString &sMaterialName);

  void              materialMapClear();
  void              materialMapPut(OdDbStub* pMaterialStub, OdMtlImplPtr pMtl);
  OdMtlPtr          materialMapFind(OdDbStub* pMaterialStub);
  
public: // OdMtlDb interface

  virtual OdUInt32  getMaterialsCount() const;
  virtual OdMtlPtr  getMaterial(OdString &sMaterialName, bool createIfNotExists = false);

  virtual OdMtlIteratorPtr createMtlIterator();

};
typedef OdSmartPtr<OdMtlDbImpl> OdMtlDbImplPtr;

class OBJTOOLKIT_EXPORT OdMtlIteratorImpl : public OdMtlIterator
{

  std::map<OdString, OdMtlImplPtr> m_mapCopy;
  std::map<OdString, OdMtlImplPtr>::const_iterator m_it;

public:
  ODRX_DECLARE_MEMBERS(OdMtlIteratorImpl);

  virtual void start();
  virtual bool done() const;
  virtual const OdString& item() const;
  virtual void step();
  virtual OdMtlPtr element();

  friend class OdMtlDbImpl;

};
typedef OdSmartPtr<OdMtlIteratorImpl> OdMtlIteratorImplPtr;

class OdObjGroupImpl;
typedef OdSmartPtr<OdObjGroupImpl> OdObjGroupImplPtr;

/** \details
Class which implements OBJ file database
*/
class OdObjDbImpl : public OdObjDb
{
public:
  ODRX_DECLARE_MEMBERS(OdObjDbImpl);

  OdMtlDbImplPtr            m_pMtlDb;

  std::vector<OdObjVertex*> m_vs;     // Vertexes
  OdGePoint2dArray          m_vts;    // Texture vertexes
  OdGeVector3dArray         m_vns;    // Vertex/face normals
  std::vector<OdObjVertexPoint*> m_vps; // Point in the parameter space of surface.
  std::vector<OdObjCurve2D*> m_curves2d; // 2D curves 

  eObjCurveType             m_currentCsType; // Type curve/surfaces
  bool                      m_currentRatCstype; // Rational curve/surfaces
  OdUInt32                  m_currentDegU; // Degree curves/surfaces
  OdUInt32                  m_currentDegV; // Degv surfaces

  OdObjGeomEntity *m_CurrentEnity;
  OdObjCurve2D *m_CurrentCurv2d;

  OdArray< OdObjGroupImplPtr >  m_groups; // Groups array, each group represents separated mesh
  OdObjGroupImplPtr         m_gCurrent;

  void                      putVS(OdUInt32 nVS, const OdGePoint3d *vs, OdUInt32Array &indices, OdInt32 *inds = NULL);
  void                      putVWS(OdUInt32 nVS, const OdGePoint3d *vs, double *weights, OdUInt32Array &inds);
  void                      putVTS(OdUInt32 nVTS, const OdGePoint2d *vts, OdUInt32Array &inds);
  void                      putVNS(OdUInt32 nVNS, const OdGeVector3d *vns, OdUInt32Array &inds);
  void                      putFace(const OdGePoint3dArray &pointsV, const OdGePoint2dArray &pointsVT);

public:

  OdObjDbImpl();
  ~OdObjDbImpl();

  void addGroup(OdObjGroupImplPtr pGroup);

public:

  // Interface implementations
  OdMtlDbPtr          getMtlDb();

  bool                  isEmpty();
  OdObjGroupIteratorPtr createGroupsIterator();
  OdResult              getGroupShell(
    OdObjGroupPtr     pGroup,
    OdGePoint3dArray  &vertices,
    OdGePoint2dArray  &texCoo,
    OdGeVector3dArray &normals,
    OdUInt32Array     &faces,
    OdArray< OdMtlPtr > &faceMaterials
  );
  OdResult              getFaceMaterials(OdObjGroupPtr pGroup, OdArray< OdMtlPtr > &faceMaterials);

  OdGeNurbCurve2d* buildNurbCurve2d(const OdObjCurve2D *pCurve2d, bool isPeriodic);
  OdGeNurbSurface* buildNurbSurface(const OdObjSurface *pSurface);
  OdResult getBrep(OdBrBrep &brep, const OdObjSurface *pSurface);

  bool getVS(OdGePoint3dArray &vs, const OdUInt32Array &inds);
  bool getVTS(OdGePoint2dArray &vts, const OdUInt32Array &inds);
  bool getVNS(OdGeVector3dArray &vns, const OdUInt32Array &inds);
  bool getVPS(OdGePoint3dArray &vps, const OdUInt32Array &inds);
  void calculateVertexNormals(OdObjGroupPtr pGroup);

};
typedef OdSmartPtr<OdObjDbImpl> OdObjDbImplPtr;

class OdObjGroupImpl;
class OdObjEntityIteratorImpl : public OdObjEntityIterator
{
public:
  ODRX_DECLARE_MEMBERS(OdObjEntityIteratorImpl);

  OdObjGroupImplPtr m_pGroup;
  OdUInt32          m_entityInd;

public:

  virtual void start(bool skipFace = true);
  virtual bool done() const;
  virtual OdUInt32 item() const;
  virtual void step(bool skipFace = true);
  virtual bool seek(const OdUInt32& entityIndex);
  virtual const OdObjGeomEntity* element();

};
typedef OdSmartPtr<OdObjEntityIteratorImpl> OdObjEntityIteratorImplPtr;

class OdObjGroupImpl : public OdObjGroup
{
private:
  OdObjDbImpl* m_pObjDb;

public:
  ODRX_DECLARE_MEMBERS(OdObjGroupImpl);

  OdString                    m_sGroupName;
  //std::vector< OdObjFace* >   m_faces;
  OdArray< OdObjGeomEntity* > m_entities;

public:

  ~OdObjGroupImpl()
  {
    unsigned int s = m_entities.size();
    for (unsigned int i = 0; i < s; ++i)
      delete m_entities.at(i);
  }

  void setDatabase(OdObjDbImpl* pObjDb)
  {
    m_pObjDb = pObjDb;
  }

  unsigned int addEntity(OdObjGeomEntity *entity)
  {
    return m_entities.append(entity);
  };

  void addFace(OdObjFace *face)
  {
    //m_faces.push_back(face);
    m_entities.append(face);
  };

  void setGroupName(const OdString &sGroupName)
  {
    m_sGroupName = sGroupName;
  };

  //
  // Interface implementation
  //

  bool isEmpty()
  {
    return m_entities.size() == 0;
  }

  OdString getGroupName()
  {
    return m_sGroupName;
  };

  OdObjEntityIteratorPtr createEntitiesIterator()
  {
    OdObjEntityIteratorImplPtr pIt = OdObjEntityIteratorImpl::createObject();
    pIt->m_pGroup = this;
    pIt->start();
    return pIt;
  };

  OdResult getGroupShell(OdGePoint3dArray  &vertices, OdGePoint2dArray  &texCoo,
    OdGeVector3dArray &normals, OdUInt32Array &faces, OdArray< OdMtlPtr > &faceMaterials);

  OdResult getFaceMaterials(OdArray< OdMtlPtr > &faceMaterials);
};
typedef OdSmartPtr<OdObjGroupImpl> OdObjGroupImplPtr;

class OdObjGroupIteratorImpl : public OdObjGroupIterator
{
  unsigned int    m_groupInd;
  OdObjDbImpl*  m_pObjDb;

  bool            setObjDb(OdObjDbImpl* pObjDb)
  {
    m_pObjDb = pObjDb;
  }

  friend class OdObjDbImpl;

public:
  ODRX_DECLARE_MEMBERS(OdObjGroupIteratorImpl);

  virtual void start(bool atBeginning = true/*, bool skipErased = true*/);
  bool done() const;
  virtual OdUInt32 item() const;
  OdObjGroupPtr element();
  void step(bool forward = true/*, bool skipErased = true*/);
  bool seek(const OdUInt32& groupIndex);

};
typedef OdSmartPtr<OdObjGroupIteratorImpl> OdObjGroupIteratorImplPtr;

/** \details
Class which implements OBJ file import
*/
class OdObjImportImpl : public OdObjImport,
                        public OdObjFileReader
{
  OdObjDbImplPtr m_pObjDb;

  OdObjImportOptions *m_pOptions;

  OdString    m_sPathFile;
  OdString    m_sPath; // This is needed for MTL files and textures loading
  OdString    m_sFileName;

  OdUInt32    parseVertex(char* &line);
  OdUInt32    parseVertexT(char* &line);
  OdUInt32    parseVertexP(char* &line);
  OdUInt32    parseNormal(char* &line);
  OdUInt32    parsePoint(char* &str);
  OdUInt32    parseLine(char* &line);
  OdUInt32    parseFace(char* &line);
  OdUInt32    parseMtlLib(OdString &line);

  bool        parseUseMtl(OdString &line);
  bool        parseCstype(char* &line);
  bool        parseDegree(char* &line);
  bool        parseCurve(char* &line);
  bool        parseCurve2(char* &line);
  bool        parseSurface(char* &line);
  bool        parseParm(char* &line);
  void        parseTrimHole(char* &line, OdObjTokens typeLoop);
  bool        parseEnd(char* &line);

  eObjCurveType    getCstypeIdByName(OdAnsiString line);

public:
  ODRX_DECLARE_MEMBERS(OdObjImportImpl);

  OdObjImportImpl();
  ~OdObjImportImpl();

  OdResult      importFile(const OdString &fileName, OdObjImportOptions *options = NULL);
  OdResult      importFile(const OdStreamBufPtr &pStreamBuf, OdObjImportOptions *options = NULL);

  OdObjDbPtr    getObjDb();
  OdMtlDbPtr    getMtlDb();
  
  OdObjImportOptions * getObjImportOptions();

  OdString      getDrawingName();
  unsigned int  getGroupsCount() const;
  OdResult      getGroupName(OdUInt32 nGroupInd, OdString &sGroupName);

};

/** \details
Class which implements OBJ file export
*/
class OdObjExportImpl : public OdObjExport
{
  OdObjDbImplPtr          m_pObjDb;

  OdString                m_sPathFile;
  OdString                m_sPath;
  OdString                m_sFileName;

  OdStreamBufPtr          m_pStreamBuf;

  OdMtlPtr                m_materialCurrent;

  unsigned int            m_vIndCounter;
  std::map<unsigned int, unsigned int> m_mapVInd;

  unsigned int            m_vTIndCounter;
  std::map<unsigned int, unsigned int> m_mapVTInd;

  unsigned int            m_vNIndCounter;
  std::map<unsigned int, unsigned int> m_mapVNInd;

  void                    exportGroup(OdObjGroupImplPtr pGroup);
  void                    exportCurve(OdObjGeomEntity** &pGeomEntityCell);
  void                    exportSurface(OdObjGeomEntity** &pGeomEntityCell);

public:
  ODRX_DECLARE_MEMBERS(OdObjExportImpl);

  OdObjExportImpl();

  void        setObjDb(OdObjDbPtr pObjDb);
  OdObjDbPtr  getObjDb();
  OdResult    exportFile(const OdString &fileName, const OdString &applicationComment);
  OdResult    exportFile(const OdStreamBufPtr &pStreamBuf, const OdString &applicationComment);

};

/** \details
Class which implements MTL file import and creates an array of materials structures
*/
class OdMtlImportImpl : public OdMtlImport,
                        public OdObjFileReader
{
  OdMtlDbImplPtr  m_pMtlDb;

  OdString        m_sMTLLibraryName;
  OdString        m_sPath;
  OdString        m_sPathFile;

  bool            parseDissolve(OdString &sp);
  bool            parseTriade(OdMtlTokens t, OdString &sP);
  bool            parseMapOptions(OdMtlTokens t, OdString &sP);

public:
  ODRX_DECLARE_MEMBERS(OdMtlImportImpl);

  OdResult        importFile(const OdString &fileName);
  OdResult        importFile(const OdStreamBufPtr &pStreamBuf);

  OdMtlDbPtr      getMtlDb();

};

/** \details
Class which implements MTL file export from array of materials structures
*/
class OdMtlExportImpl : public OdMtlExport
{
  OdMtlDbImplPtr  m_pMtlDb;

  OdString        m_sPathFile;
  OdString        m_sPath;
  OdString        m_sFileName;

  OdStreamBufPtr  m_pStreamBuf;

  void            exportFilter(OdMtlTokens t, const OdMtlImpl::OdMtlFilter &filter, OdAnsiString &str);
  void            exportOptions(OdMtlTokens t, OdMtlOptionsImplPtr opts, OdAnsiString &str);
  void            exportMaterial(OdMtlImplPtr mtl);

  bool            exportTextureFile(OdDbBaseDatabase *pDb, OdDbBaseHostAppServices *pAppServices, OdVariant &vtStr, bool bKeepNearObj);
  //bool            exportRasterImage(const OdGiRasterImage *pImg, const OdString & sPath, bool keepNearObj);

public:
  ODRX_DECLARE_MEMBERS(OdMtlExportImpl);

  OdResult        exportFile(const OdString &fileName, const OdString &applicationComment);
  OdResult        exportFile(const OdStreamBufPtr &pStreamBuf, const OdString &applicationComment);
  void            updateTexturesPaths(OdDbBaseDatabase *pDb, OdDbBaseHostAppServices *pAppServices, const OdString & sPath, bool bKeepNearObj = true);
  //void            updateRasterImagePath(const OdGiRasterImage *pImg, const OdString & sPath, bool keepNearObj);

  void            setMtlDb(OdMtlDbPtr pMtlDb);
  OdMtlDbPtr      getMtlDb();
  OdString        getFileName();
};
typedef OdSmartPtr<OdMtlExportImpl> OdMtlExportImplPtr;

OdResult exportObj(OdDbBaseDatabase *pDb, const OdGiDrawable *pEntity, const OdString &fileName, OdObjExportOptions *options);
OdResult exportObj(OdDbBaseDatabase *pDb, const OdString &fileName, OdObjExportOptions *options);

class OdObjToolkitModuleImpl : public OdObjToolkitModule
{
public:

  virtual void initApp();
  virtual void uninitApp();

  virtual OdObjImportPtr createObjImporter()
  {
    return OdObjImport::createObject();
  }

  virtual OdObjExportPtr createObjExporter()
  {
    return OdObjExport::createObject();
  }

  virtual OdMtlImportPtr createMtlImporter()
  {
    return OdMtlImport::createObject();
  }

  virtual OdMtlExportPtr createMtlExporter()
  {
    return OdMtlExportPtr();
  }

  virtual OdResult exportObj(OdDbBaseDatabase *pDb, const OdGiDrawable *pEntity, const OdString &fileName, OdObjExportOptions *options)
  {
    try
    {
      if (odrxSystemServices()->accessFile(fileName, 0) && !odrxSystemServices()->accessFile(fileName, Oda::kFileWrite))
        return eFileAccessErr;
      return OBJToolkit::exportObj(pDb, pEntity, fileName, options);
    }
    catch (...)
    {
      return eFileAccessErr;
    }
  }

  virtual OdResult exportObj(OdDbBaseDatabase *pDb, const OdString &fileName, OdObjExportOptions *options)
  {
    try
    {
      if (odrxSystemServices()->accessFile(fileName, 0) && !odrxSystemServices()->accessFile(fileName, Oda::kFileWrite))
        return eFileAccessErr;
      return OBJToolkit::exportObj(pDb, fileName, options);
    }
    catch (...)
    {
      return eFileAccessErr;
    }
  }

  virtual void updateTexturesPaths(OdMtlDbPtr pMtlDb, OdDbBaseDatabase *pDb, const OdString & sPath, OdObjExportOptions *options = NULL)
  {
    if (pMtlDb.isNull())
      return;

    OdDbBaseDatabasePEPtr pDbPE(pDb);
    OdDbBaseHostAppServices *pAppServices = pDbPE->appServices(pDb);

    OdMtlExportImplPtr pMtlExporter = OdMtlExportImpl::createObject();
    pMtlExporter->setMtlDb(pMtlDb);
    pMtlExporter->updateTexturesPaths(pDb, pAppServices, sPath, options ? options->m_keepTexturesNearObj : true);
  }

};

typedef OdSmartPtr<OdObjToolkitModuleImpl> OdObjToolkitModuleImplPtr;

}

#endif // OBJTOOLKITIMPL_H
