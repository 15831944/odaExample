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

// ExLine.cpp: implementation of the ExLine function.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DbLine.h"

class Line_Tracker : public OdEdPointTracker {
public:
  OdDbLinePtr pLine;

  virtual void setValue(const OdGePoint3d& value) {
    pLine->setEndPoint(value);
  }
  virtual int addDrawables(OdGsView* pView) {
    pView->add(pLine, 0);
    return 1;
  }
  virtual void removeDrawables(OdGsView* pView) {
    pView->erase(pLine);
  }
};

void _Line_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();

  OdDbObjectId spaceId = ExCommandsUtils::activeBlockTableRecord(pDb);
  OdDbBlockTableRecordPtr pSpace = spaceId.safeOpenObject(OdDb::kForWrite);

  OdGeVector3d vNormal(ExCommandsUtils::ucsNormal(pDb));

  OdString strNext_U(L"Specify next point or [Undo]:");
  OdString strKeywords_U(L"Undo");

  OdString strNext_CU(L"Specify next point or [Undo/Close]:");
  OdString strKeywords_CU(L"Undo Close");
  OdGePoint3d ptFirst, ptStart, ptEnd;
  int nLines = 0;

  for (bool bFinished = false; !bFinished;)
  {
    ptStart = ptFirst = pIO->getPoint(L"Specify first point:");

    for (;;)
    {
      OdDbLinePtr pNewLine = OdDbLine::createObject();
      pNewLine->setDatabaseDefaults(pDb);
      pNewLine->setNormal(vNormal);
      pNewLine->setStartPoint(ptStart);
      pNewLine->setEndPoint(ptStart);

      OdStaticRxObject<Line_Tracker> tracker;
      tracker.pLine = pNewLine;

      try
      {
        if (nLines >= 2)
        {
          ptEnd = pIO->getPoint(strNext_CU, OdEd::kInpThrowEmpty, NULL, strKeywords_CU, &tracker);
        }
        else
        {
          ptEnd = pIO->getPoint(strNext_U, OdEd::kInpThrowEmpty, NULL, strKeywords_U, &tracker);
        }
      }
      catch (const OdEdKeyword &kwd)
      {
        if (kwd.keywordIndex() == 1)
        { //Close
          ptEnd = ptFirst;
          bFinished = true;
        }
        else
        { //Undo
          if (nLines == 0)
          { //Undo first point
            break;
          }
          OdDbObjectId idLast = oddbEntLast(pDb);
          OdDbLinePtr pLine = idLast.openObject(OdDb::kForWrite);
          if (!pLine.isNull())
          {
            ptStart = pLine->startPoint();
            pLine->erase();
            --nLines;
          }
          else
          {
            ODA_FAIL();
          }
          continue;
        }
      }
      catch (const OdEdCancel& )
      {
        return;
      }

      pNewLine->setEndPoint(ptEnd);
      pSpace->appendOdDbEntity(pNewLine);
      ptStart = ptEnd;
      ++nLines;

      if (bFinished)
        return;
    }
  }
}
