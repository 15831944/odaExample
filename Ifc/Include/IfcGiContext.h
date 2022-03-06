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
#ifndef _IFC_GICONTEXTFORIFCDATABASE_H_
#define _IFC_GICONTEXTFORIFCDATABASE_H_

#include "IfcCore.h"
#include "IfcFile.h"
#include "GiDefaultContext.h"
#include "OdPlatform.h"
#include "StaticRxObject.h"
#include "Gs/Gs.h"

#include "IfcBuildOptions.h"

class OdGiContextForIfcDatabase;

class OdGiAuxDataForIfc;

/** \details 
  A data type that represents a smart pointer to an <link OdIfc::OdGiAuxDataForIfc, OdGiAuxDataForIfc> object.
*/
typedef OdSmartPtr<OdGiAuxDataForIfc> OdGiAuxDataForIfcPtr;

/** \details 
A data type that represents a smart pointer to an <link OdGiContextForIfcDatabase, OdGiContextForIfcDatabase> object.
*/
typedef OdSmartPtr<OdGiContextForIfcDatabase> OdGiContextForIfcDatabasePtr;

/** \details
A class that implements working with a vectorization context for an IFC database.
*/
class IFCCORE_EXPORT OdGiContextForIfcDatabase : public OdGiDefaultContext
{
//DOM-IGNORE-BEGIN
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

  OdIfcFile*            m_pDb;

  OdGiAuxDataForIfcPtr  m_pCtxAuxData;
  OdDAIObjectId         m_pIfcReprContextCur;

protected:
  ODCOLORREF            m_paletteBackground;
//DOM-IGNORE-END

public:
  //DOM-IGNORE-BEGIN
  ODRX_DECLARE_MEMBERS(OdGiContextForIfcDatabase);
  //DOM-IGNORE-END

  /** \details
  Creates a new Gi context instance for an IFC database with default parameters.
  \remarks 
  By default, all flags are off and the palette background color is equal to black.
  */
  OdGiContextForIfcDatabase();

  /** \details
  Destroys the Gi context object.
  */
  ~OdGiContextForIfcDatabase() {}

  /** \details
  Retrieves an IFC database that is currently associated with the Gi context object.
  \returns A raw pointer to the database that is currently being vectorized.
  Returns the IFC database that is currently being vectorized, represented as a pointer to an OdDbBaseDatabase object.
  */
  virtual OdDbBaseDatabase* database() const;

  /** \details
  Retrieves the current value of the plot generation flag.
  \returns true if the vectorization is intended for hard copy output; otherwise, the method returns false.
  */
  virtual bool isPlotGeneration() const;

  /** \details
  Sets a new value of the plot generation flag.
  \param plotGeneration [in] A new value of the plot generation flag value to be set.
  \remarks
  The plot generation flag is equal to true if the vectorization is intended for hard copy output; otherwise, the flag is equal to false.
  */
  virtual void setPlotGeneration(bool plotGeneration);

  /** \details
  Sets a new palette background color.
  \param paletteBackground [in] A new palette background color to be set.
  */
  virtual void setPaletteBackground(ODCOLORREF paletteBackground);

  /** \details
  Opens for reading the specified drawable object that belongs to the database associated with the context object.
  \param drawableId [in]  An object's identifier of the drawable to be opened.
  \returns A smart pointer to the drawable object.
  */
  virtual OdGiDrawablePtr openDrawable(OdDbStub* drawableId);

  /** \details
  Retrieves the current palette background color of the context object.
  \returns The current palette background color.
  */
  virtual ODCOLORREF paletteBackground() const;

  /** \details
  Sets a new IFC database to be vectorized.
  \param pIfcFile [in] A smart pointer to an IFC file object.
  */
  void setDatabase(OdIfcFilePtr pIfcFile);

  /** \details
  Retrieves the IFC database that is currently being vectorized.
  \returns A raw pointer to the <link OdIfcFile, OdIfcFile> object that represents the currently vectorized IFC database.
  */
  OdIfcFile* getDatabase() const;

  /** \details
  Retrieves the current information about the Gs client view object.
  \param viewInfo [out] A placeholder for the client view information.
  \remarks 
  The method accepts an instance of the Gs client viewport information object, fills it with data from the context, and returns it to a calling subroutine.
  */
  virtual void fillGsClientViewInfo(OdGsClientViewInfo& viewInfo);

//DOM-IGNORE-BEGIN
  /** \details
  Retrieves the identifier of the current internal drawable filtration function.
  \param viewportId [in] A raw pointer to the object identifier of the viewport object to be returned.
  \returns A raw pointer to the drawable filter function identifier value.
  */
  virtual OdIntPtr drawableFilterFunctionId(OdDbStub* viewportId) const;

  /** \details
  Sets a new drawable filtration function and its parameters.
  \param functionId [in] An identifier of the new internal drawable filtration function.
  \param pDrawable  [in] A raw pointer to the currently vectorized drawable.
  \param nFlags     [in] A set of input flags for the filtration function.
  \returns The resulting code of the operation.
  \remarks 
  The drawable filtration function is called for each time when the drawable vectorization is needed.
  */
  virtual OdUInt32 drawableFilterFunction(OdIntPtr functionId, const OdGiDrawable *pDrawable, OdUInt32 nFlags);
//DOM-IGNORE-END
  
  /** \details
  Returns the current value of the flag that determines whether the Gs model should be used during the vectorization.
  \returns If the Gs model is used, the method returns true; otherwise, it returns false.
  */
  bool useGsModel() const;

  /** Description:
  Sets a new value of the used Gs model flag. 
  \param enable [in] A new flag value to be set.
  \remarks 
  The used Gs model flag determines whether the Gs model is used for the vectorization process (if equal to true) or not (if equal to false).
  */
  void enableGsModel(bool enable);

  /** \details 
  Sets a new representation context.
  \param idRC [in] An identifier of an object that implements the representation context to be set.
  */
  void setRepresentationContext(OdDAIObjectId idRC);
  
  /** \details 
  Retrieves the current representation context.
  \returns The identifier of the current representation context object.
  */
  OdDAIObjectId getRepresentationContext();

  /** \details
  Retrieves the current auxiliary data for context.
  \returns A constant pointer to auxiliary data for context object.
  */
  OdGiAuxDataForIfc* getCtxAuxData();
};

#endif // _IFC_GICONTEXTFORIFCDATABASE_H_
