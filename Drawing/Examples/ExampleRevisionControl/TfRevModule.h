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

#ifndef _TfRevModule_h_Included_
#define _TfRevModule_h_Included_


#include "OdaCommon.h"
#include "Ed/EdCommandStack.h"
#include "RxModule.h"
#include "StaticRxObject.h"
#include "DbDatabase.h"
#define STL_USING_MAP
#define STL_USING_VECTOR
#include "OdaSTL.h"
#include "Tf/TfRevisionControl.h"

#include "RxDynamicModule.h"
#include "DbCommandContext.h"
#include "DbHistoryManager.h"
#include "FlatMemStream.h"
#include "StaticRxObject.h"
#include "ExSystemServices.h"
#include "OdFileBuf.h"
#include "ExHostAppServices.h"

#ifdef OD_HAVE_CONSOLE_H_FILE
#include <console.h>
#endif
#include "DebugStuff.h"
#include "MemoryStream.h"


#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>


//#pragma warning(disable: 4996)

#define SHA_SIZE 20


OD_DLL_EXPORT void executePush(void* pCmdCtx, OdDbDatabase* m_pDb);
OD_DLL_EXPORT void executePull(void* pCmdCtx, OdDbDatabase* m_pDb);
OD_DLL_EXPORT void executeCommit(void* pCmdCtx, OdDbDatabase* m_pDb);
OD_DLL_EXPORT void executeStop(void* pCmdCtx, OdDbDatabase* m_pDb);

void printDebugInfo(const OdString& message, OdEdCommandContext* pCmdCtx = 0)
{
  if (pCmdCtx)
    pCmdCtx->userIO()->putString(message);
  else
    odPrintConsoleString(message);
}

class OdRcModule;

enum OdRcCodes
{
  kOdRcSha = 1,
  kOdRcPull,
  kOdRcPush,
  kOdRcClone,
  kOdRcStop,
  kOdRcOk,
  kOdRcNotOk,
  kRCDoNothink,
  kOdRcNeedPull,
  kOdRcReset,
};

struct OdRcCommit : OdEdCommand
{
  const OdString groupName() const { return L"Revision control git"; }
  const OdString globalName() const { return L"Commit"; }
  void execute(OdEdCommandContext* pCmdCtx);
  virtual OdInt32 flags() const
  {
    return OdEdCommand::flags() | OdEdCommand::kNoUndoMarker;
  }
  OdRcModule* _module;
  OdDbDatabase* m_pDb;
};

struct OdRcPush : OdEdCommand
{
  const OdString groupName() const { return L"Revision control git"; }
  const OdString globalName() const { return L"Push"; }
  void execute(OdEdCommandContext* pCmdCtx);

  virtual OdInt32 flags() const
  {
    return OdEdCommand::flags() | OdEdCommand::kNoUndoMarker;
  }
  OdRcModule* _module;
  OdDbDatabase* m_pDb;
};

struct OdRcPull : OdEdCommand
{
  const OdString groupName() const { return L"Revision control git"; }
  const OdString globalName() const { return L"Pull"; }
  void execute(OdEdCommandContext* pCmdCtx);
  virtual OdInt32 flags() const
  {
    return OdEdCommand::flags() | OdEdCommand::kNoUndoMarker;
  }
  OdRcModule* _module;
  OdDbDatabase* m_pDb;
};

struct OdRcStop : OdEdCommand
{
  const OdString groupName() const { return L"Revision control git"; }
  const OdString globalName() const { return L"Stop_server"; }
  void execute(OdEdCommandContext* pCmdCtx);
  virtual OdInt32 flags() const
  {
    return OdEdCommand::flags() | OdEdCommand::kNoUndoMarker;
  }
  OdRcModule* _module;
  OdDbDatabase* m_pDb;
};

namespace winSockWrap
{

    void initWinSock2(WSAData& wsData, SOCKADDR_IN& addr, SOCKET& socketObj, const bool bStartServer = false)
    {
      //Initialising winSock
      if (WSAStartup(MAKEWORD(2, 1), &wsData)) {
        throw OdError(L"Error in WSAStarup");
      }
      addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
      addr.sin_port = htons(1111);//4040
      addr.sin_family = AF_INET;   // for IP protocol 
      int sz = sizeof(addr);

      socketObj = socket(AF_INET, SOCK_STREAM, NULL);
      if (bStartServer)
      {
        int res = bind(socketObj, (SOCKADDR*)&addr, sizeof(addr));
        ODA_ASSERT(res == 0);//todo add throw with desc.
        res = listen(socketObj, SOMAXCONN);
        ODA_ASSERT(res == 0);
      }
      else
      {
        if (connect(socketObj, (SOCKADDR*)&addr, sizeof(addr)) != 0)
          throw OdError("Can't connect to server");
      }
    }

    template <typename T>
    void send(SOCKET socket, const T data, const OdInt8& flag = 0, char* buf = 0, OdUInt16 countBytes = 0)
    {
      int dataLen = countBytes == 0 ? sizeof(data) : countBytes;
      int result = 0;
      if(buf)
        result = ::send(socket, buf, dataLen, NULL);
      else
        result = ::send(socket, (char*)&data, dataLen, NULL);
      if (result != dataLen)
      {
        throw OdError(L"Send data error\n");
      }
    }

    template <typename T>
    bool receive(SOCKET socket, T& data, const OdUInt16 countBytes = 0, const OdInt8& flag = 0)
    {
      int dataLen = countBytes == 0 ? sizeof(data) : countBytes;
      int resultCode = recv(socket, (char*)&data, dataLen, NULL);
      if (resultCode != dataLen)
      {
        throw OdError(L"Wrong command\n");
        return false;
      }
      return true;
    }

    void sendBigData(SOCKET socket, OdStreamBufPtr& buf)
    {
        OdUInt64 N = buf->length();
        buf->rewind();

        send(socket, N, 0);//send more
        for (OdUInt64 n = 0; ;)
        {
            char subBuf[128];
            if (n + 128 < N)
            {
                buf->getBytes(subBuf, 128);
                send(socket, 0, 0/*send more*/, subBuf, 128);
                n += 128;
            }
            else
            {
                buf->getBytes(subBuf, N - n);
                send(socket, 0, 0, subBuf, N - n);
                break;
            }
        }
    }

    bool reciveBigData(SOCKET socket, OdStreamBufPtr& sBuf)
    {
        OdUInt64 N = 0;
        winSockWrap::receive(socket, N);
        sBuf = OdFlatMemStreamManaged::createNew(N);
        const int blobSize = 128;
        char reply[blobSize];
        for (OdUInt32 n = 0; N - n;)
        {
          int getLen = recv(socket, reply, blobSize, NULL);
          if (getLen != blobSize && n+getLen < N)
          {
            throw OdError(L"Recive big data error\n");
          }
          sBuf->putBytes(reply, getLen);
          n += getLen;
        }
        sBuf->rewind();
        return true;
    }
}

void addCommitRecursive(OdTfRepository* pRep, std::set<OdTfDigest>& baseCommits, std::set<OdTfDigest>& newCommits, const OdTfDigest& to)
{
  if (baseCommits.find(to) != baseCommits.end())
    return;

  OdTfCommitInfo c;
  c = pRep->getCommitInfo(to);
  c.hash = to;
  newCommits.insert(c.hash);

  for (unsigned j = 0; j < c.parents.size(); ++j)
    addCommitRecursive(pRep, baseCommits, newCommits, c.parents[j]);
}

void addRevisionRecursive(OdTfRepository* pRep, std::set<OdTfDigest>& baseCommits, std::set<OdTfDigest>& newRevisions, const OdTfDigest& to)
{
  if (baseCommits.find(to) != baseCommits.end())
    return;

  OdTfCommitInfo c;
  c = pRep->getCommitInfo(to);
  c.hash = to;
  newRevisions.insert(c.revision);

  for (unsigned j = 0; j < c.parents.size(); ++j)
    addRevisionRecursive(pRep, baseCommits, newRevisions, c.parents[j]);
}

//send sha to other side, if commit with this sha has other side, other side return code kOdRcOk(we this sha write to array 'from'
//if return not kOdRcOk, need recursive going by parents while will not find general ancestor that will be added to array 'from'
void findAllFromSha(SOCKET socket, OdTfDigestArray& from, OdTfRepositoryPtr& rep, OdTfDigest sha)
{
  winSockWrap::send(socket, kOdRcSha, 0);//send more
  winSockWrap::send(socket, sha, 0, sha.data, sizeof(sha.data));
  OdRcCodes code;
  winSockWrap::receive(socket, code);
  if (code == kOdRcOk)
  {
    from.append(sha);
    return;
  }
  OdTfCommitInfo commitInfo = rep->getCommitInfo(sha);
  for (unsigned i = 0; i < commitInfo.parents.size(); ++i)
  {
    findAllFromSha(socket, from, rep, commitInfo.parents[i]);
  }
}
//OdTfRepository write OdTfCommitInfo objects to patch, but OdTfStorage not include it.
//serializeCommit and deserializationCommit used in clone process
void serializeCommit(OdTfCommitInfo& c, OdStreamBufPtr s)
{
  c.hash.write(s);
  c.revision.write(s);
  OdPlatformStreamer::wrInt32(*s, c.parents.size());
  for (unsigned i = 0; i < c.parents.size(); ++i)
    c.parents[i].write(s);
  OdPlatformStreamer::wrString(*s, c.annotation.author);
  OdPlatformStreamer::wrInt64(*s, c.annotation.date.packedValue());
  OdPlatformStreamer::wrString(*s, c.annotation.message);
  if (!c.annotation.userData.isNull())
  {
    OdPlatformStreamer::wrInt32(*s, (OdInt32)c.annotation.userData->length());
    c.annotation.userData->copyDataTo(s);
  }
  else
    OdPlatformStreamer::wrInt32(*s, 0);
}

//OdTfRepository write OdTfCommitInfo objects to patch, but OdTfStorage not include it.
//serializeCommit and deserializationCommit used in clone process
OdTfCommitInfo deserializationCommit(OdStreamBufPtr & s)
{
  if (s.isNull())
    return OdTfCommitInfo();
  OdTfCommitInfo c;
  c.hash.read(s);
  c.revision.read(s);
  OdUInt32 N = OdPlatformStreamer::rdInt32(*s);
  if (N > 1000)
    throw OdError("Invalid commit");
  c.parents.resize(N);
  for (unsigned i = 0; i < N; ++i)
    c.parents[i].read(s);
  c.annotation.author = OdPlatformStreamer::rdString(*s);
  c.annotation.date.setPackedValue(OdPlatformStreamer::rdInt64(*s));
  c.annotation.message = OdPlatformStreamer::rdString(*s);
  N = OdPlatformStreamer::rdInt32(*s);
  if (N > 0)
  {
    c.annotation.userData = OdFlatMemStreamManaged::createNew(N);
    s->copyDataTo(c.annotation.userData, s->tell(), s->length());
  }
  return c;
}

struct GitLikeServer
{
  OdString _path;
  OdDbDatabasePtr _db;
  OdTfRepositoryPtr _rep;
  OdDbHostAppServices* _appServices;
  OdTfDigest _rootShaRevision;
  OdTfDigest _rootShaCommit;
  void handler()
  {
    //internalRemove(L"repository_s.dsf");
    ::odrxDynamicLinker()->loadModule(TfModuleName, false);
    odTfInitialize(_appServices);
    if (_path.isEmpty() || _path.right(4).iCompare(L".dwg") == 0)
    {//create new sqlite base
      _db = _path.isEmpty() ? _appServices->createDatabase(true) : _db = _appServices->readFile(_path);
      //_rep = OdTfRepository::createObject(odrxSystemServices()->createFile(L"repository_s.dsf", Oda::FileAccessMode(Oda::kFileWrite | Oda::kFileRead), Oda::kShareDenyWrite, Oda::kCreateAlways), _appServices);
      OdStreamBufPtr sFile = OdMemoryStream::createNew();
      _rep = OdTfRepository::createObject(sFile, _db->appServices());
      _rootShaCommit = _rep->commit(_db, OdTfDigestArray());
      OdTfCommitInfo commitInfo = _rep->getCommitInfo(_rootShaCommit);
      _rootShaRevision = commitInfo.revision;
      _rep->setReference(L"master", commitInfo.hash);
    }
    else if(_path.right(4).iCompare(L".dsf") == 0)
    {//open created
      OdStreamBufPtr s = odrxSystemServices()->createFile(_path, Oda::FileAccessMode(Oda::kFileWrite | Oda::kFileRead), Oda::kShareDenyWrite, Oda::kOpenAlways);
      _rep = OdTfRepository::createObject(s, _appServices);
      _db = _rep->checkout(L"master");
      _rep->getReference(L"master", _rootShaCommit);
      OdTfCommitInfo commit =_rep->getCommitInfo(_rootShaCommit);
      while (!commit.parents.isEmpty())
        commit = _rep->getCommitInfo(commit.parents[0]);
      _rootShaRevision = commit.revision;
      _rootShaCommit = commit.hash;
    }
    else
    {
      throw OdError(L"Can't create/open repository");
    }
    WSAData wsData; SOCKADDR_IN addr; SOCKET socketListener, socket = 0;
    winSockWrap::initWinSock2(wsData, addr, socketListener, true);
    
    //int s = 1;
    //winSockWrap::send(socket, s, 0, 0, 4);

    bool bStop = false;
    int sz = sizeof(addr);
    while (true)
    {
      if (bStop)
        break;
      if(socket > 0)
        closesocket(socket);
      socket = accept(socketListener, (SOCKADDR*)&addr, &sz);
      ODA_ASSERT(socket > 0);
      OdRcCodes code;
      if(!winSockWrap::receive(socket, code))
        continue;

      switch (code)
      {
      case kOdRcStop:
      {
        bStop = true;
        break;
      }
      case kOdRcSha:
      {
        ODA_FAIL();
        break;
      }
      case kOdRcPush:
      {
        push(socket, code, _rep);

        break;
      }
      case kOdRcPull:
      {
        doPull(socket);
        break;
      }
      case kOdRcClone:
      {
        //*  first attemp to make clone via patch(do not recive all .dsf file)
        odPrintConsoleString(L"Start clone\n");
        OdTfRevisionControl::ReferenceList refList;
        _rep->getReferences(refList);
        OdTfDigestArray shaTo, shaFrom;
        OdTfRevisionControl::ReferenceList::const_iterator it = refList.begin();
        while (it != refList.end())
        {//clone all branches, get heads all branches
          shaTo.push_back(it->second);
          ++it;
        }
        std::set<OdTfDigest> baseCommits, newRevisions, newCommits;
        baseCommits.insert(_rootShaCommit);
        newCommits.insert(_rootShaCommit);
        newRevisions.insert(_rootShaRevision);
        for (unsigned i = 0; i < shaTo.size(); i++)
          addRevisionRecursive(_rep, baseCommits, newRevisions, shaTo[i]);//get all revisions from root to all branches heads
        for (unsigned i = 0; i < shaTo.size(); i++)
          addCommitRecursive(_rep, baseCommits, newCommits, shaTo[i]);//get all commits from root to all branches heads
        OdStreamBufPtr pCommitInfoBuf = OdMemoryStream::createNew();
        std::set<OdTfDigest>::const_iterator itCommits = newCommits.begin();
        while (itCommits != newCommits.end())
        {
          OdTfCommitInfo commitInfo = _rep->getCommitInfo(*itCommits);
          serializeCommit(commitInfo, pCommitInfoBuf);//write all commite. Because makePatch write only revisions
          ++itCommits;
        }
        shaTo.clear();
        for (std::set<OdTfDigest>::iterator it = newRevisions.begin(); it != newRevisions.end(); ++it)
          shaTo.append(*it);
        OdStreamBufPtr sBuf;
        try
        {
          sBuf = ((OdTfStorage*)_rep)->makePatch(shaFrom, shaTo, refList);
          OdRcCodes code = kOdRcOk;
          winSockWrap::send(socket, code, 0);//send more
          winSockWrap::sendBigData(socket, sBuf);
          OdRcCodes answer;
          winSockWrap::receive(socket, answer);
          if(answer == kOdRcOk)
              winSockWrap::sendBigData(socket, pCommitInfoBuf);
        }
        catch (const OdError& exp)
        {
          OdRcCodes code = kOdRcNotOk;
          winSockWrap::send(socket, code);
          odPrintConsoleString(L"%s\n", exp.description());
        }
        odPrintConsoleString(L"End clone\n\n");
        break;
        //*/
      }
      }
    }
    closesocket(socket); 
    closesocket(socketListener);
    WSACleanup();
//throw OdException(OdString(L"Can't bind to "));
    //OdTfRevisionControl::switchBranch(_db, L"master");
    //_db->writeFile(L"D:/Bugs/NewExampleRC/6.dwg", OdDb::kDwg, OdDb::kDHL_CURRENT);
  };

  void showLogRecursive(OdTfCommitInfo commitInfo, const OdString& s)
  {
    OdString sHash;
    sHash.format(L"%c%c%c%c%c%c", commitInfo.hash.data[0], commitInfo.hash.data[1], commitInfo.hash.data[2], commitInfo.hash.data[3], commitInfo.hash.data[4], commitInfo.hash.data[5]);
    odPrintConsoleString(L"Name: %10ls P: %d Hash: %s\n", s.c_str(), commitInfo.parents.size(), sHash.c_str());
    for (unsigned i = 0; i < commitInfo.parents.size(); ++i)
    {
      if (commitInfo.parents.size() > 1)
        odPrintConsoleString(L"startParent %d\n", i);
      OdTfCommitInfo commitInfo2 = _rep->getCommitInfo(commitInfo.parents[i]);
      showLogRecursive(commitInfo2, s);
      if (commitInfo.parents.size() > 1)
        odPrintConsoleString(L"startParent %d\n", i);
    }
  }

  void showLog(OdTfRevisionControl::ReferenceList refs)
  {
    OdTfRevisionControl::ReferenceList::iterator it = refs.begin();
    OdTfCommitInfo commitInfo;
    while (it != refs.end())
    {
      commitInfo = _rep->getCommitInfo(it->second);
      showLogRecursive(commitInfo, it->first);
      ++it;
    }
  };

  void doPull(SOCKET socket)
  {
    odPrintConsoleString(L"Start pull\n");

    OdStreamBufPtr sBuf;
    winSockWrap::reciveBigData(socket, sBuf);
    OdString branch = OdPlatformStreamer::rdString(*sBuf);
    OdTfRevisionControl::ReferenceList referenceList;
    _rep->getReferences(referenceList);
    bool bFind = referenceList.find(branch) != referenceList.end();
    if (!bFind)
    {
        winSockWrap::send(socket, kOdRcNotOk);
      return;
    }
    winSockWrap::send(socket, kOdRcOk, 0);//send more
    winSockWrap::send(socket, referenceList.find(branch)->second.data, 0, referenceList.find(branch)->second.data, sizeof(referenceList.find(branch)->second.data));
    OdRcCodes answer;
    winSockWrap::receive(socket, answer);
    if (answer == kOdRcNotOk)//no need pull
      return;
    //check need merge after pull or not
    OdTfDigest clientTopBranchSha;
    winSockWrap::receive(socket, clientTopBranchSha.data, sizeof(clientTopBranchSha.data));
    if (_rep->getCommitInfo(clientTopBranchSha).revision.isNull())
        winSockWrap::send(socket, OdRcCodes::kOdRcNotOk, 0/*send more*/);//client must be make merge after pull
    else
        winSockWrap::send(socket, OdRcCodes::kOdRcOk, 0/*send more*/);

    OdTfDigestArray shaFrom, shaTo;
    findAllFromSha(socket, shaFrom, _rep, referenceList.find(branch)->second);
    winSockWrap::send(socket, OdRcCodes::kOdRcOk, 0);//send more
    shaTo.push_back(referenceList.find(branch)->second);

    OdTfRevisionControl::ReferenceList refs;
    _rep->getReferences(refs);
    try
    {
      sBuf = _rep->makePatch(shaFrom, shaTo, refs);
      winSockWrap::send(socket, kOdRcOk, 0);//send more
      winSockWrap::sendBigData(socket, sBuf);
    }
    catch (const OdError& err)
    {
      odPrintConsoleString(L"%s\n", err.description());
      winSockWrap::send(socket, kOdRcNotOk);
      odPrintConsoleString(L"End pull\n\n");
      return;
    }
    odPrintConsoleString(L"End pull\n\n");
  }

  private:

    void push(SOCKET socket, OdRcCodes code, OdTfRepositoryPtr _rep)
    {
      odPrintConsoleString(L"Start push\n");
      OdTfDigest shaFrom, branchSha;
      while (true)
      {
          winSockWrap::receive(socket, code);
        if (code != kOdRcSha)
          break;
        winSockWrap::receive(socket, shaFrom.data, sizeof(shaFrom.data));
        OdTfCommitInfo commitInfo = _rep->getCommitInfo(shaFrom);
        if (commitInfo.revision.isNull())
            winSockWrap::send(socket, kOdRcNotOk);
        else
            winSockWrap::send(socket, kOdRcOk);
      }
      OdStreamBufPtr sBuf;
      winSockWrap::reciveBigData(socket, sBuf);
      if (_rep->getReference(OdPlatformStreamer::rdString(*sBuf), branchSha))
      {
          winSockWrap::send(socket, branchSha.data, 0, branchSha.data, sizeof(branchSha.data));
        winSockWrap::receive(socket, code);
        if (code == kOdRcNeedPull)
        {
            winSockWrap::send(socket, kRCDoNothink);
          odPrintConsoleString(L"End push\n");
          return;
        }
      }
      else
      {
        winSockWrap::send(socket, OdTfDigest::kNull().data, 0, OdTfDigest::kNull().data, sizeof(OdTfDigest::kNull().data));
        winSockWrap::receive(socket, code);
        ODA_ASSERT(code == kOdRcOk);
      }
      winSockWrap::reciveBigData(socket, sBuf);//getPatch
      OdTfDigestArray roots;
      OdTfRevisionControl::ReferenceList refs;
      try
      {
        _rep->applyPatch(sBuf, roots, refs);
        OdTfRevisionControl::ReferenceList::iterator it = refs.begin();
        while (it != refs.end())
        {
          OdTfCommitInfo commitInfo = _rep->getCommitInfo(it->second);
          if (!commitInfo.revision.isNull())
            _rep->setReference(it->first, it->second);
          ++it;
        }
        winSockWrap::send(socket, kOdRcOk);
      }
      catch (const OdError& err)
      {
        odPrintConsoleString(L"%s\n", err.description());
        winSockWrap::send(socket, kOdRcNotOk);
      }
      refs.clear();
      _rep->getReferences(refs);
      showLog(refs);
      odPrintConsoleString(L"End push\n\n");
    }
};

namespace Git {
  static void startServer(const OdString& path, OdDbHostAppServices* appServ)
  {
    GitLikeServer serv;
    serv._path = path;
    serv._appServices = appServ;
    serv.handler();
  };
}



class OdRcModule : public OdRxModule
{
  OdStaticRxObject<OdRcPush> m_RCPush;
  OdStaticRxObject<OdRcPull> m_RCUpdate;
  OdStaticRxObject<OdRcStop> m_RCStop; 
  OdStaticRxObject<OdRcCommit> m_RCCommit;
public:
  void initApp();
  void uninitApp();
};

#endif //_TfRevModule_h_Included_
