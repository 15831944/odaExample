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

#include "TfRevModule.h"
#include "DbCircle.h"
#include "DbBlockTableRecord.h"
#include "DebugStuff.h"
#include "MemoryStream.h"


ODRX_DEFINE_DYNAMIC_MODULE(OdRcModule);


void executeCommit(void* pCtx, OdDbDatabase* m_pDb)
{
  OdEdCommandContext* pCmdCtx = (OdEdCommandContext*)pCtx;
  ::odrxDynamicLinker()->loadModule(TfModuleName, false);
  OdDbDatabase* pDb = 0;
  if (pCmdCtx)
    pDb = OdDbCommandContextPtr(pCmdCtx)->database();
  else
    pDb = m_pDb;
  odTfInitialize(pDb->appServices());
  OdString msg, author;
  if (pCmdCtx)
    author = pCmdCtx->userIO()->getString(L"Enter author", OdEd::kGstAllowSpaces);
  if (pCmdCtx)
    msg = pCmdCtx->userIO()->getString(L"Enter commit message", OdEd::kGstAllowSpaces);
  OdTfRepository* pRep = OdTfRevisionControl::getRepository(pDb);
  OdTfDigestArray parents;
  OdTfRevisionControl::ReferenceList refList;
  pRep->getReferences(refList);
  OdString localBranch = OdTfRevisionControl::getLocalBranch(pDb);
  parents.append(refList.find(localBranch)->second);
  OdTfDigest sha = pRep->commit(pDb, parents, OdTfCommitAnnotation(author, msg));
  pRep->setReference(localBranch, sha);
}

void OdRcCommit::execute(OdEdCommandContext* pCmdCtx)
{
  executeCommit(pCmdCtx, m_pDb);
}

/** \details
Send code to stop server.
*/

void executeStop(void* pCtx, OdDbDatabase* m_pDb)
{
  OdEdCommandContext* pCmdCtx = (OdEdCommandContext*)pCtx;
  ::odrxDynamicLinker()->loadModule(TfModuleName, false);
  OdDbDatabase* pDb = 0;
  if (pCmdCtx)
    pDb = OdDbCommandContextPtr(pCmdCtx)->database();
  else
    pDb = m_pDb;
  odTfInitialize(pDb->appServices());
  WSAData wsData;
  SOCKADDR_IN addr;
  SOCKET socketObj;
  try
  {
    winSockWrap::initWinSock2(wsData, addr, socketObj);
    winSockWrap::send(socketObj, kOdRcStop, 0);
  }
  catch (OdException& e)
  {
    printDebugInfo(e.description(), pCmdCtx);
  }
  catch (...)
  {
    printDebugInfo(L"unknown connection error", pCmdCtx);
  }
}

void OdRcStop::execute(OdEdCommandContext* pCmdCtx)
{
  executeStop(pCmdCtx, m_pDb);
}



/** \details
Send set of commits to server (like git push)
*/

void executePush(void* pCtx, OdDbDatabase* m_pDb)
{
  OdEdCommandContext* pCmdCtx = (OdEdCommandContext*)pCtx;
  ::odrxDynamicLinker()->loadModule(TfModuleName, false);
  OdDbDatabase* pDb = 0;
  if (pCmdCtx)
    pDb = OdDbCommandContextPtr(pCmdCtx)->database();
  else
    pDb = m_pDb;
  odTfInitialize(pDb->appServices());
  OdTfRepositoryPtr pRep = OdTfRevisionControl::getRepository(pDb);
  WSAData wsData;
  SOCKADDR_IN addr;
  SOCKET socketObj;
  try
  {
    OdRcCodes code;
    winSockWrap::initWinSock2(wsData, addr, socketObj);
    winSockWrap::send(socketObj, kOdRcPush, 0);//send more
    OdTfDigestArray shaTo, shaFrom;
    OdTfDigest serverBranchSha;
    OdTfRevisionControl::ReferenceList refList;
    pRep->getReferences(refList);
    OdString s = OdTfRevisionControl::getLocalBranch(pDb);
    shaTo.append(refList.find(s)->second);
    findAllFromSha(socketObj, shaFrom, pRep, shaTo.first());
    winSockWrap::send(socketObj, kOdRcOk, 0);//send more
    OdStreamBufPtr sBuf = OdMemoryStream::createNew();
    OdPlatformStreamer::wrString(*sBuf, s);
    winSockWrap::sendBigData(socketObj, sBuf);
    winSockWrap::receive(socketObj, serverBranchSha.data, sizeof(serverBranchSha.data));
    if (pRep->getCommitInfo(serverBranchSha).revision.isNull() && !serverBranchSha.isNull())
    {
      winSockWrap::send(socketObj, OdRcCodes::kOdRcNeedPull);
      winSockWrap::receive(socketObj, code);
      ODA_ASSERT(code == kRCDoNothink);
      throw OdError(L"Server branch ahead from local. Need pull");
    }
    winSockWrap::send(socketObj, OdRcCodes::kOdRcOk, 0);//winsock

    sBuf = pRep->makePatch(shaFrom, shaTo, refList);
    winSockWrap::sendBigData(socketObj, sBuf);
    winSockWrap::receive(socketObj, code);
    if (code != kOdRcOk)
    {
      ODA_FAIL();
    }
  }
  catch (OdException& e)
  {
    printDebugInfo(e.description(), pCmdCtx);
  }
  catch (...)
  {
    printDebugInfo(L"unknown connection error\n", pCmdCtx);
  }
}

void OdRcPush::execute(OdEdCommandContext* pCmdCtx)
{
  executePush(pCmdCtx, m_pDb);
}




void pull(OdEdCommandContext* pCmdCtx, SOCKET socket, OdDbDatabase* pDb)
{
  OdTfRepositoryPtr pRep = OdTfRevisionControl::getRepository(pDb);
  winSockWrap::send(socket, kOdRcPull, 0);//send more //TODO need check, that database has one parent
  OdTfDigest shaLocalTop;
  OdString localBranch = OdTfRevisionControl::getLocalBranch(pDb);
  pRep->getReference(localBranch, shaLocalTop);
  OdStreamBufPtr res = OdMemoryStream::createNew();
  OdPlatformStreamer::wrString(*res, localBranch);
  winSockWrap::sendBigData(socket, res);
  res = 0;
  OdRcCodes answer;
  winSockWrap::receive(socket, answer);
  if (answer != kOdRcOk)
  {
    printDebugInfo(L"Remote branch not exist\n", pCmdCtx);
    return;
  }
  OdTfDigest servrTopSha;
  winSockWrap::receive(socket, servrTopSha);
  OdTfCommitInfo commit = pRep->getCommitInfo(servrTopSha);
  if (!commit.revision.isNull())
  {
    winSockWrap::send(socket, kOdRcNotOk, 0);//send more
    printDebugInfo(L"No need pull\n", pCmdCtx);
    return;
  }
  winSockWrap::send(socket, kOdRcOk, 0);//send more
  //check need merge after pull or not
  winSockWrap::send(socket, shaLocalTop, 0, shaLocalTop.data, sizeof(shaLocalTop.data));
  winSockWrap::receive(socket, answer);
  const bool bNeedMerge = answer == kOdRcNotOk;
  //search sha from for server
  OdTfDigest shaFrom;

  while (true)
  {
      winSockWrap::receive(socket, answer);
    if (answer != kOdRcSha)
      break;
    winSockWrap::receive(socket, shaFrom.data, sizeof(shaFrom.data));
    OdTfCommitInfo commitInfo = pRep->getCommitInfo(shaFrom);
    if (commitInfo.revision.isNull())
        winSockWrap::send(socket, kOdRcNotOk);
    else
        winSockWrap::send(socket, kOdRcOk);
  }
  winSockWrap::receive(socket, answer);
  if (answer != kOdRcOk)
  {
    printDebugInfo(L"Server can't create a patch\n", pCmdCtx);
    return;
  }
  OdStreamBufPtr sBuf;
  winSockWrap::reciveBigData(socket, sBuf);
  try
  {
    OdTfDigestArray roots;
    OdTfRevisionControl::ReferenceList refList;
    pRep->applyPatch(sBuf, roots, refList);
    if (!bNeedMerge)
      pRep->setReference(localBranch, refList.find(localBranch)->second);
    else
    {
      if (OdTfRevisionControl::merge(pDb, refList.find(localBranch)->second, OdTfFixedMergeHandler<OdTfRevisionControl::kMergeMineFull>()))
      {
        OdTfDigestArray parents;
        parents.append(refList.find(localBranch)->second);
        parents.append(shaLocalTop);
        OdTfDigest shaLocalTop = pRep->commit(pDb, parents, OdTfCommitAnnotation(L"client", L"mergeCommit"));
        pRep->setReference(localBranch, shaLocalTop);
      }
    }
    OdTfRevisionControl::switchBranch(pDb, localBranch);
  }
  catch (const OdError err)
  {
    winSockWrap::send(socket, kOdRcNotOk);
    throw err;
  }
  catch (...)
  {
    winSockWrap::send(socket, kOdRcNotOk);
    throw;
  }
}

namespace ExTfClone{
  void clone(OdEdCommandContext* pCmdCtx, SOCKET socket, OdDbDatabase* pDb)
  {
    //*  make clone via patch(do not receive all .dsf file)
    printDebugInfo(L"Not found repository. Executed clone\n", pCmdCtx);
    OdRcCodes code = kOdRcClone;
    winSockWrap::send(socket, code, 0);
    winSockWrap::receive(socket, code);
    if (code != kOdRcOk)
    {
      printDebugInfo(L"Server can't create a patch on clone", pCmdCtx);
      return;
    }
    OdStreamBufPtr sBuf;
    winSockWrap::reciveBigData(socket, sBuf);
    //remove("D:/Bugs/NewExampleRC/repC.dsf");
    //OdString s = L"D:/Bugs/NewExampleRC/repC.dsf";
    //if(odrxSystemServices()->accessFile("D:/Bugs/NewExampleRC/repC.dsf", 0))
      //s = L"D:/Bugs/NewExampleRC/repC2.dsf";
    //OdTfRepositoryPtr _rep = OdTfRepository::createObject(odrxSystemServices()->createFile(s, Oda::FileAccessMode(Oda::kFileWrite | Oda::kFileRead), Oda::kShareDenyWrite, Oda::kCreateAlways), pDb->appServices());
    OdStreamBufPtr sFile = OdMemoryStream::createNew();
    OdTfRepositoryPtr _rep = OdTfRepository::createObject(sFile, pDb->appServices());
    _rep->commit(pDb, OdTfDigestArray());
    OdTfDigestArray roots;
    OdTfRevisionControl::ReferenceList refList;
    try
    {
      _rep->applyPatch(sBuf, roots, refList);
      winSockWrap::send(socket, kOdRcOk, 0);
      OdStreamBufPtr sBuf;
      winSockWrap::reciveBigData(socket, sBuf);
      sBuf->rewind();
      while (!sBuf->isEof())
      {
        OdTfCommitInfo commitInfo = deserializationCommit(sBuf);
        ODA_ASSERT(!commitInfo.hash.isNull());
        _rep->writeCommitInfo(commitInfo);
      }
      OdTfRevisionControl::ReferenceList::const_iterator it = refList.begin();
      while (it != refList.end())
      {
        _rep->setReference(it->first, it->second);
        ++it;
      }
      OdTfRevisionControl::switchBranch(pDb, L"master");
    }
    catch (const OdError& err)
    {
      printDebugInfo(err.description(), pCmdCtx);
    }
  }
}


void executePull(void * pCtx, OdDbDatabase* m_pDb)
{


  OdEdCommandContext* pCmdCtx = (OdEdCommandContext*)pCtx;
  ::odrxDynamicLinker()->loadModule(TfModuleName, false);
  OdDbDatabase* pDb = 0;
  if (pCmdCtx)
    pDb = OdDbCommandContextPtr(pCmdCtx)->database();
  else
    pDb = m_pDb;
  odTfInitialize(pDb->appServices());
  WSAData wsData;
  SOCKADDR_IN addr;
  SOCKET socketObj;
  try
  {
    winSockWrap::initWinSock2(wsData, addr, socketObj);

    

    if (!OdTfRevisionControl::getLocalBranch(pDb).isEmpty())//if found name - do pull, else do clone
      pull(pCmdCtx, socketObj, pDb);
    else//clone
      ExTfClone::clone(pCmdCtx, socketObj, pDb);
  }
  catch (OdException& e)
  {
    printDebugInfo(e.description(), pCmdCtx);
  }
  catch (...)
  {
    printDebugInfo(L"unknown connection error\n", pCmdCtx);
  }
}

void OdRcPull::execute(OdEdCommandContext* pCmdCtx)
{
  executePull(pCmdCtx, m_pDb);
}



void OdRcModule::initApp()
{
  OdEdCommandStackPtr pCommands = odedRegCmds();
  pCommands->addCommand(&m_RCCommit);
  pCommands->addCommand(&m_RCPush);
  pCommands->addCommand(&m_RCUpdate);
  pCommands->addCommand(&m_RCStop);
  m_RCCommit._module = this;
  m_RCUpdate._module = this;
  m_RCStop._module = this;
  m_RCPush._module = this;
}

void OdRcModule::uninitApp()
{
  OdEdCommandStackPtr pCommands = odedRegCmds();
  pCommands->removeGroup(L"Revision control git");
}


