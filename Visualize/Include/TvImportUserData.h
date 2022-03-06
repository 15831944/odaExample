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

#ifndef _ODTV_IMPORTUSERDATA_H_INCLUDED_
#define _ODTV_IMPORTUSERDATA_H_INCLUDED_

#include "TD_PackPush.h"

#include "OdaCommon.h"
#include "OdStreamBuf.h"

#include "Ge/GePoint2d.h"
#include "Tv.h"

#define OdTvDWGUserData         L"Dwg2Visualize - ODA"

/** \details
  The structure for storing the DWG specific layout parameters, which can be used during export through PE.
*/
struct ODTV_EXPORT OdTvDwgLayoutData
{
public:

  OdString  m_strPaperName;                   // Paper space name.
  OdUInt16  m_iPaperUnits;                    // Measurement units for the paper space.

  double    m_dPrinterWidth;                  // Width for printing.
  double    m_dPrinterHeight;                 // Height for printing.

  double      m_dOffsetX;                     // Layout offset by the x-axis.
  double      m_dOffsetY;                     // Layout offset by the y-axis.
  OdGePoint2d m_paperImageOrigin;             // Origin of a paper space.

  double m_dLeftMargin;                       // Margin from the left border
  double m_dRightMargin;                      // Margin from the right border
  double m_dTopMargin;                        // Margin from the top border
  double m_dBottomMargin;                     // Margin from the bottom border

  OdInt16 m_plotType;      // Plot type
  OdInt16 m_plotRot;   // Plot rotation

  //scale parameters
  double  m_dStdScale;                        // Standard layout scale
  double  m_dCustomScaleNumerator;            // Numerator in the scale ratio. Specifies the number of inches or mm for the scale.
  double  m_dCustomScaleDenominator;          // Denominator in the scale ratio. Specifies the number of drawing units for the scale.

  // Corners of the plot window area
  double m_dXmin;                             // coordinate of the lower - left corner.
  double m_dYmin;                             // coordinate of the lower - left corner.
  double m_dXmax;                             // coordinate of the upper - right corner.
  double m_dYmax;                             // coordinate of the upper - right corner.
  
  OdInt16   m_shadePlot;                      // shading mode for plot


  /** \details
    Layout-specific properties.
  */
  enum Properties
  {
    kModelSpace = (1 << 0),                   // Defines that model space is used.
    kScaledToFit = (1 << 1),                  // Defines that layout should be scaled to fit the contents.
    kCentered = (1 << 2),                     // Defines that layout should be centered regarding contents.
    kUseStandardScale = (1 << 3),             // Defines that standard scale should be used.
    kPrintLineweights = (1 << 4),             // Defines that linewieghts should be printed in this layout.
    kPlotHidden = (1 << 5),                   // Defines that hidden content should be plotted.
    kScaleLineWeights = (1 << 6),             // Defines that lineweights can be scaled.
    kPlotPlotstyles = (1 << 7)                // Defines plot styles.
  };

  OdUInt16    m_PlotLayoutFlags;              // Plot layout flags.
  OdString    m_strCurStyleSheet;             // String that represents a name of a currently used style sheet.

  /** \details
    Default constructor for the OdTvDwgLayoutData structure. Creates structure
    with a set of properties initialized:
    <table>
    Name                                Value
    m_PlotLayoutFlags                   kModelSpace | kUseStandardScale | kPrintLineweights
    m_strPaperName                      "" (blank)
    m_iPaperUnits                       OdTvDbPlotSettings::kMillimeters
    m_dPrinterWidth                     215.9
    m_dPrinterHeight                    279.4
    m_dOffsetX                          0.0
    m_dOffsetY                          0.0
    m_paperImageOrigin                  OdGePoint2d(0.0, 0.0)
    m_dLeftMargin                       7.5
    m_dRightMargin                      7.5
    m_dTopMargin                        20.0
    m_dBottomMargin                     20.0
    m_plotType                          OdTvDbPlotSettings::kLayout
    m_plotRot                           OdTvDbPlotSettings::k0degrees
    m_dXmin                             0.0
    m_dYmin                             0.0
    m_dXmax                             0.0
    m_dYmax                             0.0
    m_dStdScale                         1.0
    m_dCustomScaleNumerator             1.0
    m_dCustomScaleDenominator           1.0
    m_shadePlot                         0  
    </table>
  */
  OdTvDwgLayoutData();
  
  /** \details
    Reads layout-specific properties from the stream buffer.
    
    \param strm [in] Pointer to a stream buffer to read the properties from.
  */
  void read(OdStreamBuf* strm);
  
  /** \details
    Writes layout-specific properties to the specified stream buffer.
    
    \param strm [in] Pointer to a stream buffer to write the data to.
  */
  void write(OdStreamBuf* strm);
};

/** \details
  The structure for storing the DWG specific view parameters, which can be used during export through PE.
*/
struct ODTV_EXPORT OdTvDwgViewData
{
  /** \details
    View types.
  */
  enum Type
  {
    kModel = 0,               // models space view
    kUnderlayingPaper = 1,    // underlaying view with paper
    kPaper = 2,               // main paper space view
    kViewport = 3             // paper space viewports 
  };

  Type        m_type;         // view type
  OdGePoint3d m_target;       // isn't used for the m_type = kViewport
  OdInt16     m_shadePlot;    // shading mode for plot (used only for the m_type = kViewport)
  bool        m_bPlotHidden;  // use hidden for plot  (used only for the m_type = kViewport)

  /** \details
    Default constructor for the OdTvDwgViewData structure. Creates structure
    with m_type set to kModel, m_target set to OdGePoint3d::kOrigin, m_shadePlot set to 0
    and m_bPlotHidden set to false.
  */
  OdTvDwgViewData();

  /** \details
    Reads view-specific properties from the stream buffer.
    
    \param strm [in] Pointer to a stream buffer to read the properties from.
  */
  void read(OdStreamBuf* strm);
  
  /** \details
    Writes view-specific properties to the specified stream buffer.
    
    \param strm [in] Pointer to a stream buffer to write the data to.
  */
  void write(OdStreamBuf* strm);
};

/** \details
  The structure for storing the DWG specific database parameters, which can be used during export through PE.
*/
struct ODTV_EXPORT OdTvDwgDbData
{
  /** \details
    Properties for the imported DWG database parameters.
  */
  enum Properties
  {
    kDisplaySilhouettes = (1 << 0),   // Only silhouettes of drawables are displayed.
  };

  OdUInt16    m_prop;                 // Stores import properties.
  OdUInt16    m_iMeasurement;         // Represents the measurement systems. 0 - english system, 1 - metric system
  OdUInt16    m_insUnits;             // INSUNITS specifies the drawing units used in the automatic scaling of blocks, Xrefs, and images 

  /** \details
    Default constructor for the OdTvDwgDbData structure. Creates structure
    with m_prop and m_iMeasurement members set to 0.
  */
  OdTvDwgDbData();

  /** \details
    Reads database-specific properties from the stream buffer.
    
    \param strm [in] Pointer to a stream buffer to read the properties from.
  */
  void read(OdStreamBuf* strm);
  
  /** \details
    Writes database-specific properties to the specified stream buffer.
    
    \param strm [in] Pointer to a stream buffer to write the data to.
  */
  void write(OdStreamBuf* strm);
};

#include "TD_PackPop.h"

#endif // _ODTV_IMPORTUSERDATA_H_INCLUDED_
