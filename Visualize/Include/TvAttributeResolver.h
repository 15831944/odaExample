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

#ifndef _ODTV_ATTRIBUTERESOLVER_H_INCLUDED_
#define _ODTV_ATTRIBUTERESOLVER_H_INCLUDED_

#include "Tv.h"
#include "TvIObject.h"

/** \details
  This is an interface class for an OdTvAttributeResolver object.
  
  \sa
  <exref target="tv_working_with_base_classes_entity.html#12">Copy Entity Data</exref>
*/ 
class ODTV_EXPORT OdTvAttributeResolver : public OdTvIObject
{
public:
  /** \details
    Enumerates conflict resolving methods.
    
    \remarks Conflicts occur when resolver tries to create object with name that already present in the destination database.
  */
  enum ConflictResolvingMethod
  {
    kMangle = 0,  //Generate new object with unique name
    kReuse = 1,   //Use destination object
    kReplace = 2  //Replace destination object by source object
  };
  /** \details
    Returns source database ID.
    
    \returns
    Identifier of a source database.
  */
  virtual OdTvDatabaseId sourceDatabase() const = 0;

  /** \details
    Returns destination database ID.
    
    \returns
    Identifier of a destination database.
  */
  virtual OdTvDatabaseId destinationDatabase() const = 0;

  /** \details
    Returns conflict resolving method.
    
    \returns
    A value from the ConflictResolvingMethod enumeration representing how conflicts are resolved.
  */
  virtual ConflictResolvingMethod resolvingMethod() const = 0;

  /** \details
    Specifies prefix for kMangle conflict resolving methods.
    
    \param str [in] Given prefix.
    \remarks kMangle conflict resolving method tries to generate new object with unique name. First, it tries [Prefix][OriginalName].
    Then, it tries [Prefix][OriginalName][_Attempt] mangleAttempts times.
  */
  virtual void setPrefix( const OdString& str ) = 0;

  /** \details
    Returns prefix for kMangle conflict resolving methods.
    
    \remarks kMangle conflict resolving method tries to generate new object with unique name. First, it tries [Prefix][OriginalName].
    Then, it tries [Prefix][OriginalName][_Attempt] mangleAttempts times.
    \returns String with a prefix that is used with kMangle conflict resolving method.
  */
  virtual OdString prefix() const = 0;

  /** \details
    Specifies number of attempts for kMangle conflict resolving methods.
    
    \param nAttempts [in] Attempts number.
    \remarks kMangle conflict resolving method tries to generate new object with unique name. First, it tries [Prefix][OriginalName].
    Then, it tries [Prefix][OriginalName][_Attempt] mangleAttempts times.
  */
  virtual void setMangleAttempts( OdUInt32 nAttempts ) = 0;

  /** \details
    Returns number of attempts for kMangle conflict resolving methods.
    
    \remarks kMangle conflict resolving method tries to generate new object with unique name. First, it tries [Prefix][OriginalName].
    Then, it tries [Prefix][OriginalName][_Attempt] mangleAttempts times.
    \returns Number of attempts for the kMangle conflict resolving method.
  */
  virtual OdUInt32 mangleAttempts() const = 0;

  /** \details
    Creates smart pointer to the OdTvAttributeResolver instance.
    
    \param sourceDb [in] ID of a source database.
    \param destDb   [in] ID of a destination database.
    \param method   [in] Conflict resolving method.
    \returns Returns the smart pointer to the OdTvAttributeResolver instance.
  */
  static OdTvSmartPtr<OdTvAttributeResolver> createObject( OdTvDatabaseId sourceDb, OdTvDatabaseId destDb, ConflictResolvingMethod method = kReuse );
};

/** \details
  A data type that represents a smart pointer to an <link OdTvAttributeResolver, OdTvAttributeResolver> object.
*/
typedef OdTvSmartPtr<OdTvAttributeResolver> OdTvAttributeResolverPtr;

#endif // _ODTV_ATTRIBUTERESOLVER_H_INCLUDED_

