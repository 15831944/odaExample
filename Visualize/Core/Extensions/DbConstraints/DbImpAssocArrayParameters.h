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

#ifndef OdTvDbImpAssocArrayParameters_INCLUDED_
#define OdTvDbImpAssocArrayParameters_INCLUDED_ /*!DOM*/
#include "map"
#include "DbConstraintsExports.h"
#include "DbEntity.h"
#include "DbFiler.h"

#include "Ge/GePoint3d.h"
#include "Ge/GeMatrix3d.h"
#include "DbAssocArrayItem.h"
#include "DbImpAssocActionBody.h"


#include "TD_PackPush.h"

class DbAssocArrayRectangularParameters;
class OdTvDbAssocArrayModifyActionBody;

/** \details
  This class represents the custom implementation of an item of an array of associated parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayItem
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayItem();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayItem();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
  /** \details
    Transforms the item.
  */
  OdResult transformBy(const OdGeMatrix3d& transform);
  /** \details
    Gets the transformation matrix.
  */
  OdResult getTransform(OdGeMatrix3d& transform, bool bCompounded) const;
  /** \details
    Sets the default transformation matrix.
  */
  OdResult setDefaultTransform(const OdGeMatrix3d& transform);
  /** \details
    Checks whether the transformation is relative.
  */
  bool hasRelativeTransform() const;
  /** \details
    Sets the erase status.
  */
  OdResult setErased(bool bErased);

  static OdTvDbImpAssocArrayItem* getImpl( const OdTvDbAssocArrayItem *pItem )
  {
    return pItem->m_pImpl;
  }

  void setModifyActionBody( OdTvDbObjectId bodyId )
  {
    m_repBodyId = bodyId;
  }

  OdTvDbObjectId modifyActionBody() const
  {
    return m_repBodyId;
  }

  bool replaced() const
  {
    return !m_repBodyId.isNull();
  }

  void reset();

protected:
  /*!DOM*/
  enum Flags
  {
    kErased = 1 << 0,
    kRealtiveTransform = 1 << 1,
    kDefaulTransform = 1 << 2,
    kItemPresent = 1 << 3,
    kModified = 1 << 4,
    kChanged = 1 << 5
  };

  /* {secret} */
  friend class OdTvDbAssocArrayItem;
  /*!DOM*/
  OdTvDbItemLocator m_locator;
  /*!DOM*/
  OdGeMatrix3d m_matrix;
  /*!DOM*/
  OdTvDbObjectId m_entityProviderId;

  OdTvDbObjectId m_repBodyId;
  
  OdGeMatrix3d m_relative;

  bool bErased; 
  
};


/** \details
  This class represents the custom implementation of an array of associated parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayParameters
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayParameters();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayParameters();

  /** \details
    Reads the .dwg file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);

  /** \details
    Writes the .dwg file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;

  /** \details
    Reads the .dxf file data of this object. 

    \param pFiler [in]  Filer object from which data are read.
    
    \remarks
    Returns the filer status.
  */
  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);

  /** \details
    Writes the .dxf file data of this object. 

    \param pFiler [in]  Pointer to the filer to which data are written.
  */
  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual void composeForLoad( OdTvDbAssocArrayParameters *pAssocArrayParam, OdDb::SaveType format, OdDb::DwgVersion version );
  /** \details
    Gets an array of items. This method is pure and must be overridden in derived classes.
  */
  virtual OdResult getItems( OdArray<OdTvDbAssocArrayItemPtr>& items ) = 0;
  /** \details
    Sets the value, expression and evaluator of the parameter using its name.
  */
  OdResult setValueParam( const OdString& paramName,
                          const OdTvDbEvalVariant& value,
                          const OdString& expression,
                          const OdString& evaluatorId,
                          OdString& errorMessage,
                          OdValue::UnitType* pUnitType = NULL);
  /** \details
    Gets a value for the parameter using its name.
  */
  OdResult getValueParam( const OdString& paramName,
                          OdTvDbEvalVariant& value,
                          OdString& expression,
                          OdString& evaluatorId,
                          OdValue::UnitType& unitType) const;
  /** \details
    Sets the geometry parameter.
  */
  OdResult setGeomParam( const OdString& paramName,
                         const OdTvDbGeomRef* pGeomRef,
                         OdTvDbObjectId& paramId);
  /** \details
    Gets the geometry parameter.
  */
  OdResult getGeomParam( const OdString& paramName,
                         OdTvDbGeomRefPtr &pGeomRef,
                         OdTvDbObjectId& paramId) const;
  /** \details
    Gets an array of the owned parameter names.
  */
  void ownedValueParamNames(OdStringArray& paramNames) const;
  /** \details
    Gets an array of the owned geometry parameter names.
  */
  void ownedGeomParamNames(OdStringArray& paramNames) const;

  virtual OdResult getItemPosition( const OdTvDbItemLocator& locator,
                            OdGePoint3d& position,
                            OdGeMatrix3d& xform) const;
  /** \details
    Gets an array of grip points.
  */
  OdResult getGripPointAt( OdArray<OdDbGripDataPtrArray>& grips) const;
  /** \details
    Sets the owner for this array of parameters.
  */
  OdResult setOwner(class OdTvDbAssocArrayActionBody* pOwner);

  static OdTvDbImpAssocArrayParameters* getImpl( const OdTvDbAssocArrayParameters *pParam )
  {
    return pParam->m_pImpl;
  }

protected:

  virtual OdResult GetItemByLocator(const OdTvDbItemLocator &locator, OdTvDbAssocArrayItemPtr &pItem) const = 0;

  virtual OdGeMatrix3d CalculateDefaultMatrix( const OdTvDbItemLocator &locator ) = 0;
  /*!DOM*/
  friend class OdTvDbAssocArrayParameters;
  friend class OdTvDbImpAssocArrayActionBody;
  /*!DOM*/
  typedef OdArray<OdTvDbAssocArrayItemPtr> ItemArray;
  ItemArray m_items;

  OdTvDbObjectIdArray getModifyBodies() const;
 
  OdTvDbObjectId m_ownerId; // class OdTvDbAssocArrayActionBody* m_pOwner;

  OdArray<OdTvDbImpValueParamPtr> m_arrValueParams;

 
  std::map <OdString, OdTvDbGeomRefPtr> m_GeomParam;

};


/** \details
  This class represents the custom implementation of an array of common parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayCommonParameters : public OdTvDbImpAssocArrayParameters
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayCommonParameters();

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayCommonParameters();

  virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
//  virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
//  virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  virtual void composeForLoad( OdTvDbAssocArrayParameters *pAssocArrayParam, OdDb::SaveType format, OdDb::DwgVersion version );

  /** \details
    Returns the level count.
  */
  int levelCount(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the level spacing.
  */
  double levelSpacing(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the row count.
  */
  int rowCount(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the row elevation.
  */
  double rowElevation(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the row spacing.
  */
  double rowSpacing(OdString& expression, OdString& evaluatorId) const;  
  /** \details
    Sets the level count to a given value.
  */
  OdResult setLevelCount( int nLevels, 
                          const OdString& expression, // = OdString::kEmpty
                          const OdString& evaluatorId, // = OdString::kEmpty
                          OdString& pErrorMessage); // = NULL
  /** \details
    Sets the offset of the level spacing to a given value.
  */
  OdResult setLevelSpacing( double offset, 
                            const OdString& expression, //  = OdString::kEmpty
                            const OdString& evaluatorId, // = OdString::kEmpty
                            OdString& pErrorMessage); // = NULL
  /** \details
    Sets the row count to a given value.
  */
  OdResult setRowCount( int nRows, 
                        const OdString& expression, // = OdString::kEmpty
                        const OdString& evaluatorId, // = OdString::kEmpty
                        OdString& pErrorMessage); // = NULL
  /** \details
    Sets the row elevation to a given value.
  */
  OdResult setRowElevation( double elevation, 
                            const OdString& expression, // = OdString::kEmpty
                            const OdString& evaluatorId, // = OdString::kEmpty
                            OdString& pErrorMessage); // = NULL
  /** \details
    Sets the offset of the row spacing to a given value.
  */
  OdResult setRowSpacing( double offset, 
                          const OdString& expression, // = OdString::kEmpty
                          const OdString& evaluatorId, // = OdString::kEmpty
                          OdString& pErrorMessage); // = NULL

  /** \details
    Sets the base point and normal of the base plane.
  */
  OdResult setBasePlane(const OdTvDbVertexRef& basePoint, 
                        const OdGeVector3d& normal, 
                        const OdTvDbFaceRef* pFace = NULL);
  /** \details
    Gets the base point and normal of the base plane.
  */
  OdResult getBasePlane(OdTvDbVertexRef& basePoint, 
                        OdGeVector3d& normal, 
                        OdTvDbFaceRef* pFace = NULL) const;
  /** \details
    Returns the item locator.
  */
  virtual OdTvDbItemLocator getCanonicalForm(const OdTvDbItemLocator& locator) const;


protected:

  /*!DOM*/
  friend class OdTvDbAssocArrayCommonParameters; 
  friend class OdTvDbAssocArrayRectangularParameters; 
  friend class OdTvDbAssocArrayPolarParameters;
  friend class OdTvDbAssocArrayPathParameters;
  friend class OdTvDbImpAssocArrayActionBody;

  void setItemCount( int nItem );
  void setLevelCount( int nLevels );
  void setRowCount( int nRows );

  virtual OdResult GetItemByLocator(const OdTvDbItemLocator &locator, OdTvDbAssocArrayItemPtr &pItem) const;

  double m_itemSpacing;
  double m_rowSpacing;
  double m_levelSpacing;
  int m_itemCount;
  int m_rowCount;
  int m_levelCount;
  double m_rowElevation;
  OdGePoint3d m_origin;
  OdGeVector3d m_BaseNormal;

  virtual void CalculateAxes();
  virtual OdGeMatrix3d GetStartMatrix() const;
  
  const OdGeVector3d& vXaxis() const {return m_vXaxis;}
  const OdGeVector3d& vYaxis() const {return m_vYaxis;}
  const OdGeVector3d& vZaxis() const {return m_vZaxis;}

private:

  OdGeVector3d m_vXaxis;
  OdGeVector3d m_vYaxis;
  OdGeVector3d m_vZaxis;

  void IncrementItemCount( int nItemStart, int nItemEnd,
    int nRowStart, int nRowEnd,
    int nLevelStart, int nLevelEnd );

  void DecrementItemCount( int nItemStart, int nItemEnd,
    int nRowStart, int nRowEnd,
    int nLevelStart, int nLevelEnd );
  
};


/** \details
  This class represents the custom implementation of an array of path parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayPathParameters : public OdTvDbImpAssocArrayCommonParameters
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayPathParameters(double itemSpacing = 200,
                                  double rowSpacing = 200,
                                  double levelSpacing = 200,
                                  int itemCount = 10,
                                  int rowCount = 1,
                                  int levelCount = 1,
                                  double rowElevation = 1);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayPathParameters();

  //virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  //virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  //virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  //virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** \details
    Returns the item count.
  */
  int itemCount(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the item spacing.
  */
  double itemSpacing(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the edge reference.
  */
  OdTvDbEdgeRef path() const;
  /** \details
    Returns the method identifier.
  */
  int method() const;
  /** \details
    Checks the alignment of items.
  */
  bool alignItems() const;
  /** \details
    Returns the start offset.
  */
  double startOffset(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the end offset.
  */
  double endOffset(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the path direction.
  */
  bool pathDirection() const;
  /** \details
    Sets the item count to a given value.
  */
  OdResult setItemCount( int nItems,
                         const OdString& expression, // = OdString::kEmpty
                         const OdString& evaluatorId, // = OdString::kEmpty
                         OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty)); // = NULL
  /** \details
    Sets the item spacing to a given value.
  */
  OdResult setItemSpacing( double offset,
                           const OdString& expression, // = OdString::kEmpty
                           const OdString& evaluatorId, // = OdString::kEmpty
                           OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty)); // = NULL
  /** \details
    Sets the edge path.
  */
  OdResult setPath(const OdTvDbEdgeRef& edgeRef);
  /** \details
    Sets the method.
  */
  OdResult setMethod(int method);
  /** \details
    Sets the alignment of items.
  */
  OdResult setAlignItems(bool bAlignItems);  
  /** \details
    Sets the start offset to a given value.
  */
  OdResult setStartOffset( double startOffset,
                           const OdString& expression = OdString::kEmpty,
                           const OdString& evaluatorId = OdString::kEmpty,
                           OdString* pErrorMessage = NULL);
  /** \details
    Sets the end offset to a given value.
  */
  OdResult setEndOffset( double startOffset,
                         const OdString& expression = OdString::kEmpty,
                         const OdString& evaluatorId = OdString::kEmpty,
                         OdString* pErrorMessage = NULL);
  /** \details
    Sets the edge direction.
  */
  OdResult setPathDirection(bool bAlongParams);
  /** \details
    Gets an array of items.
  */
  virtual OdResult getItems(OdArray<OdTvDbAssocArrayItemPtr>& items);

  virtual OdGeMatrix3d CalculateDefaultMatrix( const OdTvDbItemLocator &locator );

protected:
  
  /*!DOM*/
  friend class OdTvDbAssocArrayPathParameters;

private:

  OdTvDbEdgeRef m_rowProfile;
  int m_Mhetod;
  bool m_AlignItems;
  double m_AlignParam;
  double m_startOffset;
  double m_endOffset;
  bool m_pathDirection;
  bool m_maintainZ;
  int m_Orientation;
  double m_TangentOrientationAngle;

  OdGeVector3d tangentAtStartPoint;
  OdGeVector3d perpAtStartPoint;
  OdGeInterval intervalCurve;

};


/** \details
  This class represents the custom implementation of an array of polar parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayPolarParameters : public OdTvDbImpAssocArrayCommonParameters
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */
  OdTvDbImpAssocArrayPolarParameters(double angle = OdaToRadian(60), 
                                   double rowSpacing = 200, 
                                   double levelSpacing = 200,
                                   int itemCount = 6,
                                   int rowCount = 1, 
                                   int levelCount = 1,
                                   double rowElevation = 1);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayPolarParameters();

  //virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  //virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  //virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  //virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;

  /** \details
    Returns the item count.
  */
  int itemCount(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the angle between items.
  */
  double angleBetweenItems(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Fills all items to the angle.
  */
  double fillAngle(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the start angle.
  */
  double startAngle(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the radius.
  */
  double radius(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Checks the rotate of items.
  */
  bool rotateItems() const;
  /** \details
    Returns the direction.
  */
  int direction() const;
  /** \details
    Sets the item count to a given value.
  */
  OdResult setItemCount( int nItems, 
                         const OdString& expression, // = OdString::kEmpty
                         const OdString& evaluatorId, // = OdString::kEmpty
                         OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty) ); // = NULL
  /** \details
    Sets the angle between items to a given value.
  */
  OdResult setAngleBetweenItems( double angle, 
                                 const OdString& expression, // = OdString::kEmpty
                                 const OdString& evaluatorId, // = OdString::kEmpty
                                 OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty) ); // = NULL
  /** \details
    Sets the fill angle for items to a given value.
  */
  OdResult setFillAngle( double fillAngle, 
                         const OdString& expression, // = OdString::kEmpty
                         const OdString& evaluatorId, // = OdString::kEmpty
                         OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty) ); // = NULL
  /** \details
    Sets the start angle to a given value.
  */
  OdResult setStartAngle( double angle, 
                          const OdString& expression, // = OdString::kEmpty
                          const OdString& evaluatorId, // = OdString::kEmpty
                          OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty)); // = NULL
  /** \details
    Sets the radius to a given value.
  */
  OdResult setRadius( double radius, 
                      const OdString& expression, // = OdString::kEmpty
                      const OdString& evaluatorId, // = OdString::kEmpty
                      OdString& pErrorMessage = const_cast<OdString&>(OdString::kEmpty) ); // = NULL
  /** \details
    Switches the rotate of items.
  */
  OdResult setRotateItems(bool bRotateItems);
  /** \details
    Switches the direction between clockwise and counterclockwise.
  */
  OdResult setDirection(int direction);
  /** \details
    Gets an array of items.
  */
  virtual OdResult getItems(OdArray<OdTvDbAssocArrayItemPtr>& items);

  virtual OdGeMatrix3d CalculateDefaultMatrix( const OdTvDbItemLocator &locator );

protected:

  /*!DOM*/
  friend class OdTvDbAssocArrayPolarParameters;

private:

  double m_startAngle;
  double m_fillAngle;
  double m_radius;
  bool m_RotateItem;
  bool m_Direction;
};


/** \details
  This class represents the custom implementation of an array of rectangular parameters.

  Library: Source code provided.
  <group Contraint_Classes> 
*/
class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayRectangularParameters : public OdTvDbImpAssocArrayCommonParameters
{
public: 
  /** \details
    Constructor creates an instance of this class.
  */

  OdTvDbImpAssocArrayRectangularParameters(double columnSpacing = 200,
                                         double rowSpacing = 200,
                                         double levelSpacing = 200,
                                         int columnCount = 4,
                                         int rowCount = 3,
                                         int levelCount = 1,
                                         double rowElevation = 200,
                                         double axesAngle = OdaPI2);

  /** \details
    Destructor destroys an instance of this class.
  */
  virtual ~OdTvDbImpAssocArrayRectangularParameters();

  //virtual OdResult dwgInFields(OdTvDbDwgFiler* pFiler);
  //virtual void dwgOutFields(OdTvDbDwgFiler* pFiler) const;
  //virtual OdResult dxfInFields(OdTvDbDxfFiler* pFiler);
  //virtual void dxfOutFields(OdTvDbDxfFiler* pFiler) const;
protected:
  /** \details
    Returns the column count.
  */
  int ColumnCount(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the column spacing.
  */
  double ColumnSpacing( OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the axes angle.
  */
  double AxesAngle(OdString& expression, OdString& evaluatorId) const;
  /** \details
    Returns the axis direction.
  */
  OdGeVector3d axisDirection(OdGeVector3d* pYAxis = NULL) const;
  /** \details
    Sets the alignment of items.
  */
  OdResult setAlignItems(bool align,
                         const OdString& expression, // = OdString::kEmpty
                         const OdString& evaluatorId, // = OdString::kEmpty
                         OdString& pErrorMessage); // = NULL  
  /** \details
    Sets the column count to a given value.
  */
  OdResult setColumnCount(int nColumns, 
                          const OdString& expression, // = OdString::kEmpty
                          const OdString& evaluatorId, // = OdString::kEmpty
                          OdString& pErrorMessage); // = NULL
  /** \details
    Sets the column spacing to a given value.
  */
  OdResult setColumnSpacing(double offset, 
                            const OdString& expression, // = OdString::kEmpty
                            const OdString& evaluatorId, // = OdString::kEmpty
                            OdString& pErrorMessage); // = NULL
  /** \details
    Sets the axes angle to a given value.
  */
  OdResult setAxesAngle(double axesAngle, 
                        const OdString& expression, // = OdString::kEmpty
                        const OdString& evaluatorId, // = OdString::kEmpty
                        OdString& pErrorMessage); // = NULL  
  /** \details
    Sets the axis direction to a given value.
  */
  OdResult setAxisDirection(const OdGeVector3d& xAxis);
  /** \details
    Gets an array of items.
  */
  virtual OdResult getItems( OdArray<OdTvDbAssocArrayItemPtr>& items ) ;

  OdGeMatrix3d CalculateDefaultMatrix( const OdTvDbItemLocator &locator );

  /*!DOM*/
  friend class OdTvDbAssocArrayRectangularParameters;

private:

  double m_axesAngle;
  OdGeVector3d m_vRowProfile;
};

class DBCONSTRAINTS_EXPORT OdTvDbImpAssocArrayModifyParameters : public OdTvDbImpAssocArrayParameters
{
public:
  /** \details
    Constructor creates an instance of this class.
    */
  OdTvDbImpAssocArrayModifyParameters()
  {}

  /** \details
    Destructor destroys an instance of this class.
    */
  virtual ~OdTvDbImpAssocArrayModifyParameters();

  /** \details
    Gets an array of items.
  */
  virtual OdResult getItems( OdArray<OdTvDbAssocArrayItemPtr>& items );


protected:

  virtual OdGeMatrix3d CalculateDefaultMatrix( const OdTvDbItemLocator &locator )
  {
    return OdGeMatrix3d();
  }

  virtual OdResult GetItemByLocator(const OdTvDbItemLocator &locator, OdTvDbAssocArrayItemPtr &pItem) const;


};

#include "TD_PackPop.h"

#endif
