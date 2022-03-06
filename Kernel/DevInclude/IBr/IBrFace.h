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

#ifndef _INC_DDBRIMPFACE_3F82D5B5001F_INCLUDED
#define _INC_DDBRIMPFACE_3F82D5B5001F_INCLUDED

#include "IBrEntity.h"
#include "Ge/Ge.h"

class OdGeSurface;
class OdGeNurbSurface;
class OdIBrShell;
class OdIBrLoop;
class OdGeMatrix3d;
class OdGeExternalBoundedSurface;

class OdIBrFace : public OdIBrEntity
{
public:
		virtual bool getSurfaceAsNurb(OdGeNurbSurface& nurb) const = 0;

		virtual OdGeSurface* getSurface() const = 0;

    virtual bool getSurfaceType(OdGe::EntityId& type) const = 0;

		virtual bool getOrientToSurface() const = 0;

    virtual OdIBrShell *getShell() = 0;

    virtual void next(const OdIBrLoop *pFirstChild,  OdIBrLoop * & pCurChild) = 0;

    virtual bool getTrueColor(OdUInt32 &rgb) const = 0;

    virtual bool getColorIndex(OdUInt16 &indx) const = 0;

    virtual bool getMaterial(OdUInt64 &id) const = 0;

    virtual bool getMaterial(OdString &strMatName) const = 0;

    virtual bool getFillPattern(OdUInt64 &id) const { return false; }

    virtual bool getFillingAttributes(OdGePoint2d &origin, OdGeVector2d &dir) const { return false; }

    virtual bool getMaterialMapper(OdGeMatrix3d &/*mx*/, OdUInt8 &/*projection*/, OdUInt8& /*tiling*/, OdUInt8 &/*autoTransform*/) const { return false; }

    virtual bool getSurfaceAsTrimmedNurbs(OdUInt32& /*numNurbs*/, OdGeExternalBoundedSurface**& /*ppNurbs*/) const { return false; }

    virtual bool getExtraFillingAttributes(OdGiFill* pFill) const { return false; }

    virtual const OdGiFill* getFill() const { return nullptr; }

    virtual OdIBrFace* getFirstFaceRegion() const { return nullptr; }

    virtual OdIBrFace* getNextFaceRegion(const OdIBrFace* pFace) const { return nullptr; }
};

#endif /* _INC_DDBRIMPFACE_3F82D5B5001F_INCLUDED */

