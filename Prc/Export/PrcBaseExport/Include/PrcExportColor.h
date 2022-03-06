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

#ifndef ODPRCEXPORTCOLOR
#define ODPRCEXPORTCOLOR

#include "PrcCommon.h"
#include "Pdf2PrcExportParams.h"

/** \details 
Retrieves the current entity material.
\param params    [in] A set of export parameters.
\param pDrawable [in] A raw pointer to a drawable entity.
\returns A raw pointer to an OdDbStub object that contains information about the material.
*/
OD_TOOLKIT_EXPORT OdDbStub * getCurrentEntityMaterial(const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable);

/** \details 
Saves the current true color to a specified export context object.
\param context   [out] A placeholder for the context object where the color value should be saved.
\param params    [in] A set of export parameters where the color value for saving is allocated.
\param pDrawable [in] A raw pointer to a drawable entity.
\remarks 
The function saves the color value in the passed context object and returns it to a calling subroutine.
*/
OD_TOOLKIT_EXPORT void saveCurrentTrueColor(OdPrcExportContext &context, const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable);

/** \details 
Saves the current material to a specified export context object.
\param context   [out] A placeholder for the context object where the material object should be saved.
\param params    [in] A set of export parameters where the material object for saving is allocated.
\param pDrawable [in] A raw pointer to a drawable entity.
\remarks 
The function saves the material object in the passed context object and returns it to a calling subroutine.
*/
OD_TOOLKIT_EXPORT void saveCurrentEntityMaterial(OdPrcExportContext &context, const PDF2PRCExportParams &params, const OdGiDrawable * pDrawable);

#endif //ODPRCEXPORTCOLOR
