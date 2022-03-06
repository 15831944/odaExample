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

#ifndef _ODPRCEXPORTCONTEXT_INCLUDED_
#define _ODPRCEXPORTCONTEXT_INCLUDED_

#include "PrcExportDef.h"
#include "RxDynamicModule.h"
#include "DbBaseDatabase.h"
#include "PrcFile.h"
#define STL_USING_MAP
#include "OdaSTL.h"
#include "CmColorBase.h"

/** \details 
  The class implements storing color parameters for a drawing node. 
  <group PRC_Export_Import_Classes>
*/
class OD_TOOLKIT_EXPORT DrawingColorNode
{
public:
  /** Current color, used in material when kInherit flag is used.*/
  OdCmEntityColor drawingColor;  
  /** Current transparency setting.*/
  OdCmTransparency transparency; 
  
  /** \details 
    Creates an instance of a drawing color node.
  */
  DrawingColorNode();
  
  
  /** \details 
    The less operator for a drawing color node.
    \param colNode [in] Another drawing color node to compare with.
    \returns true if the drawing color node is less than another node specified with colNode parameter; otherwise, the method returns false.
  */
  bool operator<(const DrawingColorNode& colNode) const;
};

/** \details 
  The class implements storing material information for a drawing node. 
  <group PRC_Export_Import_Classes>
*/
class OD_TOOLKIT_EXPORT DrawingMaterialNode : public DrawingColorNode
{
public:
  /** Current material.*/
  mutable OdDbStub * pMaterial; 
  
  /** \details 
    Creates an instance of a drawing material node.
  */
  DrawingMaterialNode();
  
  /** \details 
    The less operator for a drawing material node.
    \param matNode [in] Another drawing material node to compare with.
    \returns true if the drawing material node is less than another node specified with matNode parameter; otherwise the method returns false.
  */
  bool operator<(const DrawingMaterialNode& matNode) const;
};

/** \details 
  Class implements storing .prc export context and operations with it. 
  <group PRC_Export_Import_Classes>
*/
class OD_TOOLKIT_EXPORT OdPrcExportContext : public OdRxObject
{
//DOM-IGNORE-BEGIN
protected:
  std::map<DrawingColorNode, OdPrcObjectId> m_colormap;
  OdPrcFilePtr m_pFile;
  std::map<DrawingMaterialNode, OdPrcObjectId> m_materialmap;
  OdDbBaseDatabase* m_pDb;
//DOM-IGNORE-END

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdPrcExportContext);
  //DOM-IGNORE-END

  /** \details 
  Retrieves the color cache map. 
  \returns A reference to a color cache map that consists of a set of pairs of DrawingColorNode - object identifier.
  \remarks 
  The returned map can be edited. 
  */
  std::map<DrawingColorNode, OdPrcObjectId> & colorCache(void) { return m_colormap; }

  /** \details 
  Retrieves the color cache map. 
  \returns A reference to a color cache map that consists of a set of pairs of DrawingColorNode - object identifier.
  */
  const std::map<DrawingColorNode, OdPrcObjectId> & colorCache(void) const { return m_colormap; }

  /** \details 
  Sets a new database assigned with the contex. 
  \param _pDb [in] A raw pointer to a database to be set. 
  */
  void setDatabase(OdDbBaseDatabase *_pDb) { m_pDb = _pDb; }

  /** \details 
  Retrieves the export file object.
  \returns A reference to a smart pointer to an OdPrcFile object that represents a PRC file where the exported entity or mesh should be saved. 
  \remarks 
    Returned value allows changing the context object.
  */
  OdPrcFilePtr& getFile (void) { return m_pFile; }

  /** \details 
  Retrieves the export file object.
  \returns A reference to a smart pointer to an OdPrcFile object that represents a PRC file where the exported entity or mesh should be saved. 
  */
  const OdPrcFilePtr& getFile (void) const { return m_pFile; }

  /** \details 
  Retrieves the material cache map. 
  \returns A reference to a material cache map that consists of a set of pairs of DrawingMaterialNode - object identifier.
  \remarks 
  The returned map can be edited.
  */
  std::map<DrawingMaterialNode, OdPrcObjectId> & materialCache (void) { return m_materialmap; }

  /** \details 
  Retrieves the material cache map. 
  \returns A reference to a material cache map that consists of a set of pairs of DrawingMaterialNode - object identifier.
  */
  const std::map<DrawingMaterialNode, OdPrcObjectId> & materialCache (void) const { return m_materialmap; }

  /** \details
  Retrieves the database associated with the context object.
  \returns A raw pointer to the database.
  */
  OdDbBaseDatabase* getDatabase(void) { return m_pDb; }

  /** \details 
  Creates an instance of export context.
  \remarks 
  A .prc file is created and filled with common topology in a context constructor.
  */
  OdPrcExportContext();

  /** \details
  Retrieves the identifier of a line style object for a specified drawing color node.
  \param colorNode        [in] A color node.
  \param newStructure     [out] An file structure to write the line style to.
  \param createIfNotFound [out] A flag that determines whether a new line style should be created if it is not found in the specified drawing color node.
  \returns Returns an identifier of a line style object that was found or created.
  */
  OdPrcObjectId getLineStyleID(const DrawingColorNode & colorNode, OdPrcFileStructure &newStructure, bool createIfNotFound = true);

  /** \details
  Retrieves the identifier of a line style object for a specified drawing material node.
  \param matNode          [in] A material node.
  \param fileStructure    [out] An file structure to write the line style to.
  \param createIfNotFound [out] A flag that determines whether a new line style should be created if it is not found in the specified drawing color node.
  \returns Returns an identifier of a line style object that was found or created.
  */
  OdPrcObjectId getLineStyleID(const DrawingMaterialNode & matNode, OdPrcFileStructure &fileStructure, bool createIfNotFound = true);

};

/** \details
  A data type that represents a smart pointer to a PRC export context object.
*/
SMARTPTR(OdPrcExportContext);

#endif //_ODPRCEXPORTCONTEXT_INCLUDED_
