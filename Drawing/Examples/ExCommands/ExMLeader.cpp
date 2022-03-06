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

#include "StdAfx.h"
#include "DbLeader.h"
#include "DbFcf.h"
#include "DbMLeader.h"
#include "DbAnnotativeObjectPE.h"
#include "DbAssocArrayActionBody.h"
#include "DbSmartCenterActionBody.h"
#include "DbBlockTable.h"
#include "DbBlockReference.h"
#include "DbImpAssocMLeaderActionBody.h"
#include "ExSelectionUtils.h"
#include "DbAttributeDefinition.h"

///////////////////////////////////////////////////////////////////////////////////

// old simple version of commant to insert mleader with mtext
void _MLeadText_func(OdEdCommandContext* pCmdCtx)
{
	OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
	OdDbDatabasePtr pDb = pDbCmdCtx->database();
	OdDbUserIO* pIO     = pDbCmdCtx->dbUserIO();

	int llIndex;

	OdGePoint3d first  = pIO->getPoint("Set first point");
	OdGePoint3d second = pIO->getPoint("Set second point");
	OdString strLabel  = pIO->getString("Set label");

	if (first == second) {
		pIO->putError("The points coincide");
		return;
	}

	if (strLabel.isEmpty()) {
		pIO->putError("MLeader text is empty");
		return;
	}

	OdDbObjectId spaceId = ExCommandsUtils::activeBlockTableRecord(pDb);
	OdDbBlockTableRecordPtr pSpace = spaceId.safeOpenObject(OdDb::kForWrite);

	OdDbMLeaderPtr pMLeader = OdDbMLeader::createObject();
	pMLeader->setDatabaseDefaults(pDb);
	pSpace->appendOdDbEntity(pMLeader);

	OdDbMTextPtr pMText = OdDbMText::createObject();
	pMText->setDatabaseDefaults(pDb);
	pMLeader->setEnableFrameText(true);
	pMText->setContents(strLabel);
	pMText->setLocation(second);
  pMText->setHeight(10.0);

	pMLeader->setMText(pMText);
	pMLeader->addLeaderLine(first, llIndex);
}

///////////////////////////////////////////////////////////////////////////////////

typedef enum {
  kArrowHeadFirst,
  kLandingFirst,
  kContextFirst
} TMLeaderFirstInp;

inline bool isOnOneSide(const OdGeVector3d& vDir0, const OdGeVector3d& vDir1)
{
  bool bOnOneSide = vDir0.dotProduct(vDir1) >= 0.0;
  ODA_ASSERT_ONCE(!vDir0.isParallelTo(vDir1) || bOnOneSide == vDir0.isCodirectionalTo(vDir1));
  return bOnOneSide;
}

inline int getLeaderRootIndexByLineIndex(OdDbMLeader* pMLeader,
                                         int idxLeaderLine = -1) // returns 1st in array if it is < 0
{
  ODA_ASSERT_ONCE(pMLeader);
  OdIntArray leaderIndexes;
  pMLeader->getLeaderIndexes(leaderIndexes);
  ODA_ASSERT_ONCE(leaderIndexes.size());
  for (int idx = 0; idx < (int)leaderIndexes.size(); idx++)
  {
    int idxLeader = leaderIndexes[idx];
    if (idxLeaderLine < 0) // returns 1st in array if it is < 0
      return idxLeader;
    OdIntArray leaderLineIndexes;
    pMLeader->getLeaderLineIndexes(idxLeader, leaderLineIndexes);
    if (leaderLineIndexes.contains(idxLeaderLine))
      return idxLeader;
  }
  ODA_FAIL_ONCE();
  return -1;
}

// returns true if changed
static bool adjustTextSideAligment(OdDbMLeader* pMLeader, OdDbMTextPtr pMText = OdDbMTextPtr())
{
  ODA_ASSERT_ONCE_X(MLEADER, pMLeader);

  OdDbMLeaderStyle::ContentType ctxType = pMLeader->contentType();
  if (ctxType != OdDbMLeaderStyle::kMTextContent)
  {
    ODA_ASSERT_ONCE_X(MLEADER, pMText.isNull());
    return false;
  }

  int idxLeader = getLeaderRootIndexByLineIndex(pMLeader, 
                                                -1); // for first in array
  OdGeVector3d vDoglegDir;
  pMLeader->getDoglegDirection(idxLeader, vDoglegDir); // root->m_vDirection;
  ODA_ASSERT_ONCE_X(MLEADER, !vDoglegDir.isZeroLength());

  if (pMText.isNull())
    pMText = pMLeader->mtext();
  OdGeVector3d vTextDir = pMText->direction(); // pTextContent->m_vDirection
  bool bLeftDirection = isOnOneSide(vDoglegDir, vTextDir);

  OdDbMLeaderStylePtr pMLeaderStyle = OdDbMLeaderStyle::cast(pMLeader->MLeaderStyle().openObject(OdDb::kForRead));

  OdDbMLeaderStyle::TextAlignmentType textAlign = pMLeader->textAlignmentType();
  switch (textAlign)
  {
  case OdDbMLeaderStyle::kLeftAlignment:
    if (   !bLeftDirection
        && (pMLeaderStyle.isNull() || !pMLeaderStyle->textAlignAlwaysLeft()))
      textAlign = OdDbMLeaderStyle::kRightAlignment;
    break;
  case OdDbMLeaderStyle::kRightAlignment:
    if (bLeftDirection)
      textAlign = OdDbMLeaderStyle::kLeftAlignment;
    break;
  }
  if (textAlign == pMLeader->textAlignmentType())
    return false;

  pMLeader->setTextAlignmentType(textAlign);
  return true;
}

inline int getLeaderNumVertices(OdDbMLeader* pMLeader, int idxLeaderLine)
{
  ODA_ASSERT_ONCE(pMLeader && idxLeaderLine >= 0);
  int num = 0;
  OdResult es = pMLeader->numVertices(idxLeaderLine, num);
  ODA_ASSERT_ONCE(es == eOk);
  return num;
}

struct MLeaderTracker : public OdEdPointTracker
{
  OdDbDatabase* m_pDb;
  OdDbMLeaderStyle::ContentType m_ctxType, m_ctxTypeByStyle;
  OdDbMLeaderStyle::LeaderType m_lnType, m_lnTypeByStyle;
  bool m_bEnableLanding, m_bEnableLandingByStyle;
  double m_dogleg, m_doglegByStyle;
  OdDbObjectId m_idBlock, m_idBlockByStyle;
  TMLeaderFirstInp m_enFirst;
  OdGePoint3d m_ptFirst, m_ptNext;
  int m_maxPoints, m_idxPoint, 
      m_idxLeader, // root index
      m_idxLeaderLine; // line index in root
  bool m_bAlignmentChanged;
  OdDbMLeaderPtr m_pMLeader;
  MLeaderTracker()
    : m_ctxType(OdDbMLeaderStyle::kNoneContent)
    , m_ctxTypeByStyle(OdDbMLeaderStyle::kNoneContent)
    , m_lnType(OdDbMLeaderStyle::kStraightLeader)
    , m_lnTypeByStyle(OdDbMLeaderStyle::kStraightLeader)
    , m_bEnableLanding(true)
    , m_bEnableLandingByStyle(true)
    , m_dogleg(0.0)
    , m_doglegByStyle(0.0)
    , m_enFirst(kArrowHeadFirst)
    , m_maxPoints(2)
    , m_idxPoint(0) 
    , m_idxLeader(-1) // none
    , m_idxLeaderLine(-1) // none
    , m_bAlignmentChanged(false)
  {
  }
  virtual int addDrawables(OdGsView* pView)
  {
    if (m_pMLeader.get())
      pView->add(m_pMLeader, 0);
    return 1;
  }
  virtual void removeDrawables(OdGsView* pView)
  {
    if (m_pMLeader.get())
      pView->erase(m_pMLeader);
  }
  virtual void setValue(const OdGePoint3d& value)
  {
    if (m_pMLeader.isNull())
      return;
    ODA_ASSERT_ONCE(m_idxPoint >= 0 && m_idxPoint < m_maxPoints);
    if (m_idxPoint >= m_maxPoints)
      return;
    if (!m_idxPoint)
    {
      switch (m_enFirst)
      {
      case kArrowHeadFirst:
      case kLandingFirst:
        ODA_ASSERT_ONCE(m_idxPoint > 0);
        break;
      case kContextFirst:
        switch (m_ctxType)
        {
        case OdDbMLeaderStyle::kBlockContent:
          m_pMLeader->setBlockPosition(value); break;
        case OdDbMLeaderStyle::kMTextContent:
          m_pMLeader->setTextLocation(value); break;
        }
        break;
      }
      return;
    }
    
    OdResult es;
    int num = getLeaderNumVertices(m_pMLeader, m_idxLeaderLine);
    OdGeVector3d vDir;
    OdGePoint3d pt;
    if (m_enFirst == kArrowHeadFirst)
    {
      if (num > 1)
      {
        m_pMLeader->getVertex(m_idxLeaderLine, num - 2, pt);
        vDir = value - pt;
      }
      es = m_pMLeader->setLastVertex(m_idxLeaderLine, value);
    }
    else
    {
      if (num > 1)
      {
        m_pMLeader->getVertex(m_idxLeaderLine, 1, pt);
        //vDir = value - pt; 
        vDir = pt - value;
      }
      es = m_pMLeader->setFirstVertex(m_idxLeaderLine, value);
    }
    ODA_ASSERT_ONCE(es == eOk);

    bool isLastPoint = (m_idxPoint == (m_maxPoints - 1));
    switch (m_enFirst)
    {
    case kLandingFirst:
    case kContextFirst:
      if (!isLastPoint)
        return;
      break;
    }

    OdGeVector3d vDoglegDir;
    if (!vDir.isZeroLength())
      m_pMLeader->getDoglegDirection(m_idxLeader, vDoglegDir);
    bool bChangeRootDir = false;
    if (!vDoglegDir.isZeroLength())
      bChangeRootDir = !isOnOneSide(vDoglegDir, vDir);
    if (bChangeRootDir)
    {
      if (m_enFirst == kArrowHeadFirst)
        vDoglegDir = -vDoglegDir;
      m_pMLeader->setDoglegDirection(m_idxLeader, vDoglegDir); // for recompute  without redraw // m_pMLeader->downgradeOpen(), m_pMLeader->upgradeOpen();

      m_pMLeader->getLastVertex(m_idxLeaderLine, pt);
      ODA_ASSERT_ONCE_X(MLEADER, pt != value);
      //if (pt != value)
        m_pMLeader->setLastVertex(m_idxLeaderLine, value); // critical // CORE-17753
    }
    ODA_ASSERT_VAR(else)
      ODA_ASSERT(true); // brk

    m_bAlignmentChanged = adjustTextSideAligment(m_pMLeader); // CORE-17753
  }

  OdDbMLeaderPtr createMLeader()
  {
    ODA_ASSERT_ONCE(m_idxPoint || m_enFirst == kContextFirst);

    bool wasMissing = m_pMLeader.isNull();
    if (wasMissing)
    {
      m_pMLeader = OdDbMLeader::createObject();
      m_pMLeader->setDatabaseDefaults(m_pDb);

      OdDbAnnotativeObjectPEPtr pAnnoPe = OdDbAnnotativeObjectPE::cast(m_pMLeader);
      bool bAnno = pAnnoPe->annotative(m_pMLeader), bUpdated = false;
      if (m_ctxType != m_pMLeader->contentType())
        m_pMLeader->setContentType(m_ctxType);
      m_pMLeader->setEnableAnnotationScale(false);
      if (bAnno)
        pAnnoPe->setFromStyle(m_pMLeader, bUpdated); // CORE-17686
    }

    if (!m_pMLeader->isDBRO()) // && m_idxPoint)
    {
      OdResult es = m_pMLeader->postMLeaderToDb(m_pDb);
      ODA_ASSERT_ONCE(es == eOk);
      if (es != eOk)
        throw OdError(es);
    }

    if (m_lnType != m_lnTypeByStyle)
      m_pMLeader->setLeaderLineType(m_lnType);
    if (m_bEnableLanding != m_bEnableLandingByStyle)
      m_pMLeader->setEnableLanding(m_bEnableLanding);
    if (m_bEnableLanding && !OdEqual(m_dogleg, m_doglegByStyle))
      m_pMLeader->setDoglegLength(m_dogleg);

    if (wasMissing)
    {
      switch (m_ctxType)
      {
      case OdDbMLeaderStyle::kBlockContent:
        if (m_idBlock != m_idBlockByStyle)
        {
          ODA_ASSERT_ONCE(!m_idBlock.isNull());
          m_pMLeader->setBlockContentId(m_idBlock);
        }
        inputBlockAttributes(NULL); // clear attributes as ACAD
        break;
      case OdDbMLeaderStyle::kMTextContent:
        inputMText(NULL);
        break;
      }
    }

    return m_pMLeader;
  }

  void inputOptions(OdDbUserIO* pIO)
  {
    OdString sPrompt, sKeywords, sType;
    int idxKey = -1, idxDef = -1, num = 0;
    while (true)
    {
      //Enter an option [Leader type/leader lAnding/Content type/Maxpoints/First angle/Second angle/eXit options] <eXit options>:
      sPrompt = L"Enter an option [Leader type/leader lAnding/Content type/Maxpoints"
        //L"/First angle/Second angle" // TODO
        L"/eXit options] <eXit options>";
      sKeywords = L"Leader lAnding Content Maxpoints First Second eXit";
      idxKey = pIO->getKeyword(sPrompt, sKeywords, 6);
      if (idxKey >= 0)
      {
        switch (idxKey)
        {
        case 0: // Leader type
          // Select a leader type [Straight/sPline/None] <Straight>:
          idxDef = -1;
          switch (m_lnType)
          {
          case OdDbMLeaderStyle::kStraightLeader: sType = L"Straight"; idxDef = 0; break;
          case OdDbMLeaderStyle::kSplineLeader: sType = L"sPline"; idxDef = 1; break;
          case OdDbMLeaderStyle::kInVisibleLeader: sType = L"None"; idxDef = 2; break;
          }
          sPrompt.format(L"Select a leader type [Straight/sPline/None] <%ls>", sType.c_str());
          sKeywords = L"Straight sPline None";
          idxKey = pIO->getKeyword(sPrompt, sKeywords, idxDef);
          if (idxKey >= 0)
          {
            switch (idxKey)
            {
            case 0: m_lnType = OdDbMLeaderStyle::kStraightLeader; break;
            case 1: m_lnType = OdDbMLeaderStyle::kSplineLeader; break;
            case 2: m_lnType = OdDbMLeaderStyle::kInVisibleLeader; break;
            }
          }
          break;
        case 1:
          // Use landing [Yes/No] <Yes>:
          sPrompt.format(L"Use landing [Yes/No] <%ls>", m_bEnableLanding ? L"Yes" : L"No");
          sKeywords = L"Yes No";
          idxDef = m_bEnableLanding ? 0 : 1;
          idxKey = pIO->getKeyword(sPrompt, sKeywords, idxDef);
          if (idxKey != idxDef)
          {
            m_bEnableLanding = !m_bEnableLanding;
            if (m_bEnableLanding)
            {
              //Specify fixed landing distance <0.3600>:
              sPrompt.format(L"Specify fixed landing distance <%ls>", m_pDb->formatter().formatLinear(m_dogleg).c_str());
              double dDist = pIO->getDist(sPrompt, OdEd::kInpDefault, m_dogleg);
              if (dDist >= 0 && !OdEqual(dDist, m_dogleg))
                m_dogleg = dDist;
            }
          }
          break;
        case 2: // Content type
          //Select a content type [Block/Mtext/None] <Mtext>:
          idxDef = -1;
          switch (m_ctxType)
          {
          case OdDbMLeaderStyle::kBlockContent: sType = L"Block"; idxDef = 0; break;
          case OdDbMLeaderStyle::kMTextContent: sType = L"Mtext"; idxDef = 1; break;
          case OdDbMLeaderStyle::kNoneContent: sType = L"None"; idxDef = 2; break;
          }
          sPrompt.format(L"Select a content type [Block/Mtext/None] <%ls>", sType.c_str());
          sKeywords = L"Block Mtext None";
          idxKey = pIO->getKeyword(sPrompt, sKeywords, idxDef);
          if (idxKey != idxDef)
          {
            switch (idxKey)
            {
            case 0:
            {
              m_idBlock = m_idBlockByStyle;
              if (m_idBlock.isNull())
              {
                OdDbBlockTablePtr pBlocks = m_pDb->getBlockTableId().safeOpenObject(OdDb::kForRead);
                OdString sBlock;
                while (!(sBlock = pIO->getString(L"Enter block name", OdEd::kGstAllowSpaces)).isEmpty()) // | OdEd::kGstNoEmpty);
                {
                  if (pBlocks->has(sBlock))
                    break;
                  pIO->putError(::odrxSystemServices()->formatMessage(eInvalidBlockName)); // eMissingBlockName
                }
                if (sBlock.isEmpty())
                {
                  pIO->putError(::odrxSystemServices()->formatMessage(eInvalidInput));
                  break;
                }
                m_idBlock = pBlocks->getAt(sBlock);
              }
              m_ctxType = OdDbMLeaderStyle::kBlockContent;
              break;
            }
            case 1: 
              m_ctxType = OdDbMLeaderStyle::kMTextContent; break;
            case 2: 
              m_ctxType = OdDbMLeaderStyle::kNoneContent; break;
            }
          }
          break;
        case 3:
          // Enter the maximum points for leader line <2>:
          sPrompt.format(L"Enter the maximum points for leader line <%d>", m_maxPoints);
          while ((num = pIO->getInt(sPrompt, OdEd::kInpDefault, m_maxPoints)) <= 1)
            pIO->putError(::odrxSystemServices()->formatMessage(eInvalidInput));
          m_maxPoints = num;
          break;
        case 4: // First angle
          // Enter first angle constraint <0>: 90 //TODO
        case 5: // Second angle
          // Enter second angle constraint <0>: 90 //TODO
        case 6: // eXit"
          return;
        } // switch
      } // if
    } // while(true)
  }

  void inputBlockAttributes(OdDbUserIO* pIO = NULL) // NULL to clear attributes
  {
    OdDbBlockTableRecordPtr pBlockRec = OdDbBlockTableRecord::cast(m_pMLeader->blockContentId().openObject(OdDb::kForWrite));
    if (pBlockRec.isNull() || !pBlockRec->hasAttributeDefinitions())
      return;
    if (pIO)
      pIO->putString(L"Enter attribute values");

    OdDbObjectIteratorPtr pIt = pBlockRec->newIterator();
    for (pIt->start(); !pIt->done(); pIt->step())
    {
      OdDbEntityPtr pEnt = pIt->entity(OdDb::kForWrite);
      if (pEnt.isNull() || !pEnt->isKindOf(OdDbAttributeDefinition::desc()))
        continue;

      OdDbAttributeDefinition* pAttDef = OdDbAttributeDefinition::cast(pEnt).get();
      OdDbAttributePtr pNewAtt = OdDbAttribute::createObject();
      pNewAtt->setDatabaseDefaults(m_pDb);

      OdString sAttrText;
      if (pIO)
        sAttrText = pIO->getString(L"Enter Attr <Block>", OdEd::kGstAllowSpaces, 
                                   L"Block"); // ,L"Block");

      pNewAtt->setTextString(sAttrText);
      //pNewAtt->setTag(L"tag");
      //pNewAtt->setLockPositionInBlock(false);
      OdResult es = m_pMLeader->setBlockAttributeValue(pAttDef->objectId(), pNewAtt);
      ODA_ASSERT_ONCE(es == eOk);
    }
  }

  void inputMText(OdDbUserIO* pIO = NULL) // NULL for initial drag
  {
    OdDbMLeaderStylePtr pStyle = m_pDb->mleaderstyle().safeOpenObject(OdDb::kForRead);
    OdString sText;
    OdDbMTextPtr pMText;
    pMText = m_pMLeader->mtext();
    if (pMText.get())
    {
      sText = pMText->contents();
      if (sText.find(L"ABC") >= 0) // included L"\\ABC"
      {
        pMText->setContents(OdString::kEmpty);
        m_pMLeader->setMText(pMText);
        //next is critical for redraw in ODE via CORE-17773 (update views in all methods of UserIO)
        m_pMLeader->downgradeOpen(); m_pMLeader->upgradeOpen();
      }
      pMText = NULL; // renew via style
    }
    if (pMText.isNull())
    {
      pMText = pStyle->defaultMText();
      ODA_ASSERT_ONCE(pMText.get());
    }
    if (pIO)
    {
      do
        sText = pIO->getString(L"Enter Text <ABC>", OdEd::kGstAllowSpaces, L"ABC");
      while (sText.isEmpty());
    }
    else
      sText = L"ABC";
    pMText->setContents(sText);
    OdDbMLeaderStyle::TextAlignmentType tpPrev = m_pMLeader->textAlignmentType();
    m_pMLeader->setMText(pMText);
    m_bAlignmentChanged = (tpPrev != m_pMLeader->textAlignmentType());
  }

  void inputFirstPoint(OdDbUserIO* pIO)
  {
    ODA_ASSERT_ONCE(pIO);

    OdString sPrompt, sKeywords, sType;
    int idxKey = -1, idxDef = -1;

    while (true)
    {
      m_idxPoint = 0;
      switch (m_enFirst)
      {
      default: ODA_FAIL_ONCE();
      case kArrowHeadFirst:
        sPrompt = L"Specify leader arrowhead location or [";
        // TODO CORE-17605 //sPrompt = L"leader Landing first/Content first/";
        break;
      case kLandingFirst:
        sPrompt = L"Specify leader landing location or [leader arrowHead first/Content first/"; break;
      case kContextFirst:
        switch (m_ctxType)
        {
        case OdDbMLeaderStyle::kBlockContent:
          sPrompt = L"Specify insertion point for block"; break;
        case OdDbMLeaderStyle::kMTextContent:
          sPrompt = L"Specify leader corner of text"; break;
        default: ODA_FAIL_ONCE(); sPrompt = L"";  break;
        }
        sPrompt += L" or [leader arrowHead first/leader Landing first/";
      }
      sPrompt += L"Options]<Options>";
      sKeywords = L"arrowHead Landing Content Options";

      if (m_enFirst == kContextFirst)
        createMLeader();

      idxKey = -1; // of "arrowHead Landing Content Options"
      try {
        m_ptFirst = pIO->getPoint(sPrompt, OdEd::kInpThrowEmpty, // OdEd::kGptDefault,
                                  NULL, sKeywords, this);
      }
      catch (OdEdKeyword& key)
      {
        idxKey = key.keywordIndex();
      }
      catch (OdEdEmptyInput&)
      {
        idxKey = 3; // Options
      }

      switch (idxKey)
      {
      case -1:
        if (m_enFirst == kContextFirst)
        {
          switch (m_ctxType)
          {
          case OdDbMLeaderStyle::kBlockContent:
            m_pMLeader->setBlockPosition(m_ptFirst);
            inputBlockAttributes(pIO);
            break;
          case OdDbMLeaderStyle::kMTextContent:
            m_pMLeader->setTextLocation(m_ptFirst);
            inputMText(pIO);
            break;
          }
        }
        break;
      case 0: // arrowHead first
        m_enFirst = kArrowHeadFirst; continue;
      case 1: // Landing first
        m_enFirst = kLandingFirst; continue;
      case 2: // Content first
        m_enFirst = kContextFirst; continue;
      case 3: // Options
        inputOptions(pIO);
        continue;
      }
      break;
    } // while
  }

  bool inputNextPoint(OdDbUserIO* pIO)
  {
    ODA_ASSERT_ONCE(pIO);
    OdResult es;
    int num = 0;
    if (++m_idxPoint == 1)
    {
      createMLeader();
      m_idxLeaderLine = -1;
      switch (m_enFirst)
      {
      case kArrowHeadFirst:
        es = m_pMLeader->addLeaderLine(m_ptFirst, m_idxLeaderLine);
        ODA_ASSERT_ONCE(es == eOk && m_idxLeaderLine >= 0);
        m_idxLeader = getLeaderRootIndexByLineIndex(m_pMLeader, m_idxLeaderLine);
        num = getLeaderNumVertices(m_pMLeader, m_idxLeaderLine);
        if (num == 1)
        {
          if (m_ctxType == OdDbMLeaderStyle::kNoneContent)
          {
            m_pMLeader->addLastVertex(m_idxLeader, m_ptFirst);
            m_pMLeader->setFirstVertex(m_idxLeader, m_ptFirst); // problem with switch from block style
          }
        }
        break;

      case kLandingFirst:
        m_pMLeader->addLeader(m_idxLeader);
        ODA_ASSERT_ONCE(m_idxLeader >= 0);
        es = m_pMLeader->addLeaderLine(m_idxLeader, m_idxLeaderLine);
        ODA_ASSERT_ONCE(es == eOk && m_idxLeaderLine >= 0);
        num = getLeaderNumVertices(m_pMLeader, m_idxLeaderLine);
        if (num == 1)
        {
          if (m_ctxType == OdDbMLeaderStyle::kNoneContent)
            m_pMLeader->addLastVertex(m_idxLeader, m_ptFirst);
        }
        break;

      case kContextFirst:
        //m_pMLeader->addLeader(m_idxLeader);
        //es = m_pMLeader->addLeaderLine(m_idxLeader, m_idxLeaderLine);
        es = m_pMLeader->addLeaderLine(m_ptFirst, m_idxLeaderLine);
        m_idxLeader = getLeaderRootIndexByLineIndex(m_pMLeader, m_idxLeaderLine);

        ODA_ASSERT_ONCE(es == eOk && m_idxLeader >= 0 && m_idxLeaderLine >= 0);
        ODA_ASSERT_VAR(num = getLeaderNumVertices(m_pMLeader, m_idxLeaderLine);)
        ODA_ASSERT_ONCE(num); // && num == 2);

        //while (!(num = getLeaderNumVertices(m_pMLeader, m_idxLeaderLine)))
        while ((num = getLeaderNumVertices(m_pMLeader, m_idxLeaderLine)) < 2)
          m_pMLeader->addFirstVertex(m_idxLeaderLine, m_ptFirst);

        OdGeVector3d vDoglegDir;
        m_pMLeader->getDoglegDirection(m_idxLeader, vDoglegDir);

        switch (m_ctxType)
        {
        case OdDbMLeaderStyle::kBlockContent:
          m_pMLeader->setBlockPosition(m_ptFirst);
          m_pMLeader->setDoglegDirection(m_idxLeader, vDoglegDir);
          break; // restore
        case OdDbMLeaderStyle::kMTextContent:
          m_pMLeader->setTextLocation(m_ptFirst); break; // restore
        }
        break;
      } // switch
    }
    if (m_idxPoint >= m_maxPoints)
      return false;
    bool isLastPoint = (m_idxPoint == (m_maxPoints - 1));

    if (m_idxPoint > 1)
    {
      switch (m_enFirst)
      {
      case kLandingFirst:
      case kContextFirst:
        m_pMLeader->addFirstVertex(m_idxLeader, m_ptNext); // by prev next
        break;
      case kArrowHeadFirst:
        m_pMLeader->addLastVertex(m_idxLeader, m_ptNext); // by prev next
        break;
      }
    }

    OdString sPrompt, sKeywords;
    int idxKey = -1, idxDef = -1;

    sPrompt = L"Specify next point";
    if (isLastPoint)
    {
      switch (m_enFirst)
      {
      case kContextFirst:
      case kLandingFirst:
        sPrompt = L"Specify leader arrowhead location"; break;
      case kArrowHeadFirst:
        sPrompt = L"Specify leader landing location"; break;
      }
    }

    setValue(OdGePoint3d(m_ptFirst.x + 1e-3, m_ptFirst.y, m_ptFirst.z));
    while (true)
    {
      m_ptNext = pIO->getPoint(sPrompt, OdEd::kGstNoEmpty, NULL, OdString::kEmpty, this);
      if (m_ptNext != m_ptFirst)
        break;
      pIO->putError(::odrxSystemServices()->formatMessage(eSingularPoint)); //"The points coincide"
    }
    setValue(m_ptNext);

    if (isLastPoint && m_enFirst == kArrowHeadFirst)
    {
      switch (m_ctxType)
      {
      case OdDbMLeaderStyle::kBlockContent:
        //m_pMLeader->setBlockPosition(m_ptNext); 
        inputBlockAttributes(pIO);
        break;
      case OdDbMLeaderStyle::kMTextContent:
        //m_pMLeader->setTextLocation(m_ptNext); 
        inputMText(pIO);
        if (m_bAlignmentChanged)
          adjustTextSideAligment(m_pMLeader); // CORE-17753
        break;
      }
    }

    return true;
  }
};

void _MLeader_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
  OdDbMLeaderStylePtr pStyle = pDb->mleaderstyle().safeOpenObject(OdDb::kForRead);

  OdStaticRxObject<MLeaderTracker> tracker;
  tracker.m_pDb = pDb;
  tracker.m_enFirst = kArrowHeadFirst;
  tracker.m_lnType = tracker.m_lnTypeByStyle = pStyle->leaderLineType();
  tracker.m_bEnableLanding = tracker.m_bEnableLandingByStyle = pStyle->enableLanding();
  tracker.m_dogleg = tracker.m_doglegByStyle = pStyle->doglegLength();
  tracker.m_ctxType = tracker.m_ctxTypeByStyle = pStyle->contentType();
  tracker.m_idBlock = tracker.m_idBlockByStyle = pStyle->blockId();
  tracker.m_maxPoints = 2;

  tracker.inputFirstPoint(pIO);
  while (tracker.inputNextPoint(pIO))
    ;
}

//bool FindSlectedEntityForAssocMLeader(OdDbUserIO* pIO, OdDbSelectionSetPtr &pSSet, OdGePoint3dArray* ptsOfSelEntityPointer, bool isFirstEnt)
//{
//  struct ArrayFilter : public OdStaticRxObject<OdEdSSetTracker>
//  {
//    virtual int addDrawables(OdGsView*) { return 0; }
//    virtual void removeDrawables(OdGsView*) {}
//
//    virtual bool append(const OdDbObjectId& entId, const OdDbSelectionMethod*)
//    {
//      OdDbEntityPtr pEnt = OdDbEntity::cast(entId.safeOpenObject(OdDb::kForRead));
//      if (pEnt.isNull())
//        return false;
//
//      return OdDbAssocArrayActionBody::isAssociativeArray(pEnt);
//    }
//    virtual bool remove(const OdDbObjectId&, const OdDbSelectionMethod*)
//    {
//      return true;
//    }
//  } arrayFilter;
//
//  OdString message = isFirstEnt ? L"Select first point for assoc rotateds dimension:" : L"Select second point for assoc rotateds dimension:";
//  pSSet = pIO->select(message, OdEd::kSelSingleEntity | OdEd::kSelSinglePass,//
//    NULL, //const OdSelectionSet* pDefVal,
//    L"",//const OdString& sKeywords,
//    NULL, //OdSSetTracker* pBaseTracker,
//    ptsOfSelEntityPointer //OdGePoint3dArray* ptsPointer)
//    );// , 0, OdString::kEmpty, &arrayFilter);
//
//  return true;
//}

void _AssocMLeader_func(OdEdCommandContext* pCmdCtx)
{
  OdDbCommandContextPtr pDbCmdCtx(pCmdCtx);
  OdDbDatabasePtr pDb = pDbCmdCtx->database();
  OdDbUserIO* pIO = pDbCmdCtx->dbUserIO();
  OdDbSelectionSetPtr pSmartObject;
  OdDbSmartCenterActionBodyPtr smartBody;
  OdGePoint3dArray ptsSelected;
  OdDbObjectId     selectedEntId;
  OdDbBlockReferencePtr pBody;
  OdDbObjectId bodyId;
  OdDbFullSubentPathArray entPathArray;

  OdDbSubentId SentId;

  //if (false == FindSlectedEntityForAssocMLeader(pIO, pSmartObject, &ptsOfSelEntity, true))
  //  return;

  OdDbFullSubentPath path = selectedFullSubentPath(pIO, pDb, L"Select first point for assoc rotateds dimension:", ptsSelected, pSmartObject);

  if (path.objectIds().length() > 0)
  {
    entPathArray.append(path);
  }

  if (!pSmartObject->objectIdArray().isEmpty())
  {
    selectedEntId = pSmartObject->objectIdArray().first();
    pBody = OdDbBlockReference::cast(selectedEntId.openObject(OdDb::kForRead));

    if (!pBody.isNull())
    {
      bodyId = OdDbAssocArrayActionBody::getControllingActionBody(pBody);

      if (!bodyId.isNull())
        smartBody = OdDbSmartCenterActionBody::cast(bodyId.openObject());
    }
  }

  if (smartBody.isNull())
  {
    pIO->putError("This is not smart object, try again");
    return;
  }

  OdGePoint3d second = pIO->getPoint("Set second point");
  OdString strLabel = pIO->getString("Set label");

  if (ptsSelected.first() == second)
  {
    pIO->putError("The points coincide");
    return;
  }
  
  ptsSelected.append(second);

  if (strLabel.isEmpty()) 
  {
    pIO->putError("MLeader text is empty");
    return;
  }

  OdDbObjectId arrayId, actionBodyId;

  if (OdDbImpAssocMLeaderActionBody::createInstance(entPathArray, smartBody->objectId(), ptsSelected, strLabel, actionBodyId) != eOk)
  {
    pIO->putError("Object can't be created");
  }
}
