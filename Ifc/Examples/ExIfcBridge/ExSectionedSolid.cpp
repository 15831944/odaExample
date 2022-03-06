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

#include "ExSectionedSolid.h"
#include "ExIfcModelFiller.h"


ExSectionedSolid::ExSectionedSolid(OdDAIObjectId alignmentCurveId, const std::vector<ProfileData>& profilesCollection)
  : m_profilesCollection(profilesCollection)
  , m_alignmentCurveId(alignmentCurveId)
{
}

ExSectionedSolid::ExSectionedSolid(OdDAIObjectId alignmentCurveId,
                                   OdDAIObjectId profileId,
                                   OdDAIObjectId beginGirder,
                                   OdDAIObjectId endGirder)
  : m_alignmentCurveId(alignmentCurveId)
{
  m_profilesCollection.push_back({ profileId , beginGirder });
  m_profilesCollection.push_back({ profileId , endGirder });
}

OdIfc::OdIfcEntityPtr ExSectionedSolid::subProcess()
{
  //
  // Girder 3d representation
  //
  OdIfc::OdIfcEntityPtr grc = m_b->filler()->getGeometricRepresentationContext("Model");
  if (grc.isNull())
  {
    ODA_ASSERT("Not convenient graphic representation context found.");
    return OdIfc::OdIfcEntityPtr();
  }

  OdIfcModelPtr model = m_b->filler()->model();

  OdIfc::OdIfcEntityPtr pSR = model->createEntityInstance("ifcshaperepresentation");
  pSR->putAttr(OdIfc::kContextOfItems, OdDAIObjectId(grc->id()));

  OdIfc::OdIfcEntityPtr sectionedSolid = model->createEntityInstance("ifcsectionedsolidhorizontal");
  if (sectionedSolid.isNull())
  {
    ODA_ASSERT("Can not create ifcsectionedsolidhorizontal.");
    return OdIfc::OdIfcEntityPtr();
  }

  sectionedSolid->putAttr("directrix", m_alignmentCurveId);
  OdRxValue crossSectionsRxValue = sectionedSolid->getAttr("crosssections");

  OdDAI::OdDAIObjectIdList*  crossSectionIdList;
  if (crossSectionsRxValue >> crossSectionIdList == false)
  {
    ODA_ASSERT("Can not get crosssections from ifcsectionedsolidhorizontal.");
    return OdIfc::OdIfcEntityPtr();
  }

  if (!m_profilesCollection.empty())
  {
    crossSectionIdList->createEmpty();
  }

  int sectionIdIndex = 0;
  for (const auto& profileData : m_profilesCollection)
  {
    crossSectionIdList->addByIndex(sectionIdIndex, OdDAIObjectId(profileData.profileId));
    ++sectionIdIndex;
  }

  OdDAIObjectIds positions;
  for (const auto& profileData : m_profilesCollection)
  {
    OdIfc::OdIfcEntityPtr pAxis = model->createEntityInstance("ifcaxis2placementlinear");
    pAxis->putAttr("location", profileData.distanceAlong);
    positions.append(model->appendEntityInstance(pAxis));
  }
  sectionedSolid->putAttr("crosssectionpositions", positions);
  sectionedSolid->putAttr("fixedaxisvertical", true);
  m_b->filler()->appendId(pSR, OdIfc::kItems, model->appendEntityInstance(sectionedSolid));
  setStyledItem(sectionedSolid, "ConcreteLight");

  OdAnsiString strBody("Body");
  OdAnsiString strType("CSG");
  pSR->putAttr(OdIfc::kRepresentationIdentifier, strBody);
  pSR->putAttr(OdIfc::kRepresentationType, strType);
  model->appendEntityInstance(pSR);

  OdAnsiString strGirderSegment("girder_segment");
  m_b->getProduct()->putAttr("predefinedtype", strGirderSegment);

  return pSR;
}
