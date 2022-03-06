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
#include "RxVariantValue.h"
#include "RxModelTreeBaseNode.h"
#include "OdPlatformStreamer.h"
#include "ExPrintConsole.h"
#include "OdPath.h"
#include "MemoryStream.h"
#include "RxModelHierarchyTreeBase.h"
#include "tinyxml/tinyxml.h"

#define STL_USING_ALL
#include "OdaSTL.h"

//#define CREATE_XML_BENCHMRK
//#define CREATE_FILE_BENCHMRK


#if defined(__hpux)
#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#define TEST_ASSERT_STR(expr, str) if (!(expr)) throw LINE_STRING
#define TEST_ASSERT(expr) TEST_ASSERT_STR((expr) , __LINE__) 
#else
#define TEST_ASSERT(expr) if (!(expr)) throw __OD_T(#expr)
#endif

//#define WRITE_DB_ID

class ParamHolder
{
public:
  ~ParamHolder() {}

  static ParamHolder& instance()
  {
    static ParamHolder ret;
    return ret;
  }

  bool needCreateXMLBenchmark() const
  {
#if defined(CREATE_XML_BENCHMRK)
    return true;
#else
    return m_NeedCreateBenchmark;
#endif
  }

  bool needCreateFileBenchmark() const
  {
#if defined(CREATE_FILE_BENCHMRK)
    return true;
#else
    return m_NeedCreateBenchmark;
#endif
  }

  void setNeedCreateBenchmark(const bool state)
  {
    m_NeedCreateBenchmark = state;
  }

  void setWriteFullCacheInfo(const bool state)
  {
    m_WriteFullCacheInfo = state;
  }

  bool writeFullCacheInfo() const
  {
    return m_WriteFullCacheInfo;
  }

private:
  ParamHolder()
  {
    m_NeedCreateBenchmark = false;
    m_WriteFullCacheInfo = false;
    OdString val;
    if (eOk == ::odrxSystemServices()->getEnvVar(L"CHANGE_CDA_BENCHMARK", val))
    {
      if (0 == val.compare(L"1"))
      {
        m_NeedCreateBenchmark = true;
      }
    }
  }
  bool m_NeedCreateBenchmark;
  bool m_WriteFullCacheInfo;
};

class OdTestTreeFiler : public OdBaseHierarchyTreeFiler
{
public:
  OdTestTreeFiler(OdStreamBufPtr pStream, const OdString& file_name)
    :m_pStream(pStream)
    ,m_FileName(file_name)
  {}

  virtual bool rdBool()
  {
    return m_pStream->getByte() !=0;
  }

  virtual double rdDouble()
  {
    return OdPlatformStreamer::rdDouble(*m_pStream);
  }

  virtual OdUInt8 rdInt8()
  {
    return m_pStream->getByte();
  }

  virtual OdUInt8 rdUInt8()
  {
    return m_pStream->getByte();
  }

  virtual OdUInt16 rdInt16()
  {
    return OdPlatformStreamer::rdInt16(*m_pStream);
  }

  virtual OdUInt16 rdUInt16()
  {
    return OdPlatformStreamer::rdInt16(*m_pStream);
  }

  virtual OdUInt32 rdInt32()
  {
    return OdPlatformStreamer::rdInt32(*m_pStream);
  }

  virtual OdUInt32 rdUInt32()
  {
    return OdPlatformStreamer::rdInt32(*m_pStream);
  }

  virtual OdInt64 rdInt64()
  {
    return OdPlatformStreamer::rdInt64(*m_pStream);
  }

  virtual OdInt64 rdUInt64()
  {
    return OdPlatformStreamer::rdInt64(*m_pStream);
  }

  virtual OdString rdString()
  {
    return OdPlatformStreamer::rdString(*m_pStream);
  }

  virtual OdAnsiString rdAnsiString()
  {
    OdAnsiString out;
    int nLen = OdPlatformStreamer::rdInt32(*m_pStream);
    if (0 == nLen)
      return out;

    char* pData = out.getBufferSetLength(nLen);
    m_pStream->getBytes(pData, OdUInt32(sizeof(char) * nLen));
    out.releaseBuffer(nLen);
    return out;
  }

  virtual OdGePoint2d rdGePoint2d()
  {
    OdGePoint2d p;
    OdPlatformStreamer::rd2Doubles(*m_pStream, &p.x);
    return p;
  }

  virtual OdGePoint3d rdGePoint3d()
  {
    OdGePoint3d p;
    OdPlatformStreamer::rd3Doubles(*m_pStream, &p.x);
    return p;
  }

  virtual OdGeVector2d rdGeVector2d()
  {
    OdGeVector2d p;
    OdPlatformStreamer::rd2Doubles(*m_pStream, &p.x);
    return p;
  }

  virtual OdGeVector3d rdGeVector3d()
  {
    OdGeVector3d p;
    OdPlatformStreamer::rd3Doubles(*m_pStream, &p.x);
    return p;
  }

  virtual OdCmEntityColor rdCmEntityColor()
  {
    OdCmEntityColor ret;
    m_pStream->getBytes(&ret, sizeof(OdCmEntityColor));
    return ret;
  }

  virtual OdCmTransparency rdCmTransparency()
  {
    OdCmTransparency ret;
    m_pStream->getBytes(&ret, sizeof(OdCmTransparency));
    return ret;
  }

  virtual void wrBool(const bool value)
  {
    m_pStream->putByte(value);
  }

  virtual void wrDouble(const double value)
  {
    OdPlatformStreamer::wrDouble(*m_pStream, value);
  }

  virtual void wrInt8(const OdInt8 value)
  {
    m_pStream->putByte(value);
  }

  virtual void wrUInt8(const OdUInt8 value)
  {
    m_pStream->putByte(value);
  }

  virtual void wrInt16(const OdInt16 value)
  {
    OdPlatformStreamer::wrInt16(*m_pStream, value);
  }

  virtual void wrUInt16(const OdUInt16 value)
  {
    OdPlatformStreamer::wrInt16(*m_pStream, value);
  }

  virtual void wrInt32(const OdInt32 value)
  {
    OdPlatformStreamer::wrInt32(*m_pStream, value);
  }

  virtual void wrUInt32(const OdUInt32 value)
  {
    OdPlatformStreamer::wrInt32(*m_pStream, value);
  }

  virtual void wrInt64(const OdInt64 value)
  {
    OdPlatformStreamer::wrInt64(*m_pStream, value);
  }

  virtual void wrUInt64(const OdUInt64 value)
  {
    OdPlatformStreamer::wrInt64(*m_pStream, value);
  }

  virtual void wrString(const OdString& value)
  {
    if (ParamHolder::instance().needCreateFileBenchmark() || ParamHolder::instance().needCreateXMLBenchmark())
    {
      if (!ParamHolder::instance().writeFullCacheInfo() && (-1 != value.find(L"0000") || -1 != value.find(m_FileName) || -1 != value.find(L"kMillimeter") || -1 != value.find(L"Inches")))
        OdPlatformStreamer::wrString(*m_pStream, OdString(L"****************"));
      else
        OdPlatformStreamer::wrString(*m_pStream, value);
    }
    else
    {
      OdPlatformStreamer::wrString(*m_pStream, value);
    }
  }

  virtual void wrAnsiString(const OdAnsiString& value)
  {
    OdUInt32 nLen = value.getLength();
    OdPlatformStreamer::wrInt32(*m_pStream, nLen);
    if (0 != nLen)
      m_pStream->putBytes(value.c_str(), OdUInt32(sizeof(char) * nLen));
  }

  virtual void wrGePoint2d(const OdGePoint2d& value)
  {
    OdPlatformStreamer::wr2Doubles(*m_pStream, &value.x);
  }

  virtual void wrGePoint3d(const OdGePoint3d& value)
  {
    OdPlatformStreamer::wr3Doubles(*m_pStream, &value.x);
  }

  virtual void wrGeVector2d(const OdGeVector2d& value)
  {
    OdPlatformStreamer::wr2Doubles(*m_pStream, &value.x);
  }

  virtual void wrGeVector3d(const OdGeVector3d& value)
  {
    OdPlatformStreamer::wr3Doubles(*m_pStream, &value.x);
  }

  virtual void wrCmEntityColor(const OdCmEntityColor& value)
  {
    m_pStream->putBytes(&value, sizeof(OdCmEntityColor));
  }

  virtual void wrCmTransparency(const OdCmTransparency& value)
  {
    m_pStream->putBytes(&value, sizeof(OdCmTransparency));
  }

  OdStreamBufPtr m_pStream;
  OdString m_FileName;
};

struct LessCase
{
  bool operator()(const PropertyInfo X, const PropertyInfo Y) const
  {
    return (X.name.compare(Y.name) < 0);
  }
};

struct LessForNode
{
  bool operator()(const OdRxModelTreeBaseNodePtr X, const OdRxModelTreeBaseNodePtr Y) const
  {
    return (X->getUniqueSourceID() == Y->getUniqueSourceID()) ? (X->getNodeName().compare(Y->getNodeName()) < 0) : (X->getUniqueSourceID() < Y->getUniqueSourceID());
  }
};

bool operator == (const OdGiColorRGB& c1, const OdGiColorRGB& c2)
{
  return (OdEqual(c1.red, c2.red) && OdEqual(c1.green, c2.green) && OdEqual(c1.blue, c2.blue));
}

bool operator != (const OdGiColorRGB& c1, const OdGiColorRGB& c2)
{
  return !(c1 == c2);
}

bool operator != (const OdGiSkyParameters& c1, const OdGiSkyParameters& c2)
{
  return !(c1 == c2);
}

#define TYPE_CONTAINER \
  VARTYPE(AnsiString)\
  VARTYPE(Bool)\
  VARTYPE(Int8)\
  VARTYPE(Int16)\
  VARTYPE(Int32)\
  VARTYPE(Int64)\
  VARTYPE(GePoint2d)\
  VARTYPE(GePoint3d)\
  VARTYPE(GeVector2d)\
  VARTYPE(GeVector3d)\
  VARTYPE(CmEntityColor)\
  VARTYPE(CmTransparency)\
  VARTYPE(GeMatrix2d)\
  VARTYPE(GeMatrix3d)\
  VARTYPE(TimeStamp)\
  VARTYPE(GeExtents2d)\
  VARTYPE(GeExtents3d)\
  VARTYPE(GeQuaternion)\
  VARTYPE(GiLightAttenuation)\
  VARTYPE(GiSkyParameters)\
  VARTYPE(GiShadowParameters)\
  VARTYPE(GiColorRGB)\
  VARTYPE(GiMaterialColor)\
  VARTYPE(GiMrExposureType)\
  VARTYPE(GiMrShadowMode)\
  VARTYPE(GiMrFinalGatheringMode)\
  VARTYPE(GiMrDiagnosticMode)\
  VARTYPE(GiMrDiagnosticPhotonMode)\
  VARTYPE(GiMrDiagnosticBSPMode)\
  VARTYPE(GiMrExportMIMode)\
  VARTYPE(GiMrTileOrder)\
  VARTYPE(GiLightingMode)\
  VARTYPE(GiFilterType)\
  VARTYPEENUM(CmEntityColor, ColorMethod)\
  VARTYPEENUM(Db, LineWeight)\
  VARTYPEENUM(Db, UnitsValue)\
  VARTYPEENUM(GiDgLinetypeModifiers, WidthMode)\
  VARTYPEENUM(GiDgLinetypeModifiers, ShiftMode)\
  VARTYPEENUM(GiDgLinetypeModifiers, CornersMode)\
  VARTYPEENUM(Ge, OdGeKnotParameterization)\
  VARTYPEENUM(GiLightAttenuation, AttenuationType)\
  VARTYPEENUM(GiDrawable, DrawableType)\
  VARTYPEENUM(GiShadowParameters, ShadowType)\
  VARTYPEENUM(GiShadowParameters, ExtendedLightShape)\
  VARTYPEENUM(GiViewportTraits, DefaultLightingType)\
  VARTYPEENUM(GiMaterialTraits, LuminanceMode)\
  VARTYPEENUM(GiMaterialTraits, GlobalIlluminationMode)\
  VARTYPEENUM(GiMaterialTraits, FinalGatherMode)\
  VARTYPEENUM(GiMaterialTraits, ChannelFlags)\
  VARTYPEENUM(GiMaterialTraits, Mode)\
  VARTYPEENUM(GiMaterialTraits, IlluminationModel)\
  VARTYPEENUM(GiVisualStyle, Type)\
  VARTYPEENUM(GiVisualStyleProperties, FaceColorMode)\
  VARTYPEENUM(GiVisualStyleProperties, EdgeModel)\
  VARTYPEENUM(GiFaceStyle, FaceColorMode)\
  VARTYPEENUM(GiEdgeStyle, EdgeModel)\
  VARTYPEENUM(GiToneOperatorParameters, ExteriorDaylightMode)\

void compareProperty(const PropertyInfo& info1, const PropertyInfo& info2, const OdString& node_name, std::map<OdString, std::set<OdString> >& exclusions)
{
  odPrintConsoleString(L"Property name: %ls\n", info1.name.c_str());

  TEST_ASSERT(info1.name == info2.name);
  TEST_ASSERT(info1.localizedName == info2.localizedName);
  TEST_ASSERT(info1.uiPlacement == info2.uiPlacement);
  TEST_ASSERT(OdEqual(info1.weight, info2.weight, OdGeContext::gTol.equalPoint()));

  TEST_ASSERT(info1.value.varType() == info2.value.varType());
  
  switch (info1.value.varType())
  {
#undef VARTYPE
#define VARTYPE(Type) \
  case OdRxPropertyVariant::k##Type:\
    TEST_ASSERT(info1.value.get##Type() == info2.value.get##Type());\
    break;
    
#undef VARTYPEENUM
#define VARTYPEENUM(NameSp, Type) \
  case OdRxPropertyVariant::k##NameSp##_##Type:\
    TEST_ASSERT((OdUInt8)info1.value.get##NameSp##_##Type() == (OdUInt8)info2.value.get##NameSp##_##Type());\
    break;

    TYPE_CONTAINER

  case OdRxPropertyVariant::kDouble:
    TEST_ASSERT(OdEqual(info1.value.getDouble(), info2.value.getDouble(), OdGeContext::gTol.equalPoint()));
    break;

  case OdRxPropertyVariant::kString:
  {
    if(info2.value.getString() != OdString(L"****************"))
      TEST_ASSERT(info1.value.getString() == info2.value.getString());
  }
    break;

#undef VARTYPE
#define VARTYPE(Type) \
  case OdRxPropertyVariant::k##Type| OdRxPropertyVariant::kArray:\
    TEST_ASSERT(info1.value.get##Type##Array() == info2.value.get##Type##Array());\
    break;

#undef VARTYPEENUM
#define VARTYPEENUM(NameSp, Type) \
  case OdRxPropertyVariant::k##NameSp##_##Type| OdRxPropertyVariant::kArray:\
    TEST_ASSERT(info1.value.get##NameSp##_##Type##Array() == info2.value.get##NameSp##_##Type##Array());\
    break;

    TYPE_CONTAINER

  case OdVariant::kDouble | OdVariant::kArray:
  {
    OdDoubleArray arr1 = info1.value.getDoubleArray();
    OdDoubleArray arr2 = info2.value.getDoubleArray();
    TEST_ASSERT(arr1.size() == arr2.size());
    for (unsigned int i = 0; i < arr1.size(); ++i)
    {
      TEST_ASSERT(OdEqual(arr1[i], arr2[i], OdGeContext::gTol.equalPoint()));
    }
  }
    break;

  case OdRxPropertyVariant::kString | OdVariant::kArray:
  {
    OdStringArray arr1 = info1.value.getStringArray();
    OdStringArray arr2 = info2.value.getStringArray();
    TEST_ASSERT(arr1.size() == arr2.size());
    for (unsigned int i = 0; i < arr1.size(); ++i)
    {
      if (info2.value.getStringArray()[i] != OdString(L"****************"))
        TEST_ASSERT(arr1[i] == arr2[i]);
    }
  }
  break;
  }

  OdArray<PropertyInfo>::size_type prop_size = info1.subProperties.size();
  TEST_ASSERT(prop_size == info2.subProperties.size());
  for (OdArray<PropertyInfo>::size_type i = 0; i < prop_size; ++i)
  {
    bool is_exclusion_found = (exclusions.end() != exclusions.find(node_name)) &&
      (exclusions[node_name].end() != exclusions[node_name].find(info1.subProperties[i].name));
    if (!is_exclusion_found)
      compareProperty(info1.subProperties[i], info2.subProperties[i], node_name, exclusions);
  }
}

void compareCDANodes(const OdRxModelTreeBaseNodePtr pNode1, const OdRxModelTreeBaseNodePtr pNode2, std::map<OdString, std::set<OdString> >& exclusions)
{
  odPrintConsoleString(L"Node name: %ls (%lld)\n", pNode2->getNodeName().c_str(), pNode2->getUniqueSourceID());

  if (pNode1->getUniqueSourceID() != pNode2->getUniqueSourceID())
  {
    odPrintConsoleString(L"Node1 name: %ls (%lld)\n", pNode1->getNodeName().c_str(), pNode1->getUniqueSourceID());
  }

  TEST_ASSERT(pNode1->getUniqueSourceID() == pNode2->getUniqueSourceID());
  TEST_ASSERT(pNode1->getNodeName() == pNode2->getNodeName());
  TEST_ASSERT(pNode1->getNodeType() == pNode2->getNodeType());
  //TEST_ASSERT(pNode1->getUniqueDBID() == pNode2->getUniqueDBID());

  OdArray<PropertyInfo> propsArray1 = pNode1->getProperties();
  OdArray<PropertyInfo> propsArray2 = pNode2->getProperties();

  std::sort(propsArray1.begin(), propsArray1.end(), LessCase());
  std::sort(propsArray2.begin(), propsArray2.end(), LessCase());
  OdArray<PropertyInfo>::size_type prop_size = propsArray1.size();
  TEST_ASSERT(prop_size == propsArray2.size());
  for (OdArray<PropertyInfo>::size_type i = 0; i < prop_size; ++i)
  {
    bool is_exclusion_found = (exclusions.end() != exclusions.find(pNode1->getNodeName())) &&
      (exclusions[pNode1->getNodeName()].end() != exclusions[pNode1->getNodeName()].find(propsArray1[i].name));
    if(!is_exclusion_found)
      compareProperty(propsArray1[i], propsArray2[i], pNode1->getNodeName(), exclusions);
  }

  OdRxModelTreeBaseNodePtrArray Children1 = pNode1->getChildren();
  OdRxModelTreeBaseNodePtrArray Children2 = pNode2->getChildren();

  OdRxModelTreeBaseNodePtrArray::size_type child_size = Children1.size();
  OdRxModelTreeBaseNodePtrArray::size_type parent_size = pNode1->getParents().size();

  TEST_ASSERT(child_size == Children2.size());
  TEST_ASSERT(parent_size == pNode2->getParents().size());

  std::sort(Children1.begin(), Children1.end(), LessForNode());
  std::sort(Children2.begin(), Children2.end(), LessForNode());
  for (OdRxModelTreeBaseNodePtrArray::size_type i = 0; i < child_size; ++i)
  {
    compareCDANodes(Children1[i], Children2[i], exclusions);
  }
}

const OdChar* nodeType(HierarchyTreeObjectType type)
{
  switch (type)
  {
  case eDatabase:
    return L"eDatabase";
    break;
  case eModel:
    return L"eModel";
    break;
  case eBlock:
    return L"eBlock";
    break;
  case eBlockReference:
    return L"eBlockReference";
    break;
  case eEntity:
    return L"eEntity";
    break;
  case eHidden:
    return L"eHidden";
    break;
  default:
    return L"";
    break;
  }
}

//static OdUInt64 NodeCounter = 0;
//static OdUInt64 PropCounter = 10000000;

//void printfProperty(const OdString& array_name, const PropertyInfo& info1, OdUInt64 counter)
//{
//  odPrintConsoleString(L"{\n");
//  odPrintConsoleString(L"  PropertyInfo info;\n");
//  odPrintConsoleString(L"  info.name = OdString(L\"%ls\");\n", info1.name.c_str());
//  odPrintConsoleString(L"  info.localizedName = OdString(L\"%ls\");\n", info1.localizedName.c_str());
//  odPrintConsoleString(L"  info.uiPlacement = OdString(L\"%ls\");\n", info1.uiPlacement.c_str());
//  odPrintConsoleString(L"  info.weight = %f;\n", info1.weight);
//  
//  switch (info1.value.varType())
//  {
//  case OdRxPropertyVariant::kBool:
//    odPrintConsoleString(L" info.value.setBool(%d);\n", info1.value.getBool());
//    break;
//  case OdRxPropertyVariant::kInt8:
//    odPrintConsoleString(L"  info.value.setInt8((OdInt8)%d);\n", info1.value.getInt8());
//    break;
//  case OdRxPropertyVariant::kInt16:
//    odPrintConsoleString(L"  info.value.setInt16((OdInt16)%d);\n", info1.value.getInt16());
//    break;
//  case OdRxPropertyVariant::kInt32:
//    odPrintConsoleString(L"  info.value.setInt32(%d);\n", info1.value.getInt32());
//    break;
//  case OdRxPropertyVariant::kInt64:
//    odPrintConsoleString(L"  info.value.setInt64(%lld);\n", info1.value.getInt64());
//    break;
//  case OdRxPropertyVariant::kDouble:
//    odPrintConsoleString(L"  info.value.setDouble(%Lf);\n", info1.value.getDouble());
//    break;
//  case OdRxPropertyVariant::kGePoint2d:
//    odPrintConsoleString(L"  info.value.setGePoint2d(OdGePoint2d(%Lf, %Lf));\n", info1.value.getGePoint2d().x, info1.value.getGePoint2d().y);
//    break;
//  case OdRxPropertyVariant::kGeVector2d:
//    odPrintConsoleString(L"  info.value.setGeVector2d(OdGeVector2d(%Lf, %Lf));\n", info1.value.getGeVector2d().x, info1.value.getGeVector2d().y);
//    break;
//  case OdRxPropertyVariant::kGePoint3d:
//    odPrintConsoleString(L"  info.value.setGePoint3d(OdGePoint3d(%Lf, %Lf, %Lf));\n", info1.value.getGePoint3d().x, info1.value.getGePoint3d().y,
//      info1.value.getGePoint3d().z);
//    break;
//  case OdRxPropertyVariant::kGeVector3d:
//    odPrintConsoleString(L"  info.value.setGeVector3d(OdGeVector3d(%Lf, %Lf, %Lf));\n", info1.value.getGeVector3d().x, info1.value.getGeVector3d().y,
//      info1.value.getGeVector3d().z);
//    break;
//  case OdRxPropertyVariant::kCmEntityColor:
//    odPrintConsoleString(L"  {\n");
//    odPrintConsoleString(L"    OdCmEntityColor color;\n");
//    odPrintConsoleString(L"    color.setColor(%d);\n",
//      info1.value.getCmEntityColor().color());
//    odPrintConsoleString(L"    info.value.setCmEntityColor(color);\n");
//    odPrintConsoleString(L"  }\n");
//    break;
//  case OdRxPropertyVariant::kCmTransparency:
//    odPrintConsoleString(L"  {\n");
//    odPrintConsoleString(L"    OdCmTransparency tr;\n");
//    odPrintConsoleString(L"    tr.serializeIn(%d);\n", info1.value.getCmTransparency().serializeOut());
//    odPrintConsoleString(L"    info.value.setCmTransparency(tr);\n");
//    odPrintConsoleString(L"  }\n");
//    break;
//  case OdRxPropertyVariant::kString:
//  {
//    odPrintConsoleString(L"  info.value.setString(L\"%ls\");\n", 
//      (-1 != info1.value.getString().find(OdString(L"0000"))) ? OdString(L"****************").c_str() : info1.value.getString().c_str());
//  }
//  break;
//  case OdRxPropertyVariant::kAnsiString:
//  {
//    odPrintConsoleString(L"  info.value.setAnsiString(OdString(L\"%ls\"));\n", OdString(info1.value.getAnsiString()).c_str());
//  }
//  break;
//  case OdRxPropertyVariant::kBool | OdVariant::kArray:
//    odPrintConsoleString(L"  OdBoolArray array;\n");
//    odPrintConsoleString(L"  info.value.setBoolArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getBoolArray().size(); ++i)
//      odPrintConsoleString(L"  info.value.asBoolArray().append(%d);\n", info1.value.getBoolArray()[i]);
//    break;
//  case OdRxPropertyVariant::kInt8 | OdVariant::kArray:
//    odPrintConsoleString(L"  OdInt8Array array;\n");
//    odPrintConsoleString(L"  info.value.setInt8Array(array);\n");
//    for (unsigned int i = 0; i < info1.value.getInt8Array().size(); ++i)
//      odPrintConsoleString(L"  info.value.asInt8Array().append((OdInt8)%d);\n", info1.value.getInt8Array()[i]);
//    break;
//  case OdRxPropertyVariant::kInt16 | OdVariant::kArray:
//    odPrintConsoleString(L"  OdInt16Array array;\n");
//    odPrintConsoleString(L"  info.value.setInt16Array(array);\n");
//    for (unsigned int i = 0; i < info1.value.getInt16Array().size(); ++i)
//      odPrintConsoleString(L"  info.value.asInt16Array().append((OdInt16)%d);\n", info1.value.getInt16Array()[i]);
//    break;
//  case OdRxPropertyVariant::kInt32 | OdVariant::kArray:
//    odPrintConsoleString(L"  OdInt32Array array;\n");
//    odPrintConsoleString(L"  info.value.setInt32Array(array);\n");
//    for (unsigned int i = 0; i < info1.value.getInt32Array().size(); ++i)
//      odPrintConsoleString(L"  info.value.asInt32Array().append(%d);\n", info1.value.getInt32Array()[i]);
//    break;
//  case OdRxPropertyVariant::kInt64 | OdVariant::kArray:
//    odPrintConsoleString(L"  OdInt64Array array;\n");
//    odPrintConsoleString(L"  info.value.setInt64Array(array);\n");
//    for (unsigned int i = 0; i < info1.value.getInt64Array().size(); ++i)
//      odPrintConsoleString(L"  info.value.asInt64Array().append(%lld);\n", info1.value.getInt64Array()[i]);
//    break;
//  case OdRxPropertyVariant::kDouble | OdVariant::kArray:
//    odPrintConsoleString(L"  OdDoubleArray array;\n");
//    odPrintConsoleString(L"  info.value.setDoubleArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getDoubleArray().size(); ++i)
//      odPrintConsoleString(L"  info.value.asDoubleArray().append(%Lf);\n", info1.value.getDoubleArray()[i]);
//    break;
//  case OdRxPropertyVariant::kGePoint2d | OdVariant::kArray:
//    odPrintConsoleString(L"  OdGePoint2dArray array;\n");
//    odPrintConsoleString(L"  info.value.setGePoint2dArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getGePoint2dArray().size(); ++i)
//      odPrintConsoleString(L"  info.value.asGePoint2dArray().append(OdGePoint2d(%Lf, %Lf));\n", info1.value.getGePoint2dArray()[i].x,
//        info1.value.getGePoint2dArray()[i].y);
//    break;
//  case OdRxPropertyVariant::kGeVector2d | OdVariant::kArray:
//    odPrintConsoleString(L"  OdGeVector2dArray array;\n");
//    odPrintConsoleString(L"  info.value.setGeVector2dArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getGeVector2dArray().size(); ++i)
//      odPrintConsoleString(L"  info.value.asGeVector2dArray().append(OdGeVector2d(%Lf, %Lf));\n", info1.value.getGeVector2dArray()[i].x,
//        info1.value.getGeVector2dArray()[i].y);
//    break;
//  case OdRxPropertyVariant::kGePoint3d | OdVariant::kArray:
//    odPrintConsoleString(L"  OdGePoint3dArray array;\n");
//    odPrintConsoleString(L"  info.value.setGePoint3dArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getGePoint3dArray().size(); ++i)
//      odPrintConsoleString(L"  info.value.asGePoint3dArray().append(OdGePoint3d(%Lf, %Lf, %Lf));\n", info1.value.getGePoint3dArray()[i].x,
//        info1.value.getGePoint3dArray()[i].y,
//        info1.value.getGePoint3dArray()[i].z);
//    break;
//  case OdRxPropertyVariant::kGeVector3d | OdVariant::kArray:
//    odPrintConsoleString(L"  OdGeVector3dArray array;\n");
//    odPrintConsoleString(L"  info.value.setGeVector3dArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getGeVector3dArray().size(); ++i)
//      odPrintConsoleString(L"  info.value.asGeVector3dArray().append(OdGeVector3d(%Lf, %Lf, %Lf));\n", info1.value.getGeVector3dArray()[i].x,
//        info1.value.getGeVector3dArray()[i].y,
//        info1.value.getGeVector3dArray()[i].z);
//    break;
//  case OdRxPropertyVariant::kCmEntityColor | OdVariant::kArray:
//    odPrintConsoleString(L"  OdCmEntityColorArray array;\n");
//    odPrintConsoleString(L"  info.value.setCmEntityColorArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getCmEntityColorArray().size(); ++i)
//    {
//      odPrintConsoleString(L"  {\n");
//      odPrintConsoleString(L"    OdCmEntityColor color;\n");
//      odPrintConsoleString(L"    color.setColor(%d);\n",
//        info1.value.getCmEntityColorArray()[i].color());
//      odPrintConsoleString(L"    info.value.asCmEntityColorArray().append(color);\n");
//      odPrintConsoleString(L"  }\n");
//    }
//    break;
//  case OdRxPropertyVariant::kCmTransparency | OdVariant::kArray:
//    odPrintConsoleString(L"  OdCmTransparencyArray array;\n");
//    odPrintConsoleString(L"  info.value.setCmTransparencyArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getCmTransparencyArray().size(); ++i)
//    {
//      odPrintConsoleString(L"  {\n");
//      odPrintConsoleString(L"    OdCmTransparency tr;\n");
//      odPrintConsoleString(L"    tr.serializeIn(%d);\n", info1.value.getCmTransparencyArray()[i].serializeOut());
//      odPrintConsoleString(L"    info.value.asCmTransparencyArray().append(tr);\n");
//      odPrintConsoleString(L"  }\n");
//    }
//    break;
//  case OdRxPropertyVariant::kString | OdVariant::kArray:
//    odPrintConsoleString(L"  OdStringArray array;\n");
//    odPrintConsoleString(L"  info.value.setStringArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getStringArray().size(); ++i)
//    {
//      odPrintConsoleString(L"  info.value.asStringArray().append(L\"%ls\");\n", 
//        (-1 != info1.value.getString().find(OdString(L"0000"))) ? OdString(L"****************").c_str() : info1.value.getStringArray()[i].c_str());
//    }
//    break;
//  case OdRxPropertyVariant::kAnsiString | OdVariant::kArray: 
//    odPrintConsoleString(L"  OdAnsiStringArray array;\n");
//    odPrintConsoleString(L"  info.value.setAnsiStringArray(array);\n");
//    for (unsigned int i = 0; i < info1.value.getAnsiStringArray().size(); ++i)
//    {
//      odPrintConsoleString(L"  info.value.asAnsiStringArray().append(OdString(L\"%s\"));\n", OdString(info1.value.getAnsiStringArray()[i]).c_str());
//    }
//    break;
//  }
//
//  odPrintConsoleString(L"%ls.append(info);\n", array_name.c_str());
//  OdArray<PropertyInfo>::size_type prop_size = info1.subProperties.size();
//  for (OdArray<PropertyInfo>::size_type i = 0; i < prop_size; ++i)
//  {
//    OdString sub_props_name(array_name + OdString().format(L"[%d].subProperties", counter));
//    printfProperty(sub_props_name, info1.subProperties[i], i);
//  }
//  odPrintConsoleString(L"}\n");
//}
//
//void printfCDANodes(const OdRxModelTreeBaseNodePtr pNode1, OdUInt64 counter)
//{
//  OdString name = pNode1->getNodeName();
//  odPrintConsoleString(L"TEST_ASSERT(%llu == pNode%d->getUniqueSourceID());\n", pNode1->getUniqueSourceID(), counter);
//  odPrintConsoleString(L"TEST_ASSERT(OdString(L\"%ls\") == pNode%d->getNodeName());\n", name.c_str(), counter);
//
//  odPrintConsoleString(L"TEST_ASSERT(%ls == pNode%d->getNodeType());\n", nodeType(pNode1->getNodeType()), counter);
//
//  odPrintConsoleString(L"OdArray<PropertyInfo> Properties%d = pNode%d->getProperties();\n", counter, counter);
//
//  OdArray<PropertyInfo> InfoArray1 = pNode1->getProperties();
//  odPrintConsoleString(L"TEST_ASSERT(%d == Properties%d.size());\n", InfoArray1.size(), counter);
//
//  OdString array_name = OdString().format(L"sampleProperties%d", counter);
//
//  odPrintConsoleString(L"OdArray<PropertyInfo> %ls;\n", array_name.c_str());
//
//  for (OdArray<PropertyInfo>::size_type i = 0; i < InfoArray1.size(); ++i)
//  {
//    printfProperty(array_name, InfoArray1[i], i);
//  }
//  odPrintConsoleString(L"comparePropertiesArray(pNode%d->getProperties(), sampleProperties%d);\n", counter, counter);
//
//  odPrintConsoleString(L"TEST_ASSERT(%d == pNode%d->getChildren().size());\n", pNode1->getChildren().size(), counter);
//  odPrintConsoleString(L"TEST_ASSERT(%d == pNode%d->getParents().size());\n", pNode1->getParents().size(), counter);
//
//  for (OdRxModelTreeBaseNodePtrArray::size_type i = 0; i < pNode1->getChildren().size(); ++i)
//  {
//    ++NodeCounter;
//    odPrintConsoleString(L"OdRxModelTreeBaseNodePtr pNode%d = pNode%d->getChildren()[%d];\n", NodeCounter, counter, i);
//    printfCDANodes(pNode1->getChildren()[i], NodeCounter);
//  }
//}

/********************************************************************************/
/* Write PropertyInfo to XML node                                               */
/********************************************************************************/
void xmlProperty(PropertyInfo& info, TiXmlElement* parentXmlNode, const OdString& file_name)
{
  TiXmlElement* xmlNode = new TiXmlElement("property");
  parentXmlNode->LinkEndChild(xmlNode);

  xmlNode->SetAttribute("name", OdAnsiString(info.name, CP_UTF_8));
  xmlNode->SetAttribute("localizedName", OdAnsiString(info.localizedName, CP_UTF_8));
  xmlNode->SetAttribute("uiPlacement", OdAnsiString(info.uiPlacement, CP_UTF_8));
  xmlNode->SetAttribute("weight", info.weight);

  switch (info.value.varType())
  {
  case OdRxPropertyVariant::kBool:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdBool");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getBool()));
  }
    break;
  case OdRxPropertyVariant::kInt8:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdInt8");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getInt8()));
  }
    break;
  case OdRxPropertyVariant::kInt16:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdInt16");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getInt16()));
  }
    break;
  case OdRxPropertyVariant::kInt32:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdInt32");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getInt32()));
  }
    break;
  case OdRxPropertyVariant::kInt64:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdInt64");
    xmlValueNode->SetAttribute("val", OdString().format(L"%lld", info.value.getInt64()));
  }
    break;
  case OdRxPropertyVariant::kDouble:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdDouble");
    xmlValueNode->SetAttribute("val", OdString().format(L"%f", info.value.getDouble()));
  }
    break;
  case OdRxPropertyVariant::kGePoint2d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGePoint2d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGePoint2d(%f, %f)",info.value.getGePoint2d().x, info.value.getGePoint2d().y));
  }
    break;
  case OdRxPropertyVariant::kGeVector2d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeVector2d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeVector2d(%f, %f)", info.value.getGeVector2d().x, info.value.getGeVector2d().y));
  }
    break;
  case OdRxPropertyVariant::kGePoint3d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGePoint3d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGePoint3d(%f, %f, %f)", info.value.getGePoint3d().x, info.value.getGePoint3d().y,
      info.value.getGePoint3d().z));
  }
    break;
  case OdRxPropertyVariant::kGeVector3d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeVector3d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeVector3d(%f, %f, %f)", info.value.getGeVector3d().x, info.value.getGeVector3d().y,
      info.value.getGeVector3d().z));
  }
    break;
  case OdRxPropertyVariant::kCmEntityColor:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdCmEntityColor");
    xmlValueNode->SetAttribute("val", info.value.getCmEntityColor().color());
  }
    break;
  case OdRxPropertyVariant::kCmTransparency:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdCmTransparency");
    xmlValueNode->SetAttribute("val", info.value.getCmTransparency().serializeOut());
  }
    break;
  case OdRxPropertyVariant::kString:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdString");
    xmlValueNode->SetAttribute("val", 
      !ParamHolder::instance().writeFullCacheInfo() && ((-1 != info.value.getString().find(OdString(L"0000")) || -1 != info.value.getString().find(file_name))
      || -1 != info.value.getString().find(L"kMillimeter") || -1 != info.value.getString().find(L"Inches")) ? OdString(L"****************") : OdAnsiString(info.value.getString(), CP_UTF_8));
  }
  break;
  case OdRxPropertyVariant::kAnsiString:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdAnsiString");
    xmlValueNode->SetAttribute("val", info.value.getAnsiString());
  }
  break;
  case OdRxPropertyVariant::kGiMrExposureType:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrExposureType");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrExposureType()));
  }
  break;
  case OdRxPropertyVariant::kGiMrShadowMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrShadowMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrShadowMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMrFinalGatheringMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrFinalGatheringMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrFinalGatheringMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMrDiagnosticMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrDiagnosticMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrDiagnosticMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMrDiagnosticPhotonMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrDiagnosticPhotonMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrDiagnosticPhotonMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMrDiagnosticBSPMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrDiagnosticBSPMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrDiagnosticBSPMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMrExportMIMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrExportMIMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrExportMIMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMrTileOrder:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMrTileOrder");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMrTileOrder()));
  }
  break;
  case OdRxPropertyVariant::kGiLightingMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiLightingMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiLightingMode()));
  }
  break;
  case OdRxPropertyVariant::kGiFilterType:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiFilterType");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiFilterType()));
  }
  break;
  case OdRxPropertyVariant::kCmEntityColor_ColorMethod:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdCmEntityColor::ColorMethod");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getCmEntityColor_ColorMethod()));
  }
  break;
  case OdRxPropertyVariant::kDb_LineWeight:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdDb::LineWeight");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getDb_LineWeight()));
  }
  break;
  case OdRxPropertyVariant::kDb_UnitsValue:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdDb::UnitsValue");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getDb_UnitsValue()));
  }
  break;
  case OdRxPropertyVariant::kGiDgLinetypeModifiers_WidthMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiDgLinetypeModifiers::WidthMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiDgLinetypeModifiers_WidthMode()));
  }
  break;
  case OdRxPropertyVariant::kGiDgLinetypeModifiers_ShiftMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiDgLinetypeModifiers::ShiftMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiDgLinetypeModifiers_ShiftMode()));
  }
  break;
  case OdRxPropertyVariant::kGiDgLinetypeModifiers_CornersMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiDgLinetypeModifiers::CornersMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiDgLinetypeModifiers_CornersMode()));
  }
  break;
  case OdRxPropertyVariant::kGe_OdGeKnotParameterization:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGe::OdGeKnotParameterization");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGe_OdGeKnotParameterization()));
  }
  break;
  case OdRxPropertyVariant::kGiLightAttenuation_AttenuationType:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiLightAttenuation::AttenuationType");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiLightAttenuation_AttenuationType()));
  }
  break;
  case OdRxPropertyVariant::kGiDrawable_DrawableType:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiDrawable::DrawableType");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiDrawable_DrawableType()));
  }
  break;
  case OdRxPropertyVariant::kGiShadowParameters_ShadowType:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiShadowParameters::ShadowType");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiShadowParameters_ShadowType()));
  }
  break;
  case OdRxPropertyVariant::kGiShadowParameters_ExtendedLightShape:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiShadowParameters::ExtendedLightShape");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiShadowParameters_ExtendedLightShape()));
  }
  break;
  case OdRxPropertyVariant::kGiViewportTraits_DefaultLightingType:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiViewportTraits::DefaultLightingType");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiViewportTraits_DefaultLightingType()));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialTraits_LuminanceMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::LuminanceMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMaterialTraits_LuminanceMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialTraits_GlobalIlluminationMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::GlobalIlluminationMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMaterialTraits_GlobalIlluminationMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialTraits_FinalGatherMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::FinalGatherMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMaterialTraits_FinalGatherMode()));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialTraits_ChannelFlags:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::ChannelFlags");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMaterialTraits_ChannelFlags()));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialTraits_Mode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::Mode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMaterialTraits_Mode()));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialTraits_IlluminationModel:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::IlluminationModel");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiMaterialTraits_IlluminationModel()));
  }
  break;
  case OdRxPropertyVariant::kGiVisualStyle_Type:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiVisualStyle::Type");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiVisualStyle_Type()));
  }
  break;
  case OdRxPropertyVariant::kGiVisualStyleProperties_FaceColorMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiVisualStyleProperties::FaceColorMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiVisualStyleProperties_FaceColorMode()));
  }
  break;
  case OdRxPropertyVariant::kGiVisualStyleProperties_EdgeModel:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiVisualStyleProperties::EdgeModel");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiVisualStyleProperties_EdgeModel()));
  }
  break;
  case OdRxPropertyVariant::kGiFaceStyle_FaceColorMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiFaceStyle::FaceColorMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiFaceStyle_FaceColorMode()));
  }
  break;
  case OdRxPropertyVariant::kGiEdgeStyle_EdgeModel:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiEdgeStyle::EdgeModel");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiEdgeStyle_EdgeModel()));
  }
  break;
  case OdRxPropertyVariant::kGiToneOperatorParameters_ExteriorDaylightMode:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiToneOperatorParameters::ExteriorDaylightMode");
    xmlValueNode->SetAttribute("val", OdString().format(L"%d", info.value.getGiToneOperatorParameters_ExteriorDaylightMode()));
  }
  break;
  case OdRxPropertyVariant::kGeMatrix2d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeMatrix2d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeMatrix2d(%f, %f, %f, %f, %f, %f, %f, %f, %f)", 
      info.value.getGeMatrix2d()[0][0], info.value.getGeMatrix2d()[0][1], info.value.getGeMatrix2d()[0][2],
      info.value.getGeMatrix2d()[1][0], info.value.getGeMatrix2d()[1][1], info.value.getGeMatrix2d()[1][2],
      info.value.getGeMatrix2d()[2][0], info.value.getGeMatrix2d()[2][1], info.value.getGeMatrix2d()[2][2]));
  }
  break;
  case OdRxPropertyVariant::kGeMatrix3d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeMatrix3d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeMatrix2d(%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f)", 
      info.value.getGeMatrix3d()[0][0], info.value.getGeMatrix3d()[0][1], info.value.getGeMatrix3d()[0][2],info.value.getGeMatrix3d()[0][3],
      info.value.getGeMatrix3d()[1][0], info.value.getGeMatrix3d()[1][1], info.value.getGeMatrix3d()[1][2],info.value.getGeMatrix3d()[1][3],
      info.value.getGeMatrix3d()[2][0], info.value.getGeMatrix3d()[2][1], info.value.getGeMatrix3d()[2][2],info.value.getGeMatrix3d()[2][3],
      info.value.getGeMatrix3d()[3][0], info.value.getGeMatrix3d()[3][1], info.value.getGeMatrix3d()[3][2],info.value.getGeMatrix3d()[3][3]));
  }
  break;
  case OdRxPropertyVariant::kGeScale3d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeScale3d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeScale3d(%f, %f, %f)", info.value.getGeScale3d().sx, info.value.getGeScale3d().sy,
      info.value.getGeScale3d().sz));
  }
  break;
  case OdRxPropertyVariant::kTimeStamp:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdTimeStamp");
    xmlValueNode->SetAttribute("val", OdString().format(L"%lld", info.value.getTimeStamp().packedValue()));
  }
  break;
  case OdRxPropertyVariant::kGeExtents2d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeExtents2d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeExtents2d((%f, %f) (%f, %f))", 
      info.value.getGeExtents2d().minPoint().x, info.value.getGeExtents2d().minPoint().y,
      info.value.getGeExtents2d().maxPoint().x, info.value.getGeExtents2d().maxPoint().y));
  }
  break;
  case OdRxPropertyVariant::kGeExtents3d:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeExtents3d");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeExtents3d((%f, %f, %f) (%f, %f, %f))", 
      info.value.getGeExtents3d().minPoint().x, info.value.getGeExtents3d().minPoint().y, info.value.getGeExtents3d().minPoint().z,
      info.value.getGeExtents3d().maxPoint().x, info.value.getGeExtents3d().maxPoint().y, info.value.getGeExtents3d().maxPoint().z));
  }
  break;
  case OdRxPropertyVariant::kGeQuaternion:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGeQuaternion");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGeQuaternion(%f, %f, %f, %f)",
      info.value.getGeQuaternion().w, info.value.getGeQuaternion().x, info.value.getGeQuaternion().y, info.value.getGeQuaternion().z));
  }
  break;
  case OdRxPropertyVariant::kGiLightAttenuation:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiLightAttenuation");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGiLightAttenuation(%d, %d, %f, %f)",
      info.value.getGiLightAttenuation().attenuationType(), info.value.getGiLightAttenuation().useLimits(), 
      info.value.getGiLightAttenuation().startLimit(), info.value.getGiLightAttenuation().endLimit()));
  }
  break;
  case OdRxPropertyVariant::kGiSkyParameters:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiSkyParameters");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGiSkyParameters(%d, %f, %f, %f, %f, %d, %d, %d, %f, %f, %f, %f, %d, %f, %f, %f, %f, %f)",
      info.value.getGiSkyParameters().illumination(),
      info.value.getGiSkyParameters().intensityFactor(),
      info.value.getGiSkyParameters().haze(),
      info.value.getGiSkyParameters().horizonHeight(),
      info.value.getGiSkyParameters().horizonBlur(),
      info.value.getGiSkyParameters().groundColor().color(),
      info.value.getGiSkyParameters().nightColor().color(),
      info.value.getGiSkyParameters().aerialPerspective(),
      info.value.getGiSkyParameters().visibilityDistance(),
      info.value.getGiSkyParameters().diskScale(),
      info.value.getGiSkyParameters().glowIntensity(),
      info.value.getGiSkyParameters().diskIntensity(),
      info.value.getGiSkyParameters().solarDiskSamples(),
      info.value.getGiSkyParameters().sunDirection().x,
      info.value.getGiSkyParameters().sunDirection().y,
      info.value.getGiSkyParameters().sunDirection().z,
      info.value.getGiSkyParameters().redBlueShift(),
      info.value.getGiSkyParameters().saturation()
    ));
  }
  break;
  case OdRxPropertyVariant::kGiShadowParameters:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiShadowParameters");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGiShadowParameters(%d, %d, %d, %d, %d, %d, %f, %f, %f)",
      info.value.getGiShadowParameters().shadowsOn(),
      info.value.getGiShadowParameters().shadowType(),
      info.value.getGiShadowParameters().shadowMapSize(),
      info.value.getGiShadowParameters().shadowMapSoftness(),
      info.value.getGiShadowParameters().shapeVisibility(),
      info.value.getGiShadowParameters().extendedLightShape(),
      info.value.getGiShadowParameters().extendedLightLength(),
      info.value.getGiShadowParameters().extendedLightWidth(),
      info.value.getGiShadowParameters().extendedLightRadius()
    ));
  }
  break;
  case OdRxPropertyVariant::kGiColorRGB:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiColorRGB");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGiColorRGB(%f, %f, %f)", info.value.getGiColorRGB().red, info.value.getGiColorRGB().green,
      info.value.getGiColorRGB().blue));
  }
  break;
  case OdRxPropertyVariant::kGiMaterialColor:
  {
    TiXmlElement* xmlValueNode = new TiXmlElement("value");
    xmlNode->LinkEndChild(xmlValueNode);
    xmlValueNode->SetAttribute("type", "OdGiMaterialColor");
    xmlValueNode->SetAttribute("val", OdString().format(L"OdGiMaterialColor(%d, %f, %d)", info.value.getGiMaterialColor().method(), info.value.getGiMaterialColor().factor(),
      info.value.getGiMaterialColor().color().color()));
  }
  case OdRxPropertyVariant::kBool | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getBoolArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdBool");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getBoolArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kInt8 | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getInt8Array().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdInt8");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getInt8Array()[i]));
    }
    break;
  case OdRxPropertyVariant::kInt16 | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getInt16Array().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdInt16");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getInt16Array()[i]));
    }
    break;
  case OdRxPropertyVariant::kInt32 | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getInt32Array().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdInt32");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getInt32Array()[i]));
    }
    break;
  case OdRxPropertyVariant::kInt64 | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getInt64Array().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdInt64");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%lld", info.value.getInt64Array()[i]));
    }
    break;
  case OdRxPropertyVariant::kDouble | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getDoubleArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdDouble");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%f", info.value.getDoubleArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGePoint2d | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGePoint2dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGePoint2d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGePoint2d(%f, %f)", info.value.getGePoint2dArray()[i].x, info.value.getGePoint2dArray()[i].y));
    }
    break;
  case OdRxPropertyVariant::kGeVector2d | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGeVector2dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeVector2d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeVector2d(%f, %f)", info.value.getGeVector2dArray()[i].x, info.value.getGeVector2dArray()[i].y));
    }
    break;
  case OdRxPropertyVariant::kGePoint3d | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGePoint3dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGePoint3d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGePoint3d(%f, %f, %f)", info.value.getGePoint3dArray()[i].x, info.value.getGePoint3dArray()[i].y,
        info.value.getGePoint3dArray()[i].z));
    }
    break;
  case OdRxPropertyVariant::kGeVector3d | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGeVector3dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeVector3d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeVector3d(%f, %f, %f)", info.value.getGeVector3dArray()[i].x, info.value.getGeVector3dArray()[i].y,
        info.value.getGeVector3dArray()[i].z));
    }
    break;
  case OdRxPropertyVariant::kCmEntityColor | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getCmEntityColorArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdCmEntityColor");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getCmEntityColorArray()[i].color()));
    }
    break;
  case OdRxPropertyVariant::kCmTransparency | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getCmTransparencyArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdCmTransparency");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getCmTransparencyArray()[i].serializeOut()));
    }
    break;
  case OdRxPropertyVariant::kString | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getStringArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdString");
      xmlValueNode->SetAttribute("val",  
        (-1 != info.value.getStringArray()[i].find(OdString(L"0000")) || 
          -1 != info.value.getStringArray()[i].find(file_name)) || -1 != info.value.getStringArray()[i].find(L"kMillimeter") || -1 != info.value.getStringArray()[i].find(L"Inches") ?
        OdString(xmlValueNode->Attribute("val")) + OdString(L"****************") : OdAnsiString(xmlValueNode->Attribute("val")) + OdAnsiString(info.value.getStringArray()[i], CP_UTF_8));
    }
    break;
  case OdRxPropertyVariant::kAnsiString | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getAnsiStringArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdAnsiString");
      xmlValueNode->SetAttribute("val", OdAnsiString(xmlValueNode->Attribute("val")) + info.value.getAnsiStringArray()[i]);
    }
    break;
  case OdRxPropertyVariant::kGiMrExposureType | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrExposureTypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrExposureType");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrExposureTypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrShadowMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrShadowModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrShadowMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrShadowModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrFinalGatheringMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrFinalGatheringModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrFinalGatheringMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrFinalGatheringModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrDiagnosticMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrDiagnosticModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrDiagnosticMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrDiagnosticModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrDiagnosticPhotonMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrDiagnosticPhotonModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrDiagnosticPhotonMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrDiagnosticPhotonModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrDiagnosticBSPMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrDiagnosticBSPModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrDiagnosticBSPMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrDiagnosticBSPModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrExportMIMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrExportMIModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrExportMIMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrExportMIModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMrTileOrder | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMrTileOrderArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMrTileOrder");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMrTileOrderArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiLightingMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiLightingModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiLightingMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiLightingModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiFilterType | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiFilterTypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiFilterType");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiFilterTypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kCmEntityColor_ColorMethod | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getCmEntityColor_ColorMethodArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdCmEntityColor::ColorMethod");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getCmEntityColor_ColorMethodArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kDb_LineWeight | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getDb_LineWeightArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdDb::LineWeight");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getDb_LineWeightArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kDb_UnitsValue | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getDb_UnitsValueArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdDb::UnitsValue");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getDb_UnitsValueArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiDgLinetypeModifiers_WidthMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiDgLinetypeModifiers_WidthModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiDgLinetypeModifiers::WidthMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiDgLinetypeModifiers_WidthModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiDgLinetypeModifiers_ShiftMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiDgLinetypeModifiers_ShiftModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiDgLinetypeModifiers::ShiftMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiDgLinetypeModifiers_ShiftModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiDgLinetypeModifiers_CornersMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiDgLinetypeModifiers_CornersModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiDgLinetypeModifiers::CornersMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiDgLinetypeModifiers_CornersModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGe_OdGeKnotParameterization | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGe_OdGeKnotParameterizationArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGe::OdGeKnotParameterization");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGe_OdGeKnotParameterizationArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiLightAttenuation_AttenuationType | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiLightAttenuation_AttenuationTypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiLightAttenuation::AttenuationType");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiLightAttenuation_AttenuationTypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiDrawable_DrawableType | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiDrawable_DrawableTypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiDrawable::DrawableType");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiDrawable_DrawableTypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiShadowParameters_ShadowType | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiShadowParameters_ShadowTypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiShadowParameters::ShadowType");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiShadowParameters_ShadowTypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiShadowParameters_ExtendedLightShape | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiShadowParameters_ExtendedLightShapeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiShadowParameters::ExtendedLightShape");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiShadowParameters_ExtendedLightShapeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiViewportTraits_DefaultLightingType | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiViewportTraits_DefaultLightingTypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiViewportTraits::DefaultLightingType");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiViewportTraits_DefaultLightingTypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMaterialTraits_LuminanceMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMaterialTraits_LuminanceModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::LuminanceMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMaterialTraits_LuminanceModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMaterialTraits_GlobalIlluminationMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMaterialTraits_GlobalIlluminationModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::GlobalIlluminationMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMaterialTraits_GlobalIlluminationModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMaterialTraits_FinalGatherMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMaterialTraits_FinalGatherModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::FinalGatherMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMaterialTraits_FinalGatherModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMaterialTraits_ChannelFlags | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMaterialTraits_ChannelFlagsArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::ChannelFlags");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMaterialTraits_ChannelFlagsArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMaterialTraits_Mode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMaterialTraits_ModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::Mode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMaterialTraits_ModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiMaterialTraits_IlluminationModel | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiMaterialTraits_IlluminationModelArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialTraits::IlluminationModel");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiMaterialTraits_IlluminationModelArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiVisualStyle_Type | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiVisualStyle_TypeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiVisualStyle::Type");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiVisualStyle_TypeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiVisualStyleProperties_FaceColorMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiVisualStyleProperties_FaceColorModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiVisualStyleProperties::FaceColorMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiVisualStyleProperties_FaceColorModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiVisualStyleProperties_EdgeModel | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiVisualStyleProperties_EdgeModelArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiVisualStyleProperties::EdgeModel");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiVisualStyleProperties_EdgeModelArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiFaceStyle_FaceColorMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiFaceStyle_FaceColorModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiFaceStyle::FaceColorMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiFaceStyle_FaceColorModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiEdgeStyle_EdgeModel | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiEdgeStyle_EdgeModelArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiEdgeStyle::EdgeModel");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiEdgeStyle_EdgeModelArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGiToneOperatorParameters_ExteriorDaylightMode | OdVariant::kArray:
    for (unsigned int i = 0; i < info.value.getGiToneOperatorParameters_ExteriorDaylightModeArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiToneOperatorParameters::ExteriorDaylightMode");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%d", info.value.getGiToneOperatorParameters_ExteriorDaylightModeArray()[i]));
    }
    break;
  case OdRxPropertyVariant::kGeMatrix2d | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGeMatrix2dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeMatrix2d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeMatrix2d(%f, %f, %f, %f, %f, %f, %f, %f, %f)",
        info.value.getGeMatrix2dArray()[i][0][0], info.value.getGeMatrix2dArray()[i][0][1], info.value.getGeMatrix2dArray()[i][0][2],
        info.value.getGeMatrix2dArray()[i][1][0], info.value.getGeMatrix2dArray()[i][1][1], info.value.getGeMatrix2dArray()[i][1][2],
        info.value.getGeMatrix2dArray()[i][2][0], info.value.getGeMatrix2dArray()[i][2][1], info.value.getGeMatrix2dArray()[i][2][2]));
    }
  }
  break;
  case OdRxPropertyVariant::kGeMatrix3d | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGeMatrix3dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeMatrix3d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeMatrix2d(%f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f, %f)",
        info.value.getGeMatrix3dArray()[i][0][0], info.value.getGeMatrix3dArray()[i][0][1], info.value.getGeMatrix3dArray()[i][0][2], info.value.getGeMatrix3dArray()[i][0][3],
        info.value.getGeMatrix3dArray()[i][1][0], info.value.getGeMatrix3dArray()[i][1][1], info.value.getGeMatrix3dArray()[i][1][2], info.value.getGeMatrix3dArray()[i][1][3],
        info.value.getGeMatrix3dArray()[i][2][0], info.value.getGeMatrix3dArray()[i][2][1], info.value.getGeMatrix3dArray()[i][2][2], info.value.getGeMatrix3dArray()[i][2][3],
        info.value.getGeMatrix3dArray()[i][3][0], info.value.getGeMatrix3dArray()[i][3][1], info.value.getGeMatrix3dArray()[i][3][2], info.value.getGeMatrix3dArray()[i][3][3]));
    }
  }
  break;
  case OdRxPropertyVariant::kGeScale3d | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGeScale3dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeScale3d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeScale3d(%f, %f, %f)", info.value.getGeScale3dArray()[i].sx, info.value.getGeScale3dArray()[i].sy,
        info.value.getGeScale3dArray()[i].sz));
    }
  }
  break;
  case OdRxPropertyVariant::kTimeStamp | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getTimeStampArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdTimeStamp");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"%lld", info.value.getTimeStampArray()[i].packedValue()));
    }
  }
  break;
  case OdRxPropertyVariant::kGeExtents2d | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGeExtents2dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeExtents2d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeExtents2d((%f, %f) (%f, %f))",
        info.value.getGeExtents2dArray()[i].minPoint().x, info.value.getGeExtents2dArray()[i].minPoint().y,
        info.value.getGeExtents2dArray()[i].maxPoint().x, info.value.getGeExtents2dArray()[i].maxPoint().y));
    }
  }
  break;
  case OdRxPropertyVariant::kGeExtents3d | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGeExtents3dArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeExtents3d");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeExtents3d((%f, %f, %f) (%f, %f, %f))",
        info.value.getGeExtents3dArray()[i].minPoint().x, info.value.getGeExtents3dArray()[i].minPoint().y, info.value.getGeExtents3dArray()[i].minPoint().z,
        info.value.getGeExtents3dArray()[i].maxPoint().x, info.value.getGeExtents3dArray()[i].maxPoint().y, info.value.getGeExtents3dArray()[i].maxPoint().z));
    }
  }
  break;
  case OdRxPropertyVariant::kGeQuaternion | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGeQuaternionArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGeQuaternion");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGeQuaternion(%f, %f, %f, %f)",
        info.value.getGeQuaternionArray()[i].w, info.value.getGeQuaternionArray()[i].x, info.value.getGeQuaternionArray()[i].y, info.value.getGeQuaternionArray()[i].z));
    }
  }
  break;
  case OdRxPropertyVariant::kGiLightAttenuation | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGiLightAttenuationArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiLightAttenuation");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGiLightAttenuation(%d, %d, %f, %f)",
        info.value.getGiLightAttenuationArray()[i].attenuationType(), info.value.getGiLightAttenuationArray()[i].useLimits(),
        info.value.getGiLightAttenuationArray()[i].startLimit(), info.value.getGiLightAttenuationArray()[i].endLimit()));
    }
  }
  break;
  case OdRxPropertyVariant::kGiSkyParameters | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGiSkyParametersArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiSkyParameters");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGiSkyParameters(%d, %f, %f, %f, %f, %d, %d, %d, %f, %f, %f, %f, %d, %f, %f, %f, %f, %f)",
        info.value.getGiSkyParametersArray()[i].illumination(),
        info.value.getGiSkyParametersArray()[i].intensityFactor(),
        info.value.getGiSkyParametersArray()[i].haze(),
        info.value.getGiSkyParametersArray()[i].horizonHeight(),
        info.value.getGiSkyParametersArray()[i].horizonBlur(),
        info.value.getGiSkyParametersArray()[i].groundColor().color(),
        info.value.getGiSkyParametersArray()[i].nightColor().color(),
        info.value.getGiSkyParametersArray()[i].aerialPerspective(),
        info.value.getGiSkyParametersArray()[i].visibilityDistance(),
        info.value.getGiSkyParametersArray()[i].diskScale(),
        info.value.getGiSkyParametersArray()[i].glowIntensity(),
        info.value.getGiSkyParametersArray()[i].diskIntensity(),
        info.value.getGiSkyParametersArray()[i].solarDiskSamples(),
        info.value.getGiSkyParametersArray()[i].sunDirection().x,
        info.value.getGiSkyParametersArray()[i].sunDirection().y,
        info.value.getGiSkyParametersArray()[i].sunDirection().z,
        info.value.getGiSkyParametersArray()[i].redBlueShift(),
        info.value.getGiSkyParametersArray()[i].saturation()
      ));
    }
  }
  break;
  case OdRxPropertyVariant::kGiShadowParameters | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGiShadowParametersArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiShadowParameters");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGiShadowParameters(%d, %d, %d, %d, %d, %d, %f, %f, %f)",
        info.value.getGiShadowParametersArray()[i].shadowsOn(),
        info.value.getGiShadowParametersArray()[i].shadowType(),
        info.value.getGiShadowParametersArray()[i].shadowMapSize(),
        info.value.getGiShadowParametersArray()[i].shadowMapSoftness(),
        info.value.getGiShadowParametersArray()[i].shapeVisibility(),
        info.value.getGiShadowParametersArray()[i].extendedLightShape(),
        info.value.getGiShadowParametersArray()[i].extendedLightLength(),
        info.value.getGiShadowParametersArray()[i].extendedLightWidth(),
        info.value.getGiShadowParametersArray()[i].extendedLightRadius()
      ));
    }
  }
  break;
  case OdRxPropertyVariant::kGiColorRGB | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGiColorRGBArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiColorRGB");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGiColorRGB(%f, %f, %f)", info.value.getGiColorRGBArray()[i].red, info.value.getGiColorRGBArray()[i].green,
        info.value.getGiColorRGBArray()[i].blue));
    }
  }
  case OdRxPropertyVariant::kGiMaterialColor | OdVariant::kArray:
  {
    for (unsigned int i = 0; i < info.value.getGiMaterialColorArray().size(); ++i)
    {
      TiXmlElement* xmlValueNode = new TiXmlElement("value");
      xmlNode->LinkEndChild(xmlValueNode);
      xmlValueNode->SetAttribute("type", "OdGiMaterialColor");
      xmlValueNode->SetAttribute("val", OdString(xmlValueNode->Attribute("val")) + OdString().format(L"OdGiMaterialColor(%d, %f, %d)", info.value.getGiMaterialColorArray()[i].method(), info.value.getGiMaterialColorArray()[i].factor(),
        info.value.getGiMaterialColorArray()[i].color().color()));
    }
  }
  }

  OdArray<PropertyInfo>::size_type prop_size = info.subProperties.size();
  if (0 != prop_size)
  {
    TiXmlElement* xmlPropsNode = new TiXmlElement("SubProperties");
    xmlNode->LinkEndChild(xmlPropsNode);
    std::sort(info.subProperties.begin(), info.subProperties.end(), LessCase());
    for (OdArray<PropertyInfo>::size_type i = 0; i < prop_size; ++i)
    {
      xmlProperty(info.subProperties[i], xmlPropsNode, file_name);
    }
  }
}

/********************************************************************************/
/* Create XML node from Hierarchy Tree Node                                     */
/********************************************************************************/
void xmlCDANodes(const OdRxModelTreeBaseNodePtr pTreeNode, TiXmlElement* parentXmlNode, const OdString& file_name)
{
  OdString name = pTreeNode->getNodeName();

  TiXmlElement* xmlNode = new TiXmlElement("node");
  parentXmlNode->LinkEndChild(xmlNode);

  xmlNode->SetAttribute("name", OdAnsiString(name, CP_UTF_8));
  xmlNode->SetAttribute("UniqueSourceID", OdAnsiString().format("%llu", pTreeNode->getUniqueSourceID()));
#if WRITE_DB_ID
  xmlNode->SetAttribute("UniqueDBID", OdAnsiString().format("%llu", pTreeNode->getUniqueDBID()));
#else
  xmlNode->SetAttribute("UniqueDBID", OdAnsiString().format("%llu", "***"));
#endif
  xmlNode->SetAttribute("NodeType", OdString(nodeType(pTreeNode->getNodeType())));

  OdArray<PropertyInfo> info_array = pTreeNode->getProperties(); 
  OdArray<PropertyInfo>::size_type prop_size = info_array.size();
  if (0 != prop_size)
  {
    TiXmlElement* xmlPropsNode = new TiXmlElement("Properties");
    xmlNode->LinkEndChild(xmlPropsNode);
    std::sort(info_array.begin(), info_array.end(), LessCase());
    for (OdArray<PropertyInfo>::size_type i = 0; i < prop_size; ++i)
    {
      xmlProperty(info_array[i], xmlPropsNode, file_name);
    }
  }

  OdRxModelTreeBaseNodePtrArray child_array = pTreeNode->getChildren();
  OdRxModelTreeBaseNodePtrArray::size_type ch_size = child_array.size();
  if (0 != ch_size)
  {
    TiXmlElement* xmlChildNode = new TiXmlElement("Children");
    xmlNode->LinkEndChild(xmlChildNode);
    std::sort(child_array.begin(), child_array.end(), LessForNode());
    for (OdRxModelTreeBaseNodePtrArray::size_type i = 0; i < ch_size; ++i)
    {
      xmlCDANodes(child_array[i], xmlChildNode, file_name);
    }
  }
}

/********************************************************************************/
/* Create prefix information for for file.                                      */
/********************************************************************************/
OdString createFilePrefix(const bool create_properties_cache, const std::set<OdString>* collected_properties)
{
  if (NULL == collected_properties)
  {
    if (create_properties_cache)
      return L"CACHE";
    else
      return L"TREE";
  }
  if (0 == collected_properties->size())
    return L"TREE";
  else
    return L"PART_CACHE";
}

/********************************************************************************/
/* Create XML from Hierarchy Tree                                               */
/********************************************************************************/
OdSharedPtr<TiXmlDocument> xmlCDATree(const OdRxModelTreeBaseNodePtr pTree, const OdString& file_name, 
  const OdString& file_prefix)
{
   OdSharedPtr<TiXmlDocument> _xml = new TiXmlDocument;

  _xml->LinkEndChild(new TiXmlDeclaration("1.0", "UTF-8", "no"));

  OdString output_path = file_name;
  int i1 = file_name.reverseFind('\\');
  int i2 = file_name.reverseFind('/');
  int i = odmax(i1, i2);
  output_path = output_path.left(i + 1);
  OdString output_file = file_name.mid(i + 1);
  i = output_file.find(L'.');
  if (i != -1)
    output_file = output_file.left(i);

  TiXmlElement* root = new TiXmlElement(output_file);
  _xml->LinkEndChild(root);

  xmlCDANodes(pTree, root, file_name);

  if (ParamHolder::instance().needCreateXMLBenchmark())
  {
    _xml->SaveFile(OdString().format(L"%ls_%ls.xml", file_name.c_str(), file_prefix.c_str()));
  }

  return _xml;
}

void compareXMLProperty(TiXmlElement* sample, TiXmlElement* node, OdStringArray& error_list, std::map<OdString, std::set<OdString> >& exclusions)
{
  OdString node_name(sample->Parent()->Parent()->ToElement()->Attribute("name"));

  OdString sample_pr_val(sample->Value());
  OdString pr_val(node->Value());
  if (0 != sample_pr_val.compare(pr_val))
  {
    error_list.append(OdString().format(L"Node %ls has invalid key %ls", node_name.c_str(), pr_val.c_str()));
  }

  OdString sample_name(sample->Attribute("name"));
  OdString name(node->Attribute("name"));
  if (0 != sample_name.compare(name))
  {
    error_list.append(OdString().format(L"Node %ls property name : %ls != %ls", node_name.c_str(), sample_name.c_str(), name.c_str()));
  }

  OdString sample_localizedName(sample->Attribute("localizedName"));
  OdString localizedName(node->Attribute("localizedName"));
  if (0 != sample_localizedName.compare(localizedName))
  {
    error_list.append(OdString().format(L"Node %ls property %ls localizedName : %ls != %ls", node_name.c_str(), sample_name.c_str(), sample_localizedName.c_str(), localizedName.c_str()));
  }
  OdString sample_uiPlacement(sample->Attribute("uiPlacement"));
  OdString uiPlacement(node->Attribute("uiPlacement"));
  if (0 != sample_uiPlacement.compare(uiPlacement))
  {
    error_list.append(OdString().format(L"Node %ls property %ls uiPlacement : %ls != %ls", node_name.c_str(), sample_name.c_str(), sample_uiPlacement.c_str(), uiPlacement.c_str()));
  }
  OdString sample_weight(sample->Attribute("weight"));
  OdString weight(node->Attribute("weight"));
  if (0 != sample_weight.compare(weight))
  {
    error_list.append(OdString().format(L"Node %ls property %ls weight : %ls != %ls", node_name.c_str(), sample_name.c_str(), sample_weight.c_str(), weight.c_str()));
  }

  TiXmlElement* sample_child_elem = sample->FirstChildElement();
  TiXmlElement* child_elem = node->FirstChildElement();

  if (NULL == sample_child_elem || NULL == child_elem)
  {
    if (NULL != sample_child_elem || NULL != child_elem)
      error_list.append(OdString().format(L"Node %ls property %ls is not the same", node_name.c_str(), sample_name.c_str()));
    return;
  }

  while (NULL != sample_child_elem && NULL != child_elem)
  {
    OdString elem_value(child_elem->Value());
    OdString sample_elem_value(sample_child_elem->Value());
    if (0 != sample_elem_value.compare(elem_value))
    {
      error_list.append(OdString().format(L"Nodes %ls are not the same", sample_name.c_str()));
      return;
    }

    if (sample_elem_value == L"value")
    {
      OdString sample_val_type(sample_child_elem->Attribute("type"));
      OdString val_type(child_elem->Attribute("type"));
      if ( 0 != sample_val_type.compare(val_type))
      {
        error_list.append(OdString().format(L"Node %ls property %ls valueType is not the same: %ls != %ls", node_name.c_str(), sample_name.c_str(),
          sample_val_type.c_str(), val_type.c_str()));
      }
      OdString sample_val(sample_child_elem->Attribute("val"));
      OdString val(child_elem->Attribute("val"));
      if (0 != sample_val.compare(L"****************") && 0 != sample_val.compare(val))
      {
        bool is_equal_IFC_nan = ((0 == val.compare(L"nan")) && (0 == sample_val.compare(L"nan(snan)")));

        if (!is_equal_IFC_nan) // for IFC
        {
          error_list.append(OdString().format(L"Node %ls property %ls value is not the same: %ls != %ls", node_name.c_str(), sample_name.c_str(),
            sample_val.c_str(), val.c_str()));
        }
      }
    }
    else if (sample_elem_value == L"SubProperties")
    {
      TiXmlElement* sample_prop = sample_child_elem->FirstChildElement();
      TiXmlElement* prop = child_elem->FirstChildElement();
      while (NULL != sample_prop && NULL != prop)
      {
        bool is_exclusion_found = (exclusions.end() != exclusions.find(node_name)) &&
          (exclusions[node_name].end() != exclusions[node_name].find(OdString(sample_prop->Attribute("name"))));
        if (!is_exclusion_found)
          compareXMLProperty(sample_prop, prop, error_list, exclusions);
        sample_prop = sample_prop->NextSiblingElement();
        prop = prop->NextSiblingElement();
      }
      if (NULL != sample_prop || NULL != prop)
        error_list.append(OdString().format(L"Nodes %ls don't have same number of properties", sample_name.c_str()));
    }
    sample_child_elem = sample_child_elem->NextSiblingElement();
    child_elem = child_elem->NextSiblingElement();
  }
  if (NULL != sample_child_elem || NULL != child_elem)
    error_list.append(OdString().format(L"Node %ls property %ls is not the same", node_name.c_str(), sample_name.c_str()));
}

void compareXMLNode(TiXmlElement* sample, TiXmlElement* node, OdStringArray& error_list, std::map<OdString, std::set<OdString> >& exclusions)
{

  OdString sample_pr_val(sample->Value());
  OdString pr_val(node->Value());
  if (0 != sample_pr_val.compare(pr_val))
  {
    error_list.append(OdString().format(L"Database has invalid key %ls", pr_val.c_str()));
  }

  OdString sample_name(sample->Attribute("name"));
  OdString name(node->Attribute("name"));
  if (0 != sample_name.compare(name))
  {
    error_list.append(OdString().format(L"Node name : %ls != %ls", sample_name.c_str(), name.c_str()));
  }
  OdString sample_ID(sample->Attribute("UniqueSourceID"));
  OdString ID(node->Attribute("UniqueSourceID"));
  if (0 != sample_ID.compare(ID))
  {
    error_list.append(OdString().format(L"ID for node %ls : %ls != %ls",sample_name.c_str(), sample_ID.c_str(), ID.c_str()));
  }
  //OdString sample_DB_ID(sample->Attribute("UniqueDBID"));
  //OdString DB_ID(node->Attribute("UniqueDBID"));
  //if (0 != sample_DB_ID.compare(DB_ID))
  //{
  //  error_list.append(OdString().format(L"DB_ID for node %ls : %ls != %ls",sample_name.c_str(), sample_DB_ID.c_str(), DB_ID.c_str()));
  //}
  OdString sample_type(sample->Attribute("NodeType"));
  OdString type(node->Attribute("NodeType"));
  if (0 != sample_type.compare(type))
  {
    error_list.append(OdString().format(L"Type for node %ls : %ls != %ls", sample_name.c_str(), sample_type.c_str(), type.c_str()));
  }

  TiXmlElement* sample_child_elem = sample->FirstChildElement();
  TiXmlElement* child_elem = node->FirstChildElement();
  
  if (NULL == sample_child_elem || NULL == child_elem)
  {
    if (NULL != sample_child_elem || NULL != child_elem)
      error_list.append(OdString().format(L"Nodes %ls are not the same", sample_name.c_str()));
    return;
  }

  while (NULL != sample_child_elem && NULL != child_elem)
  {
    OdString elem_value(child_elem->Value());
    OdString sample_elem_value(sample_child_elem->Value());
    if (0 != sample_elem_value.compare(elem_value))
    {
      error_list.append(OdString().format(L"Nodes %ls are not the same", sample_name.c_str()));
      return;
    }

    if (sample_elem_value == L"Properties")
    {
      TiXmlElement* sample_prop = sample_child_elem->FirstChildElement();
      TiXmlElement* prop = child_elem->FirstChildElement();
      while (NULL != sample_prop && NULL != prop)
      {
        bool is_exclusion_found = (exclusions.end() != exclusions.find(sample_name)) &&
          (exclusions[sample_name].end() != exclusions[sample_name].find(OdString(sample_prop->Attribute("name"))));
        if (!is_exclusion_found)
          compareXMLProperty(sample_prop, prop, error_list, exclusions);
        sample_prop = sample_prop->NextSiblingElement();
        prop = prop->NextSiblingElement();
      }
      if (NULL != sample_prop || NULL != prop)
        error_list.append(OdString().format(L"Nodes %ls don't have same number of properties", sample_name.c_str()));
    }
    else
    {
      if (sample_elem_value == L"Children")
      {
        TiXmlElement* sample_child = sample_child_elem->FirstChildElement();
        TiXmlElement* child = child_elem->FirstChildElement();
        while (NULL != sample_child && NULL != child)
        {
          compareXMLNode(sample_child, child, error_list, exclusions);
          sample_child = sample_child->NextSiblingElement();
          child = child->NextSiblingElement();
        }
        if (NULL != sample_child || NULL != child)
          error_list.append(OdString().format(L"Nodes %ls don't have same number of children", sample_name.c_str()));
      }
    }
    sample_child_elem = sample_child_elem->NextSiblingElement();
    child_elem = child_elem->NextSiblingElement();
  }
  if (NULL != sample_child_elem || NULL != child_elem)
    error_list.append(OdString().format(L"Nodes %ls are not the same", sample_name.c_str()));

}

void compareXMLTree(OdSharedPtr<TiXmlDocument> xml1, OdSharedPtr<TiXmlDocument> xml2, std::map<OdString, std::set<OdString> >& exclusions)
{
  OdStringArray error_list;

  TiXmlElement* sample_root = xml1->RootElement();
  TiXmlElement* root = xml2->RootElement();

  TiXmlElement* sample_child_elem = sample_root->FirstChildElement();
  TiXmlElement* child_elem = root->FirstChildElement();
  if (NULL == sample_child_elem || NULL == child_elem)
  {
    if (NULL != sample_child_elem || NULL != child_elem)
      error_list.append(OdString().format(L"File haven't database node"));
    return;
  }

  compareXMLNode(sample_child_elem, child_elem, error_list, exclusions);
  for (OdStringArray::size_type i = 0; i < error_list.size(); ++i)
  {
    odPrintConsoleString(L"%ls\n", error_list[i].c_str());
  }
  TEST_ASSERT(0 == error_list.size());
}

void compareCDATrees(OdRxModelHierarchyTreeBasePtr pTree1, OdRxModelHierarchyTreeBasePtr pTree2, std::map<OdString, std::set<OdString> >& exclusions)
{
  TEST_ASSERT(!pTree1.isNull());
  TEST_ASSERT(!pTree2.isNull());
  OdRxModelTreeBaseNodePtr pDBNode1 = pTree1->getDatabaseNode();
  TEST_ASSERT(!pDBNode1.isNull());
  OdRxModelTreeBaseNodePtr pDBNode2 = pTree2->getDatabaseNode();
  TEST_ASSERT(!pDBNode2.isNull());

  compareCDANodes(pDBNode1, pDBNode2, exclusions);
}

void prepareExclusions(std::map<OdString, std::set<OdString> >& exclusions, OdRxModelTreeBaseNodePtr& pTree)
{
  std::map<OdString, std::set<OdString> >::iterator it = exclusions.find(L"***");
  if (it != exclusions.end())
  {
    exclusions.insert(std::make_pair(pTree->getNodeName(), it->second));
    exclusions.erase(it);
  }
}

void compareWithSavedTest(const OdRxObject* pDb, const OdString& file_name,  std::map<OdString,
  std::set<OdString> >& exclusions, const bool create_properties_cache, const bool class_dependent_hierarchy, 
  const bool class_dependent_property,  const std::set<OdString>* collected_properties)
{
  OdRxModelHierarchyTreeBasePtr pHierarchyTreeBase = OdRxModelHierarchyTreeBase::createObject();

  OdRxModelTreeBaseNodePtr pTree;
  if(NULL == collected_properties)
    pTree = pHierarchyTreeBase->createDatabaseHierarchyTree(pDb, create_properties_cache, class_dependent_hierarchy, class_dependent_property);
  else
    pTree = pHierarchyTreeBase->createDatabaseHierarchyTree(pDb, collected_properties, class_dependent_hierarchy, class_dependent_property);

  OdStreamBufPtr pStream = ::odrxSystemServices()->createFile(OdString().format(L"%ls_%ls.CDA", file_name.c_str(), 
    createFilePrefix(create_properties_cache, collected_properties).c_str()),
    Oda::FileAccessMode(Oda::kFileWrite | Oda::kFileRead), Oda::kShareDenyNo, Oda::kOpenAlways);


  OdTestTreeFiler pFiler(pStream, file_name);

  if (ParamHolder::instance().needCreateFileBenchmark())
  {
    //create sample
    pHierarchyTreeBase->serialize(&pFiler);
  }

  OdRxModelHierarchyTreeBasePtr pSampleHierarchyTreeBase = OdRxModelHierarchyTreeBase::createObject();
  pStream->rewind();
  pSampleHierarchyTreeBase->deserialize(&pFiler);

  prepareExclusions(exclusions, pTree);

  compareCDATrees(pHierarchyTreeBase, pSampleHierarchyTreeBase, exclusions);
}

void loadSaveTest(const OdRxObject* pDb, const OdString& file_name, const bool create_properties_cache, 
  const bool class_dependent_hierarchy, const bool class_dependent_property)
{
  OdRxModelHierarchyTreeBasePtr pHierarchyTreeBase = OdRxModelHierarchyTreeBase::createObject();

  OdRxModelTreeBaseNodePtr pTree = pHierarchyTreeBase->createDatabaseHierarchyTree(pDb, create_properties_cache, class_dependent_hierarchy, class_dependent_property);

  OdStreamBufPtr pStream = OdMemoryStream::createNew();

  OdTestTreeFiler pFiler(pStream, file_name);
  pHierarchyTreeBase->serialize(&pFiler);

  OdRxModelHierarchyTreeBasePtr pSavedHierarchyTreeBase = OdRxModelHierarchyTreeBase::createObject();
  pStream->rewind();
  pSavedHierarchyTreeBase->deserialize(&pFiler);

  std::map<OdString, std::set<OdString> > exclusions;
  compareCDATrees(pHierarchyTreeBase, pSavedHierarchyTreeBase, exclusions);
}

void XMLTest(const OdRxObject* pDb, const OdString& file_name, std::map<OdString,
  std::set<OdString> >& exclusions, const bool create_properties_cache, 
  const bool class_dependent_hierarchy, const bool class_dependent_property, const std::set<OdString>* collected_properties)
{
  OdRxModelHierarchyTreeBasePtr pHierarchyTreeBase = OdRxModelHierarchyTreeBase::createObject();

  OdRxModelTreeBaseNodePtr pNode0;
  if (NULL == collected_properties)
    pNode0 = pHierarchyTreeBase->createDatabaseHierarchyTree(pDb, create_properties_cache, class_dependent_hierarchy, class_dependent_property);
  else
    pNode0 = pHierarchyTreeBase->createDatabaseHierarchyTree(pDb, collected_properties, class_dependent_hierarchy, class_dependent_property);
  TEST_ASSERT(!pNode0.isNull());

  OdString file_prefix = createFilePrefix(create_properties_cache, collected_properties);

  OdSharedPtr<TiXmlDocument> xml = xmlCDATree(pNode0, file_name, file_prefix);

  OdSharedPtr<TiXmlDocument> sample_xml = new TiXmlDocument;
  sample_xml->LoadFile(OdString().format(L"%ls_%ls.xml", file_name.c_str(), file_prefix.c_str()));

  prepareExclusions(exclusions, pNode0);

  compareXMLTree(sample_xml, xml, exclusions);
}

void DumpToXML(const OdRxObject* pDb, const OdString& file_name, const bool create_properties_cache,
  const bool class_dependent_hierarchy, const bool class_dependent_property)
{
  /****************************************************************/
  /* Create OdRxModelHierarchyTreeBase object                    */
  /****************************************************************/
  OdRxModelHierarchyTreeBasePtr pHierarchyTreeBase = OdRxModelHierarchyTreeBase::createObject();

  /****************************************************************/
  /* Fill the hierarchical tree from the drawing database         */
  /****************************************************************/
  OdRxModelTreeBaseNodePtr pNode0 = pHierarchyTreeBase->createDatabaseHierarchyTree(pDb, create_properties_cache, class_dependent_hierarchy, class_dependent_property);
  TEST_ASSERT(!pNode0.isNull());

  OdString file_prefix = createFilePrefix(create_properties_cache, NULL);
  
  ParamHolder::instance().setNeedCreateBenchmark(true);
  ParamHolder::instance().setWriteFullCacheInfo(true);
  
  /****************************************************************/
  /* Create XML from the hierarchical tree                        */
  /****************************************************************/
  xmlCDATree(pNode0, file_name, file_prefix);
}


