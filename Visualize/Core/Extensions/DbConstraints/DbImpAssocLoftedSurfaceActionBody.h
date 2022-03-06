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
#ifndef DbImpAssocLoftedSurfaceActionBody_INCLUDED_
#define DbImpAssocLoftedSurfaceActionBody_INCLUDED_ /*!DOM*/

#include "DbImpAssocExtrudedSurfaceActionBody.h"
#include "TD_PackPush.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** \details
This class represents the custom implementation of the action body based on AnnotationActionBody.

Library: Source code provided.
<group Contraint_Classes>
*/

class DBCONSTRAINTS_EXPORT OdTvDbImpAssocLoftedSurfaceActionBody : public OdTvDbImpAssocExtrudedSurfaceActionBody// OdTvDbImpAssocAnnotationActionBody
{
public:
  OdTvDbImpAssocLoftedSurfaceActionBody();
  ~OdTvDbImpAssocLoftedSurfaceActionBody();
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
  Returns a pointer to the array of parameters for writing.
  */
	OdTvDbAssocLoftParametersPtr parameters() const;
  OdTvDbAssocLoftParametersPtr& parameters();
  ////////////////////////////////////////////////////////////////////// for parent classes
  /** \details
  This is the notification call of the corresponding evaluate() method
  of the parent class that owns this action body.
  */
  virtual void evaluateOverride(OdTvDbObjectId parentActionId);

  /// <summary>
  /// <para> Get continuity of a specific of the resulting surface </para>
  /// <para>
  OdResult getContinuity(OdTvDbImpAssocLoftParameters::ProfileType type, int &continuity, OdTvDbAssocActionPtr pAction, OdString& expression  /*= OdString()*/,
    OdString& evaluatorId /*= OdString()*/) const;

  /// <summary>
  /// <para> Set continuity of a specific of the resulting surface </para>
  /// <para>
  OdResult setContinuity(OdTvDbImpAssocLoftParameters::ProfileType type, int continuity, OdTvDbAssocActionPtr pAction, const OdString& expression /* = OdString()*/,
    const OdString& evaluatorId /*= OdString()*/);

  /// <summary>
  /// <para> Get bulge factor of a specific of the resulting surface </para>
  /// <para>
  OdResult getBulge(OdTvDbImpAssocLoftParameters::ProfileType type, double &bulge, OdTvDbAssocActionPtr pAction, OdString& expression /*= OdString()*/,
    OdString& evaluatorId /*= OdString()*/) const;

  /// <summary>
  /// <para> Set bulge of a specific of the resulting surface </para>
  /// <para>
  OdResult setBulge(OdTvDbImpAssocLoftParameters::ProfileType type, double bulge, OdTvDbAssocActionPtr pAction, const OdString& expression/* = OdString()*/,
    const OdString& evaluatorId /*= OdString()*/);

  /// <summary> 
  /// Create an instance of OdTvDbAssocLoftedSurfaceActionBody
  /// </summary>
  static OdResult createInstance(
		const OdTvDbFullSubentPathArray crossSectionsArray,
		const OdTvDbFullSubentPathArray guideCurves,// TODO
		const OdTvDbFullSubentPath pathCurve,				// TODO
		const OdTvDbLoftOptions& loftOptions,				// TODO
		//const OdArray<int>& continuityArray,
		//const OdArray<double>& bulgeArray,
		//bool bEnabled,
	  OdTvDbObjectId& actionBodyId);

  virtual OdStringArray compareWith(OdTvDbImpAssocActionBody *paramIDToCompare, OdDb::DwgVersion filerVersion = OdDb::kDHL_CURRENT) const;

protected:
  OdTvDbAssocLoftParametersPtr m_pParams;
  short m_continuity;
  double m_bulge;
private:
  OdUInt32 m_unknownInt32;
};

#include "TD_PackPop.h"

#endif
