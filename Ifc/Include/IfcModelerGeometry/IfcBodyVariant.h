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

#ifndef _IFC_BODYVARIANT_H_
#define _IFC_BODYVARIANT_H_

#include "IfcBuildOptions.h"
#include "IfcCommon.h"

#include "Br/BrBrep.h"


namespace FacetModeler {
  class Body;
}
class OdMdBody;
class BODY;

/** \details 
Contains declarations related to working with IFC file content.
*/
namespace OdIfc
{
  /** \details
    Defines an interface to get a body from a representation item of an OdIfcProduct.

    \remarks
    Note that the OdIfcBodyVariant object does not own the body that it contains.
  */
  class IFCGEOM_EXPORT OdIfcBodyVariant
  {
  public:
    /** \details
      Enumerates referenced body types.
    */
    enum Type
    {
      /**No body is referenced.*/
      kEmpty, 
      /**A reference to a FacetModeler body.*/
      kFacetModelerBody, 
      /**A reference to an OdBrepModeler body.*/
      kMdBody, 
      /**A reference to a Spatial Acis body.*/
      kAcisBody, 
      /**A reference to an IfcBrepBuilder body.*/
      kIfcBrep, 
    };

    /** \details
      Creates a new instance of the OdIfcBodyVariant class that does not reference any body.
    */
    OdIfcBodyVariant();

    /** \details
      Checks if the body is a FacetModeler body.
      \returns true if the body is a FacetModeler body; otherwise the method returns false.
    */
    bool isFacetModelerBody() const { return kFacetModelerBody == m_type; }
    
    /** \details
      Sets a new FacetModeler body reference.
      \param pFacetModelerBody [in] A FacetModeler body object to be set.
    */
    void setFacetModelerBody(const FacetModeler::Body* pFacetModelerBody);
    
    /** \details
      Retrieves the referenced FacetModeler body.
      \returns A raw pointer to a FacetModeler::Body object that represents the referenced FacetModeler body.
    */
    const FacetModeler::Body* facetModelerBody() const;

    /** \details
      Checks if the body is an OdBrepModeler body.
      \returns true if the body is an OdBrepModeler body; otherwise the method returns false.
    */
    bool isMdBody() const { return kMdBody == m_type; }
    
    /** \details
      Sets a new OdBrepModeler body reference.
      \param pMdBody [in] A new OdBrepModeler body object to be set.
    */
    void setMdBody(const OdMdBody* pMdBody);
    
    /** \details
      Retrieves the current referenced OdBrepModeler body.
      \returns A raw pointer to an OdBrepModeler object that represents the current referenced OdBrepModeler body.
    */
    const OdMdBody* mdBody() const;

    /** \details
      Checks if the body is a Spatial Acis body.
      \returns true if the body is a Spatial Acis body; otherwise the method returns false.
    */
    bool isAcisBody() const { return kAcisBody == m_type; }
    
    /** \details
      Sets a new Spatial Acis body reference.
      \param pAcisBody [in] A Spatial Acis body object to be set.
    */
    void setAcisBody(const BODY* pAcisBody);
    
    /** \details
      Retrieves the current referenced Spatial Acis body.
      \returns A raw pointer to a Spatial Acis body object.
    */
    const BODY* acisBody() const;

    /** \details
      Checks if the body is an IfcBrepBuilder body.
      \returns true if the body is an IfcBrepBuilder body; otherwise the method returns false.
    */
    bool isIfcBrep() const { return kIfcBrep == m_type; }
    
    /** \details
      Sets a new IfcBrepBuilder body reference.
      \param ifcBrBrep [in] A nw IfcBrepBuilder body object to be set.
    */
    void setIfcBrep(const OdBrBrep& ifcBrBrep);
    
    /** \details
      Retrieves the current referenced IfcBrepBuilder body.
      \returns An IfcBrepBuilder object that represents the body.
    */
    OdBrBrep ifcBrep() const;

    /** \details
      Retrieves the type of the referenced body.
      \returns The referenced body type.
    */
    Type kind() const { return m_type; }

  //DOM-IGNORE-BEGIN
  private:
    union
    {
      const FacetModeler::Body* pFmBody;
      const OdMdBody* pMdBody;
      const BODY* pAcisBody;
    };
    OdBrBrep m_brep;
    Type m_type;
    //DOM-IGNORE-END
  };

}

#endif // _IFC_BODYVARIANT_H_
