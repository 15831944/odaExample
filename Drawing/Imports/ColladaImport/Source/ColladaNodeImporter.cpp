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
#include "ColladaNodeImporter.h"


namespace TD_COLLADA_IMPORT
{
  NodeImporter::NodeImporter( DocumentImporter* documentImporter )
    : ImporterBase(documentImporter)
  {}

  NodeImporter::~NodeImporter()
  {}


  bool NodeImporter::importNodes( const COLLADAFW::NodePointerArray& nodes )
  {
    for ( size_t i = 0, count = nodes.getCount(); i < count; ++i)
    {
      if ( !importNode( nodes[i] ) )
        return false;
    }
    return true;
  }

  bool NodeImporter::importNode( const COLLADAFW::Node* node )
  {
    COLLADABU::Math::Matrix4 mat = node->getTransformationMatrix();
    const COLLADAFW::UniqueId& nodeUniqueId = node->getUniqueId();
    addUniqueIdFWNodePair( nodeUniqueId, node );
    const COLLADAFW::NodePointerArray& childNodes = node->getChildNodes();
    for ( size_t i = 0, count = childNodes.getCount(); i < count; ++i)
    {
      if ( !importNode( childNodes[i] ) )
      {
        return false;
      }
    }
    return true;
  }
}
