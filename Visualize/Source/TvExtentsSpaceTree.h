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

#ifndef _ODTV_EXTENTSSPACETREEBASE_H_INCLUDED_
#define _ODTV_EXTENTSSPACETREEBASE_H_INCLUDED_

#include "TD_PackPush.h"

#include "Tv.h"
#include "OdList.h"
#include "GiPathNode.h"
#include "DbObjectId.h"
#include "TvGeometryDataImpl.h"
#include "GiDrawableSelectPE.h"
#define STL_USING_VECTOR
#include "OdaSTL.h"


#define ODTV_NUM_AXIS 3

class OdTvExtentsSpaceTreeBase;

class OdTvExtentsSpaceNode
{
public:
  //constructor
  OdTvExtentsSpaceNode(OdTvExtentsSpaceNode* pParent, OdTvExtents3d& extents, int nDepth);

  //destructor
  virtual ~OdTvExtentsSpaceNode();

  // methods
  // check that the node is leave
  virtual bool isLeave() const;

  //set/get the depth of the node
  virtual void setDepth(int depth);
  virtual int getDepth() const;

  // retrieve the stored objects list
  virtual OdVector<OdUInt64, OdMemoryAllocator<OdUInt64> >* getObjecsPtr();

  //retrieve extents of node
  const OdTvExtents3d& getExtents() const;

  //set/get parent
  virtual void setParent(OdTvExtentsSpaceNode* pNode);
  virtual OdTvExtentsSpaceNode* getParent() const;

  //set/get left child
  virtual void setLeftChild(OdTvExtentsSpaceNode* pNode);
  virtual OdTvExtentsSpaceNode* getLeftChild() const;

  //set/get right child
  virtual void setRightChild(OdTvExtentsSpaceNode* pNode);
  virtual OdTvExtentsSpaceNode* getRightChild() const;

  // send objects to reactor
  virtual OdUInt32 sendObjectsToReactor(OdGiDrawablePESelectionReactor* pSelectionReactor, const OdGeMatrix3d& transform,
                                        OdTvExtentsSpaceTreeBase* pTree, bool bNeedEyeDepth) const;

  //get memory used for this node
  virtual OdUInt64 getObjectSize() const;

protected:
  // left child node (only link, not need to delete)
  OdTvExtentsSpaceNode*   m_pLeftChild;
  //right child node (only link, not need to delete)
  OdTvExtentsSpaceNode*   m_pRightChild;
  //parent node (only link, not need to delete)
  OdTvExtentsSpaceNode*   m_pParent;

  // extents of the node
  OdTvExtents3d           m_extents;

  // array of objects
  OdVector<OdUInt64, OdMemoryAllocator<OdUInt64> >      m_objects;

  // special (the power of 8 or power of 4 ) depth of the node in the tree
  int                 m_iDepth;
};

class OdTvExtentsSpaceTreeBase
{
public:

  enum
  {
    kEmpty = 0,
    kOutOfExtents = 1,
    kOutOfPoly = 2,
    kBelongPoly = 3
  };

  class SelectionContext
  {
  public:
    SelectionContext() : m_pPolyPts(NULL), m_nPolyPts(0), m_bValid(false){}

    SelectionContext(const OdGePoint2d* pPoly, OdUInt32 nPolyPts) : m_nPolyPts(nPolyPts), m_bValid(true)
    {
      m_pPolyPts = const_cast<OdGePoint2d*>(pPoly);

      // Calculate selection extents
      for (OdUInt64 i = 0; i < nPolyPts; i++)
        m_selectionExtents.addPoint(*(pPoly + i));
    }

    OdGePoint2d*  m_pPolyPts;
    OdUInt32      m_nPolyPts;
    OdGeExtents2d m_selectionExtents;
    bool          m_bValid;
  };

  //constructor
  OdTvExtentsSpaceTreeBase(OdTvGeometryDataImpl* pParentGeometry, OdUInt64 iMaxDepth, OdUInt64 iMaxNodeObjects);

  //destructor
  virtual ~OdTvExtentsSpaceTreeBase();

  //build the tree (the correctness of the incoming extents should check the caller)
  virtual void buildTree(OdTvExtents3d& extents, OdUInt64 iDepth = 2);

  // reset the tree
  virtual void reset();

  //process object
  virtual void addObject(OdUInt64 object, const OdGeTol& tol = OdGeContext::gTol);

  // retrieve the leaves nodes
  virtual OdList<OdTvExtentsSpaceNode*>* retrieveLeaves();

  //retrieve the root node
  OdTvExtentsSpaceNode* getRootNode() const;

  //retrieve the extents of the root node
  virtual bool getRootExtents(OdTvExtents3d& exts);

  //returns the number of markers which are covered by this tree
  virtual OdUInt64 getCoveredMarkers() const { return 1; }

  //check that object is present
  virtual bool hasObject(OdUInt64 objID) const;

  //calculates the eye depth of the object
  virtual double getObjectEyeDepth(OdUInt64 objID, const OdGeMatrix3d& transform);

  //check object for belonging in the selection polygon
  virtual OdUInt32 inspectObject(OdUInt64 objID, const SelectionContext& selContext, const OdGeTol& tol,
                                 const OdGeMatrix3d& transform, double& objectEyeDepth);

  //reset marks about what object was already sent to the reactor
  virtual void resetSentMarks();

  //check that object already was sent to the reactor
  virtual bool wasSent(OdUInt64 objID) const;

  //mark that object was already sent to reactor
  virtual void markSent(OdUInt64 objID);

  //resize sent markers vector
  virtual void resizeSentMarkers() = 0;

  // Remove object from tree
  virtual void removeObject(OdUInt64 object);

  // Returns the total number of objects in the tree
  virtual OdUInt64 getObjectsNum() const = 0;

  // Clear cached matrix
  virtual void clearCache();

  // Get matrix for specifies path node
  virtual OdTvMatrix getTransformMatrix(const OdGiPathNode& pathNode);

  // Update transform matrix
  virtual void updateTransform();

  // Set transform matrix
  virtual void setTransformMatrix(const OdTvMatrix& transform);

  // find objects which fit the selection context conditions and send them to the selection reactor
  virtual OdUInt32 query(OdTvExtentsSpaceNode* pNode, const SelectionContext& selContext, const OdGeTol& tol,
                         const OdGeMatrix3d& transform, bool bNeedEyeDepth, OdGiDrawablePESelectionReactor* pSelectionReactor);

protected:

  // Build up tree
  virtual void buildUpTree(OdUInt64 object) = 0;

  // internal recursive method for building the tree
  virtual void constructChilds(OdTvExtentsSpaceNode* pParentNode, int axislevel, int curDepth);

  // internal recursive method for building up the tree
  virtual void buildUpBrotherAndParent(OdTvExtentsSpaceNode* pNode, int axislevel, const OdTvVector& buildDirection);

  // internal recursive method for process objects
  virtual void nodeProcessObject(OdTvExtentsSpaceNode* pNode, OdUInt64 object, const OdGeTol& tol = OdGeContext::gTol);

  // Remove object from tree
  virtual bool removeObjectFromNode(OdTvExtentsSpaceNode* pNode, OdUInt64 object, const OdGeTol& tol = OdGeContext::gTol);

  virtual bool isInExtents(OdTvExtentsSpaceNode* pNode, OdUInt64 object, bool bContains = false, const OdGeTol& tol = OdGeContext::gTol) const = 0;

  // reset matrix
  virtual void resetTransform();

  void cacheMatrix(const OdGiPathNode& pathNode);
  bool isCached(const OdGiPathNode& pathNode) const;

  // find objects which fit the selection context conditions and send them to the selection reactor
  OdUInt32 queryInternal(OdTvExtentsSpaceNode* pNode, const OdGeTol& tol, const OdGeMatrix3d& transform, bool bNeedEyeDepth, OdGiDrawablePESelectionReactor* pSelectionReactor);

  //calcualtes the size of the dynamic data for which the memory was allocated
  OdUInt64 getSizeOfDynamicData() const;

protected:
  OdTvExtentsSpaceNode* m_pRootNode;

  // list of all nodes
  OdList<OdTvExtentsSpaceNode*> m_Nodes;

  // list of all leaves
  OdList<OdTvExtentsSpaceNode*> m_Leaves;

  // Splitting when the number of objects starts to be greater than 'm_iMaxNodeObjects'
  OdUInt64          m_iMaxNodeObjects;

  // Point to geometry, which contains this tree (only link, not need to delete)
  OdTvGeometryDataImpl* m_pParentGeometry;

  // Max depth
  OdUInt64          m_iMaxDepth;

  // Transform matrix from the appropriate OdTvGeometryData and it's parent sub entities (if exists)
  OdTvMatrix            m_transformMatrix;

  // Cached path and matrix. From parent entities and/or inserts. The overall transfrom is equal to 'm_cachedTransform' * 'm_transformMatrix'
  OdArray<OdTvDbObjectId>   m_cachedPath;
  OdTvMatrix                m_cachedTransform;

  //vector where it is stored that some object already was sent to the reactor
  std::vector<OdUInt8>  m_bitsAlreadySent;

  //context with data for the selection
  SelectionContext      m_queryContext;
};



class OdTvExtentsSpaceTreeVertex : public OdTvExtentsSpaceTreeBase
{
public:
  OdTvExtentsSpaceTreeVertex(OdTvPointArray* pPointsArray, OdUInt64 iMaxDepth, OdUInt64 iMaxNodeObjects, OdTvGeometryDataImpl* pParentGeometry);
  virtual ~OdTvExtentsSpaceTreeVertex();

  // Get number of points
  virtual OdUInt64 getObjectsNum() const;

  //returns the number of markers which are covered by this tree
  virtual OdUInt64 getCoveredMarkers() const;

  //check that object is present
  virtual bool hasObject(OdUInt64 objID) const;

  //calculates the eye depth of the object
  virtual double getObjectEyeDepth(OdUInt64 objID, const OdGeMatrix3d& transform);

  //check object for belonging in the selection polygon
  virtual OdUInt32 inspectObject(OdUInt64 objID, const SelectionContext& selContext, const OdGeTol& tol,
                                 const OdGeMatrix3d& transform, double& objectEyeDepth);

  //resize sent markers
  virtual void resizeSentMarkers();

  // Get point by position
  bool getPoint(OdUInt64 objID, OdTvPoint& point) const;
  OdUInt64 getObjectSize() const;

protected:
  // Build up tree
  virtual void buildUpTree(OdUInt64 objID);

  // Check if object is in node extents
  virtual bool isInExtents(OdTvExtentsSpaceNode* pNode, OdUInt64 objID, bool bContains = false, const OdGeTol& tol = OdGeContext::gTol) const;

protected:
  // Array to points (only link, not need to delete)
  OdTvPointArray*       m_pPointsArray;
};



class OdTvExtentsSpaceTreeTriangle : public OdTvExtentsSpaceTreeBase
{
public:
  OdTvExtentsSpaceTreeTriangle(OdTvPointArray* pPointsArray, OdInt32Array* pFacesArray, OdUInt64 iMaxDepth, OdUInt64 iMaxNodeObjects, OdTvGeometryDataImpl* pParentGeometry);
  virtual ~OdTvExtentsSpaceTreeTriangle();

  //process object
  void addObject(OdUInt64 object, const OdGeTol& tol = OdGeContext::gTol);

  // Get number of points
  virtual OdUInt64 getObjectsNum() const;

  //returns the number of markers which are covered by this tree
  virtual OdUInt64 getCoveredMarkers() const;

  //check that object is present
  virtual bool hasObject(OdUInt64 objID) const;

  //calculates the eye depth of the object
  virtual double getObjectEyeDepth(OdUInt64 objID, const OdGeMatrix3d& transform);

  //check object for belonging in the selection polygon
  virtual OdUInt32 inspectObject(OdUInt64 objID, const SelectionContext& selContext, const OdGeTol& tol,
                                 const OdGeMatrix3d& transform, double& objectEyeDepth);

  //resize sent markers
  virtual void resizeSentMarkers();

  static double computeZOnTriangle(const OdGePoint2d& point2d, const OdGePoint3d& point3d1,
    const OdGePoint3d& point3d2, const OdGePoint3d& point3d3);

protected:
  // Build up tree
  virtual void buildUpTree(OdUInt64 objID);

  // Check if object is in node extents
  virtual bool isInExtents(OdTvExtentsSpaceNode* pNode, OdUInt64 objID, bool bContains = false, const OdGeTol& tol = OdGeContext::gTol) const;

protected:
  OdTvPointArray*           m_pPointsArray;
  OdInt32Array*             m_pFacesArray;
  bool                      m_bCachedObjectExtentsValid;
  OdTvExtents3d             m_currentObjectExtents;
};

#include "TD_PackPop.h"

#endif //_ODTV_EXTENTSSPACETREEBASE_H_INCLUDED_
