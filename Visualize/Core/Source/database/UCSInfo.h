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

#ifndef _ODUCSINFO_INCLUDED_
#define _ODUCSINFO_INCLUDED_

#include "DbObjectId.h"
#include "ViewportDefs.h"

#include "Ge/GePoint3d.h"
#include "DbAudit.h"

class OdUCSInfo
{
public:
  OdGePoint3d            m_UcsOrigin;
  OdGeVector3d           m_UcsXAxisDir;
  OdGeVector3d           m_UcsYAxisDir;
  OdDb::OrthographicView m_UcsOrthoViewType;
  double                 m_dUcsElevation;
  OdTvDbHardPointerId      m_BaseUcsId;
  OdTvDbHardPointerId      m_NamedUcsId;

public:
  OdUCSInfo() : m_UcsXAxisDir(OdGeVector3d::kXAxis), 
    m_UcsYAxisDir(OdGeVector3d::kYAxis), m_UcsOrthoViewType(OdDb::kNonOrthoView), m_dUcsElevation(0.0)
  {}

  OdGePoint3d& ucsOrigin() { return m_UcsOrigin; }
  const OdGePoint3d& getUcsOrigin() const { return m_UcsOrigin; }
  void setUcsOrigin(const OdGePoint3d& value) { m_UcsOrigin = value; }

  OdGeVector3d& ucsXAxisDir() { return m_UcsXAxisDir; }
  const OdGeVector3d& getUcsXAxisDir() const { return m_UcsXAxisDir; }
  void setUcsXAxisDir(const OdGeVector3d& value) { m_UcsXAxisDir = value; }

  OdGeVector3d& ucsYAxisDir() { return m_UcsYAxisDir; }
  const OdGeVector3d& getUcsYAxisDir() const { return m_UcsYAxisDir; }
  void setUcsYAxisDir(const OdGeVector3d& value) { m_UcsYAxisDir = value; }

  OdDb::OrthographicView getUcsOrthoViewType() const { return m_UcsOrthoViewType; }
  void setUcsOrthoViewType(OdDb::OrthographicView value) { m_UcsOrthoViewType = value; }

  double getUcsElevation() const { return m_dUcsElevation; }
  void setUcsElevation(double value = 0.0) { m_dUcsElevation = value; }

  OdTvDbHardPointerId& baseUcsId() { return m_BaseUcsId; }
  const OdTvDbHardPointerId& getBaseUcsId() const { return m_BaseUcsId; }
  void setBaseUcsId(const OdTvDbHardPointerId& value) { m_BaseUcsId = value; }

  void setNamedUcsId(const OdTvDbHardPointerId& value) { m_NamedUcsId = value; }
  OdTvDbHardPointerId& namedUcsId() { return m_NamedUcsId; }
  const OdTvDbHardPointerId& getNamedUcsId() const { return m_NamedUcsId; }

  bool auditAxes(OdTvDbAuditInfo* pAuditInfo, OdTvDbObject* pObj)
  {
    bool bFixErrors = (pAuditInfo == NULL) || pAuditInfo->fixErrors();
    bool bXInvalid = false;
    bool bYInvalid = false;
    double dXLength = m_UcsXAxisDir.length();
    double dYLength = m_UcsYAxisDir.length();
    if (OdZero(dXLength) || OdZero(dYLength))
    {
      bXInvalid = true;
      bYInvalid = true;
      if (bFixErrors)
      {
        m_UcsXAxisDir = OdGeVector3d::kXAxis;
        m_UcsYAxisDir = OdGeVector3d::kYAxis;
      }
    }
    else
    {
      if (!OdEqual(dXLength, 1.))
      {
        bXInvalid = true;
        if (bFixErrors)
        {
          m_UcsXAxisDir /= dXLength;
        }
      }
      if (!OdEqual(dYLength, 1.))
      {
        bYInvalid = true;
        if (bFixErrors)
        {
          m_UcsYAxisDir /= dXLength;
        }
      }
    }

    bool bPerp = m_UcsXAxisDir.isPerpendicularTo(m_UcsYAxisDir);

    if (bFixErrors && !bPerp)
    {
      const OdGeVector3d ucsZAxis = m_UcsXAxisDir.crossProduct(m_UcsYAxisDir);
      m_UcsYAxisDir = ucsZAxis.crossProduct(m_UcsXAxisDir);
      dYLength = m_UcsYAxisDir.length();
      if (!OdZero(dYLength))
        m_UcsYAxisDir /= dYLength;
      else
        m_UcsYAxisDir = m_UcsXAxisDir.perpVector();
    }

    if (bXInvalid || bYInvalid || !bPerp)
    {
      if (pObj)
      { //Report errors
        OdTvDbHostAppServices* pHostApp = pObj->database()->appServices();
  	    OdString sName = odTvDbGetObjectName(pObj).c_str();
        if (bXInvalid)
        {
          if (pAuditInfo)
          {
            pAuditInfo->printError(sName,
                pHostApp->formatMessage(sidVpUCSInvalidXAxis),
                pHostApp->formatMessage(sidVarValidInvalid),
                pHostApp->formatMessage(sidNormalized));
            pAuditInfo->errorsFound(1);
            if (bFixErrors)
              pAuditInfo->errorsFixed(1);
          }
          else
          {
            OdString strMess(sName);
            strMess += OD_T(": ");
            strMess += pHostApp->formatMessage(sidVpUCSInvalidXAxis);
            pHostApp->warning(strMess);
          }
        }
        if (bYInvalid)
        {
          if (pAuditInfo)
          {
            pAuditInfo->printError(sName,
                pHostApp->formatMessage(sidVpUCSInvalidYAxis),
                pHostApp->formatMessage(sidVarValidInvalid),
                pHostApp->formatMessage(sidNormalized));
            pAuditInfo->errorsFound(1);
            if (bFixErrors)
              pAuditInfo->errorsFixed(1);
          }
          else
          {
            OdString strMess(sName);
            strMess += OD_T(": ");
            strMess += pHostApp->formatMessage(sidVpUCSInvalidYAxis);
            pHostApp->warning(strMess);
          }
        }
        if (!bPerp)
        {
          if (pAuditInfo)
          {
            pAuditInfo->printError(sName,
                pHostApp->formatMessage(sidVpUCSNonPerpendicular),
                pHostApp->formatMessage(sidVarValidInvalid),
                pHostApp->formatMessage(sidVarDefRepair));
            pAuditInfo->errorsFound(1);
            if (bFixErrors)
              pAuditInfo->errorsFixed(1);
          }
          else
          {
            OdString strMess(sName);
            strMess += OD_T(": ");
            strMess += pHostApp->formatMessage(sidVpUCSNonPerpendicular);
            pHostApp->warning(strMess);
          }
        }
      }
      return false;
    }
    return true;
  }

};


#endif // _ODUCSINFO_INCLUDED_
