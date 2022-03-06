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

#ifndef _SVGEXPORT_H_INCLUDED_
#define _SVGEXPORT_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
  SVG export device is derived from OdGsDevice. It is used for saving 
  DWG drawings in SVG format.

  Remarks:
  Before calling OdGsDevice::update(), OnSize() must be called,
    setting device output rectangle.
  
  SvgExport device supports following properties:

  * "Output" - of type OdStreamBuf, must be set to output stream.
  * "LineWeightScale" - size of pixel in device units, used for scaling lineweights.
  * "ImageBase" - path where to copy images 
      (if not set, absolute file paths are written to svg)
  * "ImageUrl" - prefix, to prepend to image name 
      (eg: "http://www.mysite.com/images/", or "../images/")
  * "DefaultImageExt" - default extension for the embedded images (png)
  * "ShxLineWeight" - line weight of shx font output (default 0.05)
  * "Precision" - number of decimal digits in doubles 
      (as in printf("%.9g",...) - 9 digits ), default = 6
  * "BackGround" (ODCOLORREF) - if set to non-white a rectangle of given color 
      will be drawn behind the drawing, simulating background.
  * "GenericFontFamily" - font to substitute if correct is missing,
      following generic font families are supported in SVG:
      "serif", "sans-serif", "cursive", "fantasy", "monospace"
  * "Tolerance" - rendering deviation (default 0.5)
  * "UseHLR" - Use hidden line removal in rendering (false by default)
  * "EnableGouraudShading" - Gradients are rendered via Gouraud-shaded triangles (true by default) 
  * "ExplodeShxTexts" - SHX texts are represented as lines & curves (true by default)
  * "RemoveFirstSpacesOfText" Skip initial spaces when rendering text strings (true by default)
  * "ColorPolicy" - 0 = Colors are unchanged, 1 = Drawing is converted to monochrome, 2 = Drawing is converted to grayscale
  * "MinimalWidth" - minimal line width in SVG, so that lineweight scaling would not produce invisible lines (default 0.05)
*/

#endif
