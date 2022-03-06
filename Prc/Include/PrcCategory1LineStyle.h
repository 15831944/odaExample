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

#ifndef _PRCCATEGORY1LINESTYLE_INCLUDED_
#define _PRCCATEGORY1LINESTYLE_INCLUDED_ 
 

#include "PrcObjectId.h"
#include "PrcBase.h"
#include "PrcRgbColor.h"
#include "PrcColorIndex.h"
#include "Gi/GiMaterial.h"

SMARTPTR(OdPrcCategory1LineStyle);
class OdPrcFileStructure;

/** \details 
Class stores data of line styles.
<group PRC_Graphic_Classes> 
*/
class PRC_TOOLKIT OdPrcCategory1LineStyle : public OdPrcReferencedBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcCategory1LineStyle)
  //DOM-IGNORE-END

  /** \details
  Sets a new line width of the line style.

  \param line_width [in] A new value of the line width to be set.
  */
  void setLineWidth(double line_width);
  
  /** \details
  Returns the current line width of the line style.
  */
  double lineWidth() const;

  /** \details
  Sets a new color index for the line style.
  This method sets the material identifier to zero.

  \param colorIndex [in] A new color index in OdPrcFileStructureGlobals.colors() array to be set.
  */
  void setColor(OdPrcColorIndex colorIndex = OdPrcColorIndex::kUninit);

  /** \details
  Sets a new color for the line style.
  This method sets the material identifier to zero.
  Object must be database resident.

  \param r [in] A new red component value to be set. 0-1 range.
  \param g [in] A new green component value to be set. 0-1 range.
  \param b [in] A new blue component value to be set. 0-1 range.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setColor(double r, double g, double b, bool preventDuplication = false);

  /** \details
  Sets a new color for the line style.
  This method sets the material identifier to zero.
  Object must be database resident.

  \param color [in] A new color in r,g,b format.
  \param preventDuplication [in] Add new color to the end of color array or search the array to prevent duplication.
  */
  void setColor(const OdPrcRgbColor &color, bool preventDuplication = false);
  
  /** \details
  Returns the current color index of the line style. Color index is an index in OdPrcFileStructureGlobals.colors() array.
  Will throw an exception if no color attached.
  */
  OdPrcColorIndex getColor() const;

  /** \details
  Returns the current color of the line style. Will throw an exception in case of uninitialized object.
  */
  OdCmEntityColor getTrueColor() const;

  /** \details
  Sets a new picture index of the line style.
  The method sets the line pattern identifier to zero.

  \param idx_picture [in] A new picture index to be set.
  */
  void setPictureIdx(OdUInt32 idx_picture);
  
  /** \details
  Returns the current picture index of the line style.
  */
  OdUInt32 getPictureIdx() const;
  
  /** \details
  Sets a new material identifier of the line style.
  This method sets the color index to zero.

  \param materialID [in] A new material identifier to be set.
  */
  void setMaterialID (const OdPrcObjectId &materialID);
  
  /** \details
  Returns the current material identifier of the line style.
  */
  OdPrcObjectId getMaterialID() const;

  /** \details
  Clears the material identifier.
  */
  void clearMaterialID();
  
  /** \details
  Sets a new line pattern identifier of the line style.
  The method sets the picture index to zero.

  \param patternID [in] A new line pattern identifier to be set.
  */
  void setLinePatternID (const OdPrcObjectId &patternID);
  
  /** \details 
  Returns the current line pattern identifier of the line style.
  */
  OdPrcObjectId getLinePatternID() const;

  /** \details 
  Clears the identifier of the line pattern.
  */
  void clearLinePatternID();
  
  /** \details
  Sets a new transparency value of the line style.

  \param transparency [in] A new transparency value of the line style.
  */
  void setTransparency (OdInt8 transparency);
  
  /** \details
  Clears the information about the line style's transparency.
  */
  void clearTransparency();
  
  /** \details
  Sets new first additional data of the line style.

  \param additional_data_1 [in] New first additional data to be set.
  */
  void setAdditionalData1 (OdInt8 additional_data_1);
  
  /** \details
  Clears the information about the first additional data.
  */
  void clearAdditionalData1();
  
  /** \details
  Sets new second additional data of the line style.

  \param additional_data_2 [in] New second additional data.
  */
  void setAdditionalData2 (OdInt8 additional_data_2);
  
  /** \details
  Clears the information about second additional data.
  */
  void clearAdditionalData2();
  
  /** \details
  Sets new third additional data of the line style.

  \param additional_data_3 [in] New third additional data.
  */
  void setAdditionalData3 (OdInt8 additional_data_3);
  
  /** \details
  Clears the information about third additional data.
  */
  void clearAdditionalData3();

  /** \details
  Returns true if current lineStyle has transparency.
  
  \param transparency [out] Receives the current transparency of the line style.
  */
  bool getTransparency(OdInt8 & transparency) const;

  /** \details
  Returns true if current lineStyle has AdditionalData1.
  
  \param data [out] Receives the current AdditionalData1 of the line style.
  */
  bool getAdditionalData1(OdInt8 & data) const;

  /** \details
  Returns true if current lineStyle has AdditionalData2.
  
  \param data [out] Receives the current AdditionalData2 of the line style.
  */
  bool getAdditionalData2(OdInt8 & data) const;

  /** \details
  Returns true if current lineStyle has AdditionalData3.
  
  \param data [out] Receives the current AdditionalData3 of the line style.
  */
  bool getAdditionalData3(OdInt8 & data) const;

  /** \details
  Puts new RGB color in file structure globals, creates new LineStyle that uses that color and returns its object id
  \param r                        [in] A red color value (0-1 range).
  \param g                        [in] A green color value (0-1 range).
  \param b                        [in] A blue color value (0-1 range).
  \param postToFileStructure      [out] A reference to a file structure where the new line style should be created and saved.
  \param preventColorDuplication  [in] Add new color to the end of color array or search the array to prevent duplication.
  \returns The identifier of the newly created line style object.
  */
  static OdPrcObjectId createByColor(double r, double g, double b, OdPrcFileStructure &postToFileStructure, bool preventColorDuplication = false);

  /** \details
  Puts new prc material in file structure globals, creates new LineStyle that uses that material and returns its object id
  \param materialId          [in] An identifier of the material that should be used for the line style creation.
  \param postToFileStructure [out] A reference to a file structure where the new line style should be created and saved.
  \returns The identifier of the newly created line style object.
  */
  static OdPrcObjectId createByMaterial(const OdPrcObjectId &materialId, OdPrcFileStructure &postToFileStructure);
  
  /** \details
  Adds a new PRC material object represented with an OdGiMaterialTraits object in the file structure globals storage and creates a new line style object that uses the specified material.
  \param pTraits                              [in] A raw pointer to an OdGiMaterialTraits object that contains data about a material.
  \param pColor                               [in] A raw pointer to a color object to be used as a source of the color for the line style.
  \param pTransparency                        [in] A transparency level to be set for the line style.
  \param pDb                                  [in] A raw pointer to an associated drawing database.
  \param fileStructure                        [out] A reference to a file structure where the new line style should be created and saved.
  \param useSpecularHighlightingOverride      [in] A flag that determines whether the specular highlighting override is used.
  \param specularHighlightingFromVisualStyle  [in] A value of overriding specular highlighting from the visual style.
  \returns The identifier of the newly created line style object; if the creation fails, returns a null identifier.
  \remarks 
  A NULL identifier returns true when its isNull() method is called. 
  */
  static OdPrcObjectId createByMaterial(const OdGiMaterialTraits* pTraits, const OdCmEntityColor* pColor, const OdCmTransparency * pTransparency, 
    OdDbBaseDatabase *pDb, OdPrcFileStructure &fileStructure);
protected:
  virtual OdUInt32 subSetAttributes(OdGiDrawableTraits * traits) const;
};

#endif // _PRCCATEGORY1LINESTYLE_INCLUDED_

