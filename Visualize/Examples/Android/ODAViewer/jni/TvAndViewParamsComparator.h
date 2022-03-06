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

#ifndef TVANDVIEWPARAMSCOMPARATOR_H
#define TVANDVIEWPARAMSCOMPARATOR_H

#include "TvGsView.h"

class TvAndViewParamsComparator
{
public:
    TvAndViewParamsComparator()
    : viewPos(0., 0., 0.), viewTarget(0., 0., 0.)
    , viewUpVect(0., 0., 0.), viewFieldWidth(0.), viewFieldHeight(0.)
    { };
    
    TvAndViewParamsComparator(const OdTvGsViewId& viewId)
    : viewPos(0., 0., 0.), viewTarget(0., 0., 0.)
    , viewUpVect(0., 0., 0.), viewFieldWidth(0.), viewFieldHeight(0.)
    {
        if(!viewId.isNull())
        {
            OdTvGsViewPtr pView = viewId.openObject();
            if(!pView.isNull())
            {
                viewPos = pView->position();
                viewTarget = pView->target();
                viewUpVect = pView->upVector();
                viewFieldWidth = pView->fieldWidth();
                viewFieldHeight = pView->fieldHeight();
            }
        }
    };
    ~TvAndViewParamsComparator(){};
    
    bool operator!=(const TvAndViewParamsComparator& params) const
    {
        if (viewPos != params.viewPos)
            return true;
        
        if (viewTarget != params.viewTarget)
            return true;
        
        if (viewUpVect != params.viewUpVect)
            return true;
        
        if (viewFieldWidth != params.viewFieldWidth)
            return true;
        
        if (viewFieldHeight != params.viewFieldHeight)
            return true;
        
        return false;
    }
    
public:
    OdTvPoint viewPos;
    OdTvPoint viewTarget;
    OdTvVector viewUpVect;
    double viewFieldWidth;
    double viewFieldHeight;
};


#endif //TVANDVIEWPARAMSCOMPARATOR_H
