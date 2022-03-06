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

#ifndef _PDF_PROPERTIES_INCLUDED_ 
#define _PDF_PROPERTIES_INCLUDED_

#include "RxDispatchImpl.h"
#include "RxVariantValue.h"
#include "DbDatabase.h"

/** \details
  <group OdPdfImport_Classes> 

  This class implements the properties for PDF importer.
*/
class PdfProperties : public OdRxDispatchImpl<>
{
  OdString         m_Password;
  OdString         m_Path;
  OdDbDatabasePtr  m_pDb;
  OdInt32          m_PageNumber;
  bool             m_ImportVectorGeometry;
  bool             m_ImportSolidFills;
  bool             m_ImportTrueTypeText;
  bool             m_ImportRasterImages;
//Gradient fills are imported as bitmap-images
  bool             m_ImportGradientFills;
  bool             m_ImportWidgets;
  OdUInt8          m_LayersUseType; 
 
 //m_LayersUseType:
 //0 - Use PDF Layers
 //   in this case, layers are created of the PDF_ <Layer name from the PDF document>.The visibility of the layers is determined by their 
 //   visibility in the pdf document. If the object is not on any of the layers, then it is installed on layers similar to case 1. 
 //   If the object in the pdf document is on more than one layer, then when it is imported, it is set to the "inner" layer of those on which it seted
 //1 - Create object layers
 //   Creating object layers(PDF_Geometry, PDF_Solid Fills, PDF_Images, and PDF_Text etc and PDF_Geometry_Invisible, PDF_Solid Fills_Invisible, 
 //   PDF_Images_Invisible, and PDF_Text _Invisible for invisible objects)
 //2 - Use current layer
 //   Importing all specified PDF objects to the current layer. (For invisible objects - invisible layers : PDF_Geometry_Invisible, 
 //     PDF_Solid Fills_Invisible, PDF_Images_Invisible, and PDF_Text _Invisible)

  bool             m_ImportAsBlock;
  bool             m_JoinLineAndArcSegments;
  bool             m_ConvertSolidsToHatches;
  bool             m_ApplyLineweight;
  bool             m_ImportTrueTypeTextAsGeometry;
  double           m_InsertionPointX;
  double           m_InsertionPointY;
  double           m_Scaling;
  double           m_Rotation;
  bool             m_UseProgressMeter;
  bool             m_UseGeometryOptimization;
  bool             m_ImportType3AsTrueTypeText;
  bool             m_UseRgbColor;
  bool             m_ImportInvalidTTTextAsGeometry;
  //bool             m_InferLinetypesFromCllinearDashes;
  OdString         m_ImagePath;
  bool             m_UseClipping;
  bool             m_UsePageBorderClipping;
  bool             m_TakeAddMeasurementFactors;
  bool             m_CombineTextObjects;
  double           m_CharSpaceFactor;
  double           m_SpaceFactor;
  bool             m_UsePdfTransparency;
  OdUInt8          m_ImportHyperlinkMethod;
  bool             m_UseImageClipping;
  bool             m_ConsiderINSUNITS;
  OdString         m_Type3TextDefaultFont;
  OdString         m_EbeddedFontsPath;
  bool             m_ExtractEmbeddedFonts;
  bool             m_TryFixUnicodeTable;

public:
  /** Constructor. 
  */
  PdfProperties() 
    :m_PageNumber(1) 
    ,m_ImportVectorGeometry(true)
    ,m_ImportSolidFills(true)
    ,m_ImportTrueTypeText(true)
    ,m_ImportRasterImages(true)
    ,m_LayersUseType(1) 
    ,m_ImportAsBlock(false)
    ,m_JoinLineAndArcSegments(true)
    ,m_ConvertSolidsToHatches(true)
    ,m_ApplyLineweight(true)
    ,m_InsertionPointX(0.0)
    ,m_InsertionPointY(0.0)
    ,m_Scaling(1.0)
    ,m_Rotation(0.0)
    ,m_ImportTrueTypeTextAsGeometry(false)
    ,m_ImportGradientFills(true)
    ,m_UseProgressMeter(true)
    ,m_UseGeometryOptimization(true)
    ,m_ImportType3AsTrueTypeText(false)
    ,m_UseRgbColor(false)
    ,m_ImportInvalidTTTextAsGeometry(true)
    ,m_UseClipping(false)
    ,m_UsePageBorderClipping(false)
    ,m_TakeAddMeasurementFactors(true)
    ,m_CombineTextObjects(false)
    ,m_CharSpaceFactor(0.6)
    ,m_SpaceFactor(1.5)
    ,m_UsePdfTransparency(false)
    ,m_ImportHyperlinkMethod(0)
    ,m_ImportWidgets(true)
    ,m_UseImageClipping(false)
    ,m_ConsiderINSUNITS(false)
    ,m_ExtractEmbeddedFonts(false)
    ,m_TryFixUnicodeTable(false)
  {}
  ODRX_DECLARE_DYNAMIC_PROPERTY_MAP( PdfProperties );
  /** Pseudo-Constructor. 
  */
  static OdRxDictionaryPtr createObject();

  /** \details
    Returns the password.
  */
  OdString get_Password() const 
  {
    return m_Password; 
  }

  /** \details
    Puts the password.
  */
  void put_Password(const OdString& pass )
  {
    m_Password = pass; 
  }

  /** \details
    Returns the database.
  */
  OdRxObjectPtr get_Database() const 
  { 
    return m_pDb.get(); 
  }

  /** \details
    Puts the database.
  */
  void put_Database( OdRxObject* obj )
  {
    m_pDb = obj; 
  }

  /** \details
    Returns the PDF path.
  */
  OdString get_PdfPath() const 
  { 
    return m_Path; 
  }

  /** \details
    Puts the PDF path.
  */
  void put_PdfPath(const OdString& path )
  { 
    m_Path = path; 
  }

  /** \details
    Returns the layout number.
  */
  OdInt32 get_PageNumber()const 
  {
    return m_PageNumber;
  }

  /** \details
    Puts the layout number.
    Start from 1
  */
  void put_PageNumber(const OdInt32 num)
  { 
    m_PageNumber = num; 
  }

  OdUInt8 get_LayersUseType() const 
  { 
    return m_LayersUseType; 
  }

  void put_LayersUseType(const OdUInt8 type) 
  { 
    m_LayersUseType = type; 
  }

  bool get_ImportVectorGeometry() const 
  { 
    return m_ImportVectorGeometry; 
  }

  void put_ImportVectorGeometry(const bool state)
  { 
    m_ImportVectorGeometry = state; 
  }

  bool get_ImportSolidFills() const 
  { 
    return m_ImportSolidFills; 
  }

  void put_ImportSolidFills(const bool state) 
  { 
    m_ImportSolidFills = state; 
  }

  bool get_ImportTrueTypeText() const 
  { 
    return m_ImportTrueTypeText;
  }

  void put_ImportTrueTypeText(const bool state) 
  { 
    m_ImportTrueTypeText = state; 
  }

  bool get_ImportRasterImages() const 
  { 
    return m_ImportRasterImages; 
  }

  void put_ImportRasterImages(const bool state) 
  { 
    m_ImportRasterImages = state; 
  }

  bool get_ImportAsBlock() const 
  { 
    return m_ImportAsBlock; 
  }

  void put_ImportAsBlock(const bool state) 
  { 
    m_ImportAsBlock = state; 
  }

  bool get_JoinLineAndArcSegments() const 
  { 
    return m_JoinLineAndArcSegments;
  }

  void put_JoinLineAndArcSegments(const bool state) 
  { 
    m_JoinLineAndArcSegments = state; 
  }

  bool get_ConvertSolidsToHatches() const 
  { 
    return m_ConvertSolidsToHatches;
  }

  void put_ConvertSolidsToHatches(const bool state) 
  { 
    m_ConvertSolidsToHatches = state; 
  }

  bool get_ApplyLineweight() const 
  {
    return m_ApplyLineweight; 
  }

  void put_ApplyLineweight(const bool state) 
  { 
    m_ApplyLineweight = state; 
  }

  double get_InsertionPointX() const 
  { 
    return m_InsertionPointX; 
  }

  void put_InsertionPointX(const double val) 
  { 
    m_InsertionPointX = val; 
  }

  double get_InsertionPointY() const 
  { 
    return m_InsertionPointY; 
  }

  void put_InsertionPointY(const double val) 
  { 
    m_InsertionPointY = val; 
  }

  double get_Scaling() const
  { 
    return m_Scaling; 
  }

  void put_Scaling(const double val) 
  { 
    m_Scaling = val; 
  }

  double get_Rotation() const 
  { 
    return m_Rotation; 
  }

  void put_Rotation(const double val) 
  { 
    m_Rotation = val; 
  }

  bool get_ImportTrueTypeTextAsGeometry() const 
  { 
    return m_ImportTrueTypeTextAsGeometry;
  }

  void put_ImportTrueTypeTextAsGeometry(const bool state) 
  { 
    m_ImportTrueTypeTextAsGeometry = state; 
  }

  bool get_ImportGradientFills() const
  {
    return m_ImportGradientFills;
  }

  void put_ImportGradientFills(const bool state)
  {
    m_ImportGradientFills = state;
  }

  bool get_UseProgressMeter() const
  {
    return m_UseProgressMeter;
  }

  void put_UseProgressMeter(const bool state)
  {
    m_UseProgressMeter = state;
  }

  bool get_UseGeometryOptimization() const
  {
    return m_UseGeometryOptimization;
  }

  void put_UseGeometryOptimization(const bool state)
  {
    m_UseGeometryOptimization = state;
  }

  bool get_ImportType3AsTrueTypeText() const
  {
    return m_ImportType3AsTrueTypeText;
  }

  void put_ImportType3AsTrueTypeText(const bool state)
  {
    m_ImportType3AsTrueTypeText = state;
  }

  bool get_UseRgbColor() const
  {
    return m_UseRgbColor;
  }

  void put_UseRgbColor(const bool state)
  {
    m_UseRgbColor = state;
  }

  OdString get_ImagePath() const
  {
    return m_ImagePath;
  }

  void put_ImagePath(const OdString& path)
  {
    m_ImagePath = path;
  }

  bool get_ImportInvalidTTTextAsGeometry() const
  {
    return m_ImportInvalidTTTextAsGeometry;
  }

  void put_ImportInvalidTTTextAsGeometry(const bool state)
  {
    m_ImportInvalidTTTextAsGeometry = state;
  }

  bool get_UseClipping() const
  {
    return m_UseClipping;
  }

  void put_UseClipping(const bool state)
  {
    m_UseClipping = state;
  }

  bool get_UsePageBorderClipping() const
  {
    return m_UsePageBorderClipping;
  }

  void put_UsePageBorderClipping(const bool state)
  {
    m_UsePageBorderClipping = state;
  }

  bool get_TakeAddMeasurementFactors() const
  {
    return m_TakeAddMeasurementFactors;
  }

  void put_TakeAddMeasurementFactors(const bool state)
  {
    m_TakeAddMeasurementFactors = state;
  }

  bool get_CombineTextObjects() const
  {
    return m_CombineTextObjects;
  }

  void put_CombineTextObjects(const bool state)
  {
    m_CombineTextObjects = state;
  }

  double get_CharSpaceFactor() const
  {
    return m_CharSpaceFactor;
  }

  void put_CharSpaceFactor(const double val)
  {
    m_CharSpaceFactor = val;
  }

  double get_SpaceFactor() const
  {
    return m_SpaceFactor;
  }

  void put_SpaceFactor(const double val)
  {
    m_SpaceFactor = val;
  }

  bool get_UsePdfTransparency() const
  {
    return m_UsePdfTransparency;
  }

  void put_UsePdfTransparency(const bool state)
  {
    m_UsePdfTransparency = state;
  }

  OdUInt8 get_ImportHyperlinkMethod() const
  {
    return m_ImportHyperlinkMethod;
  }

  void put_ImportHyperlinkMethod(const OdUInt8 type)
  {
    m_ImportHyperlinkMethod = type;
  }

  bool get_ImportWidgets() const
  {
    return m_ImportWidgets;
  }

  void put_ImportWidgets(const bool state)
  {
    m_ImportWidgets = state;
  }

  bool get_UseImageClipping() const
  {
    return m_UseImageClipping;
  }

  void put_UseImageClipping(const bool state)
  {
    m_UseImageClipping = state;
  }

  bool get_ConsiderINSUNITS() const
  {
    return m_ConsiderINSUNITS;
  }

  void put_ConsiderINSUNITS(const bool state)
  {
    m_ConsiderINSUNITS = state;
  }

  OdString get_Type3TextDefaultFont() const
  {
    return m_Type3TextDefaultFont;
  }

  void put_Type3TextDefaultFont(const OdString& val)
  {
    m_Type3TextDefaultFont = val;
  }

  bool get_ExtractEmbeddedFonts() const
  {
    return m_ExtractEmbeddedFonts;
  }

  void put_ExtractEmbeddedFonts(const bool state)
  {
    m_ExtractEmbeddedFonts = state;
  }

  OdString get_EbeddedFontsPath() const
  {
    return m_EbeddedFontsPath;
  }

  void put_EbeddedFontsPath(const OdString& val)
  {
    m_EbeddedFontsPath = val;
  }

  bool get_TryFixUnicodeTable() const
  {
    return m_TryFixUnicodeTable;
  }

  void put_TryFixUnicodeTable(const bool state)
  {
    m_TryFixUnicodeTable = state;
  }
};

/** \details
  <group OdPdfImport_Classes> 
  Smart pointer to the PDF properties
*/
typedef OdSmartPtr<PdfProperties> PdfPropertiesPtr;

#endif // _PDF_PROPERTIES_INCLUDED_
