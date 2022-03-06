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

#ifndef _PRCREFERENCESOFPRODUCTOCCURRENCE_INCLUDED_
#define _PRCREFERENCESOFPRODUCTOCCURRENCE_INCLUDED_ 
 

#include "PrcUniqueId.h"
#include "PrcObjectId.h"

class OdPrcFile;

/** \details 
<group PRC_Miscellaneous_Classes> 

Class implements functionality for operating with references of a product occurrence. 
*/
class PRC_TOOLKIT OdPrcReferencesOfProductOccurrence
{
private:
  OdPrcObjectIdArray m_son_occurrences; // Sons : Array of pointers to the son product occurrences.
  OdPrcObjectId      m_externalDataID;  // ExternalData : Pointer to the corresponding external product occurrence. Can be NULL. 
  OdPrcObjectId      m_prototypeID;     // ProductPrototype : Pointer to the corresponding product occurrence prototype. Can be NULL.
  OdPrcObjectId      m_partID;          // PartDefinition : Pointer to the corresponding part definition. Can be NULL.

public:
  //DOM-IGNORE-BEGIN
  PRC_DECLARE_CIO(OdPrcReferencesOfProductOccurrence)
  //DOM-IGNORE-END

  /** \details
  Returns the current array son product occurrence identifiers.
  The array of son product occurrence identifiers is returned as a reference to an OdPrcObjectIdArray object, therefore it can be used to set new identifiers or modify existing ones.
  */
  OdPrcObjectIdArray& getSonProductOccurrences();

  /** \details
  Returns the current array son product occurrence identifiers.
  */
  const OdPrcObjectIdArray& getSonProductOccurrences() const;

  /** \details
  Sets a new product occurrence prototype.

  \param prototypeID [in] An identifier of a new product occurrence prototype.
  */
  void setPrototype (const OdPrcObjectId &prototypeID);

  /** \details
  Returns the current product occurrence prototype identifier.
  */
  OdPrcObjectId getPrototypeID() const;

  /** \details
  Clears the product occurrence prototype.
  */
  void clearPrototype();

  /** \details
  Returns the current identifier of the product occurrence's external data.
  */
  OdPrcObjectId getExternalDataID() const;

  /** \details
  Sets the new product occurrence's external data.

  \param externalDataID [in] An identifier of new external data to be set.
  */
  void setExternalData (const OdPrcObjectId &externalDataID);

  /** \details
  Clears the product occurrence's external data.
  */
  void clearExternalData();

  /** \details
  Sets a new corresponding part definition.

  \param partID [in] An identifier of a new corresponding part definition to be set.
  */
  void setCorrespondingPartDefinition (const OdPrcObjectId &partID);

  /** \details
  Returns the current identifier of the corresponding part definition.
  */
  OdPrcObjectId getCorrespondingPartDefinition() const;

  /** \details
  Clears the part definition.
  */
  void clearPartDefinition();

  /** \details
  Checks if the product occurrence is in the same file structure as its prototype.

  \param uuid [in] A PRC unique identifier of the referencing product occurrence.
  
  \returns Returns true if the product occurrence is in the same file structure as the prototype or returns false if it is not. 
  */
  bool isPrototypeInTheSameFileStructure (const OdPrcUniqueId &uuid) const;

  /** \details
  Checks if the product occurrence is in the same file structure as its external data.

  \param uuid [in] A PRC unique identifier of the referencing product occurrence.
  
  \returns Returns true if the product occurrence is in the same file structure as external data or returns false if it is not. 
  */
  bool isExternalDataInTheSameFileStructure (const OdPrcUniqueId &uuid) const;
};

#endif // _PRCREFERENCESOFPRODUCTOCCURRENCE_INCLUDED_

