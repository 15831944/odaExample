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

#ifndef _ODTV_IMPORT_H_INCLUDED_
#define _ODTV_IMPORT_H_INCLUDED_

#include "Tv.h"
#include "TvVisualizeFiler.h"
/** \details
  This class is an interface for LowMemoryImportAbort
*/
class ODTV_EXPORT OdTvLowMemoryImportAbort
{
public:
  /** \details
    Checks whether the low memory import should be aborted.
    
    \returns Returns true if and only if low memory import should be aborted.
  */
  virtual bool abortImport() const = 0;
};

/** \details
  This class implements the base ODA Visualize SDK import parameters.
  \sa
  <link tv_import_params_base, Work with Base Import Parameters>
*/
class ODTV_EXPORT OdTvBaseImportParams
{
public:

  /** \details
    Creates a new set of import parameters with default values.
  */
  OdTvBaseImportParams();

  /** \details
    Destroys the set of import parameters.
  */
  virtual ~OdTvBaseImportParams() {}

  /** \details
    Sets a new full path to the imported file.
    
    \param filePath [in] A new file path represented with an <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString object</exref>.
  */
  void setFilePath(const OdString& filePath);

  /** \details
    Retrieves the current full path to the imported file. 
    
    \returns Returns an <exref target="https://docs.opendesign.com/tkernel/OdString.html">OdString object</exref> that contains the file path for import.
  */
  OdString getFilePath() const;

  /** \details
    Sets a new data stream buffer for the import operation.
    
    \param pBuffer [in] A pointer to an <exref target="https://docs.opendesign.com/tkernel/OdStreamBuf.html">OdStreamBuf object</exref> that represents a new data stream buffer. 
  */
  void setStreamBuffer(OdStreamBuf* pBuffer);

  /** \details
    Retrieves current data stream buffer that is used for import operations.
    
    \returns Returns a smart pointer to an <exref target="https://docs.opendesign.com/tkernel/OdStreamBuf.html">OdStreamBuf object</exref> that is used for import operations.
  */
  OdStreamBufPtr getStreamBuffer() const;

  /** \details
    Sets a new object for storing the profiling information during import operations.
    
    \param pProfilingInfo [in] A pointer to an <link OdTvFilerTimeProfiling, OdTvFilerTimeProfiling> object that stores profiling information.
  */
  void setProfiling(OdTvFilerTimeProfiling* pProfilingInfo);

  /** \details
    Retrieves the current object for storing the profiling information during import operations.
    
    \returns Returns a raw pointer to the object that stores the profiling info.
  */
  OdTvFilerTimeProfiling* getProfiling() const;

  /** \details
    Sets a host app progress meter which will be used for direction the info about import process to the host app
    
    \param pProgressMeter [in] A pointer to an OdTvHostAppProgressMeter object
    \remarks
    Currently supports only for the low memory import from DWG.
  */
  void setProgressMeter(OdTvHostAppProgressMeter* pProgressMeter);

  /** \details
    Retrieves the host app progress meter.
    
    \returns Returns a raw pointer to the host app progress meter if it was set, NULL otherwise.
  */
  OdTvHostAppProgressMeter* getProgressMeter() const;

  /** \details
    Specifies whether to create a CDA (Common Data Access) tree during import process.
    
    \param bNeed [in] A boolean flag which is true if the CDA tree is needed.
  */
  void setNeedCDATree(bool bNeed);

  /** \details
    Retrieves the flag which indicates whether it is needed to create a CDA tree during the import process.
    
    \returns Returns true if the CDA tree should be created during the import process, false otherwise.
  */
  bool getNeedCDATree() const;

  /** \details
    Specifies whether to store native properties to CDA (Common Data Access) nodes during import process.
    
    \param bNeed [in] A boolean flag which is true if storing properties in CDA nodes is needed.
  */
  void setNeedCollectPropertiesInCDA(bool bSet);

  /** \details
    Retrieves the flag which indicates whether it is needed to store native properties in CDA nodes during the import process.
    
    \returns Returns true if to create the CDA tree during the import process.
  */
  bool getNeedCollectPropertiesInCDA() const;
  
  /** \details
    Specifies instance of OdTvLowMemoryImportAbort.
  */
  void setLowMemoryImportAbort( OdTvLowMemoryImportAbort* );
  
  /** \details
    Retrieves instance of OdTvLowMemoryImportAbort.
    
    \returns
    Pointer to the OdTvLowMemoryImportAbort instance that is used for the termination of low memory import.
  */
  OdTvLowMemoryImportAbort* getLowMemoryImportAbort() const;

  /** \details
    Sets a specified default units type (used when the file does not have its own units).
    
    \param units [in] A units type.
  */
  void setDefaultUnits(OdTv::Units units);

  /** \details
    Retrieves default units type (used when the file does not have its own units).
    
    \returns
    Value from the OdTv::Units enumeration that represents default units to set when a file does not have its own units.
  */
  OdTv::Units getDefaultUnits() const;


//DOM-IGNORE-BEGIN
protected:

  // common properties
  OdString                  m_strFilePath;            // File path for import.
  OdStreamBuf*              m_pStreamBuf;             // Stream buffer for import. Implemented only for PRC.
  OdTvFilerTimeProfiling*   m_pProfilingInfo;         // Profiling info. If NULL, time profiling is switched off.
  OdTvHostAppProgressMeter* m_pProgressMeter;         // Progress meter from app
  bool                      m_bNeedCDATree;           // Indicates that during import to create the CDA tree if it is supported.
  bool                      m_bNeedCollectPropertiesInCDA; // Indicates that during import to store properties in CDA nodes if it is supported.
  OdTvLowMemoryImportAbort* m_pLowMemoryImportAbort;
  OdTv::Units               m_defaultUnits;
//DOM-IGNORE-END
};

/** \details
  This class implements the base ODA Visualize SDK append parameters.
*/
class ODTV_EXPORT OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of append parameters with default values.
  */
  OdTvBaseAppendParams();

  /** \details
    Destroys the set of append parameters.
  */
  virtual ~OdTvBaseAppendParams() {}

  /** \details
    Sets a new transformation <link OdTvMatrix, matrix>. 
    
    \param matrix [in] A new transformation <link OdTvMatrix, matrix> to be set. 
  */
  void setTransform(const OdTvMatrix& matrix);

  /** \details
    Retrieves the current transformation <link OdTvMatrix, matrix>.
    
    \returns Returns the current transformation <link OdTvMatrix, matrix> object. 
  */
  OdTvMatrix getTransform() const;

//DOM-IGNORE-BEGIN
protected:

  // common properties
  OdTvMatrix                m_transform;            // Transform
//DOM-IGNORE-END
};


/** \details
  This class implements the base ODA Visualize SDK import parameters for custom file types (non-ODA databases): .rcs, .stl, .obj, etc.
*/
class ODTV_EXPORT OdTvCustomBaseImportParams : public OdTvBaseImportParams
{
public:

  /** \details
    Creates a new set of import parameters with default values.
  */
  OdTvCustomBaseImportParams();

  /** \details
    Destroys the set of import parameters.
  */
  virtual ~OdTvCustomBaseImportParams() {}

  /** \details
    Sets a new value of the default color.
    
    \param defcolor [in] A new default color value.
  */
  void setDefaultColor(ODCOLORREF defcolor);

  /** \details
    Retrieves the current default color value. 
    
    \returns Returns the current value of the default color. 
  */
  ODCOLORREF getDefaultColor() const;

//DOM-IGNORE-BEGIN
protected:
  ODCOLORREF m_defaultColor;    // Default entity color.
//DOM-IGNORE-END
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing from an .rcs file.
  \sa
  <link tv_import_params_rcs, Work with RCS Import Parameters>
*/
class ODTV_EXPORT OdTvRcsImportParams : public OdTvCustomBaseImportParams
{
public:

  /** \details 
    Creates a new instance of .rcs import parameters. 
  */
  OdTvRcsImportParams() 
    : OdTvCustomBaseImportParams()
    , m_iPointSize(1)
    , m_bImportAsRcsPointCloud(true)
    , m_bUseSpatialTreeForSelection(false){};

  /** \details 
    Destroys the instance of .rcs import parameters. 
  */
  virtual ~OdTvRcsImportParams() {}

  /** \details
    Sets a new value of the point size. 
    
    \param bSet [in] A new flag value to be set.
  */
  void setPointSize(OdUInt8 pointSize);

  /** \details
    Retrieves the current value of the point size. 
    
    \returns Returns the current point size value.
  */
  OdUInt8 getPointSize() const;

  /** \details
    Sets a new value of the 'import as RCS point cloud' flag.
    
    \param bSet [in] A new flag value to be set.
  */
  void setImportAsRcsPointCloud(bool bSet);

  /** \details
    Retrieves the current value of the 'import as RCS point cloud' flag.
    
    \returns Returns the current import as RCS point cloud flag value.
  */
  bool getImportAsRcsPointCloud() const;

  /** \details
    Specifies whether to use spatial tree for selection.
    
    \param bSelectable [in] A flag that determines whether to use spatial tree for selection.
  */
  void setUseSpatialTreeForSelection(bool bUseSpatialTreeForSelection);

  /** \details
    Checks whether to use spatial tree for selection.
    
    \returns Returns a flag that indicates whether spatial tree for selection should be used.
  */
  bool getUseSpatialTreeForSelection() const;

//DOM-IGNORE-BEGIN
private:
  OdUInt8 m_iPointSize;
  bool m_bImportAsRcsPointCloud;
  bool m_bUseSpatialTreeForSelection;
//DOM-IGNORE-END
};

/** \details
  This class implements the ODA Visualize SDK parameters for appending contents of .rcs files.
*/
class ODTV_EXPORT OdTvRcsAppendParams : public OdTvRcsImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new instance of parameters for appending .rcs files.
  */
  OdTvRcsAppendParams() : OdTvRcsImportParams() {};

  /** \details
    Destroys the instance of parameters for appending .rcs files.
  */
  virtual ~OdTvRcsAppendParams() {}
};

/** \details
  This class implements the ODA Visualize SDK parameters for importing from an .pts and .xyz files.
  \sa
  <link tv_import_params_unstructured_point_cloud, Work with Unstructured Point Cloud Import Parameters>
*/
class ODTV_EXPORT OdTvPointCloudImportParams : public OdTvRcsImportParams
{
public:

  /** \details
    Creates a new instance of .rcs import parameters.
  */
  OdTvPointCloudImportParams()
    : OdTvRcsImportParams()
    , m_separator(OD_T(" ")), m_iSkipLines(0)
  {
    setImportAsRcsPointCloud(false);
    m_defaultUnits = OdTv::kMeters;
  }

  /** \details
    Destroys the instance of .rcs import parameters.
  */
  virtual ~OdTvPointCloudImportParams() {}

  /** \details
    Sets a separator string value.
    
    \param separator [in] A new separator string.
  */
  void setSeparator(const OdString& separator);

  /** \details
    Retrieves the current value of the separator.
    
    \returns Returns the current separator string value.
  */
  OdString getSeparator() const;

  /** \details
    Sets column indexes of XYZ coordinates.
    
    \param x [in] X coordinate index.
    \param y [in] Y coordinate index.
    \param z [in] Z coordinate index.
  */
  void setXYZIndexes(int x, int y, int z);

  /** \details
    Retrieves the XYZ column indexes.
    
    \returns Returns the array of indexes.
  */
  OdArray<int> getXYZIndexes() const;

  /** \details
    Sets column indexes of RGB.
    
    \param r [in] Red column index.
    \param g [in] Green column index.
    \param b [in] Blue column index.
  */
  void setRGBIndexes(int r, int g, int b);

  /** \details
    Retrieves the RGB column indexes.
    
    \returns Returns the array of indexes.
  */
  OdArray<int> getRGBIndexes() const;

  /** \details
    Sets a count of lines that should be skipped.
    
    \param lines [in] A count of line for skipping.
    \remarks
    Lines are skipped from the start of the line. Skipping lines
    can be useful if the file has some text in the beginning which is not a part of point cloud data.
  */
  void setSkipLinesCount(OdUInt32 lines);

  /** \details
    Retrieves the count of lines that should be skipped.
    
    \returns Returns the count of lines that should be skipped.
    Lines are skipped from the start of the line. Skipping lines
    can be useful if the file has some text in the beginning which is not a part of point cloud data.
  */
  OdUInt32 getSkipLinesCount() const;

  //DOM-IGNORE-BEGIN
private:
  OdString m_separator;
  OdArray<int> m_xyzIndexes;
  OdArray<int> m_rgbIndexes;
  OdUInt32 m_iSkipLines;
  //DOM-IGNORE-END
};

/** \details
  This class implements the ODA Visualize SDK parameters for appending contents of .pts and .xyz files.
*/
class ODTV_EXPORT OdTvPointCloudAppendParams : public OdTvPointCloudImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new instance of parameters for appending .pts and .xyz files.
  */
  OdTvPointCloudAppendParams() : OdTvPointCloudImportParams() {};

  /** \details
    Destroys the instance of parameters for appending .pts and .xyz files.
  */
  virtual ~OdTvPointCloudAppendParams() {}
};

/** \details
  This class implements the ODA Visualize SDK parameters for importing from an .stl file.
  \sa
  <link tv_import_params_stl, Work with STL Import Parameters>
*/
class ODTV_EXPORT OdTvStlImportParams : public OdTvCustomBaseImportParams
{
  
  /** \details
    The .stl import flags. 
  */
  enum ParamFlags
  {
    /* Fix normals during the import operation.*/
    kFixNormals = 1,
    /* Unify duplicate vertices during the import operation. */
    kUnifyDuplicatedVertices = 2,
    /* Calculate normals at vertices during the import operation. */
    kCalcNormalsAtVertices = 4
  };

public:

  /** \details
    Creates a new set of import parameters with default values.
  */
  OdTvStlImportParams();

  /** \details
    Destroys the set of import parameters.
  */
  virtual ~OdTvStlImportParams() {}

  /** \details
    Sets a new value of the 'fix normals' flag. 
    
    \param bFix [in] A new flag value.
  */
  void setFixNormals(bool bFix);

  /** \details
    Retrieves the current value of the 'fix normals' flag. 
    
    \returns Returns the 'fix normals' flag value.
  */
  bool getFixNormals() const;

  /** \details
    Sets a new value of the 'unify duplicate vertices' flag.
    
    \param bUnify [in] A new flag value.
  */
  void setUnifyDuplicatedVertices(bool bUnify);

  /** \details
    Retrieves the current value of the 'unify duplicate vertices' flag.
    
    \returns Returns the unify duplicate vertices flag.
  */
  bool getUnifyDuplicatedVertices() const;

  /** \details
    Sets a new value of the 'calculate normals at vertices' flag.
    
    \param bCalc [in] A new flag value. 
  */
  void setCalcNormalsAtVertices(bool bCalc);

  /** \details
    Retrieves the current value of the 'calculate normals at vertices' flag.
    
    \returns Returns the calculate normals at vertices flag.
  */
  bool getCalcNormalsAtVertices() const;

//DOM-IGNORE-BEGIN
protected:

  OdUInt8 m_flags;
//DOM-IGNORE-END
};


/** \details
  This class implements the ODA Visualize SDK parameters for appending contents of .stl files.
*/
class ODTV_EXPORT OdTvStlAppendParams : public OdTvStlImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of parameters with default values for appending .stl files.
  */
  OdTvStlAppendParams() : OdTvStlImportParams() {};
  
  /** \details
    Destroys the set of parameters for appending .stl files.
  */
  virtual ~OdTvStlAppendParams() {}
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing .obj files.
  \sa
  <link tv_import_params_obj, Work with OBJ Import Parameters>
*/
class ODTV_EXPORT OdTvObjImportParams : public OdTvCustomBaseImportParams
{
//DOM-IGNORE-BEGIN
  bool m_bBrepFlipUVCoordinates;
  bool m_bCalculateNormals;
  bool m_bImportBrepAsBrep;
//DOM-IGNORE-END
  
public:

  /** \details
    Creates a new set of .obj file import parameters with default values.
  */
  OdTvObjImportParams();

  /** \details
    Destroys the set of .obj file import parameters.
  */
  virtual ~OdTvObjImportParams() {}

  /** \details
    Retrieves the current value of the 'B-Rep flip UV coordinates' flag.
    
    \returns Returns the current flag value. 
  */
  bool getBrepFlipUVCoordinates() const;

  /** \details
    Sets a new value of the 'B-Rep flip UV coordinates' flag.
    
    \param bBrepFlipUVCoordinates [in] A new flag value.
  */
  void setBrepFlipUVCoordinates(bool bBrepFlipUVCoordinates);

  /** \details
    Retrieves the current value of the 'import B-Rep as B-Rep' flag.
    
    \returns Returns the current flag value.
  */
  bool getImportBrepAsBrep() const;

  /** \details
    Sets a new value of the 'import B-Rep as B-Rep' flag.
    
    \param bImportBrepAsBrep [in] A new flag value.
  */
  void setImportBrepAsBrep(bool bImportBrepAsBrep);

  /** \details
    Retrieves the current value of the 'normals calculation' flag.
    
    \returns Returns the current flag value. 
  */
  bool getCalculateNormals() const;

  /** \details
    Sets a new value of the 'normals calculation' flag.
    
    \param bCalculateNormals [in] A new flag value.
  */
  void setCalculateNormals(bool bCalculateNormals);

};


/** \details
  This class implements the ODA Visualize SDK parameters for appending .obj file content.
*/
class ODTV_EXPORT OdTvObjAppendParams : public OdTvObjImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of parameters with default values for appending .obj files.
  */
  OdTvObjAppendParams() : OdTvObjImportParams() {};

  /** \details
    Destroys the set of parameters for appending .obj files.
  */
  virtual ~OdTvObjAppendParams() {}
};



/** \details
  This class implements the ODA Visualize SDK parameters for importing MCAD files.
  \sa
  <link tv_import_params_MCAD, Work with MCAD Import Parameters>
*/
class ODTV_EXPORT OdTvMCADImportParams : public OdTvCustomBaseImportParams
{
 
  /** \details
    Specific options for the MCAd import operation.
  */
  enum ParamFlags
  {
    /* Gives the names for the Visualize SDK entities according to the file object names (for example, AcDbCircle, etc). */
    kObjectNaming = 1,
    /* Stores source objects in the user data of the <link OdTvEntity, OdTvEntity> objects. */
    kStoreSource = 2,
    /* Cleans empty objects. */
    kClearEmptyObjects = 4,
    /* Rearranges objects. */
    kRearrangeObjects = 8,
    /* Import brep as OdTvBrepData. */
    kImportBrepAsBrep = 16
  };

public:

  /** \details
    Creates a new set of MCAD import parameters with default values.
  */
  OdTvMCADImportParams();

  /** \details
    Destroys the set of MCAD import parameters.
  */
  ~OdTvMCADImportParams() {}

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new rectangle object to be set.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;
  
  /** \details
    Sets a new value of the 'import B-Rep as B-Rep' flag.
    
    \param bSet [in] A new flag value.
  */
  void setImportBrepAsBrep(bool bImportBrepAsBrep);

  /** \details
    Checks whether the B-Rep objects should be loaded as B-Rep objects.
    
    \returns 
    true if and only if B-Rep should be imported as B-Rep.
  */
  bool getImportBrepAsBrep() const;

  /** \details
    Sets a new value of the facet resolution for the B-Reps.
    
    \param dFacetRes [in] A new facet resolution value.
    \remarks
    The facet resolution value varies from 0.01 to 10.0.
  */
  void setBrepFacetRes(double dFacetRes);

  /** \details
    Retrieves the current facet resolution value for the B-Reps.
    
    \returns Returns the current facet resolution value between 0.01 and 10.0.
  */
  double getBrepFacetRes() const;

//DOM-IGNORE-BEGIN
protected:

  OdTvDCRect              m_importRect;             // Output rectangle. Used for correct import of some specific objects (camera, OLE images). The normal way to set the output window size.
  double                  m_dFACETRES;              // Facet res value (between from 0.01 to 10.0).
  OdUInt8                 m_flags;                  // Different options.
//DOM-IGNORE-END

};


/** \details
  This class implements the ODA Visualize SDK parameters for appending .obj file content.
*/
class ODTV_EXPORT OdTvMCADAppendParams : public OdTvMCADImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of parameters with default values for appending .obj files.
  */
  OdTvMCADAppendParams() : OdTvMCADImportParams() {};

  /** \details
    Destroys the set of parameters for appending .obj files.
  */
  virtual ~OdTvMCADAppendParams() {}
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing .dwg files.
  \sa
  <link tv_import_params_dwg, Work with .dwg Import Parameters>
*/
class ODTV_EXPORT OdTvDwgImportParams : public OdTvBaseImportParams
{
  /** \details
    Specific options for the importing from a .dwg drawing.
  */
  enum ParamFlags
  {
    /* Gives the names of the Visualize SDK entities according to file object names (for example, AcDbCircle, etc). */
    kObjectNaming = 1,
    /* Stores source objects in the user data of the <link OdTvEntity, OdTvEntity> objects. */
    kStoreSource = 2,
    /* Cleans empty objects. */
    kClearEmptyObjects = 4,
    /* Enables (or disables) multithreading mode. */
    kMultithreading = 8,
    /* Uses facet tessellation. */
    kUseAdvancedTess = 16,
    /* Open source .dwg file in partial mode. */
    kPartialSourceOpen = 32,
    /* Import B-Rep as OdTvBrepData. */
    kImportBrepAsBrep = 64,
    /* Converted indexed colors to RGB during import. */
    kConvertIndexedToRGB = 128,
    /* Disable font substitution for missing fonts. */
    kDisableFontSubstitution = 256,
    /* Import objects on frozen layer. */
    kImportFrozenLayers = 512
  };

public:

  /** \details
    Creates a new set of .dwg import parameters with default values.
  */
  OdTvDwgImportParams();

  /** \details
    Destroys the set of .dwg import parameters.
  */
  ~OdTvDwgImportParams() {}

  /** \details
    Sets a new value of the background color.
    
    \param background [in] A new background color.
  */
  void setBackground(ODCOLORREF background);

  /** \details
    Retrieves the current value of the background color. 
    
    \returns Returns the current value of the background color.
  */
  ODCOLORREF getBackground() const;

  /** \details
    Sets a new palette to be used during the import operation.
    
    \param pPalette [in]  A pointer to the color array that represents the new palette.
    \remarks
    If the pPalette parameter is NULL, one of two default palettes is used depending on the background color value.
  */
  void setPalette(const ODCOLORREF* pPalette);

  /** \details
    Retrieves the current palette to be used during the import operation.
    
    \returns Returns a pointer to the color array that represents the current palette.
    \remarks
    If no palette is set (the method returns a NULL pointer), one of two default palettes is used depending on the background color value.
  */
  const ODCOLORREF* getPalette() const;

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new <link OdTvDCRect, rectangle object> to be set.
    \remarks
    If all components of the specified rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the returned rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;

  /** \details
    Sets a new value of the 'object naming' flag.
    
    \param bSet [in] A new flag value.
  */
  void setObjectNaming(bool bSet);

  /** \details
    Retrieves the current 'object naming' flag value.
    
    \returns Returns the current value of the object naming flag.
  */
  bool getObjectNaming() const;
  
  /** \details
    Sets a new value of the 'store source objects' flag.
    
    \param bSet [in] A new flag value.
  */
  void setStoreSourceObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'store source objects' flag.
    
    \returns Returns the current 'store source objects' flag's value.
  */
  bool getStoreSourceObjects() const;

  /** \details
    Sets a new value of the flag that determines whether empty objects should be cleared.
    
    \param bSet [in] A new flag value.
  */
  void setClearEmptyObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'clear empty objects' flag.
    
    \returns Returns true if empty objects should be cleared during the import operation; otherwise the method returns false. 
  */
  bool getClearEmptyObjects() const;

  /** \details
    Sets a new callback function for filtering element selection.
    
    \param pCallback [in]  A pointer to the <link OdTvFeedbackForChooseCallback, selection function>.
  */
  void setFeedbackForChooseCallback(OdTvFeedbackForChooseCallback pCallback);

  /** \details
    Retrieves the current callback function for element selection.
    
    \returns Returns a pointer to the current <link OdTvFeedbackForChooseCallback, callback function>.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;

  /** \details
    Sets a new value of the multithreading flag. 
    
    \param bSet [in] A new value of the flag. 
  */
  void setMultithreading(bool bSet);

  /** \details
    Retrieves the current value of the multithreading flag.
    
    \returns Returns true if multithreading mode is enabled; otherwise the method returns false. 
  */
  bool getMultithreading() const;

  /** \details
    Sets a new quantity of threads for multithreading mode. 
    
    \param nThreads [in] A new quantity of threads.
  */
  void setCountOfThreads(OdUInt16 nThreads);

  /** \details
    Retrieves the current quantity of threads for multithreading mode.
    
    \returns Returns the current number of threads that can be run at the same time in multithreading mode.
  */
  OdUInt16 getCountOfThreads() const;

  /** \details
    Sets a new value of the 'advanced tessellation usage' flag.
    
    \param bSet [in] A new flag value.
  */
  void      setUseAdvancedTess(bool bSet);

  /** \details
    Retrieves the current value of the 'advanced tessellation usage' flag. 
    
    \returns Returns true if advanced tessellation is used; otherwise the method returns false. 
  */
  bool      getUseAdvancedTess() const;

  /** \details
    Sets a new value of the facet resolution.
    
    \param dFacetRes [in] A new facet resolution value.
    \remarks 
    The facet resolution value varies from 0.01 to 10.0.
  */
  void      setFacetRes(double dFacetRes);

  /** \details
    Retrieves the current facet resolution value.
    
    \returns Returns the current facet resolution value between 0.01 and 10.0.
  */
  double    getFacetRes() const;

  /** \details
    Specifies whether the source file should be open in partial mode.
    
    \param bPartial [in] A new flag value.
  */
  void setOpenSourcePartial( bool bPartial );

  /** \details
    Checks whether the source file open mode is partial.
    
    \returns 
    true if current file open mode is partial, false otherwise.
  */
  bool getOpenSourcePartial() const;

  /** \details
    Sets a new value of the 'import B-Rep as B-Rep' flag.
    
    \param bSet [in] A new flag value.
  */
  void setImportBrepAsBrep(bool bImportBrepAsBrep);

  /** \details
    Checks whether B-Rep objects from the source files should be imported as B-Rep objects.
    
    \returns 
    true if and only if B-Rep should be imported as B-Rep.
  */
  bool getImportBrepAsBrep() const;

  /** \details
    Specifies whether the indexed colors should be converted to RGB during the import.
    
    \param bNeedConvertIndexedtoRGB [in] A new value of kConvertIndexedToRGB flag.
  */
  void setConvertIndexedToRGB(bool bNeedConvertIndexedtoRGB);

  /** \details
    Checks whether the indexed colors should be converted to RGB during import.
    
    \returns Returns value of kConvertIndexedToRGB flag.
  */
  bool getConvertIndexedToRGB() const;

  /** \details
    Specifies whether the missing fonts should not be substituted.
    
    \param bSet [in]  Flag that specifies whether to disable fonts substitution for missing fonts.
  */
  void setDisableFontSubstitution( bool bSet );
  
  /** \details
    Checks whether substitution is disabled for missing fonts.
    
    \returns
    true if and only if the missing fonts should not be substituted, false otherwise.
  */
  bool getDisableFontSubstitution() const;

  /** \details
    Sets a new value of the flag that determines whether to import objects on frozen layers.
    
    \param bSet [in] A new flag value.
  */
  void setImportFrozenLayers(bool bSet);

  /** \details
    Checks whether objects on frozen layers should be imported.
    
    \returns Returns true if objects from layer should be imported during the import operation; otherwise the method returns false.
  */
  bool getImportFrozenLayers() const;

//DOM-IGNORE-BEGIN
protected:

  ODCOLORREF                     m_background;             // Background color. Default: black.
  const ODCOLORREF*              m_pPalette;               // Palette to be used. If NULL, one of two default palettes is used depending on background color.
  OdTvDCRect                     m_importRect;             // Output rectangle. Used for correct import of some specific objects (camera, OLE images, 3D solids). The normal way to set the output window size.
  OdUInt16                       m_flags;                 // Different options.
  OdUInt16                       m_nThreads;               // Count of threads.
  double                         m_dFACETRES;              // Facet res value (between from 0.01 to 10.0).
  OdTvFeedbackForChooseCallback  m_pCallback;              // Callback for choose.
//DOM-IGNORE-END
};


/** \details
  This class implements the ODA Visualize SDK parameters for appending .dwg file content.
*/
class ODTV_EXPORT OdTvDwgAppendParams : public OdTvDwgImportParams, public OdTvBaseAppendParams
{
public:

  /** \details 
    Creates a new set of parameters for appending .dwg file content. 
  */
  OdTvDwgAppendParams() : OdTvDwgImportParams() {};

  /** \details 
    Destroys the set of parameters for appending .dwg files content. 
  */
  virtual ~OdTvDwgAppendParams() {}
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing .dgn files.
*/
class ODTV_EXPORT OdTvDgnImportParams : public OdTvBaseImportParams
{
  /** \details
    Specific options of the .dgn import operation. 
  */
  enum ParamFlags
  {
    /* Gives the names for the Visualize SDK entities according to the file object names (for example, AcDbCircle, etc). */
    kObjectNaming = 1,
    /* Stores source objects in the user data of the <link OdTvEntity, OdTvEntity> objects. */
    kStoreSource = 2,
    /* Cleans empty objects. */
    kClearEmptyObjects = 4,
    /* Use isolines for 3D objects. */
    kUseIsolinesFor3DObjects = 8
  };

public:

  /** \details
    Creates a new set of import parameters with default values.
  */
  OdTvDgnImportParams();

  /** \details
    Destroys the set of import parameters.
  */
  ~OdTvDgnImportParams() {}

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new rectangle object to be set.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;

  /** \details
    Sets a new value of the 'objects naming' flag.
    
    \param bSet [in] A new flag value.
  */
  void setObjectNaming(bool bSet);

  /** \details
    Retrieves the current 'objects naming' flag value.
    
    \returns Returns the current value of the objects naming flag.
  */
  bool getObjectNaming() const;

  /** \details
    Sets a new value of the 'store source objects' flag.
    
    \param bSet [in] A new flag value.
  */
  void setStoreSourceObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'store source objects' flag.
    
    \returns Returns the current store source objects flag's value.
  */
  bool getStoreSourceObjects() const;

  /** \details
    Sets a new callback function for filtering element selection.
    
    \param pCallback [in]  A pointer to the <link OdTvFeedbackForChooseCallback, selection function>.
  */
  void setFeedbackForChooseCallback(OdTvFeedbackForChooseCallback pCallback);

  /** \details
    Retrieves the current callback function for element selection.
    
    \returns Returns a pointer to the current <link OdTvFeedbackForChooseCallback, callback function>.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;

  /** \details
    Sets a new value of the flag that determines whether empty objects should be cleared.
    
    \param bSet [in] A new flag value.
  */
  void setClearEmptyObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'clear empty objects' flag.
    
    \returns Returns true if empty objects should be cleared during the import operation; otherwise the method returns false. 
  */
  bool getClearEmptyObjects() const;

  /** \details
    Sets a new value of the flag that determines whether to use isolines for 3D objects.
    
    \param bSet [in] A new flag value.
  */
  void setUseIsolinesFor3DObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'use isolines for 3D objects' flag.
    
    \returns Returns true if isolines for 3D objects used during the import operation; otherwise the method returns false.
  */
  bool getUseIsolinesFor3DObjects() const;

//DOM-IGNORE-BEGIN
protected:

  OdTvDCRect                     m_importRect;             // Output rectangle. Used for correct import of some specific objects. The normal way to set the output window size.
  OdUInt8                        m_flags;                  // Different options.
  OdTvFeedbackForChooseCallback  m_pCallback;              // Callback for choose.
//DOM-IGNORE-END
};


/** \details
  This class implements the ODA Visualize SDK parameters for appending .dgn files content.
*/
class ODTV_EXPORT OdTvDgnAppendParams : public OdTvDgnImportParams, public OdTvBaseAppendParams
{
public:

  /** \details 
    Creates a new set of parameters for appending .dgn file content. 
  */
  OdTvDgnAppendParams() : OdTvDgnImportParams() {};

  /** \details 
    Destroys the set of parameters for appending .dgn file content. 
  */
  virtual ~OdTvDgnAppendParams() {}
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing .prc files.
  \sa
  <link tv_import_params_prc, Work with PRC Import Parameters>
*/
class ODTV_EXPORT OdTvPrcImportParams : public OdTvBaseImportParams
{
  /** \details
    Specific options for the .prc import operation.
  */
  enum ParamFlags
  {
    /* Gives the names for the Visualize SDK entities according to the file object names (for example, AcDbCircle, etc). */
    kObjectNaming = 1,
    /* Stores source objects in the user data of the <link OdTvEntity, OdTvEntity> objects. */
    kStoreSource = 2,
    /* Cleans empty objects. */
    kClearEmptyObjects = 4,
    /* Rearranges objects. */
    kRearrangeObjects = 8,
    /* Import B-Rep as OdTvBrepData. */
    kImportBrepAsBrep = 16
  };

public:

  /** \details
    Creates a new set of .prc import parameters with default values.
  */
  OdTvPrcImportParams();

  /** \details
    Destroys the set of .prc import parameters.
  */
  ~OdTvPrcImportParams() {}

  /** \details
    Sets a new palette to be used during the import operation.
    
    \param pPalette [in] A new palette to be set represented with a pointer to an array of colors.
    \remarks
    If the pPalette parameter is NULL, one of two default palettes is used depending on the background color value.
  */
  void setPalette(const ODCOLORREF* pPalette);

  /** \details
    Retrieves the current palette to be used during the import operation.
    
    \returns Returns a pointer to an array of colors that represents the palette.
    \remarks
    If the returned pointer is NULL, one of two default palettes is used depending on the background color value.
  */
  const ODCOLORREF* getPalette() const;

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new rectangle object to be set.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;

  /** \details
    Sets a new value of the 'objects naming' flag.
    
    \param bSet [in] A new flag value.
  */
  void setObjectNaming(bool bSet);

  /** \details
    Retrieves the current 'objects naming' flag value.
    
    \returns Returns the current value of the objects naming flag.
  */
  bool getObjectNaming() const;

  /** \details
    Sets a new value of the 'store source objects' flag.
    
    \param bSet [in] A new flag value.
  */
  void setStoreSourceObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'store source objects' flag.
    
    \returns Returns the current 'store source objects' flag's value.
  */
  bool getStoreSourceObjects() const;

  /** \details
    Sets a new value of the flag that determines whether empty objects should be cleared.
    
    \param bSet [in] A new flag value.
  */
  void setClearEmptyObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'clear empty objects' flag.
    
    \returns Returns true if empty objects should be cleared during the import operation; otherwise the method returns false. 
  */
  bool getClearEmptyObjects() const;

  /** \details
    Sets a new value of the 'rearrange objects' flag.
    
    \param bSet [in] A new flag value.
  */
  void setRearrangeObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'rearrange objects' flag.
    
    \returns Returns true if the objects should be rearranged during the import operation; otherwise the method returns false. 
  */
  bool getRearrangeObjects() const;

  /** \details
    Sets a new value of the 'import B-Rep as B-Rep' flag.
    
    \param bSet [in] A new flag value.
  */
  void setImportBrepAsBrep(bool bImportBrepAsBrep);

  /** \details
    Checks whether B-Rep objects from the source files should be imported as B-Rep objects.
    
    \returns 
    true if and only if B-Rep should be imported as B-Rep.
  */
  bool getImportBrepAsBrep() const;

  /** \details
    Sets a new value of the facet resolution for the B-Reps.
    
    \param dFacetRes [in] A new facet resolution value.
    \remarks
    The facet resolution value varies from 0.01 to 10.0.
  */
  void setBrepFacetRes(double dFacetRes);

  /** \details
    Retrieves the current facet resolution value for the B-Reps.
    
    \returns Returns the current facet resolution value between 0.01 and 10.0.
  */
  double getBrepFacetRes() const;

//DOM-IGNORE-BEGIN
protected:

  const ODCOLORREF*       m_pPalette;               // Palette to be used. If NULL, one of two default palettes is used depending on the background color.
  OdTvDCRect              m_importRect;             // Output rectangle. Used for correct import of some specific objects (camera, OLE images). The normal way to set the output window size.
  double                  m_dFACETRES;              // Facet res value (between from 0.01 to 10.0).
  OdUInt8                 m_flags;                  // Different options.
//DOM-IGNORE-END
};


/** \details
  This class implements the ODA Visualize SDK parameters for appending .prc file content.
*/
class ODTV_EXPORT OdTvPrcAppendParams : public OdTvPrcImportParams, public OdTvBaseAppendParams
{
public:

  /** \details 
    Creates a new set of parameters for appending .prc file content. 
  */
  OdTvPrcAppendParams() : OdTvPrcImportParams() {};

  /** \details 
    Destroys the set of parameters for appending .prc file content. 
  */
  virtual ~OdTvPrcAppendParams() {}
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing BIM files.
  \sa
  <link tv_import_params_bim, Work with BIM Import Parameters>
*/
class ODTV_EXPORT OdTvBimImportParams : public OdTvBaseImportParams
{
  /** \details
    Specific options for BIM import operations.
  */
  enum ParamFlags
  {
    /* Gives the names for the Visualize SDK entities according to the file object names (for example, AcDbCircle, etc). */
    kObjectNaming = 1,
    /* Stores source objects in the user data of the <link OdTvEntity, OdTvEntity> objects. */
    kStoreSource = 2,
    /* Uses thin lines mode. */
    kThinLines = 4,
    /* Cleans empty objects. */
    kClearEmptyObjects = 8, 
    /* Ignore edge's colors. */
    kIgnoreEdgesColors = 16,
    /* Use silhouettes. */
    kUseSilhouettes = 32,
    /* Use multithreading vectorization. */
    kUseMTforViewsImport = 64,
    /* Create 3D view (if it doesn't exist). */
    kCreate3DView = 128,
    /* Use an alternative CDA tree with FamilySymbol. */
    kUseAlternativeCDATree = 256
  };

public:

  /** \details
    Creates a new set of BIM import parameters with default values.
  */
  OdTvBimImportParams();

  /** \details
    Destroys the set of BIM import parameters.
  */
  ~OdTvBimImportParams() {}

  /** \details
    Sets a new background value for the BIM file import operation.
    
    \param background [in] A new background color value.
  */
  void setBackground(ODCOLORREF background);

  /** \details
    Retrieves the current background value.
    
    \returns Returns the current value of the background color for the BIM file import operation.
  */
  ODCOLORREF getBackground() const;

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new rectangle object to be set.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;

  /** \details
    Sets a new value of the 'objects naming' flag.
    
    \param bSet [in] A new flag value.
  */
  void setObjectNaming(bool bSet);

  /** \details
    Retrieves the current 'objects naming' flag value.
    
    \returns Returns the current value of the objects naming flag.
  */
  bool getObjectNaming() const;

  /** \details
    Sets a new value of the 'store source objects' flag.
    
    \param bSet [in] A new flag value.
  */
  void setStoreSourceObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'store source objects' flag.
    
    \returns Returns the current store source objects flag's value.
  */
  bool getStoreSourceObjects() const;

  /** \details
    Sets a new callback function for filtering element selection.
    
    \param pCallback [in]  A pointer to the <link OdTvFeedbackForChooseCallback, selection function>.
  */
  void setFeedbackForChooseCallback(OdTvFeedbackForChooseCallback pCallback);

  /** \details
    Retrieves the current callback function for element selection.
    
    \returns Returns a pointer to the current <link OdTvFeedbackForChooseCallback, callback function>.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;

  /** \details
    Sets a new callback function for warning message.
    
    \param pCallback [in]  A pointer to the <link OdTvFeedbackForWarningCallback, warning function>.
  */
  void setFeedbackForWarningCallback(OdTvFeedbackForWarningCallback pCallback);

  /** \details
    Retrieves the current callback function for warning message.
    
    \returns Returns a pointer to the current <link OdTvFeedbackForWarningCallback, callback function>.
  */
  OdTvFeedbackForWarningCallback getFeedbackForWarningCallback() const;

  /** \details
    Sets a new 'thin lines' flag value.
    
    \param bSet [in] A new flag value.
  */
  void setThinLines(bool bSet);

  /** \details
    Retrieves the current 'thin lines' flag value.
    
    \returns Returns true if thin lines are used; otherwise the method returns false.
  */
  bool getThinLines() const;

  /** \details
    Sets a new value of the flag that determines whether empty objects should be cleared.
    
    \param bSet [in] A new flag value.
  */
  void setClearEmptyObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'clear empty objects' flag.
    
    \returns Returns true if empty objects should be cleared during the import operation; otherwise the method returns false. 
  */  
  bool getClearEmptyObjects() const;

  /** \details
    Sets a new value of the flag that determines whether edge's colors should be ignored.
    
    \param bSet [in] A new flag value.
  */
  void setIgnoreEdgesColors(bool bSet);

  /** \details
    Retrieves the current value of the 'ignore edge's colors' flag.
    
    \returns Returns true if edge's colors should be ignored during the import operation; otherwise the method returns false.
  */
  bool getIgnoreEdgesColors() const;

  /** \details
    Sets a new value of the flag for using silhouettes.
    
    \param bSet [in] A new flag value.
  */
  void setUseSilhouettes(bool bSet);

  /** \details
    Retrieves the current value of the 'silhouette usage' flag.
    
    \returns Returns true if silhouettes should be used; otherwise the method returns false.
  */
  bool getUseSilhouettes() const;

  /** \details
    Sets a new value of the flag for multithreaded views import.
    
    \param bSet [in] A new flag value.
  */
  void setUseMTforViewsImport(bool bSet);

  /** \details
    Retrieves the current value of the 'multithreaded views import' flag.
    
    \returns Returns true if multithread vectorization is enabled during the import operation; otherwise the method returns false.
  */
  bool getUseMTforViewsImport() const;

  /** \details
    Sets a new value of maximum threads for views import.
    
    \param nViewsImportThreads [in] A new value of maximum threads for vectorization.
  */
  void setViewsImportThreads(OdUInt64 nViewsImportThreads);

  /** \details
    Retrieves the current value of maximum threads for views import.
    
    \returns Returns current value of maximum threads for views import.
  */
  OdUInt64 getViewsImportThreads() const;

  /** \details
    Sets a new value of the flag for 3D view creation (if it doesn't exist).
    
    \param bSet [in] A new flag value.
  */
  void setCreate3DView(bool bSet);

  /** \details
    Retrieves the current value of the 3D view creation (if it doesn't exists) flag.
    
    \returns Returns true if 3D view creation is enabled during the import operation; otherwise the method returns false.
  */
  bool getCreate3DView() const;

  /** \details
    Sets a new value of the flag for using alternative CDA tree.
    
    \param bSet [in] A new flag value.
  */
  void setUseAlternativeCDATree(bool bSet);

  /** \details
    Retrieves the current value of the 'alternative CDA tree usage' flag.
    
    \returns Returns true if alternative CDA tree usage is enabled during the import operation; otherwise the method returns false.
  */
  bool getUseAlternativeCDATree() const;

//DOM-IGNORE-BEGIN
protected:

  ODCOLORREF                     m_background;             // Background color. Default: black.
  OdTvDCRect                     m_importRect;             // Output rectangle. Used for correct import of some specific objects (camera, OLE images). The normal way to set the output window size.
  OdUInt16                       m_flags;                  // Different options.
  OdTvFeedbackForChooseCallback  m_pCallback;              // Callback for choose.
  OdTvFeedbackForWarningCallback m_pWarningCallback;       // Callback for warning.
  OdUInt64                       m_nViewsImportThreads;    // Max number of vectorization threads
//DOM-IGNORE-END  
};

/** \details
  This class implements the ODA Visualize SDK parameters for appending BIM file content.
*/
class ODTV_EXPORT OdTvBimAppendParams : public OdTvBimImportParams, public OdTvBaseAppendParams
{
public:

  /** \details 
    Creates a new set of parameters for appending BIM file content. 
  */
  OdTvBimAppendParams() : OdTvBimImportParams() {};
  
  /** \details 
    Destroys the set of parameters for appending BIM file content. 
  */
  virtual ~OdTvBimAppendParams() {}
};


/** \details
This class implements the Visualize SDK parameters for importing NwInterop files.
\sa
<link tv_import_params_nw, Work with NW Import Parameters>
*/
class ODTV_EXPORT OdTvNwImportParams : public OdTvCustomBaseImportParams
{
public:

  /** \details
    Specific options for NW import operations.
  */
  enum ParamFlags
  {
    /* Store source. */
    kStoreSourceObjects   = 1,
    /* Change to NWC. */
    kReplaceByNwc         = 2,
    /* Import cutting planes. */
    kImportCuttingPlanes  = 4,
    /* Import Grid */
    kImportGrid  = 8
  };

  /** \details
    Creates a new set of NwInterop import parameters with default values.
  */
  OdTvNwImportParams();

  /** \details
    Destroys the set of Interop import parameters.
  */
  ~OdTvNwImportParams() {}

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new rectangle object to be set.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;

  /** \details
    Sets a new background value for the NwInterop import operation.
    
    \param background [in] A new background color value.
  */
  void setBackground(ODCOLORREF background);

  /** \details
    Retrieves the current background value.
    
    \returns Returns the current value of the background color for the NwInterop import operation.
  */
  ODCOLORREF getBackground() const;

  /** \details
    Sets a new 'store source objects' flag value.
    
    \param bVal [in] A new flag value.
  */
  void setStoreSourceObjects(bool bVal);

  /** \details
    Retrieves the 'store source objects' flag value.
    
    \returns Returns true if storage of the source objects is available; otherwise the method returns false.
  */
  bool getStoreSourceObjects() const;

  /** \details
    Sets a new 'change to Nwc' flag value.
    
    \param bVal [in] A new flag value.
    \remarks
    This option specifies to look for a corresponding cache file instead of importing data directly from a native file.
  */
  void setReplaceByNwc(bool bVal);

  /** \details
    Retrieves the 'change to Nwc' flag value.
    
    \returns Returns true if change to Nwc is available; otherwise the method returns false.
    \remarks
    This option specifies to look for a corresponding cache file instead of importing data directly from a native file.
  */
  bool getReplaceByNwc() const;

  /** \details
    Sets a new 'import cutting planes' flag value.
    
    \param bVal [in] A new flag value.
  */
  void setImportCuttingPlanes(bool bVal);

  /** \details
    Retrieves the 'import cutting planes' flag value.
    
    \returns Returns true if import of the cutting planes is available; otherwise the method returns false.
  */
  bool getImportCuttingPlanes() const;

  /** \details
    Sets a new callback function for filtering element selection.
    
    \param pCallback [in]  A pointer to the <link OdTvFeedbackForChooseCallback, selection function>.
  */
  void setFeedbackForChooseCallback(OdTvFeedbackForChooseCallback pCallback);

  /** \details
    Retrieves the current callback function for element selection.
    
    \returns Returns a pointer to the current <link OdTvFeedbackForChooseCallback, callback function>.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;

  /** \details
    Retrieves the 'import grid' flag value.
    \returns Returns true if import of the grid is available; otherwise the method returns false.
  */
  bool getImportGrid() const;

  /** \details
    Sets a new 'import grid' flag value.
    \param bVal [in] A new flag value.
  */
  void setImportGrid(bool bVal);
//DOM-IGNORE-BEGIN
protected:
  OdTvDCRect                     m_importRect;             // Output rectangle. Used for correct import of some specific objects (camera, OLE images). The normal way to set the output window size.
  ODCOLORREF                     m_background;             // Background color.
  OdUInt8                        m_flags;                  // Different flags
  OdTvFeedbackForChooseCallback  m_pCallback;              // Callback for choose.
//DOM-IGNORE-END
};

/** \details
  This class implements the Visualize SDK parameters for appending NwInterop file content.
*/
class ODTV_EXPORT OdTvNwAppendParams : public OdTvNwImportParams, public OdTvBaseAppendParams
{
public:

  /** \details 
    Creates a new set of parameters for appending NwInterop file content. 
  */
  OdTvNwAppendParams() : OdTvNwImportParams() {};

  /** \details 
    Destroys the set of parameters for appending NwInterop file content. 
  */
  virtual ~OdTvNwAppendParams() {}
};


/** \details
  This class implements the ODA Visualize SDK parameters for importing .ifc files.
  \sa
  <link tv_import_params_ifc, Work with IFC Import Parameters>
*/
class ODTV_EXPORT OdTvIfcImportParams : public OdTvCustomBaseImportParams
{
  OdTvFeedbackForChooseCallback m_pCallback;              // Callback.
  double m_deviation;                                     // Triangulation deviation value.
  OdUInt16 m_minPerCircle;                                // Minimum number of segments per circle if deviation is high.
  OdUInt16 m_maxPerCircle;                                // Maximum number of segments per circle if deviation is low.
  OdUInt8  m_modelerType;                                 // Modeler type for IFC geometry.
  bool m_bUseCustomColor;                                 // Use background color or default gradient background.
  ODCOLORREF m_BGColor;                                   // Background color.
  bool  m_isMultithreadingEnable;                         // Multithreading.
  OdUInt16  m_threadsCount;                               // Threads count.
  bool m_useDictionaryTypePath;                           // Store dictionary of TypePath to hdf5 file.
  bool m_storeInveseAttributes;                           // Store inverse attributes to hdf5 file.
  OdUInt16 m_deflateLevel;                                // DeflateLevel for hdf5 file.
  OdUInt32 m_readChunkSize;                               // Chunk size for reading hdf5 file.
  OdUInt32 m_writeChunkSize;                              // Chunk size for writing hdf5 file.
  bool m_isLogOn;                                         // Enable logging.
  bool m_isValidation;                                    // Enable loading with validation.

public:

  /** \details
    Creates a new set of IFC import parameters with default values.
  */
  OdTvIfcImportParams();

  /** \details
    Destroys the set of IFC import parameters.
  */
  virtual ~OdTvIfcImportParams() {};

  /** \details
    Sets a new value of the background color.
    
    \param defcolor [in] A new background color value.
  */
  void setBGColor(ODCOLORREF defcolor);

  /** \details
    Retrieves the current background color value.
    
    \returns Returns the current value of the background color.
  */
  ODCOLORREF getBGColor() const;


  /** \details
    Enables the user-defined background color.
    
    \param enable [in] Flag that specifies whether to enable user-defined background.
  */
  void setEnableBGColor(bool enable);

  /** \details
    Checks whether user-defined background color is enabled.
    
    \returns 
    true if user-defined background color is enabled, false otherwise.
  */
  bool getEnableBGColor() const;

  /** \details
    Sets a new value of the threads count for the multi-threaded import.
    
    \param threadsCount [in] A new threads count value.
  */
  void setThreadsCount(OdUInt16 threadsCount);

  /** \details
    Retrieves the current threads count for the multithreaded import.  
    
    \returns 
    Returns the current count of threads for the multithreaded import.
  */
  OdUInt16 getThreadsCount() const;

  /** \details
    Enables or disables the multithreading.
    
    \param enable [in] Flag that states whether to enable multithreading.
  */
  void setEnableMultithreading(bool enable);

  /** \details
    Checks whether multithreading is enabled.
    
    \returns 
    Returns true if multithreading is enabled, false - otherwise.
  */
  bool getEnableMultithreading() const;

  /** \details
    Enables the logging.
    
    \param enable [in] Flag that specifies whether to enable logging.
    \remarks
    If the option is enabled, a new .log file is created with the same file name where the logging information is stored.
  */
  void setIsLogOn(bool enable);
  
  /** \details
    Checks whether logging is enabled.
    
    \returns Returns true if logging is enabled, false - otherwise.
    \remarks
    If the option is enabled, a new .log file is created with the same file name where the logging information is stored.
  */
  bool getIsLogOn() const;

  /** \details
    Sets a new value for 'use dictionary of TypePath' flag for hdf5 file.
    
    \param useDictionaryTypePath [in] A new value for 'use dictionary of TypePath' flag value.
  */
  void setUseDictionaryTypePath(bool useDictionaryTypePath);

  /** \details
    Retrieves the current 'use dictionary of TypePath' flag value for hdf5 file.
    
    \returns 
    true if the 'use dictionary of TypePath' flag is enabled, false otherwise.
  */
  bool getUseDictionaryTypePath() const;

  /** \details
    Sets a new value for 'store inverse attributes' flag for hdf5 file.
    
    \param storeInverseAttributes [in] A new value for 'store inverse attributes' flag value.
    \sa
    <exref target="https://docs.opendesign.com/tifc/ifc_overview_schemas.html">IFC Schemas</exref>
  */
  void setStoreInveseAttributes(bool storeInverseAttributes);

  /** \details
    Retrieves the current 'store inverse attributes' flag value for hdf5 file.
    
    \returns 
    true if the 'store inverse attributes' flag is enabled, false otherwise.
    \sa 
    <exref target="https://docs.opendesign.com/tifc/ifc_overview_schemas.html">IFC Schemas</exref>
  */
  bool getStoreInveseAttributes() const;

  /** \details
    Sets a new value of the deflate level for hdf5 file.
    The deflate level controls how much the file content is compressed.
    
    \param deflateLevel [in] A new deflate level value from 0 to 9.
  */
  void setDeflateLevel(OdUInt16 deflateLevel);

  /** \details
    Retrieves the current deflate level value for hdf5 file.
    
    \returns 
    Returns the current value of the deflate level from 0 to 9, 
    where 0 indicates no compression and 9 represents the maximum compression.
  */
  OdUInt16 getDeflateLevel() const;

  /** \details
    Sets a new value of the chunk size to read from hdf5 file.
    This parameter defines the number of data rows that are read at a time.
    
    \param readChunkSize [in] A new chunk size value.
    \remarks
    By default read chunk size is 0 (unlimited).
  */
  void setReadChunkSize(OdUInt32 readChunkSize);

  /** \details
    Retrieves the current chunk size value to read from hdf5 file.
    This parameter represents the number of data rows that are read at a time.
    
    \returns 
    Returns the current value of the chunk size.
    \remarks
    By default read chunk size is 0 (unlimited).
  */
  OdUInt32 getReadChunkSize() const;

  /** \details
    Sets a new value of the chunk size to write to hdf5 file.
    This parameter defines the number of data rows that are written at a time.
    
    \param writeChunkSize [in] A new chunk size value.
    \remarks
    By default write chunk size is 1024.
  */
  void setWriteChunkSize(OdUInt32 writeChunkSize);

  /** \details
    Retrieves the current chunk size value to write to hdf5 file.
    This parameter represents the number of data rows that are written at a time.
    
    \returns 
    Returns the current value of the chunk size.
    \remarks
    By default write chunk size is 1024.
  */
  OdUInt32 getWriteChunkSize() const;

  /** \details
    Sets the callback function.

    \param pCallback [in]  A pointer to the function.
  */
  void setFeedbackForChooseCallback(OdTvFeedbackForChooseCallback pCallback);

  /** \details
    Retrieves the current callback function for element selection.
    
    \returns 
    Returns a pointer to the current callback function.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;
  
  /** \details
    Retrieves the deviation value that is used during the triangulation process.

    \returns 
    Returns a double value that shows the maximum allowed deviation of a triangulated shape.
  */
  double getDeviation() const;
  
  /** \details
    Sets the maximum allowed deviation value of a triangulated shape.
  
    \param deviation [in]  A double value that specifies how much a triangulated shape will deviate from the same shape represented by an equation.
  */
  void setDeviation(double deviation);

  /** \details
    Retrieves how many segments are used to construct a shape if the deviation value is high.
  
    \returns Returns an OdUInt16 value that represents the quantity of segments used to form a shape when the deviation value is high.
  */
  OdUInt16 getMinPerCircle() const;
  
  /** \details
    Sets the minimum amount of segments required to construct a shape if the deviation value is high.
  
    \param minPerCircle [in]  Minimum quantity of segments used to form a shape when the deviation value is high.
  */
  void setMinPerCircle(OdUInt16 minPerCircle);

  /** \details
    Retrieves how many segments are used to construct a shape if the deviation value is low.
  
    \returns Returns an OdUInt16 value that represents the quantity of segments used to form a shape when the deviation value is low.
  */
  OdUInt16 getMaxPerCircle() const;
  
  /** \details
    Sets the minimum amount of segments required to construct a shape if the deviation value is low.
  
    \param maxPerCircle [in]  Maximum quantity of segments used to form a shape when the deviation value is low.
  */
  void setMaxPerCircle(OdUInt16 maxPerCircle);

  /** \details
    Retrieves modeler type, that will be used to create IFC geometry.
  
    \returns Returns an OdUInt8 value that represents a modeler type. Possible returned values:
    <table>
      Name                                Value
      0                                   ODA Facet Modeler
      1                                   Spatial ACIS modeler
      2                                   ODA Brep Modeler
    </table>
  */
  OdUInt8 getModelerType() const;
  
  /** \details
    Sets the modeler type, that will be used to create IFC geometry.
  
    \param type [in]  Modeler type for IFC SDK. Possible values: 0 (ODA Facet Modeler), 1 (Spatial ACIS modeler) and 2 (ODA Brep Modeler).
  */
  void setModelerType(OdUInt8 type);

  /** \details
    Checks whether loading with validation is enabled.
    
    \returns Returns true if loading with validation is enabled, false - otherwise.
  */
  bool getLoadingWithValidation() const;

  /** \details
    Enables validation while loading IFC file.
  
    \param validation [in] Flag that specifies whether to perform validation while file loading.
  */
  void setLoadingWithValidation(bool validation);
};


/** \details
  This class implements the ODA Visualize SDK parameters for appending .ifc files.
*/
class ODTV_EXPORT OdTvIfcAppendParams : public OdTvIfcImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of parameters for appending content of an .ifc file.
  */
  OdTvIfcAppendParams() : OdTvIfcImportParams() {};

  /** \details
    Destroys the set of parameters for appending content of an .ifc file.
  */
  virtual ~OdTvIfcAppendParams() {};

};

/** \details
  This class implements the ODA Visualize SDK parameters for importing .dwf files.
*/
class ODTV_EXPORT OdTvDwfImportParams : public OdTvBaseImportParams
{
public:
  /** \details
    Specific options for the importing from a .dwf drawing.
  */
  enum ParamFlags
  {
    /* Gives the names of the Visualize SDK entities according to file object names (for example, AcDbCircle, etc). */
    kObjectNaming = 1,
    /* Stores source objects in the user data of the <link OdTvEntity, OdTvEntity> objects. */
    kStoreSource = 2,
    /* Cleans empty objects. */
    kClearEmptyObjects = 4,
    /* Converts indexed colors to RGB during import. */
    kConvertIndexedToRGB = 8
  };

public:

  /** \details
    Creates a new set of .dwf import parameters with default values:
    m_background = ODRGB(0, 0, 0)
    m_pPalette = NULL
    m_pCallback = NULL
    m_flags = kClearEmptyObjects
    m_importRect = (0, 0, 0, 0)
  */
  OdTvDwfImportParams();

  /** \details
    Destroys the set of .dwf import parameters.
  */
  ~OdTvDwfImportParams() {}

  /** \details
    Sets a new value of the background color.
    
    \param background [in] A new background color.
  */
  void setBackground(ODCOLORREF background);

  /** \details
    Retrieves the current value of the background color.
    
    \returns Returns the current value of the background color.
  */
  ODCOLORREF getBackground() const;

  /** \details
    Sets a new palette to be used during the import operation.
    
    \param pPalette [in]  A pointer to the color array that represents the new palette.
    \remarks
    If the pPalette parameter is NULL, one of two default palettes is used depending on the background color value.
  */
  void setPalette(const ODCOLORREF* pPalette);

  /** \details
    Retrieves the current palette to be used during the import operation.
    
    \returns Returns a pointer to the color array that represents the current palette.
    \remarks
    If no palette is set (the method returns a NULL pointer), one of two default palettes is used depending on the background color value.
  */
  const ODCOLORREF* getPalette() const;

  /** \details
    Sets a new device rectangle that is used during the import operation.
    
    \param rect [in]  A new <link OdTvDCRect, rectangle object> to be set.
    \remarks
    If all components of the specified rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  void setDCRect(const OdTvDCRect& rect);

  /** \details
    Retrieves the current device rectangle that is used during the import operation.
    
    \returns Returns the current device rectangle object.
    \remarks
    If all components of the returned rectangle are equal to zero, the rectangle is not associated with the Visualize device.
  */
  OdTvDCRect  getDCRect() const;

  /** \details
    Sets a new value of the 'object naming' flag.
    
    \param bSet [in] A new flag value.
  */
  void setObjectNaming(bool bSet);

  /** \details
    Retrieves the current 'object naming' flag value.
    
    \returns Returns the current value of the 'object naming' flag.
  */
  bool getObjectNaming() const;

  /** \details
    Sets a new value of the 'store source objects' flag.
    
    \param bSet [in] A new flag value.
  */
  void setStoreSourceObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'store source objects' flag.
    
    \returns Returns the current 'store source objects' flag's value.
  */
  bool getStoreSourceObjects() const;

  /** \details
    Sets a new value of the flag that determines whether empty objects should be cleared.
    
    \param bSet [in] A new flag value.
  */
  void setClearEmptyObjects(bool bSet);

  /** \details
    Retrieves the current value of the 'clear empty objects' flag.
    
    \returns Returns true if empty objects should be cleared during the import operation; otherwise the method returns false.
  */
  bool getClearEmptyObjects() const;

  /** \details
    Sets a new callback function for filtering element selection.
    
    \param pCallback [in]  A pointer to the <link OdTvFeedbackForChooseCallback, selection function>.
  */
  void setFeedbackForChooseCallback(OdTvFeedbackForChooseCallback pCallback);

  /** \details
    Retrieves the current callback function for element selection.
    
    \returns Returns a pointer to the current <link OdTvFeedbackForChooseCallback, callback function>.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;

  /** \details
    Specifies whether the indexed colors should be converted to RGB during import.
    
    \param bNeedConvertIndexedtoRGB [in] A new value of kConvertIndexedToRGB flag.
  */
  void setConvertIndexedToRGB(bool bNeedConvertIndexedtoRGB);

  /** \details
    Checks whether the indexed colors should be converted to RGB during import.
    
    \returns Returns value of kConvertIndexedToRGB flag.
  */
  bool getConvertIndexedToRGB() const;

  //DOM-IGNORE-BEGIN
protected:

  ODCOLORREF                    m_background; // Background color. Default: black.
  const ODCOLORREF*             m_pPalette;   // Palette to be used. If NULL, one of two default palettes is used depending on background color.
  OdTvDCRect                    m_importRect; // Output rectangle. Used for correct import of some specific objects (camera, OLE images, 3D solids). The normal way to set the output window size.
  OdUInt16                      m_flags;      // Different options.
  OdTvFeedbackForChooseCallback m_pCallback;  // Callback for choose.
  //DOM-IGNORE-END
};

/** \details
  This class implements the ODA Visualize SDK parameters for appending .dwf files.
*/
class ODTV_EXPORT OdTvDwfAppendParams : public OdTvDwfImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of parameters for appending content of an .dwf file.
  */
  OdTvDwfAppendParams() : OdTvDwfImportParams() {};

  /** \details
    Destroys the set of parameters for appending content of an .dwf file.
  */
  virtual ~OdTvDwfAppendParams() {};
};

/** \details
  This class implements the ODA Visualize SDK parameters for importing .vsf files.
*/
class ODTV_EXPORT OdTvVsfImportParams : public OdTvBaseImportParams
{
public:
  enum ParamFlags
  {
    kMtImport = 1
  };
public:

  /** \details
    Creates a new set of .vsf import parameters with default values.
  */
  OdTvVsfImportParams();

  /** \details
    Destroys the set of .vsf import parameters.
  */
  ~OdTvVsfImportParams() {}

  /** \details
    Specifies whether the file has to be imported in multi-threading mode.

    \param bNeedMT [in] A new value of kMtImport flag.
  */
  void setMtImport( bool bNeedMT );

  /** \details
    Checks whether the file has to be imported in multi-threading mode.

    \returns Returns value of kMtImport flag.
  */
  bool getMtImport() const;

  /** \details
  Sets a new callback function for filtering element selection.

  \param pCallback [in]  A pointer to the <link OdTvFeedbackForChooseCallback, selection function>.
*/
  void setFeedbackForChooseCallback( OdTvFeedbackForChooseCallback pCallback );

  /** \details
    Retrieves the current callback function for element selection.

    \returns Returns a pointer to the current <link OdTvFeedbackForChooseCallback, callback function>.
  */
  OdTvFeedbackForChooseCallback getFeedbackForChooseCallback() const;
  //DOM-IGNORE-BEGIN
protected:
  OdUInt8                       m_flags;      // Different options.
  OdTvFeedbackForChooseCallback m_pCallback;  // Callback for choose.
  //DOM-IGNORE-END
};

/** \details
  This class implements the ODA Visualize SDK parameters for appending .vsf files.
*/
class ODTV_EXPORT OdTvVsfAppendParams : public OdTvVsfImportParams, public OdTvBaseAppendParams
{
public:

  /** \details
    Creates a new set of parameters for appending content of an .vsf file.
  */
  OdTvVsfAppendParams() : OdTvVsfImportParams() {};

  /** \details
    Destroys the set of parameters for appending content of an .vsf file.
  */
  virtual ~OdTvVsfAppendParams() {};
};

#endif //_ODTV_IMPORT_H_INCLUDED_
