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
#ifndef __PRC_GICONTEXTFORBMDATABASE_H__
#define __PRC_GICONTEXTFORBMDATABASE_H__

#include "GiDefaultContext.h"
#include "OdPlatform.h"
#include "StaticRxObject.h"
#include "PrcFile.h"
#include "Gs/Gs.h"

#include "TD_PackPush.h"

/** \details
Class implements storage for graphical properties values that can be applied to an entity: show flag and its inheritance, color, and material.
<group PRC_Gs_Gi_Classes>
*/
class PRC_TOOLKIT OdPrcGraphicsValuesStorage
{
  //DOM-IGNORE-BEGIN
  OdUInt16 m_currentBits;
  OdDbStub * m_currentMaterial;
  //DOM-IGNORE-END
public:
  /** \details
  Creates new graphical properties storage with default values.
  */
  OdPrcGraphicsValuesStorage() : m_currentBits(PRC_GRAPHICS_Show), m_currentMaterial(NULL) {}

  /** \details
  Returns the current value of show behavior bits.
  */
  OdUInt16 getCurrentBits();

  /** \details
  Sets a new value for the show behavior bits.
  \param currentBits [in] A new bits value to be set.
  */
  void setCurrentBits(OdUInt16 currentBits);

  /** \details
  Returns the current material.
  */
  OdDbStub * getCurrentMaterial();

  /** \details
  Sets a new material.
  \param material [in] A new material.
  */
  void setCurrentMaterial(OdDbStub * material);
};

/** \details
This class implements the context for a .prc database that is used in vectorization.

<group PRC_Gs_Gi_Classes>
*/
class PRC_TOOLKIT OdGiContextForPrcDatabase : public OdGiDefaultContext
{
public:
  /** \details 
  Drawing options.
  */
  enum EPRCDrawOptions {
    EPRCDrawDefault, // Default drawing options.
    EPRCDrawGeom,    // Draw as a geometry.
    EPRCDrawMarkups  // Draw as markups.
  };

  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGiContextForPrcDatabase);
  //DOM-IGNORE-END

  /** \details
  Returns the current set of graphical values from a cache object.
  */
  const OdPrcGraphicsValuesStorage & graphicsValuesStorage() const;

  /** \details
  Returns the current set of graphical values from a cache object for changing (value storage is returned as a reference, therefore it can be changed and affects the cache object).
  */
  OdPrcGraphicsValuesStorage & graphicsValuesStorage();

  /** \details
  Returns the current set of references from a cache object for changing (the map is returned as a reference, therefore it can be changed and affects the cache object).
  */
  std::map<OdPrcObjectId, OdPrcObjectId> & references();

  /** \details
  Returns the current set of references from a cache object.
  */
  const std::map<OdPrcObjectId, OdPrcObjectId> & references() const;

  /** \details
  Returns the current draw mode (everything, only geometry, or only markups).
  */
  const EPRCDrawOptions DrawMode(void) const;

  /** \details
  Sets the current draw mode (everything, only geometry, or only markups).
  \param drawMode [in] A new draw mode to be set.
  */
  void SetDrawMode(EPRCDrawOptions drawMode);

  /** \details
  Creates the Gi context for the .prc database.
  All flags are off.  Palette background color is equal to black.
   */
  OdGiContextForPrcDatabase();

  /** \details
  Destroys the Gi context for the .prc database.
   */
  ~OdGiContextForPrcDatabase();

  /** \details
  Returns the .prc database that is currently being vectorized, represented as a pointer to an OdDbBaseDatabase object.
  */
  virtual OdDbBaseDatabase* database() const;

  /** \details
  Returns the current value of the plot generation flag.
  The plot generation flag is equal to true if this vectorization is intended for hard copy output and is equal to false in the other case.
  */
  virtual bool isPlotGeneration() const;

  /** \details
  Sets a new value of the plot generation flag.
  The plot generation flag is equal to true if this vectorization is intended for hard copy output and is equal to false in the other case.

  \param plotGeneration [in] A new value of the plot generation flag value to be set.
  */
  virtual void setPlotGeneration(bool plotGeneration);

  /** \details
  Sets a new palette background color.

  \param paletteBackground [in] A new palette background color to be set.
  */
  virtual void setPaletteBackground(ODCOLORREF paletteBackground);

  /** \details
  Opens for reading the specified drawable object belonging to the database associated with this context object.

  \param drawableId [in]  An object ID of the drawable to be opened.

  \returns Returns a smart pointer to the drawable object.
  */
  virtual OdGiDrawablePtr openDrawable(OdDbStub* drawableId);

  /** \details
  Returns the palette background color.
  */
  virtual ODCOLORREF paletteBackground() const;

  /** \details
  Sets a new .prc database to be vectorized.

  \param pPrcFile [in] A smart pointer to a .prc file object.
  */
  void setDatabase(OdPrcFilePtr pPrcFile);

  /** \details
  Returns the .prc database that is currently being vectorized.
  */
  OdPrcFile* getDatabase() const;

  /** \details
  Returns the OdGsClientViewInfo for the specified viewport.

  \param vpId     [in]  An object ID of the viewport.
  \param viewInfo [out] Receives the client view info.
  */
  virtual void fillGsClientViewInfo(OdGsClientViewInfo& viewInfo);

  /** \details
  Returns the internal drawable filtration function ID.

  \param viewportId [in] A pointer to the object ID of the viewport object to be queried.
  */
  virtual OdIntPtr drawableFilterFunctionId(OdDbStub* viewportId) const;

  /** \details
  Sets a set of flags for a drawable filtration function (to be called for each drawable vectorization).

  \param functionId [in] An internal drawable filtration function ID.
  \param pDrawable  [in] A currently vectorizing drawable pointer.
  \param nFlags     [in] A set of input flags.
  */
  virtual OdUInt32 drawableFilterFunction(OdIntPtr functionId, const OdGiDrawable *pDrawable, OdUInt32 nFlags);

  /** \details
  Returns the current value of the GsModel flag.
  */
  bool useGsModel() const;

  /** Description:
  Controls the GsModel flag of this context object.

  \param enable [in] A new value of the GsModel flag to be set.
  */
  void enableGsModel(bool enable);

  /** \details 
  Retrieves the stub to a material object with a specified identifier from a specified database.
  \param pBaseDb [in] A raw pointer to a database object that contains the material.
  \param materialId [in] An identifier of the material object.
  \returns Returns a raw pointer to an OdDbStub object. 
  */
  OdDbStub* getStubByMaterialId(OdDbBaseDatabase *pBaseDb, const OdUInt64& materialId) const;
  
//DOM-IGNORE-BEGIN
protected:
  ODCOLORREF m_paletteBackground;
  OdPrcGraphicsValuesStorage m_graphicsValuesStorage;
  std::map<OdPrcObjectId, OdPrcObjectId> m_references;
  EPRCDrawOptions m_drawMode;

private:
  enum
  {
    kPlotGeneration = 1,
    kUseGsModel = 2,
    kOdGiZeroTextNormals = 4,
    kDisableLayoutHelperLinkReactors = 8,
    kTTFPolyDraw = 16,
    kTrackDbDestroy = 32,
    kManageContextualColors = 64,
    kKeepPSLayoutHelperView = 128,
    kErasePSLayoutHelperView = 256,
    kLastFlag = kErasePSLayoutHelperView
  };

  OdUInt32              m_fflags;

  //!DOM : public OdStaticRxObject<OdPrcFileReactor>
  class PRC_TOOLKIT DatabaseHolder
  {
  public:
    DatabaseHolder();
    ~DatabaseHolder();

    void setDatabase(OdPrcFile * pDb);
    void goodbye(const OdPrcFile* pDb);

    OdPrcFile* m_pDb;
  } m_DbHolder;
//DOM-IGNORE-END
};

/** \details
This template class is a specialization of the OdSmartPtr class for OdGiContextForPrcDatabase object pointers.
*/
typedef OdSmartPtr<OdGiContextForPrcDatabase> OdGiContextForPrcDatabasePtr;

#include "TD_PackPop.h"

#endif
