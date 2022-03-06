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

#ifndef _ODTV_COLLIDEDRESULT_H_INCLUDED_
#define _ODTV_COLLIDEDRESULT_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"
#include "TvEntity.h"
#include "TvSelection.h"

class OdTvCollidedResult;

/** \details
  A data type that represents a smart pointer to an <link OdTvCollidedResult, OdTvCollidedResult> object.
*/
typedef OdTvSmartPtr<OdTvCollidedResult> OdTvCollidedResultPtr;

/** \details
  The abstract interface class for managing a set of collided Visualize SDK objects.
  \sa
  <link tv_working_with_features_collision_detection, Work with Collision Detection>
*/
class ODTV_EXPORT OdTvCollidedResult : public OdTvIObject
{
public:

  /** \details
    Creates a new collided objects set with specified selection level.
    
    \param level [in] An <link OdTvSelectionOptions__Level, OdTvSelectionOptions::Level> enum that contains selection level.
    \returns Returns a smart pointer to the created collided objects set.
  */
  static OdTvCollidedResultPtr createObject(const OdTvSelectionOptions::Level level);

  /** \details
    Retrieves the iterator for getting access to items that are contained in the collided result object.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a smart pointer to the <link OdTvSelectionSetIteratorPtr, iterator> object.
    \remarks
    If the rc parameter is not null and the iterator object was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvSelectionSetIteratorPtr getIterator(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the quantity of items that are contained in the collided result.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns the number of items from collided result.
    \remarks
    If the rc parameter is not null and the quantity of selected items was successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdUInt32 numItems(OdTvResult* rc = NULL) const = 0;

  /** \details
    Retrieves the current selection level for the collided result.
    
    \param rc [out] A pointer to a value of <link OdTvResult, OdTvResult> type that contains the result of the retrieve operation.
    \returns Returns a value from the <link OdTvSelectionOptions__Level, OdTvSelectionOptions::Level> enum that represents the current selection level.
    \remarks
    If the rc parameter is not null and the current selection level were successfully returned, the rc parameter accepts the tvOk value; otherwise it contains an appropriate error code.
  */
  virtual OdTvSelectionOptions::Level getLevel(OdTvResult* rc = NULL) const = 0;

  /** \details
    Removes the entity item from the collided result (all subentity paths for this entity also will be removed).
    
    \param id     [in] An identifier of the removed entity.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the entity item was successfully removed from the collided result, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeEntity(const OdTvEntityId& id) = 0;

  /** \details
    Removes the sub-entity item (a sub-entity, geometry or sub-geometry entity) with a specified full path from the collided result.
    
    \param id           [in] An identifier of the removed entity.
    \param subItemPath  [in] A sub-item path object.
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the sub-entity item was successfully removed from the selection set, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult removeSubEntity(const OdTvEntityId& id, const OdTvSubItemPath& subItemPath) = 0;

  /** \details
    Removes all members from this collided result.
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the collided result was successfully cleared, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult clear() = 0;

  /** \details
    Append all members from incoming collided result to this collided results (results should have the same level - see getLevel method)
    
    \returns Returns a value of <link OdTvResult, OdTvResult> type that contains the result of the operation.
    \remarks
    If the collided result were successfully appended, the method returns the tvOk value; otherwise it returns an appropriate error code.
  */
  virtual OdTvResult append(const OdTvCollidedResultPtr& results) = 0;

};

/** \details
  This class represents collided pairs.
*/
class ODTV_EXPORT OdTvCollidedPair
{
public:
  /** \details
    Constructs the instance of OdTvCollidedPair.
  */
  OdTvCollidedPair();
  /** \details
    Initializes the instance of OdTvCollidedPair.
    
    \param first    [in] First collided element.
    \param second   [in] Second collided element.
    \param distance [in] Collision distance.
  */
  void initialize( const OdTvSubItemPath& first, const OdTvSubItemPath& second, double distance = 0.0 );
  
  /** \details
    Provides access to the first collided element.
    
    \returns Returns OdTvSubItemPath that refers to the first collided element.
  */
  const OdTvSubItemPath& first() const;
  
  /** \details
    Provides access to the second collided element.
    
    \returns Returns OdTvSubItemPath that refers to the second collided element.
  */
  const OdTvSubItemPath& second() const;
  
  /** \details
    Provides access to the collision distance.
    
    \returns Returns the collision distance.
    \remarks Negative values represent penetration depth, zero value means touching, positive value represents distance between non-collided elements.
  */
  double distance() const;
//DOM-IGNORE-BEGIN
protected:
  OdTvSubItemPath m_first;
  OdTvSubItemPath m_second;
  double m_distance;
//DOM-IGNORE-END
};

/** \details
  A data type that represents an array of <link OdTvCollidedPair, OdTvCollidedPair> objects.
*/
typedef OdArray<OdTvCollidedPair> OdTvCollidedPairResult;

/** \details
  This class represents collision detection options.
*/
class ODTV_EXPORT OdTvCollisionOptions
{
public:
  /** \details
    Collision detection type.
  */
  enum CollisionDetectionType
  {
    kIntersection = 0, //Detects intersection and touching
    kClearance = 1     //Detects intersection, touching and "too close" objects.
  };
public:
  
  /** \details
    Default constructor for the OdTvCollisionOptions class. Constructs a set of options with collision type set to kIntersection,
    collision level is OdTvSelectionOptions::kEntity and zero tolerance. Also, by default collision distance is not calculated.
  */
  OdTvCollisionOptions();
  
  /** \details
    Retrieves the collision detection type.
    
    \returns
    A value from the CollisionDetectionType enumeration representing requested collision detection type.
  */
  CollisionDetectionType type() const;
  
  /** \details
    Specifies collision detection type.
    
    \param t [in] Collision detection type.
  */
  void setType( CollisionDetectionType t );
  
  /** \details
    Retrieves the collision detection level.
    
    \returns
    A value from the OdTvSelectionOptions::Level enumeration representing requested collision detection level.
  */
  OdTvSelectionOptions::Level level() const;
  
  /** \details
    Specifies collision detection level.
    
    \param l [in] Collision detection level.
  */
  void setLevel( OdTvSelectionOptions::Level l );
  
  /** \details
    Retrieves the collision detection tolerance.
    
    \returns a tolerance value that depends on collision detection type.
    For kIntersections, zero tolerance means intersections and touching. Non-zero tolerance means intersections only with the specified tolerance.
    For kClearance, zero tolerance means intersections and touching. Non-zero tolerance means intersections, touching and elements that are too close to each other.
  */
  double tolerance() const;
  
  /** \details
    Specifies collision detection tolerance.
    
    \param tol [in] Collision detection tolerance.
    \remarks Meaning of tolerance depends on collision detection type.
    For kIntersections, zero tolerance means intersections and touching. Non-zero tolerance means intersections only with specified tolerance.
    For kClearance, zero tolerance means intersections and touching. Non-zero tolerance means intersections, touching and elements that are too close to each other.
  */
  void setTolerance( double tol );
  
  /** \details
    Checks whether collision detection calculates collision distance.
    
    \returns Returns flag that indicates whether collision detection calculates collision distance.
  */
  bool calculateDistance() const;
  
  /** \details
    Specifies whether collision detection should calculate collision distance.
    
    \param bCalc [in] The flag that indicates that collision detection should calculate collision distance.
    \remarks If this option is FALSE, collision detection for two elements will be stopped after detecting the first intersection.
    If this option is TRUE, collision detection for two elements will check all possible intersections to calculate the most appropriate collision distance.
  */
  void setCalculateDistance( bool bCalc );
  /** \details
    Checks whether collision detection ignores view extents.
    \returns Returns flag that indicates whether collision detection ignores view extents.
    \remarks Some collision detection variants (like "All with all") process only visible (inside view extents) objects. This option
    allow to process all objects independent of view extents.
  */
  bool ignoreViewExtents() const;
  /** \details
    Specifies whether collision detection should ignores view extents.
    \param bIgnore [in] The flag that indicates that collision detection should ignores view extents.
    \remarks Some collision detection variants (like "All with all") process only visible (inside view extents) objects. This option
    allow to process all objects independent of view extents.
  */
  void setIgnoreViewExtents( bool bIgnore );
//DOM-IGNORE-BEGIN
protected:
  CollisionDetectionType m_type;
  OdTvSelectionOptions::Level m_level;
  double m_tolerance;
  bool m_bCalcDistance;
  bool m_bIgnoreViewExtents;
//DOM-IGNORE-END
};



#endif // _ODTV_COLLIDEDRESULT_H_INCLUDED_
