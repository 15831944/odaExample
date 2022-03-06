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

#ifndef COLORMAPPING_DEFINED
#define COLORMAPPING_DEFINED

#include "OdPlatform.h"

// Background is dark if  Red < 128 && Green < 128 && Blue < 128
// Background is light if  Red > 127 || Green > 127 || Blue > 127
/** \details
	Checks whether the background is light.

	\param backgroung [in] The background as an ODCOLORREF value.
	\returns The true value if the background is light, or false if the background is dark.
	\remarks
	Returns true if Red < 128 && Green < 128 && Blue < 128.
	Returns false if Red > 127 || Green > 127 || Blue > 127.
 */
inline bool odcmIsBackgroundLight(ODCOLORREF backgroung)
{
  return (ODGETRED(backgroung) >= 128 ||
					ODGETGREEN(backgroung) >= 128 ||
					ODGETBLUE(backgroung) >= 128);
}

//DD:EXPORT_ON

// Returns palette for dark background
/** \details
	Gets the palette for a dark background.

	\returns The palette for the dark background.
*/
FIRSTDLL_EXPORT const ODCOLORREF * odcmAcadDarkPalette();

// Returns palette for light background
/** \details
	Gets the palette for a light background.

	\returns The palette for the light background.
*/
FIRSTDLL_EXPORT const ODCOLORREF * odcmAcadLightPalette();

// Returns palette for printing
/** \details
	Gets the palette for printing.

	\returns The palette for printing.
*/
FIRSTDLL_EXPORT const ODCOLORREF * odcmAcadPlotPalette();

// Returns palette for given background
/** \details
	Gets the palette for a given background.

	\returns The palette for the given background.
*/
FIRSTDLL_EXPORT const ODCOLORREF * odcmAcadPalette(ODCOLORREF backgr);


// Returns RGB for given color index
// pPalette - palette to perform mapping
/** \details
	Gets the RGB values for a given color index.

	\param pPalette [in] Palette to perform mapping.
	\returns RGB valued for the given color index.
 */
FIRSTDLL_EXPORT ODCOLORREF odcmLookupRGB(int index, const ODCOLORREF* pPalette);

// Returns color index for given RGB
// pPalette - palette to perform mapping
/** \details
	Gets the color index for a given RGB.

	\param rgb [in] RGB to perform mapping.
	\param pPalette [in] Palette to perform mapping.
	\returns Color index for the given RGB.
 */
FIRSTDLL_EXPORT int odcmLookupACI(ODCOLORREF rgb, const ODCOLORREF* pPalette);

//DD:EXPORT_OFF

#endif	// COLORMAPPING_DEFINED
