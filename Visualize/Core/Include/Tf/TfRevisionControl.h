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


#ifndef _TFREVISIONCONTROL_H_INCLUDED_
#define _TFREVISIONCONTROL_H_INCLUDED_

#include "TfSchemaManager.h"
#include "DbObjectIterator.h"
#include "ThreadsCounter.h"

#define STL_USING_MAP
#include "OdaSTL.h"

#include <stdexcept>
//class OdDbDatabaseTv;
//#include "../../Source/TvDatabaseImpl.h"

/** \details
  Declares merge policy types. Merge policy determines conflict resolution
  action when automatic resolution fails. Manual assumes some kind of user
  interaction &mdash; not implemented yet.
*/
enum OdTvTfMergePolicy
{
  /** Use data from the target branch */
  kOdTfMergePreferTheirs,  
  /** Use data from the source branch */
  kOdTfMergePreferMine,    
  /** Let the user decide which branch data to use */
  kOdTfMergeManual        
};

/** \details
  This structure stores hash codes for commits.
*/
struct TFDLL_EXPORT OdTvTfDigest
{
  /** Data array to store a hash code. */
  char data[20];

  /** \details
    Writes the hash code to a stream buffer.

    \param pBuf [in] Stream buffer to write data to.
  */
  void write(OdStreamBuf* pBuf) const { pBuf->putBytes(data, 20); }

  /** \details
    Reads a hash code from a stream buffer.

    \param pBuf [in] Stream buffer to read data from.
  */
  void read(OdStreamBuf* pBuf) { pBuf->getBytes(data, 20); }

  /** \details
    "Less than" comparison operator.

    \param other [in] Hash code to compare with this hash code.
    \returns
    True if this hash code is less than other hash code; false if this hash code
    is equal or greater than other hash code.
  */
  bool operator < (const OdTvTfDigest& other) const
  {
    return memcmp(data, other.data, 20) < 0;
  }

  /** \details
    Comparison operator.

    \param other [in] Hash code to compare with this hash code.
    \returns
    True if this hash code is equal to other hash code; false otherwise.
  */
  bool operator == (const OdTvTfDigest& other) const
  {
    return memcmp(data, other.data, 20) == 0;
  }

  /** \details
    Negative comparison operator.

    \param other [in] Hash code to compare with this hash code.
    \returns
    True if this hash code is not equal to other hash code; false otherwise.
  */
  bool operator != (const OdTvTfDigest& other) const
  {
    return memcmp(data, other.data, 20) != 0;
  }

  /** \details
    Creates and returns a NULL hash code.
  */
  static OdTvTfDigest kNull()
  {
    OdTvTfDigest res;
    memset(res.data, 0, 20);
    return res;
  }

  /** \details
    Checks whether this hash code is a NULL hash code.

    \returns
    True if this hash code is a NULL hash code; false otherwise.
  */
  bool isNull() const
  {
    char test[20] = { 0 };
    return memcmp(test, data, 20) == 0;
  }

  /** \details
    Default constructor for instances of the OdTvTfDigest structure.
    Creates a NULL hash code.
  */
  OdTvTfDigest()
  {
    memset(data, 0, 20);
  }
};

/** \details
  This type represents arrays of hash codes.
*/
typedef OdArray<OdTvTfDigest, OdMemoryAllocator<OdTvTfDigest> > OdTvTfDigestArray;

/** \details
  This namespace contains revision control specific definitions.
*/
namespace OdTvTfRevisionControl
{
  /** \details
    Reference list.
  */
  typedef std::map<OdString, OdTvTfDigest> ReferenceList;

  /** \details
    Declares change types.
  */
  enum ChangeType
  {
    /** Object added to database */
    kObjectAdded = 1, 
    /** Object deleted from database */
    kObjectDeleted,   
    /** Object modified */
    kObjectModified    
  };

  /** \details
    Change list.
  */
  typedef std::map<OdDbHandle, ChangeType> ChangeList;
};



/** \details
  Structure describing a commit in the revision control database.
*/
struct TFDLL_EXPORT OdTvTfCommitAnnotation
{
  /** Commit author. */
  OdString author;      
  /** Commit message. */
  OdString message;     
  /** Commit timestamp. */
  OdTimeStamp date;     
  /** Arbitrary user data. */
  OdStreamBufPtr userData; 

  /** \details
    Constructor for instances of the OdTvTfCommitAnnotation structure.

    \param author              [in] Commit author.
    \param message             [in] Commit message.
    \param date                [in] Commit timestamp.
    \param arbitraryUserData   [in] Arbitrary user data.
  */
  OdTvTfCommitAnnotation(
    const OdString& author = OdString::kEmpty,
    const OdString& message = OdString::kEmpty,
    const OdTimeStamp& date = OdTimeStamp(OdTimeStamp::kInitUniversalTime),
    OdStreamBuf* arbitraryUserData = 0);
};

/** \details
  Structure describing a commit relationships in the revision control database.

  \remarks
  Array of parent commits contains one record for usual commit and several for
  merge commit. In case of merge commit, the first record in the array
  corresponds to the target branch, i.e. the branch into which the merge was
  done.
*/
struct TFDLL_EXPORT OdTvTfCommitInfo
{
  /** Hash of the commit itself. */
  OdTvTfDigest hash;              
  /** Hash of the parents. */
  OdTvTfDigestArray parents; 
  /** Hash of the revision object. */
  OdTvTfDigest revision;          
  /** Describing a commit in the revision control database. */
  OdTvTfCommitAnnotation annotation;

  /** \details
    Constructor for instances of the OdTvTfCommitInfo structure.

    \param author              [in] Commit author.
    \param message             [in] Commit message.
    \param date                [in] Commit timestamp.
    \param arbitraryUserData   [in] Arbitrary user data.
  */
  OdTvTfCommitInfo(const OdString& author = OdString::kEmpty, const OdString& message = OdString::kEmpty, const OdTimeStamp& date = OdTimeStamp(OdTimeStamp::kInitUniversalTime), OdStreamBuf* arbitraryUserData = 0)
    :annotation(author, message, date, arbitraryUserData) {}
};

class OdTvTfRepository;

/** \details
  This template class is a specialization of the OdSmartPtr class for smart
  pointers to objects of the OdTvTfRepository class.
*/
typedef OdSmartPtr<OdTvTfRepository> OdTvTfRepositoryPtr;


struct OdTvTfStorage;

/** \details
  This template class is a specialization of the OdSmartPtr class for smart
  pointers to objects of the OdTvTfStorage structure.
*/
typedef OdSmartPtr<OdTvTfStorage> OdTvTfStoragePtr;
struct OdTvTfStorageImpl;
struct OdTvTfStorageImpl;

namespace OdTvTfRevisionControl
{
  /** \details
    Gets an existing .dsf storage.

    \param pDb [in] Database linked to the OdTvTfStorage.
    \returns Pointer to the OdTvTfRepository object. Returns a NULL pointer if the
    database is not linked to the OdTvTfStorage.
  */
  TFDLL_EXPORT OdTvTfRepository* getRepository(OdTvDbDatabase* pDb);

  /** \details
    Removes the link between the OdTvDbDatabase and the OdTvTfStorage.

    \param pDb [in] Database linked to the OdTvTfStorage.
    \returns Pointer to the OdTvTfRepository object. Returns a NULL pointer if the
    database is not linked to the OdTvTfStorage.
  */
  TFDLL_EXPORT OdTvTfRepositoryPtr detachRepository(OdTvDbDatabase* pDb);

  /** \details
    Saves changes in the database to the repository, creates a commit object and
    shifts the current branch tip if not checkout as detached. The
    "objectsToSave" optional parameter is a list of objects to save. It can be
    used to perform a partial commit.

    Includes all tracked merged commits as parents of the commit.

    \param pDb           [in] The database, which state has to be saved.
    \param message       [in] Commit message.
    \param objectsToSave [in] A list of objects to be saved. Optional. Used to
                              perform a partial commit.

    \returns Hash code of the commit.
  */
  TFDLL_EXPORT OdTvTfDigest commit(OdTvDbDatabase* pDb, const OdTvTfCommitAnnotation& message, const OdTvDbObjectIdArray* objectsToSave = 0);

  /** \details
    Merges changes from the repository to the database. Merge operation does not
    automatically commit changes, only runtime database is changed.

    Adds the source commit as a tracked merge parent for this drawing. This
    makes the source commit as a parent when committing the changes to the
    repository.

    \remarks
    If the merge was fast forward, no merge commit is necessary.
    If the "noFastForward" flag is true, and the remote branch is directly above
    or below this one in the commit graph, the function does nothing.

    \param pDb           [in] Database to merge changes into.
    \param sha           [in] Commit to be used as a source for merge.
    \param conflicts    [out] Array of objects having conflicts.
    \param mp            [in] Merge policy in case of a conflict.
    \param noFastForward [in] Flag that prohibits fast forward merging (when true).

    \returns False if merge was fast forward; true otherwise.
  */
  TFDLL_EXPORT bool merge(OdTvDbDatabase* pDb, const OdTvTfDigest& sha, OdHandleArray& conflicts,
    OdTvTfMergePolicy mp = kOdTfMergePreferTheirs, bool noFastForward = false);

  /** \details
    Merges changes from the repository to the database. Merge operation does not
    automatically commit changes, only runtime database is changed.

    Adds the source commit as a tracked merge parent for this drawing. This
    makes the source commit as a parent when committing the changes to the
    repository.

    \remarks
    If the merge was fast forward, no merge commit is necessary.
    If the "noFastForward" flag is true, and the remote branch is directly above
    or below this one in the commit graph, the function does nothing.

    \param pDb           [in] Database to merge chances into.
    \param reference     [in] Reference to be used as a source for merge.
    \param conflicts    [out] Array of objects having conflicts.
    \param mp            [in] Merge policy in case of a conflict.
    \param noFastForward [in] Flag that prohibits fast forward merging (when true).

    \returns False if merge was fast forward; true otherwise.
  */
  TFDLL_EXPORT bool merge(OdTvDbDatabase* pDb, const OdString& reference, OdHandleArray& conflicts,
    OdTvTfMergePolicy mp = kOdTfMergePreferTheirs, bool noFastForward = false);

  /** \details
    Returns the name of the current working branch.

    \param pDb   [in] Database to get the working branch from.
    \param head [out] Hash code of the branch head commit.

    \remarks
    If no revision control storage is associated with the database, returns
    OdString::kEmpty.

    \returns Current working branch name.
  */
  TFDLL_EXPORT OdString getLocalBranch(OdTvDbDatabase* pDb, OdTvTfDigest* head = 0);

  /** \details
    Updates the database to the revision on the tip of the specified branch and
    makes this branch default for commits. All uncommitted changes in the runtime
    database will be lost. This behavior can be modified by setting the "hard"
    flag. If "hard" is set to false and there are non-committed changes in the
    database, operation will fail. If "hard" is true (default), all
    non-committed changes will be lost.

    \param pDb        [in] Database which storage to switch the branch in.
    \param branchName [in] Name of the branch to switch to.
    \param hard       [in] Flag that defines the behavior of the function if
                           there are non-committed changes in the database.
  */
  TFDLL_EXPORT void switchBranch(OdTvDbDatabase* pDb, const OdString& branch, bool hard = true);

  /** \details
    Gets a list of objects that were changed since the last commit.

    \param pDb [in] Database to get the list of changes.
    \returns An array of object IDs.
  */
  TFDLL_EXPORT OdTvDbObjectIdArray getLocalChanges(OdTvDbDatabase* pDb);


  /** \details
    Creates a new OdStreamBufPtr with compressed data from the OdTvTfStorage
    linked to the OdTvDbDatabase.

    \param pDb [in] Database linked to the OdTvTfStorage.
    \returns New storage stream buffer.
  */
  TFDLL_EXPORT OdStreamBufPtr compressData(OdTvDbDatabase* pDb);

  /** \details
    Loads objects from the storage if earlier a partial checkout was performed.

    \remarks
    This function is designed to run in a separate thread.

    \param pDb      [in] Database to load objects to.
    \param pObjects [in] Iterator that contains a list of objects to be loaded.
    \param pReactor [in] Reactor for multi-threaded loading. Optional.
  */
  TFDLL_EXPORT void loadObjects(OdTvDbDatabase* pDb, OdTvDbObjectIterator* pObjects, OdMTLoadReactor* pReactor = 0);

  /** \details
    Begins partial import of the database into the revision control storage if
    the full import cannot be performed or not needed.

    \remarks
    Branch name and commit information are default.

    \param pStream [in] Stream, associated with the storage.
    \param pDb     [in] Database to be imported to the storage.
  */
  TFDLL_EXPORT void beginPartialImport(OdStreamBuf* pStream, OdTvDbDatabase* pDb);

  /** \details
    Imports an object to the storage.

    \remarks
    Used only with beginPartialImport() and endPartialImport().

    \param id               [in] ID of the object to be imported to the storage.
    \param pageObjectToDisk [in] If true (default) flushes the stream buffer to
                                 the file after importing the object.
  */
  TFDLL_EXPORT void writeObjectPartial(OdTvDbObjectId id, bool pageObjectToDisk = true);

  /** \details
    Ends the partial import to the revision control storage creating a first
    revision.

    \param pDb [in] Database to end the partial import.
  */
  TFDLL_EXPORT void endPartialImport(OdTvDbDatabase* pDb);

  /** \details
    Gets a list of handles of the objects that differ between revisions.
    Revisions may actually be unrelated.

    \param pDb         [in] Database which storage to get the list of differences from.
    \param newRevision [in] Hash code of the first revision.
    \param oldRevision [in] Hash code of the second revision.
    \param result     [out] List of changes, containing IDs of objects that differ between revisions.
  */
  TFDLL_EXPORT void getRevisionDifference(OdTvDbDatabase* pDb, const OdTvTfDigest& newRevision, const OdTvTfDigest& oldRevision, ChangeList& result);
}

/** \details
  This structure represents the low level storage of drawing revisions.
*/
struct TFDLL_EXPORT OdTvTfStorage : public OdRxObject
{
  /** \details
    Destroys the OdTvTfStorage object.
  */
  ~OdTvTfStorage();

  /** \details
    Open an existing .dsf storage or create a new .dsf storage without history
    tracking.

    \param pStream  [in] Stream, associated with the storage.
    \param pHostApp [in] Platform specific host application services.

    \returns Pointer to the repository object corresponding to the storage.
  */
  //static OdTvTfStoragePtr createObject(OdStreamBuf* pStream, OdTvDbHostAppServices* pHostApp);

  /** \details
    Stores a .dwg database into the .dsf storage. Can be used for both the
    initial import in the repository or for integrating changes made by third
    party editors.

    The returned hash is the only way to access the stored revision of the
    drawing. There is no way to retrieve the hash of an existing revision,
    as such the hash should be stored by other external means.

    \param pDb           [in] Database to be stored in the storage.
    \param objectsToSave [in] List of objects to be saved. Optional.
                              Used to perform a partial revision.

    \returns Hash ID of the created revision in the storage.
  */
  OdTvTfDigest store(OdTvDbDatabase* pDb, const OdTvDbObjectIdArray* objectsToSave = 0);

  /** \details
    Retrieves a drawing database from the storage. The database is checked out
    from a specific revision from the storage. If "partial" is false, all the
    objects are loaded in memory. If they will be eventually loaded anyway, it
    is much faster not to set "partial" flag to true.

    \param sha     [in] Source revision to check out a database from.
    \param partial [in] Flag that determines whether all the objects are loaded
                        in memory (false) or not (true).

    \returns Pointer to the database corresponding to the checked out state.
  */
  OdTvDbDatabasePtr retrieve(const OdTvTfDigest& sha, bool partial = false);

  /** \details
    Merges changes from the repository to the database. Merge operation does not
    automatically save the changes, only runtime database is changed.

    \param pDb        [in] Database to merge into.
    \param head       [in] Revision which the database was loaded from.
    \param remote     [in] Revision to be used as a source for the merge.
    \param ancestor   [in] Common ancestor revision for head and remote.
    \param conflicts [out] Array of objects having conflicts.
    \param mp         [in] Merge policy in case of a conflict.
  */
  void merge(OdTvDbDatabase* pDb,
    const OdTvTfDigest& head, const OdTvTfDigest& remote, const OdTvTfDigest& ancestor,
    OdHandleArray& conflicts, OdTvTfMergePolicy mp = kOdTfMergePreferTheirs);

  /** \details
    Collects all the changes since the "from" set of revisions to the "to" set
    of revisions. Together with applyPatch() it is designed to transfer changes
    between storages.

    The "from" set of revisions is considered available in the remote storage.
    The "to" set of revisions are the revisions that need to be made available
    on the remote. Also "to" must contain hashes "from". Each names a single
    revision to be included. So, if all revisions of a branch need to be
    included, then each revision from that branch needs to be included in the
    "to" set.

    Consider the following example scenarios:

    Remote:        -- C7
                 /
    C0 -- C1 -- C2 -------- C5 -- C6
           \                /     ^
             -- C3 -- C4 --     master

    Local:    master
                v
    C0 -- C1 -- C2
           \
             -- C3
                ^
             branch1

    If the local storage has revision C3 and wants to update to head of master,
    it makes a request to the remote 'update({C3}, {master})' which is
    translated on the remote to 'makePatch({C3}, {C6})'. This will only include
    the differences between revision C3 and revision C6 into the patch {C3, C4, C5, C6}.

    If the local repository has two branches up to C2, C3 (C0, C1, C2, C3) and
    wants to pull the remote changes up to C6, it makes a request to the remote
    'pull({C2, C3}, master)' which is translated on the remote to
    'makePatch({C0, C1, C2, C3}, {C2, C3, C4, C5, C6, C7})'. This will include
    all objects from C2, C3, C4, C5, C6 and C7 in the patch not already
    available in any of the local branches.
    C2, C3 must be included in the patch. Reason: the local storage stores C2,
    C3 without compression. But on the remote storage revisions, that are not
    branch head revisions, will be compressed {C0, C1, C2, C3, C4, C5}.
    Patch in the local storage replaces not compressed {C2, C3} to compressed.
    C7 must be included because it branched from C2.

    This can also be used for the initial clone of a repository by making a
    request to the remote 'pull({}, master)' which is thus translated to
    'makePatch({}, {C0, C1, C2, C3, C4, C5, C6, C7})'
    'update({}, {master})' which only includes all objects for C6 in the patch.

    \param from [in] Set of revision hashes for the starting revisions.
    \param to   [in] Set of revision hashes for the ending revisions.
    \param refs [in] Set of references to be included in the patch.

    \returns Pointer to a stream buffer associated with the patch file.
  */
  OdStreamBufPtr makePatch(OdTvDbDatabase* pDb,
    const OdTvTfDigestArray& from, const OdTvTfDigestArray& to,
    const OdTvTfRevisionControl::ReferenceList& refs = OdTvTfRevisionControl::ReferenceList()) const;

  /** \details
    Applies a patch created by makePatch() on a storage to get all the changes
    contained in the patch file transfered to the storage.

    \remarks
    applyPatch() will fail if any if the path required revisions is not
    available in the storage (makePatch() "from" parameter).

    \param s      [in] Stream buffer associated with the patch file.
    \param roots [out] Set of root objects created by the patch
                       (makePatch() "to" parameter).
    \param refs  [out] Set of references included in the patch. These won't be
                       set on the storage yet and thus require further
                       processing.
  */
  void applyPatch(OdStreamBuf* s,
    OdTvTfDigestArray& roots, OdTvTfRevisionControl::ReferenceList& refs);

  /** \details
    Gets a list of handles of the objects that differ between revisions.
    Revisions may actually be unrelated.

    \param newRevision [in] Hash code of the first revision.
    \param oldRevision [in] Hash code of the second revision.
    \param result     [out] A list of changes, containing IDs of objects that
                            differ between revisions.
  */
  void getRevisionDifference(const OdTvTfDigest& newRevision,
    const OdTvTfDigest& oldRevision, OdTvTfRevisionControl::ChangeList& result) const;

  /** \details
    Retrieves the stream associated with the storage.

    \returns Sream associated with the storage.
  */
  OdStreamBufPtr getStorageStream() const; 

  /** \details
    Writes a branch with its hash.

    \param refName [in] Branch name.
    \param sha     [in] Branch hash.
  */
  void setReference(const OdString& refName, const OdTvTfDigest& sha);

  /** \details
    Writes a set of branches with their hashes.

    \param branches [in] Set of branches with their hashes.
  */
  void setReference(const OdTvTfRevisionControl::ReferenceList& branches);

  /** \details
    Returns the hash of the specified branch.

    \param refName [in] Branch name.
    \param sha    [out] Hash code of the branch head commit.

    \returns False if the specified branch does not exist; true otherwise.
  */
  bool getReference(const OdString& refName, OdTvTfDigest& sha) const;

  /** \details
    Gets a set of branch names and their hashes from the repository.

    \param refs [out] Container with branches and their hashes.
  */
  void getReferences(OdTvTfRevisionControl::ReferenceList& refs) const;

  OdTvTfDigest applyPatchExtended(OdTvDbDatabase* pDb, OdStreamBufPtr& pPath, OdTvTfDigest shaRevision);
  OdStreamBufPtr makePatchExtended(OdTvDbDatabase* pDb);
protected:
  // Internal implementation not writing a header section. To be used in derived
  // makePatch() implementations.
  void makePatch(OdTvDbDatabase* pDb, OdStreamBuf* s,
    const OdTvTfDigestArray& from, const OdTvTfDigestArray& to,
    const OdTvTfRevisionControl::ReferenceList& refs) const;

  protected:
    friend struct OdTvTfStorageImpl;
    friend void OdTvTfRevisionControl::beginPartialImport(OdStreamBuf* pStream, OdTvDbDatabase* pDb);
    OdTvTfStorageImpl* m_pImpl;
};

/** \details
  Storage of drawing revisions with history tracking. Drawing databases checked
  out from this repository will have check out tracking information associated
  with it (branch tracking, parent commit, merge tracking, etc.).
*/
class TFDLL_EXPORT OdTvTfRepository : public OdTvTfStorage
{
public:
  /** \details
    Opens an existing .dsf storage or creates a new .dsf storage.

    \param pStream  [in] Stream associated with the storage.
    \param pHostApp [in] Platform specific host application services.

    \returns Pointer to the repository object corresponding to the storage.
  */
  static OdTvTfRepositoryPtr createObject(OdStreamBuf* pStream, OdTvDbHostAppServices* pHostApp);

  /** \details
    Initializes a storage after creation by
    OdTvTfRepository::createObject(OdStreamBuf*, OdTvDbHostAppServices*).

    \param isNewStorage [in] True to create a new storage.
  */
  void init(const bool isNewStorage);

  /** \details
    Commit a .dwg database into the .dsf repository. Can be used for both the
    initial import in the repository or for integrating changes made by third
    party editors.

    The parameter "parents" specifies the parent commits for which this database
    state is considered the next revision. "Parents" is empty for an initial
    commit, contains a single commit for a regular revision, or contains
    multiple commits for a merge revision.

    Importing does not update any references/branches so the returned hash must
    be stored as a reference, otherwise the commit will become inaccessible.

    \param pDb           [in] Database to be imported to the storage.
    \param parents       [in] Parent commits of the imported database.
    \param message       [in] Commit information.
    \param objectsToSave [in] List of objects to be saved. Optional.
                              Used to perform a partial commit.

    \returns Hash ID of the created commit in the repository.
  */
  OdTvTfDigest commit(OdTvDbDatabase* pDb, const OdTvTfDigestArray& parents,
    const OdTvTfCommitAnnotation& message = OdTvTfCommitAnnotation(),
    const OdTvDbObjectIdArray* objectsToSave = 0);

  /** \details
    The initial import to store a .dwg database into the .dsf storage. 

    \param pDb         [in] Database to be stored in the storage.
    \param localbranch [in] Branch to be set as current for commits.

    \returns Hash ID of the created commit in the repository.
  */
  OdTvTfDigest import(OdTvDbDatabase* pDb, const OdString& localbranch);
  OdTvTfDigest importReferencedDatabase(OdTvDbDatabase* pDb, const OdString& localbranch);

  /** \details
    Reads a database from the repository. The database is checked out from a
    specific revision from the repository. A "localBranch" sets a default branch
    for commit. If "localBranch" is an empty string, the database will be
    detached from any branch. If "partial" is false, all the objects are loaded
    in memory. If they will be eventually loaded anyway, it is much faster not
    to set "partial" flag to true.

    \param sha         [in] Source commit to check out a database from.
    \param localBranch [in] Branch to be set as current for commits.
    \param partial     [in] Flag that determines whether all the objects are
                            loaded in memory (false) or not (true).

    \returns Pointer to the database corresponding to the checked out state.
  */
  OdTvDbDatabasePtr checkout(const OdTvTfDigest& sha, const OdString& localBranch,
    bool partial = false);

  /** \details
    Convenience checkout() method using a reference as a source.

    \param reference   [in] Source branch to check out a database from.
    \param localBranch [in] Branch to be set as current for commits.
    \param partial     [in] Flag that determines whether all the objects are
                            loaded in memory (false) or not (true).

    \returns Pointer to the database corresponding to a checked out state.
  */
  OdTvDbDatabasePtr checkout(const OdString& reference, const OdString& localBranch, bool partial = false);

  /** \details
    Convenience checkout() method using a branch for both as source and as
    current branch for commits.

    \param branch  [in] Branch for both source and to be set as current for
                        commits.
    \param partial [in] Flag that determines whether all the objects are
                        loaded in memory (false) or not (true).

    \returns Pointer to the database corresponding to a checked out state.
  */
  OdTvDbDatabasePtr checkout(const OdString& branch, bool partial = false);

  /** \details
    Same as OdTvTfStorage::makePatch() but for commits instead of revisions and
    all intermediate commits along the branch(es) are automatically included.

    \param from [in] Set of commit hashes for the starting commits.
    \param to   [in] Set of commit hashes for the ending commits.
    \param refs [in] Set of references to be included in the patch.

    \returns Pointer to the stream buffer associated with the patch file.
  */
  OdStreamBufPtr makePatch(
    const OdTvTfDigestArray& from, const OdTvTfDigestArray& to,
    const OdTvTfRevisionControl::ReferenceList& refs = OdTvTfRevisionControl::ReferenceList()) const;

  /** \details
    Same as OdTvTfStorage::makePatch() but for commits instead of revisions and
    all intermediate commits along the branch(es) are automatically included.

    \param from [in] Set of commit hashes for the starting commits.
    \param to   [in] Commit hash of the end commit.
    \param refs [in] Set of references to be included in the patch.

    \returns Pointer to the stream buffer associated with the patch file.
  */
  OdStreamBufPtr makePatch(
    const OdTvTfDigestArray& from, const OdTvTfDigest& to,
    const OdTvTfRevisionControl::ReferenceList& refs = OdTvTfRevisionControl::ReferenceList()) const;

  /**
    Reads from the storage a structure describing relationships of a commit in
    the revision control database.

    \param sha [in] Commit hash.

    \returns Structure describing a commit relationships in the revision control
    database.
  */
  OdTvTfCommitInfo getCommitInfo(const OdTvTfDigest& sha) const;

  /**
    Writes to the storage a structure describing relationships of a commit in
    the revision control database.

    \param commitInfo [in] Structure describing relationships of a commit in the
                           revision control database.

    \returns Hash of the write commit.
    \remarks
    Also the hash of the write commit is stored in the current OdTvTfCommitInfo
    structure (OdTvTfCommitInfo::hash field in the commitInfo parameter).
  */
  OdTvTfDigest writeCommitInfo(OdTvTfCommitInfo& commitInfo);
};

#endif //_TFREVISIONCONTROL_H_INCLUDED_
