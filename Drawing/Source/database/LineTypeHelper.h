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

#ifndef __LINETYPEHELPER_H_
#define __LINETYPEHELPER_H_

#include <math.h>
#include <stdlib.h>

#include "OdaCommon.h"
#include "DbLinetypeTable.h"
#include "DbLinetypeTableRecordImpl.h"
#include "DbTextStyleTable.h"
#include "OdUtilAds.h"
#include "OdDToStr.h"
#include "OdStringBuf.h"

class CStringCutter
{
  OdString m_Text;
  int m_pos;
public:
  CStringCutter(const OdChar* str)
    : m_Text(str)
    , m_pos(0)
  {
  }
  void Set(const OdChar* str)
  {
    m_Text = str;
    m_pos = 0;
  }
  bool GetNext(OdString &str)
  {
    int i = m_Text.find(',', m_pos);
    if (i == -1)
    {
      str = m_Text.mid(m_pos);
      m_pos = m_Text.getLength();
      return true;
    } 
    else
    {
      str = m_Text.mid(m_pos, i - m_pos);
      m_pos = i+1;
    }
    return false;
  }
  bool GetDescription(OdString &str)
  {
    // the description may contain comma's, so return the rest of the string without
    // any further looking for comma's.
    str = m_Text.mid(m_pos);
    m_pos = m_Text.getLength();
    return true;
  }
};

class CLineTypeBuilder
{
  OdString m_Name;
  OdString m_Description;
  OdString m_TextAt;
  OdDbObjectId m_IdAt;
  bool m_IsShapeFileAt;
  OdGeVector2d m_OffsetAt;
  bool m_IsUcsOrientedAt;
  bool m_IsUprightAt;
  double m_RotationAt;
  double m_ScaleAt;
  bool m_hasAt;
  OdString m_FileNameAt;
public:
  CLineTypeBuilder()
    : m_IsShapeFileAt(false)
    , m_IsUcsOrientedAt(false)
    , m_IsUprightAt(false)
    , m_RotationAt(0.)
    , m_ScaleAt(1.)
    , m_hasAt(false)
  {}
  bool isEqName(const OdString &pattern) const
  {
    return odutWcMatchNoCase(m_Name, pattern);
  }
  bool PrepareString(OdString &str) const
  {
    str.trimLeft();
    int i = str.find(OD_T(";;")); // delete comment
    if (i != -1)
      str = str.left(i);
    return str.isEmpty();
  }
  bool TryMeAsNameDescription(const OdString &str)
  {
    if (str[0] != '*')
      return false;

    CStringCutter cutter(str.c_str() + 1);
    if (!cutter.GetNext(m_Name))
    {
      cutter.GetDescription(m_Description);

      //description should be no longer than 47 characters long.
      m_Description = m_Description.left(47);
    }
    else
    {
      m_Description.empty();
    }

    return true;
  }

  bool TryMeAsInfoAndAdd2Table(const OdString &str, OdDbLinetypeTablePtr pTbl, OdDbTextStyleTablePtr pTStyleTbl, OdDb::DuplicateLinetypeLoading dlt)
  {
    OdString tmp;

    bool bCommaReplaced = false;

    OdString source = str;
    int pos = source.find(OD_T("[\""));
    while (pos != -1 && source[0] == 'A')
    {
      int pos2 = source.find(OD_T("\""), pos + 2);
      if (pos2 != -1)
      {
        tmp = source.mid(pos, pos2 - pos + 1);
        OdString tmp2 = tmp;
        tmp2.replace(L',', L'\01');
        source.replace(tmp, tmp2);
        bCommaReplaced = true;
      }
      pos = source.find(OD_T("[\""), pos2 + 1);
    }
    CStringCutter cutter(source);

    if (cutter.GetNext(tmp))
      return false;

    OdDbLinetypeTableRecordPtr pLTRec;
    pLTRec = OdDbLinetypeTableRecord::createObject();
    if (pLTRec.isNull())
      throw OdError(eNullObjectPointer);

    if (!tmp.iCompare(OD_T("A")))
    {
      pLTRec->setIsScaledToFit(false);
    }
    else if (!tmp.iCompare(OD_T("S")))
    {
      pLTRec->setIsScaledToFit(true);
    }
    else
    {
      return false;
    }

    pLTRec->setName(m_Name);
    pLTRec->setComments(m_Description);

    bool bFinish;
    int indx = -1;

    double PatternLen = 0;

    pLTRec->setNumDashes(12); // at most
    do
    {
      bFinish = cutter.GetNext(tmp);

      m_OffsetAt.set(0., 0.);
      m_IsUcsOrientedAt = false;
      m_IsUprightAt = false;
      m_RotationAt = 0.;
      m_ScaleAt = 1.;
      m_IsShapeFileAt = false;
      m_IdAt = 0;
      m_FileNameAt = m_TextAt = OD_T("");
      m_hasAt = false;

      if (tmp[0] == '[')
      {
        if (indx == -1)
          return false;

        m_hasAt = true;

        tmp.deleteChars(0);
        bool bEnd;
        if (tmp[0] == '\"') // text
        {
          tmp = tmp.mid(1, tmp.getLength()-2);
          if (bCommaReplaced)
            tmp.replace(L'\01', L',');
          m_TextAt = tmp;

          if (cutter.GetNext(tmp)) return false;

          OdDbObjectId id;
          bEnd = tmp[tmp.getLength()-1] == ']';
          if (bEnd)
          {
            tmp.deleteChars(tmp.getLength()-1);
          }
          m_IdAt = pTStyleTbl->getAt(tmp);
        }
        else // shape
        {
          m_TextAt = tmp;

          if (cutter.GetNext(tmp)) return false;

          OdDbObjectId id;
          bEnd = tmp[tmp.getLength()-1] == ']';
          if (bEnd)
          {
            tmp.deleteChars(tmp.getLength()-1);
          }

          m_FileNameAt = tmp;

          OdDbTextStyleTableRecordPtr pR;
          OdDbSymbolTableIteratorPtr pIt = pTStyleTbl->newIterator();
          while (!pIt->done())
          { 
            pR = pIt->getRecordId().safeOpenObject();
            if (!pR->fileName().iCompare(tmp))
            {
              m_IdAt = pIt->getRecordId();
              break;
            }
            pIt->step();
          }
          m_IsShapeFileAt = true;
        }

        if (!bEnd)
        {
          do
          {
            bFinish = cutter.GetNext(tmp);
            bEnd = tmp[tmp.getLength()-1] == ']';
            if (bEnd)
            {
              tmp.deleteChars(tmp.getLength()-1);
            }
            else if (bFinish)
              return false;

            if (tmp.getLength() < 3 || tmp[1] != '=')
              return false;

            double val = odStrToD(tmp.c_str() + 2);
            switch(tmp[0])
            {
              case 'A':
              case 'a':
                m_IsUcsOrientedAt = true;
                m_RotationAt = OdaToRadian(val);
              break;
              case 'R':
              case 'r':
                m_IsUcsOrientedAt = false;
                m_RotationAt = OdaToRadian(val);
              break;
              case 'U':
              case 'u':
                m_IsUprightAt = true;
                m_RotationAt = OdaToRadian(val);
              break;
              case 'S':
              case 's':
                m_ScaleAt = val;
              break;
              case 'X':
              case 'x':
                m_OffsetAt.x = val;
              break;
              case 'Y':
              case 'y':
                m_OffsetAt.y = val;
              break;
              default:
                return false;
            }
          } while(!bEnd);
        }
      }  
      else
      {
        indx++;
        if (indx >= pLTRec->numDashes())
        {
          OdDbLinetypeTableRecordImpl::resizeDashes(pLTRec, indx + 1);
        }
        double len = odStrToD(tmp);
        pLTRec->setDashLengthAt(indx, len);
        PatternLen += fabs(len);
      }

      if (m_hasAt)
      {
        m_hasAt = false;
        if (!m_IdAt)
        {
          if (!m_IsShapeFileAt)
            return false;
          OdDbTextStyleTableRecordPtr pR;
          pR = OdDbTextStyleTableRecord::createObject();
          pR->setFileName(m_FileNameAt);
          pR->setIsShapeFile(true);
          pR->setTextSize(0.);
          m_IdAt = pTStyleTbl->add(pR);
          if (!m_IdAt) 
            return false;
        }
        if (m_IsShapeFileAt)
        {
          OdUInt16 ShapeIndx = OdDbTextStyleTableRecordImpl::shapeIndexByName(m_IdAt, m_TextAt);
          if (!ShapeIndx)
            return false;
          pLTRec->setShapeNumberAt(indx, ShapeIndx);
        }  
        else
        {
          pLTRec->setTextAt(indx, m_TextAt);
        }

        pLTRec->setShapeStyleAt(indx, m_IdAt);
        pLTRec->setShapeOffsetAt(indx, m_OffsetAt);
        pLTRec->setShapeIsUcsOrientedAt(indx, m_IsUcsOrientedAt);
        pLTRec->setShapeIsUprightAt(indx, m_IsUprightAt);
        pLTRec->setShapeRotationAt(indx, m_RotationAt);
        pLTRec->setShapeScaleAt(indx, m_ScaleAt);
      }

    } while (!bFinish);
    OdDbLinetypeTableRecordImpl::resizeDashes(pLTRec, indx + 1); // real count

    pLTRec->setPatternLength(PatternLen);

    try 
    {
      pTbl->add(pLTRec);
      ODA_ASSERT(pLTRec->isDBRO());
    }
    catch (const OdError_DuplicateRecordName& err)
    {
      switch (dlt)
      {
      case OdDb::kDltReplace:
        {
          OdDbSymbolTableRecordPtr pOldRec = err.existingRecordId().safeOpenObject(OdDb::kForWrite);
          pOldRec->copyFrom(pLTRec);
        }
        break;
      case OdDb::kDltIgnore:
        break;
      default:
        throw;
      }
    }

    return true;
  } // TryMeAsInfoAndAdd2Table
};


#endif //__LINETYPEHELPER_H_
