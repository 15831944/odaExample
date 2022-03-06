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

#ifndef _IFC_MODELERGEOMETRY_H_
#define _IFC_MODELERGEOMETRY_H_

#include "Ge/GeVector3d.h"
#include "Ge/GeCurve3d.h"

#include "IfcCommon.h"
#include "IfcDeviationParams.h"
#include "IfcBodyVariant.h"

#include "IfcBuildOptions.h"
#include "IfcSimpleTypes.h"

class OdIBrFile;

/** \details
  Provides a set of classes and enumerations for working with OdIfc objects.
*/
namespace OdIfc {
  class OdIfcVisualData;

  /** \details
    Defines supported boolean operations.
  */
  enum IfcBooleanOperator
  {
    /** \details
      Union operator.
    */
    kIfcBooleanOperator_UNION, 
    /** \details
      Intersection operator.
    */
    kIfcBooleanOperator_INTERSECTION,
    /** \details
      Difference operator.
    */
    kIfcBooleanOperator_DIFFERENCE
  };

  /** \details
    Defines which operands of a boolean operation should stay unchanged.
  */
  enum IfcModelerKeep
  {
    /** \details
      All operands will be destroyed.
    */
    kNeither,
    /** \details
      The first operand will stay unchanged.
    */
    kTool,
    /** \details
      The second operand will stay unchanged.
    */
    kBlank,
    /** \details
      All operands will stay unchanged.
    */
    kBoth
  };

  //DOM-IGNORE-BEGIN
  class OdIfcHalfSpaceSolid;
  typedef OdSmartPtr<OdIfcHalfSpaceSolid> OdIfcHalfSpaceSolidPtr;

  class OdIfcConnectedFaceSet;
  typedef OdSmartPtr<OdIfcConnectedFaceSet> OdIfcConnectedFaceSetPtr;

  class OdIfcAdvancedBrep;
  typedef OdSmartPtr<OdIfcAdvancedBrep> OdIfcAdvancedBrepPtr;

  class OdIfcModelerGeometry;
  typedef OdSmartPtr<OdIfcModelerGeometry> OdIfcModelerGeometryPtr;

  class OdIfcSweptDiskSolid;
  typedef OdSmartPtr<OdIfcSweptDiskSolid> OdIfcSweptDiskSolidPtr;

  class OdIfcProfileDef;
  typedef OdSmartPtr<OdIfcProfileDef> OdIfcProfileDefPtr;

  class OdIfcSectionedSolid;
  typedef OdSmartPtr<OdIfcSectionedSolid> OdIfcSectionedSolidPtr;

  class OdIfcFixedReferenceSweptAreaSolid;
  typedef OdSmartPtr<OdIfcFixedReferenceSweptAreaSolid> OdIfcFixedReferenceSweptAreaSolidPtr;

  class OdIfcAxisLateralInclination;
  typedef OdSmartPtr<OdIfcAxisLateralInclination> OdIfcAxisLateralInclinationPtr;

  class OdIfcAlignmentCant;
  typedef OdSmartPtr<OdIfcAlignmentCant> OdIfcAlignmentCantPtr;
  //DOM-IGNORE-END

  /** \details 
    The class provides geometry modeler functionality for IFC SDK.
    It keeps a body for the visualization and other operations in the format of appropriate modeler implementation.
  */
  class IFCGEOM_EXPORT OdIfcModelerGeometry : public OdRxObject
  {
  protected:

    //DOM-IGNORE-BEGIN
    void copyFrom(const OdRxObject*) = 0;
    //DOM-IGNORE-END

  public:
    //DOM-IGNORE-BEGIN
    ODRX_DECLARE_MEMBERS(OdIfcModelerGeometry);
    //DOM-IGNORE-END

    /** \details
      Draws the body to the <exref target="https://docs.opendesign.com/tv/OdGiWorldDraw.html">OdGiWorldDraw interface</exref>.

      \param pWd [in] A raw pointer to the object for the entity-level vectorization.
      
      \returns true if the body was successfully drawn; otherwise the method returns false.
    */
    virtual bool draw(OdGiWorldDraw* pWd) const = 0;
    
    /** \details
      Transforms the body within the geometry modeler.

      \param m [in] A transformation matrix object.
    */
    virtual void transform(const OdGeMatrix3d &m) = 0;
    
    /** \details
      Calculates the extents of the body within the geometry modeler.

      \param box [out] A placeholder for the body extents object.

      \returns
      Returns eOk if the bounding box was successfully returned; otherwise, the eNullExtents value is returned. 
      
      \remarks 
      If the bounding box was not successfully calculated, the output parameter, that contains the box object, is equal to the NULL value.
    */
    virtual OdResult getBoundingBox(OdGeExtents3d &box) const = 0;

    /** \details
      Copies the body from a specified geometry modeler instance.

      \param b [in] A smart-pointer to the source geometry modeler object.

      \returns
      Returns the copy result code: eOk if the body was successfully copied; eNullEntityPointer if the source is NULL; 
      eIllegalEntityType if the source object is not an instance of the OdIfcModelerGeometry class.
    */
    virtual OdResult copyBody(OdIfcModelerGeometryPtr b) = 0;
    
    /** \details
      Creates a half-space solid and stores it in the geometry modeler object.

      \param tool [in] A smart-pointer to the half-space solid object.

      \returns
      Returns the creation result code: 
      * eOk if the half-space solid was successfully created.
      * eNullEntityPointer if the tool has the illegal type.
      * eGeneralModelingFailure in other cases.
      \remarks 
      The method returns the eNullEntityPointer value when the geometry modeler body is equal to the NULL, or the surface 
      that defines the side of the half-space is equal to the NULL.      
    */
    virtual OdResult boolean(OdIfcHalfSpaceSolidPtr tool) = 0;

    /** \details
      Performs a specified boolean operation between the currently stored blank body and the tool. 
      The result of the operation is stored in the geometry modeler object instead of the currently stored body.

      \param tool [in] A tool operand represented with a smart-pointer to the geometry modeler object.
      \param op   [in] A type of the boolean operation to be performed.
      \param keep [in] An option value that determines which operands stay unchanged after the operation.

      \returns
      Returns the operation result code: 
      * eOk if the operation was performed successfully.
      * eIllegalEntityType if operands have illegal types.
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult boolean(OdIfcModelerGeometryPtr tool, IfcBooleanOperator op, IfcModelerKeep keep = kBoth) = 0;
    
    /** \details
      Performs a specified boolean operation between the currently stored body and the tool. 
      The result of the operation is stored in the specified geometry modeler object.

      \param tool   [in] A tool operand.
      \param blank  [in] A blank operand.
      \param op     [in] A type of the boolean operation to be performed.
      \param keep [in]  An option value that determines which operands stay unchanged after the operation.

      \returns
      Returns the operation result code: 
      * eOk if the operation was performed successfully.
      * eIllegalEntityType if operands have illegal types.
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult boolean(OdIfcModelerGeometryPtr tool, OdIfcModelerGeometryPtr blank, IfcBooleanOperator op, IfcModelerKeep keep = kBoth) = 0;
    
    /** \details
      Creates an extrusion body and stores it in the geometry modeler object.

      \param profile [in] A smart pointer to the base profile for the extrusion.
      \param dir     [in] A vector object that represents the length and the direction of the extrusion.

      \returns
      Returns the operation result code: 
      * eOk if the extrusion was performed successfully.
      * eNullEntityPointer if the smart pointer to the base profile is NULL.
      * eEmptySet if the base profile has no contours.
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult extrude(OdIfcProfileDefPtr profile, OdGeVector3d dir) = 0;
    
    /** \details
      Creates a revolution body and stores it in the geometry modeler object.

      \param profile          [in] A smart pointer to the base profile for the extrusion.
      \param axisOfRevolution [in] A vector object that represents the axis of the revolution that is used by the base profile for revolution body creation.
      \param axisPosition     [in] A point that defines the position of the revolution axis.
      \param startAng         [in] A starting angle value of the revolution.
      \param endAng           [in] An ending angle of the revolution.

      \returns
      Returns the operation result code: 
      * eOk if the revolution was created successfully.
      * eNullEntityPointer if the smart pointer to the base profile is NULL.
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult revolve(OdIfcProfileDefPtr profile, const OdGeVector3d& axisOfRevolution, const OdGePoint3d& axisPosition, double startAng, double endAng) = 0;
    
    /** \details
      Creates a solid constructed by sweeping potentially variable cross sections along a directrix.

      \param pSolid [in]  A smart pointer to the sectioned solid entity. 

      \returns
      Returns the operation result code: 
      * eOk if the revolution was created successfully.
      * eNullPtr if the smart pointer to the sectioned solid entity is NULL.
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult sweep(OdIfcSectionedSolidPtr pSolid) = 0;

    /** \details
      Creates a specialized IfcDirectrixDistanceSweptAreaSolid object. 
      The orientation of the profile's X-axis always follows the rule defined by the specified IfcAxisLateralInclination object.

      \param pProfile     [in]  A smart pointer to the base profile for the sweep.
      \param pPath        [in]  A smart pointer to a curve object that defines the main sweep path.
      \param pInclination [in]  A smart pointer to an object that represents the lateral inclination of the base profile based on the specified path.
      \param isFixedAxisVertical [in]  A flag that Indicates whether the profile is oriented with its Y-axis facing upwards in +Z direction (true), or vertically perpendicular to the sweep directrix varying according to the slope (false). 

      \returns
      * eOk if the method works successfully.
      * eNullEntityPointer if the pProfile or the OdGeCurvePtrs smart pointers are NULL
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult sweepWithInclination(OdIfcProfileDefPtr pProfile, OdGeCurve3dPtr pPath, OdIfcAxisLateralInclinationPtr pInclination, bool isFixedAxisVertical) = 0;
    
    /** \details
      Creates a specialized sweep with cants. The orientation of the profile's x-axis
      is always follows the rule defined by the IfcAlignment.

      \param pProfile [in] A smart pointer to the base profile for the sweep.
      \param pPath    [in] A smart pointer to a curve object that defines the main sweep path.
      \param pCant    [in] Defines the lateral inclination of the sweep profile based on the sweep path.

      \returns
      Returns result code, eOk if all right, eNullEntityPointer if pProfile or OdGeCurvePtrs are NULL,
      or eGeneralModelingFailure in other cases.
    */
    virtual OdResult sweepWithCant(OdIfcProfileDefPtr pProfile, OdGeCurve3dPtr pPath, OdIfcAlignmentCantPtr pInclination) = 0;
    
    /** \details
    Sweeps the body along a path and stores the result in the geometry modeler object.

     \param pSolid [in] A smart pointer to the swept disk solid entity.

     \returns
      Returns the operation result code: 
    * eOk if the swept body was created successfully.
    * eNullPtr if the smart pointer to the swept disk solid entity is NULL.
    * eGeneralModelingFailure in other cases.
   */
    virtual OdResult sweep(OdIfcSweptDiskSolidPtr pSolid) = 0;

    /** \details
     Creates a type of the swept area solid that is the result of the sweeping a specified area along a directrix. 
     The swept area is provided by a subtype of the OdIfcProfileDef class. 
     The profile is placed by an implicit cartesian transformation operator at the start point of the sweep, where the profile normal agrees 
     to the tangent of the directrix at this point, and the profile's x-axis agrees to the FixedReference direction. 
     The orientation of the curve during the sweeping operation is controlled by the FixedReference direction.

     \param pSolid [in] A smart pointer to the OdIfcFixedReferenceSweptAreaSolid entity.

     \returns
      Returns the operation result code: 
      * eOk if the sweep operation was successful.
      * eNullPtr if the smart pointer to the OdIfcFixedReferenceSweptAreaSolid entity is NULL.
      * eGeneralModelingFailure in other cases.
   */
    virtual OdResult sweep(OdIfcFixedReferenceSweptAreaSolidPtr pSolid) = 0;

    /** \details
      Creates a faceted body and stores it in the geometry modeler object.

      \param pFaceSet [in] A smart pointer to the set of faces for the body.

      \returns
      Returns the operation result code: 
      * eOk if the faceted body was successfully created.
      * eInvalidInput in other cases.
    */
    virtual OdResult createFacetedBrep(OdIfcConnectedFaceSetPtr pFaceSet) = 0;

    /** \details
      Creates a tessellated body and stores it in the geometry modeler object.

      \param vertices [in] An array of points that represents the ordered list of points used by the faces.
      \param faces    [in] A two-dimensional array that contains the list for the indexed-based faces.
      \param isClosed [in] A flag value that determines whether the tessellated body is a closed shell or not.
      \param normals  [in] An array of 3D vectors, which contain normals.
      \param pData    [in] A raw pointer to additional visual data (faces' colors and textures).
      \param flags    [in] Additional flags for each face indicating break lines between faces or designation as a hole or void.

      \returns
      Returns the operation result code: 
      * eOk if the tessellated body was successfully created.
      * eInvalidInput in other cases.
    */
    virtual OdResult createTessellation(const OdGePoint3dArray& vertices, const OdArray<OdArray<int> >& faces, OdDAI::Boolean isClosed, const OdGeVector3dArray& normals, const OdIfc::OdIfcVisualData* pData, const OdArray<IfcInteger>& flags = OdArray<IfcInteger>()) = 0;
    
    /** \details
      Creates a tessellated body and stores it in the geometry modeler object.

      \param vertices [in] An array of points that represents the ordered list of points used by the faces.
      \param faces    [in] A two-dimensional array that contains the list for the indexed-based faces.
      \param isClosed [in] A flag value that determines whether the tessellated body is a closed shell or not.
      \param pData    [in] A raw pointer to additional visual data (faces' colors and textures).

      \returns
      Returns result code, eOk if all right, eInvalidInput in other cases.
    */
    virtual OdResult createTessellation(const OdGePoint3dArray& vertices, const OdDAIObjectIds& faces, OdDAI::Boolean isClosed, const OdIfc::OdIfcVisualData* pData) = 0;

    /** \details
      Creates an OdBrFile object from the specified OdIfcAdvnacedBrep object and stores it into the geometry modeler object.

      \param pBrep [in] A smart pointer to the OdIfcAdvancedBrep entity.

      \returns
      Returns the operation result code: 
      * eOk if the operation was successful.
      * eWrongObjectType if getting the attribute is failed.
      * eNullObjectPointer if the specified OdIfcAdvancedBrep entity or its sub-entity has an unsupported type.
      * eEmptySet if the specified OdIfcAdvancedBrep entity or its sub-entity has empty set;
      * eGeneralModelingFailure in other cases.
    */
    virtual OdResult createAdvancedBrep(OdIfcAdvancedBrepPtr pBrep) = 0;
    
    /** \details
      Creates a box body in the geometry modeler object.

      \param ptOrigin [in] A point that defines the box position.
      \param vSizes   [in] The box sizes.

      \returns
      Returns the operation result code: eOk if the box was successfully created; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult box(const OdGePoint3d& ptOrigin, const OdGeVector3d& vSizes) = 0;

    /** \details
      Creates a block body in the geometry modeler object.

      \param ptOrigin [in] A point that defines the block position.
      \param xLength  [in] A length of the block along the X-axis.
      \param yLength  [in] A length of the block along the Y-axis.
      \param zLength  [in] A length of the block along the Z-axis.

      \returns
      Returns the operation result code: eOk if the block was successfully created; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult block(const OdGePoint3d& ptOrigin, double xLength, double yLength, double zLength) = 0;

    /** \details
      Creates a rectangular pyramid body in the geometry modeler object.

      \param ptOrigin [in] A point that defines the position of the pyramid.
      \param xLength  [in] A length of the pyramid along the X-axis.
      \param yLength  [in] A length of the pyramid along the Y-axis.
      \param height   [in]  A height of the pyramid.

      \returns
      Returns the operation result code: eOk if the pyramid was successfully created; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult rectangularPyramid(const OdGePoint3d& ptOrigin, double xLength, double yLength, double height) = 0;

    /** \details
      Creates a right circular cone body in the geometry modeler object.

      \param ptOrigin     [in] A point that defines the position of cone.
      \param height       [in] A height of the cone.
      \param bottomRadius [in] A radius of the cone.

      \returns
      Returns the operation result code: eOk if the cone was successfully created; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult rightCircularCone(const OdGePoint3d& ptOrigin, double height, double bottomRadius) = 0;

    /** \details
      Creates a right circular cylinder body in the geometry modeler object.

      \param ptOrigin [in] A point that defines the position of the cylinder.
      \param height   [in] A height of the cylinder.
      \param radius   [in] a radius of the cylinder.

      \returns
      Returns the operation result code: eOk if the cylinder was successfully created; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult rightCircularCylinder(const OdGePoint3d& ptOrigin, double height, double radius) = 0;

    /** \details
      Creates a sphere body in the geometry modeler object.

      \param ptOrigin [in] A point that defines the position of the sphere.
      \param radius   [in] A radius of the sphere.

      \returns
      Returns the operation result code: eOk if the sphere was successfully created; otherwise, the method returns an appropriate error code.
    */
    virtual OdResult sphere(const OdGePoint3d& ptOrigin, double radius) = 0;

    /** \details
      Assigns deviation params to the geometry modeler object.

      \param params [in]  A set of deviation parameters to be assigned.
    */
    virtual void setDeviationParams(const OdIfcDeviationParams& params) = 0;

    /** \details
      Retrieves the OdBrFile interface from the geometry modeler object.

      \returns Returns a raw pointer to the OdIBrFile interface.
    */
    virtual OdIBrFile* brep() const = 0;

    /** \details
      Retrieves the container with the body from the geometry modeler object.

      \returns Returns an OdIfcBodyVariant object that represents the body container. 
      \remarks 
      The value returned by the method is up to date only while the modeler is not changed.
    */
    virtual OdIfcBodyVariant bodyContainer() const = 0;
  };

}

#endif // _IFC_MODELERGEOMETRY_H_
