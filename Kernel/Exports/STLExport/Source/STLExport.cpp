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

#include "OdaCommon.h"
#include "STLExport.h"
#include "OdError.h"
#include "Gi/GiFastExtCalc.h"
#include "Gi/GiTransformed.h"
#include "Gi/GiDummyGeometry.h"
#include "Gi/GiGeometrySimplifier.h"
#include "GiDefaultContext.h"
#include "StaticRxObject.h"
#include "MemoryStream.h"
#include "OdPlatformStreamer.h"
#include "Gs/GsBaseInclude.h"
#include "RxObjectImpl.h"
#include "RxDynamicModule.h"
#include "OdDToStr.h"
#include "Ge/GeGbl.h"

#define STL_USING_LIMITS
#define STL_USING_VECTOR
#define STL_USING_MAP
#define STL_USING_ALGORITHM
#define STL_USING_FUNCTIONAL
#include "OdaSTL.h"

// http://www.ennex.com/~fabbers/StL.asp
// http://en.wikipedia.org/wiki/STL_(file_format)

namespace TD_STL_EXPORT
{
  static void rotateViewForAecNeeds(OdGsViewPtr pNewView)
  {
    pNewView->setView(OdGePoint3d::kOrigin, OdGePoint3d(0,1,0), OdGeVector3d::kXAxis, 1, 1);
  }

  class StubVectorizeDevice : public OdGsBaseVectorizeDevice
  {
  protected:
    ODRX_USING_HEAP_OPERATORS(OdGsBaseVectorizeDevice);
  public:
    StubVectorizeDevice() { }
    ~StubVectorizeDevice() { }
  };

  class StubVectorizeView : public OdGsBaseVectorizeViewDef, public OdGiGeometrySimplifier
  {
  protected:
    float m_epsilon;
    const OdStlExportParams *m_StlParams;
  public:
    StubVectorizeView() : m_epsilon(0.001f), m_StlParams(NULL) { }
    ~StubVectorizeView() { }

    void setParams(const OdStlExportParams &params)
    {
      m_StlParams = &params;
    }

    virtual double deviation(const OdGiDeviationType deviationType, const OdGePoint3d& pointOnCurve) const
    {
      return m_StlParams->deviation();
    }

    void setEpsilon(float e)
    {
      m_epsilon = e;
    }
    
    StubVectorizeDevice* device() { return static_cast<StubVectorizeDevice*>(OdGsBaseVectorizeView::device()); }

    void loadViewport() { }
    void beginViewVectorization()
    {
      OdGsBaseVectorizer::beginViewVectorization();

      setEyeToOutputTransform( getEyeToWorldTransform() );

      OdGiGeometrySimplifier::setDrawContext(OdGsBaseVectorizer::drawContext());
      output().setDestGeometry((OdGiGeometrySimplifier&)*this);
    }
    void endViewVectorization()
    {
      OdGsBaseVectorizer::endViewVectorization();
    }
  };

  class OdSTLOutBase : public StubVectorizeView
  {
  public:
    void setStream(OdStreamBuf *pOutStream)
    {
      m_pOutStream = pOutStream;
    }    

    void beginViewVectorization()
    {
      StubVectorizeView::beginViewVectorization();
      start();
    }

    void endViewVectorization()
    {
      finish();
      StubVectorizeView::endViewVectorization();
    }

  protected:
    OdStreamBuf *m_pOutStream;    

    struct Od3Float
    {
      float x;
      float y;
      float z;

      Od3Float()
        : x(0.), y(0.), z(0.)
      { }

      Od3Float(float a, float b, float c)
        : x(a), y(b), z(c)
      { }

      Od3Float const operator- (const Od3Float other) const
      {
        return Od3Float(x - other.x, y - other.y, z - other.z);
      }

      Od3Float operator- (const Od3Float other)
      {
        return Od3Float(x - other.x, y - other.y, z - other.z);
      }

      void normalize()
      {
        float len = sqrt(x*x + y*y + z*z);
        x /= len;
        y /= len;
        z /= len;
      }

      bool same(const Od3Float other, const float e) const
      {
        return  fabs(x - other.x) <= e &&
                fabs(y - other.y) <= e &&
                fabs(z - other.z) <= e;
      }

      float dotProduct(Od3Float other)
      {
          return (x * other.x) + (y * other.y) + (z * other.z);
      }

      Od3Float crossProduct(Od3Float other)
      {
          return Od3Float((y * other.z) - (z * other.y), (z * other.x) - (x * other.z), (x * other.y) - (y * other.x));
      }

      void set(const OdGePoint3d &p)
      {
        x = (float)p.x;
        y = (float)p.y;
        z = (float)p.z;
      }

      void set(const OdGeVector3d &p)
      {
        if (p.isZeroLength())
        {
          x = y = z = 0;
        }
        else
        {
          OdGeVector3d n = p.normal();
          x = (float)n.x;
          y = (float)n.y;
          z = (float)n.z;
        }
      }
    };

    struct TriangleInfo
    {
      Od3Float normal;
      Od3Float p1;
      Od3Float p2;
      Od3Float p3;
      OdCmEntityColor color;

      bool collinear(float tol)
      {
        return p1.same(p2, tol) || p1.same(p3, tol) || p3.same(p2, tol);
      }
    };

    OdArray<TriangleInfo> m_Data;
    Od3Float              m_LowPoint;

    virtual void triangleOut(const TriangleInfo &cell) = 0;
    virtual void addTriangle(const TriangleInfo &cell)
    {
      compareMin(m_LowPoint, cell.p1);
      compareMin(m_LowPoint, cell.p2);
      compareMin(m_LowPoint, cell.p3);

      m_Data.append(cell);
    }

    // method from OdGiGeometrySimplifier
    virtual void polylineOut(OdInt32 , const OdGePoint3d* ) {}
    virtual void polygonOut( OdInt32 num, const OdGePoint3d* pPnts, const OdGeVector3d* pNormal) 
    {
      if (num != 3)
      {
        OdGiGeometrySimplifier::polygonOut(num, pPnts, pNormal);
        return;
      }

      TriangleInfo cell;

      cell.p1.set(pPnts[0]);
      cell.p2.set(pPnts[1]);
      cell.p3.set(pPnts[2]);

      if (pNormal)
      {
        cell.normal.set(*pNormal);
      }

      if (!m_StlParams->correctSolid() || !cell.collinear(m_epsilon))
      {
        cell.color = effectiveTraits().trueColor();
        addTriangle(cell);
      }
    }

    static const float MIN_FLOAT;

  public:
    OdSTLOutBase()
      : m_pOutStream(0), m_LowPoint(MIN_FLOAT, MIN_FLOAT, MIN_FLOAT)
    {
      
    }

    virtual void start() = 0;

    virtual void finish()
    {
      bool bX = m_LowPoint.x > 0;
      bool bY = m_LowPoint.y > 0;
      bool bZ = m_LowPoint.z > 0;

      checkSolid();
      OdArray<TriangleInfo>::iterator pIt = m_Data.begin();
      OdArray<TriangleInfo>::iterator pEnd = m_Data.end();
      
      if (!m_StlParams->positiveOctant() || bX && bY && bZ)
      {
        while(pIt != pEnd)
        {
          triangleOut(*pIt);
          ++pIt;
        }
      }
      else
      {
        m_LowPoint.x -= MIN_FLOAT;
        m_LowPoint.y -= MIN_FLOAT;
        m_LowPoint.z -= MIN_FLOAT;

        while(pIt != pEnd)
        {
          if (!bX) {pIt->p1.x -= m_LowPoint.x; pIt->p2.x -= m_LowPoint.x; pIt->p3.x -= m_LowPoint.x;}
          if (!bY) {pIt->p1.y -= m_LowPoint.y; pIt->p2.y -= m_LowPoint.y; pIt->p3.y -= m_LowPoint.y;}
          if (!bZ) {pIt->p1.z -= m_LowPoint.z; pIt->p2.z -= m_LowPoint.z; pIt->p3.z -= m_LowPoint.z;}
          triangleOut(*pIt);
          ++pIt;
        }
      }
    }
        	
  protected:
    void checkSolid()
    {      
      if (!m_StlParams->correctSolid())
        return;

      //prepare data             
      OdGePoint3dArray points;
      points.resize(m_Data.size() * 3);
      OdGePoint3dArray::iterator pPoint = points.begin();
      OdArray<TriangleInfo>::iterator pIt = m_Data.begin();
      OdArray<TriangleInfo>::iterator pEnd = m_Data.end();
      while(pIt != pEnd)
      {
        pPoint->set(pIt->p1.x, pIt->p1.y, pIt->p1.z); ++pPoint;
        pPoint->set(pIt->p2.x, pIt->p2.y, pIt->p2.z); ++pPoint;
        pPoint->set(pIt->p3.x, pIt->p3.y, pIt->p3.z); ++pPoint;
        ++pIt;
      }

      double vol;
      OdGePoint3d base(m_LowPoint.x, m_LowPoint.y, m_LowPoint.z);
      OdGeError e = geSolidSignedVolume(points, vol, &base);
      if (e == OdGe::kOk && vol < 0)
      {
        bool isValid;
        e = geValidSolid(points, isValid, m_epsilon);
        if (e == OdGe::kOk && isValid)
        {
          reorderTriangles();
        }
      }
    }

    void compareMin(Od3Float &target, const Od3Float source)
    {
      if (target.x > source.x) target.x = source.x;
      if (target.y > source.y) target.y = source.y;
      if (target.z > source.z) target.z = source.z;
    }

    void compareMax(Od3Float &target, const Od3Float source)
    {
      if (target.x < source.x) target.x = source.x;
      if (target.y < source.y) target.y = source.y;
      if (target.z < source.z) target.z = source.z;
    }

    void reorderTriangles()
    {
      OdArray<TriangleInfo>::iterator pIt = m_Data.begin();
      OdArray<TriangleInfo>::iterator pEnd = m_Data.end();
      while(pIt != pEnd)
      {
        Od3Float dummy = pIt->p2;
        pIt->p2 = pIt->p3;
        pIt->p3 = dummy;

        if (!(pIt->normal.x == 0 && pIt->normal.y == 0 && pIt->normal.z == 0))
        {
          //to recalculate normal or just inverse it?
          pIt->normal.x *= -1;
          pIt->normal.y *= -1;
          pIt->normal.z *= -1;
          /*
          dummy = pIt->p2 - pIt->p1;
          pIt->normal = dummy.crossProduct(pIt->p3 - pIt->p2);
          pIt->normal.normalize();
          */
        }
        ++pIt;
      }
    }

  };

  const float OdSTLOutBase::MIN_FLOAT = 0.01f;

  double dfix(double d)
  {
    return OdZero(d) ? 0. : d;
  }

  class OdSTLOutText : public OdSTLOutBase
  {
  protected:

    virtual void triangleOut(const TriangleInfo &cell)
    {
      OdAnsiString str;
      str.format("   facet normal %ls %ls %ls\x0D\x0A", odDToStr(dfix(cell.normal.x), 'f', 6).c_str(), odDToStr(dfix(cell.normal.y), 'f', 6).c_str(), odDToStr(dfix(cell.normal.z), 'f', 6).c_str());
      m_pOutStream->putBytes(str.c_str(), str.getLength());

      str = "      outer loop\x0D\x0A";
      m_pOutStream->putBytes(str.c_str(), str.getLength());

      str.format("         vertex %ls %ls %ls\x0D\x0A", odDToStr(dfix(cell.p1.x), 'f', 6).c_str(), odDToStr(dfix(cell.p1.y), 'f', 6).c_str(), odDToStr(dfix(cell.p1.z), 'f', 6).c_str());
      m_pOutStream->putBytes(str.c_str(), str.getLength());
      str.format("         vertex %ls %ls %ls\x0D\x0A", odDToStr(dfix(cell.p2.x), 'f', 6).c_str(), odDToStr(dfix(cell.p2.y), 'f', 6).c_str(), odDToStr(dfix(cell.p2.z), 'f', 6).c_str());
      m_pOutStream->putBytes(str.c_str(), str.getLength());
      str.format("         vertex %ls %ls %ls\x0D\x0A", odDToStr(dfix(cell.p3.x), 'f', 6).c_str(), odDToStr(dfix(cell.p3.y), 'f', 6).c_str(), odDToStr(dfix(cell.p3.z), 'f', 6).c_str());
      m_pOutStream->putBytes(str.c_str(), str.getLength());

      str = "      endloop\x0D\x0A";
      m_pOutStream->putBytes(str.c_str(), str.getLength());
      str = "   endfacet\x0D\x0A";
      m_pOutStream->putBytes(str.c_str(), str.getLength());
    }

  public:
    OdSTLOutText()
      : OdSTLOutBase()
    {
    }

    virtual void start() 
    {
      OdAnsiString str = "solid ODA StlExport\x0D\x0A";
      m_pOutStream->putBytes(str.c_str(), str.getLength());
    }

    virtual void finish() 
    {
      OdSTLOutBase::finish();
      OdAnsiString str = "endsolid ODA StlExport\x0D\x0A";
      m_pOutStream->putBytes(str.c_str(), str.getLength());
    }
  };

  class OdSTLOutBinary : public OdSTLOutBase
  {
  protected:
    virtual void triangleOut(const TriangleInfo &cell)
    {
      m_pOutStream->putBytes(&cell.normal, 12);
      m_pOutStream->putBytes(&cell.p1, 12);
      m_pOutStream->putBytes(&cell.p2, 12);
      m_pOutStream->putBytes(&cell.p3, 12);

      if (!m_StlParams->useColors())
      {
        OdPlatformStreamer::wrInt16(*m_pOutStream, 0);
      }
      else
      {
        // Color support
        const OdCmEntityColor &color = cell.color;
        if (color.isByColor() || color.isByACI())
        {
          double r, g, b;

          if (color.isByACI())
          {
            OdUInt16 index = color.colorIndex();

            if (m_StlParams->palette())
            {
              ODCOLORREF colorRef = m_StlParams->palette()[index];

              r = ODGETRED(colorRef);
              g = ODGETGREEN(colorRef);
              b = ODGETBLUE(colorRef);
            }
            else
            {
              OdUInt32 rgb = OdCmEntityColor::lookUpRGB(index);

              r = (double)OdCmEntityColor::red(&rgb);
              g = (double)OdCmEntityColor::green(&rgb);
              b = (double)OdCmEntityColor::blue(&rgb);
            }
          }
          else
          {
            r = color.red();
            g = color.green();
            b = color.blue();
          }

          OdUInt8 ir = (OdUInt8)(r / 255. * 31.);
          OdUInt8 ig = (OdUInt8)(g / 255. * 31.);
          OdUInt8 ib = (OdUInt8)(b / 255. * 31.);

          OdInt16 output = (1 << 15) + (ir << 10) + (ig << 5) + ib;
          OdPlatformStreamer::wrInt16(*m_pOutStream, output);
        }
        else
        {
          OdPlatformStreamer::wrInt16(*m_pOutStream, 0);
        }
      }
    }

  public:
    OdSTLOutBinary( )
    {
    }

    virtual void start() 
    {
      OdAnsiString str(' ', 80);
      m_pOutStream->putBytes(str.c_str(), 80);
    }

    virtual void finish() 
    {
      OdPlatformStreamer::wrInt32(*m_pOutStream, m_Data.size());
      OdSTLOutBase::finish();
    }
  };

  class StubDeviceModuleText : public OdGsBaseModule
  {
    OdStreamBuf *m_pOutStream;
  public:
    void setStream(OdStreamBuf *pOutStream) 
    {
      m_pOutStream = pOutStream;
    }
  protected:
    OdSmartPtr<OdGsBaseVectorizeDevice> createDeviceObject()
    {
      return OdRxObjectImpl<StubVectorizeDevice, OdGsBaseVectorizeDevice>::createObject();
    }
    OdSmartPtr<OdGsViewImpl> createViewObject()
    {
      OdSmartPtr<OdGsViewImpl> pP = OdRxObjectImpl<OdSTLOutText, OdGsViewImpl>::createObject();
      ((OdSTLOutText*)pP.get())->setStream(m_pOutStream);
      return pP;
    }
    OdSmartPtr<OdGsBaseVectorizeDevice> createBitmapDeviceObject()
    {
      return OdSmartPtr<OdGsBaseVectorizeDevice>();
    }
    OdSmartPtr<OdGsViewImpl> createBitmapViewObject()
    {
      return OdSmartPtr<OdGsViewImpl>();
    }
  };

  class StubDeviceModuleBinary : public OdGsBaseModule
  {
    OdStreamBuf *m_pOutStream;
  public:
    void setStream(OdStreamBuf *pOutStream) 
    {
      m_pOutStream = pOutStream;
    }
  protected:
    OdSmartPtr<OdGsBaseVectorizeDevice> createDeviceObject()
    {
      return OdRxObjectImpl<StubVectorizeDevice, OdGsBaseVectorizeDevice>::createObject();
    }
    OdSmartPtr<OdGsViewImpl> createViewObject()
    {
      OdSmartPtr<OdGsViewImpl> pP = OdRxObjectImpl<OdSTLOutBinary, OdGsViewImpl>::createObject();
      ((OdSTLOutBinary*)pP.get())->setStream(m_pOutStream);
      return pP;
    }
    OdSmartPtr<OdGsBaseVectorizeDevice> createBitmapDeviceObject()
    {
      return OdSmartPtr<OdGsBaseVectorizeDevice>();
    }
    OdSmartPtr<OdGsViewImpl> createBitmapViewObject()
    {
      return OdSmartPtr<OdGsViewImpl>();
    }
  };

  ODRX_DEFINE_PSEUDO_STATIC_MODULE(StubDeviceModuleText);
  ODRX_DEFINE_PSEUDO_STATIC_MODULE(StubDeviceModuleBinary);

  struct TryToVectorizeMod
  {
    TryToVectorizeMod() { }
    virtual ~TryToVectorizeMod() { }

    virtual void modifyContext(OdGiDefaultContextPtr &pCtx) const;
    virtual void initDevice(const OdStlExportParams &params, OdGsDevicePtr &pDevice, OdGiDefaultContextPtr pCtx) const;
    virtual void vectorizationTest(OdGsDevicePtr pDevice) const;
  };

  void tryToVectorize(const OdStlExportParams &params, const TryToVectorizeMod &pMod = TryToVectorizeMod());

  void TryToVectorizeMod::modifyContext(OdGiDefaultContextPtr &/*pCtx*/) const { }
  
  void TryToVectorizeMod::initDevice(const OdStlExportParams &params, OdGsDevicePtr &pDevice, OdGiDefaultContextPtr pCtx) const
  {
    OdGsViewPtr pNewView = pDevice->createView();

    OdGeExtents3d extents;
    params.entity().getGeomExtents(extents);
    ((StubVectorizeView*)pNewView.get())->setEpsilon(std::numeric_limits<float>::epsilon() * extents.minPoint().distanceTo(extents.maxPoint()));
    ((StubVectorizeView*)pNewView.get())->setParams(params);

    pNewView->setMode(OdGsView::kFlatShaded);

    // AEC draw entities as 2d geom in top view. So rotate view a bit (rotation back will be applied automatically due to 
    // setEyeToOutputTransform( getEyeToWorldTransform() ); in beginViewVectorization()
    rotateViewForAecNeeds(pNewView);

    pDevice->addView( pNewView );

    pNewView->add((OdGiDrawable*)&params.entity(), 0);

    pDevice->setUserGiContext( pCtx );
  }

  void TryToVectorizeMod::vectorizationTest(OdGsDevicePtr pDevice) const
  {
    // Default implementation only make one step of vectorization
    pDevice->update();
  }

  void tryToVectorize(const OdStlExportParams &params, const TryToVectorizeMod &pMod)
  {
    odgsInitialize();
    OdGsModulePtr pGsModule = params.textMode() ? ODRX_STATIC_MODULE_ENTRY_POINT(StubDeviceModuleText)(OD_T("StubDeviceModuleText"))
                                                : ODRX_STATIC_MODULE_ENTRY_POINT(StubDeviceModuleBinary)(OD_T("StubDeviceModuleBinary"));

    if (params.textMode())
      ((StubDeviceModuleText*)pGsModule.get())->setStream(&params.stream());
    else
      ((StubDeviceModuleBinary*)pGsModule.get())->setStream(&params.stream());

    OdGiDefaultContextPtr pContext = OdDbBaseDatabasePEPtr(&params.database())->createGiContext(&params.database());
    OdGsDevicePtr pDevice = pGsModule->createDevice();

    //pContext->setDatabase(pDb);
    //pContext->enableGsModel(bGsModelEnable);
    pMod.modifyContext(pContext);
    pMod.initDevice(params, pDevice, pContext);

    OdGsDCRect screenRect(OdGsDCPoint(0, 1000), OdGsDCPoint(1000, 0));
    pDevice->onSize(screenRect);
    pMod.vectorizationTest(pDevice);
    pDevice.release();
    pContext.release();
    pGsModule.release();
    odgsUninitialize();
  }

  OdResult doExport(const OdStlExportParams &params)
  {
    OdResult ret = eOk;
    try
    {
      tryToVectorize(params);
    }
    catch (const OdError& e)
    {
      ret = e.code();
    }
    catch(...)
    {
      ret = eExtendedError;
    }

    return ret;
  }

  OdResult exportSTL(OdDbBaseDatabase *pDb, const OdGiDrawable &pEntity, OdStreamBuf &pOutStream, bool bTextMode, double dDeviation, bool positiveOctant)
  {
    OdStlExportParams params;
    params.setDatabase(*pDb).setEntity(pEntity).setStream(pOutStream).setTextMode(bTextMode).setDeviation(dDeviation).setPositiveOctant(positiveOctant).setCorrectSolid(false);
    return doExport(params);
  }

  OdResult exportSTLEx(OdDbBaseDatabase *pDb, const OdGiDrawable &pEntity, OdStreamBuf &pOutStream, bool bTextMode, double dDeviation, bool positiveOctant)
  {
    OdStlExportParams params;
    params.setDatabase(*pDb).setEntity(pEntity).setStream(pOutStream).setTextMode(bTextMode).setDeviation(dDeviation).setPositiveOctant(positiveOctant).setCorrectSolid(true);
    return doExport(params);
  }

  OdResult exportSTLEx(const OdStlExportParams &params)
  {
    return doExport(params);
  }

  OdStlExportParams::OdStlExportParams()
    : m_dDeviation(0.)
    , m_bPositiveOctant(true)
    , m_bTextMode(true)
    , m_bCorrectSolid(false)
    , m_bUseColors(false)
    , m_pDb(NULL)
    , m_pEntity(NULL)
    , m_pOutStream(NULL)
    , m_pPalette(NULL)
  {
  }

  bool OdStlExportParams::isValid() const
  {
    return m_pDb != NULL && m_pEntity != NULL && m_pOutStream != NULL;
  }

  OdStlExportParams &OdStlExportParams::setDatabase(OdDbBaseDatabase &pDb)
  {
    m_pDb = &pDb;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setEntity(const OdGiDrawable &pEntity)
  {
    m_pEntity = &pEntity;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setStream(OdStreamBuf &pOutStream)
  {
    m_pOutStream = &pOutStream;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setDeviation(double dDeviation)
  {
    m_dDeviation = dDeviation;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setPositiveOctant(bool bPositiveOctant)
  {
    m_bPositiveOctant = bPositiveOctant;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setTextMode(bool bTextMode)
  {
    m_bTextMode = bTextMode;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setCorrectSolid(bool bCorrectSolid)
  {
    m_bCorrectSolid = bCorrectSolid;
    return *this;
  }
  OdStlExportParams &OdStlExportParams::setUseColors(bool bUseColors)
  {
    m_bUseColors = bUseColors;
    return *this;
  }

  OdStlExportParams & OdStlExportParams::setPalette(const ODCOLORREF* pPalette)
  {
    m_pPalette = pPalette;
    return *this;
  }

  OdDbBaseDatabase &OdStlExportParams::database() const
  {
    return *m_pDb;
  }
  const OdGiDrawable &OdStlExportParams::entity() const
  {
    return *m_pEntity;
  }
  OdStreamBuf &OdStlExportParams::stream() const
  {
    return *m_pOutStream;
  }
  double OdStlExportParams::deviation() const
  {
    return m_dDeviation;
  }
  bool OdStlExportParams::positiveOctant() const
  {
    return m_bPositiveOctant;
  }
  bool OdStlExportParams::textMode() const
  {
    return m_bTextMode;
  }
  bool OdStlExportParams::correctSolid() const
  {
    return m_bCorrectSolid;
  }
  bool OdStlExportParams::useColors() const
  {
    return m_bUseColors;
  }

  const ODCOLORREF* OdStlExportParams::palette() const
  {
    return m_pPalette;
  }

};
