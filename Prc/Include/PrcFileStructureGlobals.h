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

#ifndef _PRCFILESTRUCTUREGLOBALS_INCLUDED_
#define _PRCFILESTRUCTUREGLOBALS_INCLUDED_ 
 

#include "PrcBase.h"
#include "PrcMarkupSerializationHelper.h"
#include "PrcRgbColor.h"
#include "PrcPicture.h"
#include "PrcRepresentationItem.h"
#include "PrcCategory1LineStyle.h"
#include "PrcLinePattern.h"
#include "PrcMaterial.h"
#include "PrcTextureDefinition.h"
#include "PrcFillPattern.h"
#include "PrcUserData.h"
#include "PrcUniqueId.h"
#include "PrcObjectId.h"
#define STL_USING_ALL
#include "OdaSTL.h"

class OdPrcFile;

SMARTPTR(OdPrcFileStructureGlobals);

/** \details
<group PRC_Files_Structures_Assemblies>

Class stores global data of a file structure.
Global data contains coordinate systems, colors, line styles, and references to other file structures for each entity in the file structure.
*/
class PRC_TOOLKIT OdPrcFileStructureGlobals : public OdPrcBase
{
public:
  //DOM-IGNORE-BEGIN
  ODPRC_DECLARE_MEMBERS_PRCBASE(OdPrcFileStructureGlobals)
  //DOM-IGNORE-END

  /** \details 
  Returns current user defined data of the file structure global data.
  User data is returned as a reference to an OdPrcUserData object, therefore it can be used to set new user data.
  */
  OdPrcUserData &userData();
  
  /** \details 
  Returns current user defined data of the file structure global data.
  */
  const OdPrcUserData &userData() const;
  
  /** \details 
  Returns the current picture array of the file structure global data.
  The picture array is returned as a reference to an OdPrcPicturePtrArray object, therefore it can be used to set a new picture array.
  */
  OdPrcPicturePtrArray &pictures();
  
  /** \details 
  Returns the current picture array of the file structure global data.
  */
  const OdPrcPicturePtrArray &pictures() const;
  
  /** \details 
  Returns the current color definition array of the file structure global data.
  The color definition array is returned as a reference to an OdPrcRgbColorArray object, therefore it can be used to set a new color definition array.
  */
  OdPrcRgbColorArray &colors();
  
  /** \details 
  Returns the current color definition array of the file structure global data.
  */
  const OdPrcRgbColorArray &colors() const;
  
  /** \details 
  Returns the current markup serialization helper object of the file structure global data.
  The markup serizalization helper object is returned as a reference to an OdPrcMarkupSerializationHelper object, therefore it can be used to set a new serizalization helper for markups.
  */
  OdPrcMarkupSerializationHelper &markupSerializationHelper();
  
  /** \details 
  Returns the current markup serialization helper object of the file structure global data.
  */
  const OdPrcMarkupSerializationHelper &markupSerializationHelper() const;
  
  /** \details 
  Sets a new value of the tessellation angle degree of the file structure global data.
  
  \param tessellation_angle_degree [in] A new tessellation angle degree to be set.
  */
  void setTessellationAngleDegree(double tessellation_angle_degree);
  
  /** \details 
  Returns the current tessellation angle degree of the file structure global data.
  */
  double tessellationAngleDegree() const;
  
  /** \details 
  Sets a new value of the tessellation chord height of the file structure global data.
  
  \param tessellation_chord_height_ratio [in] A new tessellation chord height to be set.
  */
  void setTessellationChordHeightRatio(double tessellation_chord_height_ratio);
  
  /** \details 
  Returns the current tessellation chord height of the file structure global data.
  */
  double tessellationChordHeightRatio() const;
  
  /** \details 
  Returns the current array of category 1 line styles of the file structure global data.
  The line styles array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new line styles array.
  */
  const OdPrcObjectIdArray& category1LineStyles(void) const;
  
  /** \details 
  Returns the current array of category 1 line styles of the file structure global data.
  */
  OdPrcObjectIdArray& category1LineStyles(void);
  
  /** \details 
  Returns the current line pattern array of the file structure global data.
  */
  const OdPrcObjectIdArray& linePatterns(void) const;
  
  /** \details 
  Returns the current line patterns array of the file structure global data.
  The line patterns array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new line patterns array.
  */
  OdPrcObjectIdArray& linePatterns(void);
  
  /** \details 
  Returns the current materials array of the file structure global data.
  */
  const OdPrcObjectIdArray& materials(void) const;
  
  /** \details 
  Returns the current materials array of the file structure global data.
  The materials array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new materials array.
  */  
  OdPrcObjectIdArray& materials(void);
  
  /** \details 
  Returns the current texture definitions array of the file structure global data.
  */
  const OdPrcObjectIdArray& textureDefinitions(void) const;
  
  /** \details 
  Returns the current texture definitions array of the file structure global data.
  The texture definitions array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new texture definitions array.
  */  
  OdPrcObjectIdArray& textureDefinitions(void);
  
  /** \details 
  Returns the current fill patterns array of the file structure global data.
  */
  const OdPrcObjectIdArray& fillPatterns(void) const;
  
  /** \details 
  Returns the current fill patterns array of the file structure global data.
  The fill patterns array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new fill patterns array.
  */  
  OdPrcObjectIdArray& fillPatterns(void);
  
  /** \details 
  Returns the current coordinate systems array of the file structure global data.
  */
  const OdPrcObjectIdArray& coordinateSystem(void) const;
  
  /** \details 
  Returns the current coordinate systems array of the file structure global data.
  The coordinate systems array is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set a new coordinate systems array.
  */
  OdPrcObjectIdArray& coordinateSystem(void);

  /** \details 
  Returns the current referenced file systems array of the file structure global data.
  */
  const OdPrcObjectIdArray& referencedFileStructuresID() const;
};

#endif // _PRCFILESTRUCTUREGLOBALS_INCLUDED_

