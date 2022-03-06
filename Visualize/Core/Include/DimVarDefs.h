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



#ifndef BLKVAR_DEF
#define BLKVAR_DEF  VAR_DEF
#endif

#ifndef ANNOVAR_DEF
#define ANNOVAR_DEF  VAR_DEF
#endif

#ifndef ODTDB_LINEWEIGHT
#define ODTDB_LINEWEIGHT OdDb::LineWeight /*!DOM*/
#define DOUNDEF_ODTDB_LINEWEIGHT
#endif

#ifndef ODTDIST
#define ODTDIST  double /*!DOM*/
#define DOUNDEF_ODTDIST
#endif

#ifndef ODTORIENT
#define ODTORIENT  double /*!DOM*/
#define DOUNDEF_ODTORIENT
#endif

#ifndef ODTUNITLESS
#define ODTUNITLESS  double /*!DOM*/
#define DOUNDEF_ODTUNITLESS
#endif

#ifndef ODTDECSEP
#define ODTDECSEP  OdInt16 /*!DOM*/
#define DOUNDEF_ODTDECSEP
#endif

#ifndef ODTARROWBLK
#define ODTARROWBLK  OdTvDbHardPointerId /*!DOM*/
#define DOUNDEF_ODTARROWBLK
#endif

#ifndef ODTTEXTSTYLEID
#define ODTTEXTSTYLEID  OdTvDbHardPointerId /*!DOM*/
#define DOUNDEF_ODTTEXTSTYLEID
#endif


#ifndef ODTLINETYPEID
#define ODTLINETYPEID  OdTvDbHardPointerId /*!DOM*/
#define DOUNDEF_ODTLINETYPEID
#endif

#ifndef NullIdAllowed
#define NullIdAllowed true
#define DOUNDEF_NullIdAllowed
#endif


/** **********************************************
 *
 * Dimension variables definitions
*/

//          Type              Name    DXF     Default value         Metric Def Value      Reserve1   Reserve2erve2

/**
  <title DIMADEC>
  <toctitle DIMADEC>
   
  <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           –1 ... 8
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R14+
  </table>
   
  DIMADEC specifies the number of decimal places in angular dimensions. If DIMADEC == –1, the number of decimal places is
  determined by DIMDEC.
   
  <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimadec()
   OdTvDbDatabase::setDimadec()
   &nbsp; 
   OdTvDbDimension::dimadec()
   OdTvDbDimension::setDimadec()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimadec()
   OdTvDbDimStyleTableRecord::setDimadec()
  </table>
  
  \sa
  <link DIMDEC, DIMDEC>

<group TD_SysVars_D>
  */
//<dom_var_def>OdInt16 DIMADEC;
VAR_DEF(OdInt16,              adec,   179,    (0),                  (0),                  (),        TvValidateRange(0, 8))

/**
  <title DIMALT>
  <toctitle DIMALT>
   
  <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
  </table>
  
  DIMALT controls the display of alternate measurements in dimensions.
   
  <table>
   <b>Value</b>   <b>Description</b>
   false          Disabled
   true           Enabled
  </table>
   
  <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimalt()
   OdTvDbDatabase::setDimalt()
   &nbsp; 
   OdTvDbDimension::dimalt()
   OdTvDbDimension::setDimalt()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimalt()
   OdTvDbDimStyleTableRecord::setDimalt()
   </table>
   
 <group TD_SysVars_D>
 */
//<dom_var_def>bool DIMALT;
VAR_DEF(bool,                 alt,    170,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMALTD>
  <toctitle DIMALTD>
   
  <table>
   <b>Type</b>            OdUInt16
   <b>Initial value</b>   2 | 3
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
  </table>
   
   DIMALTD specifies the number of decimal places in alternate measurements in dimensions.
   
  <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimaltd()
   OdTvDbDatabase::setDimaltd()
   &nbsp; 
   OdTvDbDimension::dimaltd()
   OdTvDbDimension::setDimaltd()
   &nbsp;
   OdTvDbDimStyleTableRecord::dimaltd()
   OdTvDbDimStyleTableRecord::setDimaltd()
  </table>
 
<group TD_SysVars_D>
*/
//<dom_var_def>OdUInt16 DIMALTD;
VAR_DEF(OdUInt16,             altd,   171,    (2),                  (3),                  (),        TvValidateRange(0,8))

/**
  <title DIMALTF>
   <toctitle DIMALTF>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   25.4 | (1.0 / 25.4)
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMALTF specifies the distance multiplier for alternate
   measurements in dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimaltf()
   OdTvDbDatabase::setDimaltf()
   &nbsp; 
   OdTvDbDimension::dimaltf()
   OdTvDbDimension::setDimaltf()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimaltf()
   OdTvDbDimStyleTableRecord::setDimaltf()
   </table>
   
   <group TD_SysVars_D>
*/
//<dom_var_def>double DIMALTF;
VAR_DEF(double,               altf,   143,    (25.4),               (0.03937007874016),   (),        TvValidateRange(DBL_MIN, DBL_MAX))

/**
  <title DIMALTRND>
  <toctitle DIMALTRND>
   
  <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
  </table>
   
   DIMALTRND specifies the rounding of alternate measurements in dimensions. If DIMALTRND == 0.0, no rounding is performed.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimaltrnd()
   OdTvDbDatabase::setDimaltrnd()
   &nbsp; 
   OdTvDbDimension::dimaltrnd()
   OdTvDbDimension::setDimaltrnd()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimaltrnd()
   OdTvDbDimStyleTableRecord::setDimaltrnd()
   </table>
   
  <group TD_SysVars_D>
*/
//<dom_var_def>double DIMALTRND;
VAR_DEF(ODTDIST,              altrnd, 148,    (0.0),                (0.0),                (),        TvValidateRange(0,DBL_MAX))

/**
  <title DIMALTTD>
  <toctitle DIMALTTD>
   
  <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   2(imperial) | 3(metric)
   <b>Range</b>           0 ... 8
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMALTTD specifies the number of decimal places in tolerance values in alternate measurements in dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimalttd()
   OdTvDbDatabase::setDimalttd()
   &nbsp; 
   OdTvDbDimension::dimalttd()
   OdTvDbDimension::setDimalttd()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimalttd()
   OdTvDbDimStyleTableRecord::setDimalttd()
   </table>
   
  <group TD_SysVars_D>
*/
//<dom_var_def>OdInt16 DIMALTTD;
VAR_DEF(OdInt16,              alttd,  274,    (2),                  (3),                  (),        TvValidateRange(0,8))

/**
  <title DIMALTTZ>
  <toctitle DIMALTTZ>
   
   <table>
   <b>Type</b>            OdUInt8
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 15
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMALTTZ controls zero suppression in tolerance values in alternate measurements in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Suppress zero feet and exactly zero inches.
   1              Include zero feet and exactly zero inches.
   2              Include zero feet and suppress exactly zero inches.
   3              Suppress zero feet and include exactly zero inches.
   4              Suppress leading decimal zeros.
   8              Suppress trailing decimal zeros.
   12             Suppress leading and trailing decimal zeros.
   </table>
   
   Values 0-3 affect only feet-and-inch dimensions, and may be combined with values 4-12.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimalttz()
   OdTvDbDatabase::setDimalttz()
   &nbsp; 
   OdTvDbDimension::dimalttz()
   OdTvDbDimension::setDimalttz()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimalttz()
   OdTvDbDimStyleTableRecord::setDimalttz()
   </table>

  <group TD_SysVars_D>
*/
//<dom_var_def>OdUInt8 DIMALTTZ;
VAR_DEF(OdUInt8,              alttz,  286,    (0),                  (0),                  (),        TvValidateRange(0,15))

/**
  <title DIMALTU>
  <toctitle DIMALTU>
   
  <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   2
   <b>Range</b>           1 ... 8
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
  </table>
   
  DIMALTU controls the formatting for alternate units in dimensions.
   
  <table>
   <b>Value</b>   <b>Description</b>
   1              Scientific
   2              Decimal
   3              Engineering
   4              Architectural (stacked)
   5              Fractional (stacked)
   6              Architectural
   7              Fractional
   8              Microsoft Windows Desktop
  </table>
   
   Values 0-3 affect only feet-and-inch dimensions, and may be combined with values 4-12.
   
  <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimaltu()
   OdTvDbDatabase::setDimaltu()
   &nbsp; 
   OdTvDbDimension::dimaltu()
   OdTvDbDimension::setDimaltu()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimaltu()
   OdTvDbDimStyleTableRecord::setDimaltu()
  </table>

  <group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMALTU;
VAR_DEF(OdInt16,              altu,   273,    (2),                  (2),                  (),        TvValidateRange(1,8))

/**
  <title DIMALTZ>
  <toctitle DIMALTZ>
   
   <table>
   <b>Type</b>            OdUInt8
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 15
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMALTZ controls zero suppression in alternate measurements in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Suppress zero feet and exactly zero inches.
   1              Include zero feet and exactly zero inches.
   2              Include zero feet and suppress exactly zero inches.
   3              Suppress zero feet and include exactly zero inches.
   4              Suppress leading decimal zeros.
   8              Suppress trailing decimal zeros.
   12             Suppress leading and trailing decimal zeros.
   </table>
   
   Values 0-3 affect only feet-and-inch dimensions, and may be combined with values 4-12.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimaltz()
   OdTvDbDatabase::setDimaltz()
   &nbsp; 
   OdTvDbDimension::dimaltz()
   OdTvDbDimension::setDimaltz()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimaltz()
   OdTvDbDimStyleTableRecord::setDimaltz()
   </table>  

   <group TD_SysVars_D>
   */
//<dom_var_def>OdUInt8 DIMALTZ;
VAR_DEF(OdUInt8,              altz,   285,    (0),                  (0),                  (),        TvValidateRange(0,15))

/**
  <title DIMAPOST>
  <toctitle DIMAPOST>
   
   <table>
   <b>Type</b>            OdString
   <b>Initial value</b>   ""
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMAPOST specifies a prefix and/or suffix for the alternate
   measurements text in dimensions. DIMAPOST is in the form
   prefix\<\>suffix. The '\<\>' in DIMAPOST is replaced by the
   alternate measurements text.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimapost()
   OdTvDbDatabase::setDimapost()
   &nbsp; 
   OdTvDbDimension::dimapost()
   OdTvDbDimension::setDimapost()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimapost()
   OdTvDbDimStyleTableRecord::setDimapost()
   </table>

   <group TD_SysVars_D>
   */
//<dom_var_def>OdString DIMAPOST;
VAR_DEF(OdString,             apost,  4,      (OD_T("")),                 (OD_T("")),                 (),        TvValidateNone())

/**
  <title DIMASZ>
  <toctitle DIMASZ>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.18 (imperial) | 2.5 (metric)
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMASZ specifies the size of dimension and leader arrowheads.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimasz()
   OdTvDbDatabase::setDimasz()
   &nbsp; 
   OdTvDbDimension::dimasz()
   OdTvDbDimension::setDimasz()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimasz()
   OdTvDbDimStyleTableRecord::setDimasz()
   &nbsp; 
   OdTvDbLeader::dimasz()
   OdTvDbLeader::setDimasz()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMASZ;
VAR_DEF(ODTDIST,              asz,    41,     (0.18),               (2.5),                (),        TvValidateRange(0,DBL_MAX))

/**
  <title DIMATFIT>
  <toctitle DIMATFIT>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   3
   <b>Range</b>           0 ... 3
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
   </table>
   
   DIMATFIT specifies how arrows and text are placed when they do not fit within the extension lines of dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Moves text and arrows outside extension lines.
   1              Moves arrows, then text, outside extension lines. When DIMTMOVE == 1, a leader is added to moved text
   2              Moves text, then arrows, outside extension lines.
   3              Moves text or arrows for best fit.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimatfit()
   OdTvDbDatabase::setDimatfit()
   &nbsp; 
   OdTvDbDimension::dimatfit()
   OdTvDbDimension::setDimatfit()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimatfit()
   OdTvDbDimStyleTableRecord::setDimatfit()
   </table>

   <group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMATFIT;
ANNOVAR_DEF(OdInt16,          atfit,  289,    (3),                  (3),                  (),        TvValidateRange(0,3))

/**
  <title DIMAUNIT>
  <toctitle DIMAUNIT>
   
  <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 4
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
  </table>
   
   DIMAUNIT specifies the formatting for units in angular dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Decimal Degrees
   1              Degrees-Minutes-Seconds
   2              Gradians
   3              Radians
   4              Surveyor's Units
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimaunit()
   OdTvDbDatabase::setDimaunit()
   &nbsp; 
   OdTvDbDimension::dimaunit()
   OdTvDbDimension::setDimaunit()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimaunit()
   OdTvDbDimStyleTableRecord::setDimaunit()
   </table> 

   <group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMAUNIT;
VAR_DEF(OdInt16,              aunit,  275,    (0),                  (0),                  (),        TvValidateRange(0,4))

/**
  <title DIMAZIN>
  <toctitle DIMAZIN>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 3
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
   </table>
   
   DIMAZIN controls zero suppression in angular dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Display leading and trailing decimal zeros.
   1              Suppress leading decimal zeros.
   2              Suppress trailing decimal zeros.
   3              Suppress leading and trailing decimal zeros.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimazin()
   OdTvDbDatabase::setDimazin()
   &nbsp; 
   OdTvDbDimension::dimazin()
   OdTvDbDimension::setDimazin()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimazin()
   OdTvDbDimStyleTableRecord::setDimazin()
   </table> 

   <group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMAZIN;
VAR_DEF(OdInt16,              azin,   79,     (0),                  (0),                  (),        TvValidateRange(0,3))

/**
  <title DIMBLK>
  <toctitle DIMBLK>
   
   <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMBLK specifies the arrowhead block at the ends of dimension lines and leader lines. A null value 
   specifies the default arrowhead is to be used.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimblk()
   OdTvDbDatabase::setDimblk()
   &nbsp; 
   OdTvDbDimension::dimblk()
   OdTvDbDimension::setDimblk()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimblk()
   OdTvDbDimStyleTableRecord::setDimblk()
   </table>

   <group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMBLK;
BLKVAR_DEF(ODTARROWBLK,       blk,    342,    (OdTvDbObjectId::kNull),(OdTvDbObjectId::kNull),(),        TvValidateDimBlock())

/**
  <title DIMBLK1>
  <toctitle DIMBLK1>
   
  <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
  </table>
   
  DIMBLK1 specifies the first arrowhead block at the ends of dimension lines when DIMSAH == true. 
  A null value specifies the default arrowhead is to be used.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimblk1()
   OdTvDbDatabase::setDimblk1()
   &nbsp; 
   OdTvDbDimension::dimblk1()
   OdTvDbDimension::setDimblk1()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimblk1()
   OdTvDbDimStyleTableRecord::setDimblk1()
   </table>

   <group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMBLK1;
BLKVAR_DEF(ODTARROWBLK,       blk1,   343,    (OdTvDbObjectId::kNull),(OdTvDbObjectId::kNull),(),        TvValidateDimBlock())

/**
 <title DIMBLK2>
   <toctitle DIMBLK2>
   
   <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMBLK2 specifies the second arrowhead block at the ends of dimension lines when DIMSAH == true. 
   A null value specifies the default arrowhead is to be used.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimblk2()
   OdTvDbDatabase::setDimblk2()
   &nbsp; 
   OdTvDbDimension::dimblk2()
   OdTvDbDimension::setDimblk2()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimblk2()
   OdTvDbDimStyleTableRecord::setDimblk2()
   </table>       

   <group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMBLK2;
BLKVAR_DEF(ODTARROWBLK,       blk2,   344,    (OdTvDbObjectId::kNull),(OdTvDbObjectId::kNull),(),        TvValidateDimBlock())

/**
  <title DIMCEN>
   <toctitle DIMCEN>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.09 | 2.5
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMCEN controls the generation of arc and circle center marks
   and lines. The absolute value of DIMCEN specifies the size of
   the center mark, which half the length of the center mark,
   which is also the length of the portion of a center line
   beyond the arc or circle, as well as the length of the gap
   between the center mark and line. The sign of DIMCEN controls
   the generation of center marks and center lines:
   
   <table>
   <b>Value</b>   <b>Description</b>
   &lt;0            Center marks and center lines
   0                No center marks or center lines
   &gt;0            Center lines
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimcen()
   OdTvDbDatabase::setDimcen()
   &nbsp; 
   OdTvDbDimension::dimcen()
   OdTvDbDimension::setDimcen()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimcen()
   OdTvDbDimStyleTableRecord::setDimcen()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMCEN;
VAR_DEF(ODTDIST,              cen,    141,    (0.09),               (2.5),                (),        TvValidateNone())

/**
  <title DIMCLRD>
  <toctitle DIMCLRD>
   
   <table>
   <b>Type</b>            OdTvCmColor
   <b>Initial value</b>   OdCmEntityColor::kByBlock
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMCLRD specifies the color of dimension lines, leader lines,
   frames, and arrowheads.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimclrd()
   OdTvDbDatabase::setDimclrd()
   &nbsp; 
   OdTvDbDimension::dimclrd()
   OdTvDbDimension::setDimclrd()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimclrd()
   OdTvDbDimStyleTableRecord::setDimclrd()
   &nbsp; 
   OdTvDbFcf::dimclrd()
   OdTvDbFcf::setDimclrd()
   &nbsp; 
   OdTvDbLeader::dimclrd()
   OdTvDbLeader::setDimclrd()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvCmColor DIMCLRD;
VAR_DEF(OdTvCmColor,            clrd,   176,(OdCmEntityColor::kByBlock),(OdCmEntityColor::kByBlock),(), TvValidateColor())

/**
  <title DIMCLRE>
   <toctitle DIMCLRE>
   
   <table>
   <b>Type</b>            OdTvCmColor
   <b>Initial value</b>   OdCmEntityColor::kByBlock
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMCLRE specifies the color of extension lines, enter marks,
   and centerlines.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimclre()
   OdTvDbDatabase::setDimclre()
   &nbsp; 
   OdTvDbDimension::dimclre()
   OdTvDbDimension::setDimclre()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimclre()
   OdTvDbDimStyleTableRecord::setDimclre()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvCmColor DIMCLRE;
VAR_DEF(OdTvCmColor,            clre,   177,(OdCmEntityColor::kByBlock),(OdCmEntityColor::kByBlock),(), TvValidateColor())

/**
  <title DIMCLRT>
   <toctitle DIMCLRT>
   
   <table>
   <b>Type</b>            OdTvCmColor
   <b>Initial value</b>   OdCmEntityColor::kByBlock
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMCLRT specifies the color of dimension text.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimclrt()
   OdTvDbDatabase::setDimclrt()
   &nbsp; 
   OdTvDbDimension::dimclrt()
   OdTvDbDimension::setDimclrt()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimclrt()
   OdTvDbDimStyleTableRecord::setDimclrt()
   &nbsp; 
   OdTvDbFcf::dimclrt()
   OdTvDbFcf::setDimclrt()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvCmColor DIMCLRT;
VAR_DEF(OdTvCmColor,            clrt,   178,(OdCmEntityColor::kByBlock),(OdCmEntityColor::kByBlock),(), TvValidateColor())

/**
  <title DIMDEC>
  <toctitle DIMDEC>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   4 | 2
   <b>Range</b>           0 ... 8
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
  </table>
   
   DIMDEC specifies the number of decimal places in primary units in dimensions.
   
  <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimdec()
   OdTvDbDatabase::setDimdec()
   &nbsp; 
   OdTvDbDimension::dimdec()
   OdTvDbDimension::setDimdec()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimdec()
   OdTvDbDimStyleTableRecord::setDimdec()
  </table> 

<group TD_SysVars_D>
  */
//<dom_var_def>OdInt16 DIMDEC;
VAR_DEF(OdInt16,              dec,    271,    (4),                  (2),                  (),        TvValidateRange(0,8))

/**
  <title DIMDLE>
   <toctitle DIMDLE>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMDLE specifies the distance dimension lines extend beyond extension lines when arrowheads are architectural, 
   integral, oblique, tick, or none.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimdle()
   OdTvDbDatabase::setDimdle()
   &nbsp; 
   OdTvDbDimension::dimdle()
   OdTvDbDimension::setDimdle()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimdle()
   OdTvDbDimStyleTableRecord::setDimdle()
   </table>    

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMDLE;
VAR_DEF(ODTDIST,              dle,    46,     (0.0),                (0.0),                (),        TvValidateRange(0,DBL_MAX))

/**
  <title DIMDLI>
  <toctitle DIMDLI>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.38 | 3.75
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMDLI specifies distance between dimension lines for
   baseline dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimdli()
   OdTvDbDatabase::setDimdli()
   &nbsp; 
   OdTvDbDimension::dimdli()
   OdTvDbDimension::setDimdli()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimdli()
   OdTvDbDimStyleTableRecord::setDimdli()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMDLI;
VAR_DEF(ODTDIST,              dli,    43,     (0.38),               (3.75),               (),        TvValidatePositive())

/**
  <title DIMDSEP>
   <toctitle DIMDSEP>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   '.' | ','
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R14+
   </table>
   
   DIMDSEP specifies the decimal separator for dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimdsep()
   OdTvDbDatabase::setDimdsep()
   &nbsp; 
   OdTvDbDimension::dimdsep()
   OdTvDbDimension::setDimdsep()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimdsep()
   OdTvDbDimStyleTableRecord::setDimdsep()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMDSEP;
VAR_DEF(ODTDECSEP,            dsep,   278,    ('.'),                (','),                (),        TvValidateDecSep())


/**
  <title DIMEXE>
  <toctitle DIMEXE>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.18 | 1.25
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMEXE specifies the distance extension lines extend beyond dimension lines.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimexe()
   OdTvDbDatabase::setDimexe()
   &nbsp; 
   OdTvDbDimension::dimexe()
   OdTvDbDimension::setDimexe()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimexe()
   OdTvDbDimStyleTableRecord::setDimexe()
   </table>
   
   \sa
   <link DIMTSZ, DIMTSZ>
   
<group TD_SysVars_D>
   */
//<dom_var_def>double DIMEXE;
VAR_DEF(ODTDIST,              exe,    44,     (0.18),               (1.25),               (),        TvValidatePositive())

/**
  <title DIMEXO>
  <toctitle DIMEXO>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0625 | 0.625
   <b>Range</b>           >=0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMEXO specifies the distance extensions are offset from
   their origin points. DIMEXO specifies a minimum value when
   fixed-length extension lines are used.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimexo()
   OdTvDbDatabase::setDimexo()
   &nbsp; 
   OdTvDbDimension::dimexo()
   OdTvDbDimension::setDimexo()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimexo()
   OdTvDbDimStyleTableRecord::setDimexo()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMEXO;
VAR_DEF(ODTDIST,              exo,    42,     (0.0625),             (0.625),              (),        TvValidatePositive())

/**
  <title DIMFRAC>
  <toctitle DIMFRAC>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 2
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
   </table>
   
   DIMFRAC specifies the fraction format when DIMLUNIT == 4 or 5.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Horizontal Stacked
   1              Diagonal Stacked
   2              Not Stacked
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimfrac()
   OdTvDbDatabase::setDimfrac()
   &nbsp; 
   OdTvDbDimension::dimfrac()
   OdTvDbDimension::setDimfrac()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimfrac()
   OdTvDbDimStyleTableRecord::setDimfrac()
   </table>
   
   \sa
   <link DIMLUNIT, DIMLUNIT> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMFRAC;
VAR_DEF(OdInt16,              frac,   276,    (0),                  (0),                  (),        TvValidateRange(0,2))

/**
  <title DIMGAP>
   <toctitle DIMGAP>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.09 | 0.625
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMGAP specifies the gap between dimension text and dimension
   lines.
     * A negative value for DIMGAP draws a reference box round
       the dimension text.
     * Text is placed inside a dimension line only if there will
       be two line segments each as long as abs(DIMGAP).
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimgap()
   OdTvDbDatabase::setDimgap()
   &nbsp; 
   OdTvDbDimension::dimgap()
   OdTvDbDimension::setDimgap()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimgap()
   OdTvDbDimStyleTableRecord::setDimgap()
   &nbsp; 
   OdTvDbFcf::dimgap()
   OdTvDbFcf::setDimgap()
   &nbsp;
   OdTvDbLeader::dimgap()
   OdTvDbLeader::setDimgap()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMGAP;
VAR_DEF(ODTDIST,              gap,    147,    (0.09),               (0.625),              (),        TvValidateNone())

/**
  <title DIMJUST>
   <toctitle DIMJUST>
   
   <table>
   <b>Type</b>            OdUInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 4
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMJUST specifies the dimension text horizontal position.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Centered above the dimension line.
   1              By the first extension line.
   2              By the second extension line.
   3              Above the dimension line, parallel to the first extension line.
   4              Above the dimension line, parallel to the second extension line.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimjust()
   OdTvDbDatabase::setDimjust()
   &nbsp; 
   OdTvDbDimension::dimjust()
   OdTvDbDimension::setDimjust()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimjust()
   OdTvDbDimStyleTableRecord::setDimjust()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>OdUInt16 DIMJUST;
VAR_DEF(OdUInt16,             just,   280,    (0),                  (0),                  (),        TvValidateRange(0,4))

/**
  <title DIMLDRBLK>
   <toctitle DIMLDRBLK>
   
   <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
   </table>
   
   DIMLDRBLK specifies the arrowhead block at the ends of leader
   lines. A null value specifies the default arrowhead is to be
   used. Some predefined arrowhead types:
   
   <image DIMLDRBLK.gif>
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimldrblk()
   OdTvDbDatabase::setDimldrblk()
   &nbsp; 
   OdTvDbDimension::dimldrblk()
   OdTvDbDimension::setDimldrblk()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimldrblk()
   OdTvDbDimStyleTableRecord::setDimldrblk()
   &nbsp; 
   OdTvDbLeader::dimldrblk()
   OdTvDbLeader::setDimldrblk()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMLDRBLK;
VAR_DEF(ODTARROWBLK,          ldrblk, 341,    (OdTvDbObjectId::kNull),(OdTvDbObjectId::kNull),(),        TvValidateDimBlock())

/**
  <title DIMLFAC>
   <toctitle DIMLFAC>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   1.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMLFAC specifies the distance multiplier for measurements in
   dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimlfac()
   OdTvDbDatabase::setDimlfac()
   &nbsp; 
   OdTvDbDimension::dimlfac()
   OdTvDbDimension::setDimlfac()
   &nbsp;
   OdTvDbDimStyleTableRecord::dimlfac()
   OdTvDbDimStyleTableRecord::setDimlfac()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMLFAC;
VAR_DEF(double,               lfac,   144,    (1.0),                (1.0),                (),        TvValidateNone())

/**
  <title DIMLIM>
   <toctitle DIMLIM>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMLIM controls the display of dimension limits.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Disabled
   true           Enabled
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimlim()
   OdTvDbDatabase::setDimlim()
   &nbsp; 
   OdTvDbDimension::dimlim()
   OdTvDbDimension::setDimlim()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimlim()
   OdTvDbDimStyleTableRecord::setDimlim()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMLIM;
VAR_DEF(bool,                 lim,    72,     (false),              (false),              (),        TvValidateNone())

/**
  <title DIMLUNIT>
  <toctitle DIMLUNIT>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   2
   <b>Range</b>           1 ... 6
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMLUNIT controls the formatting for units in non-angular dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   1              Scientific
   2              Decimal
   3              Engineering
   4              Architectural (stacked)
   5              Fractional (stacked)
   6              Microsoft Windows Desktop
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimlunit()
   OdTvDbDatabase::setDimlunit()
   &nbsp; 
   OdTvDbDimension::dimlunit()
   OdTvDbDimension::setDimlunit()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimlunit()
   OdTvDbDimStyleTableRecord::setDimlunit()
   </table>

<group TD_SysVars_D>
*/
//<dom_var_def>OdInt16 DIMLUNIT;
VAR_DEF(OdInt16,              lunit,  277,    (2),                  (2),                  (),        TvValidateRange(1,6))

/** 
  <title DIMLWD>
  <toctitle DIMLWD>
   
   <table>
   <b>Type</b>            OdDb::LineWeight
   <b>Initial value</b>   OdDb::kLnWtByBlock
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
   </table>
   
   DIMLWD specifies the lineweight for dimension lines. Some
   specific values:
   
   <table>
   <b>Value</b>             <b>Description</b>
   OdDb::kLnWtByLayer       Lightweight is set to "ByLayer"
   OdDb::kLnWtByBlock       Lightweight is set to "ByBlock"
   OdDb::kLnWtByLwDefault   Lightweight is set to "Default", which is controlled by LWDEFAULT system variable
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimlwd()
   OdTvDbDatabase::setDimlwd()
   &nbsp; 
   OdTvDbDimension::dimlwd()
   OdTvDbDimension::setDimlwd()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimldrblk()
   OdTvDbDimStyleTableRecord::setDimldrblk()
   &nbsp; 
   OdTvDbLeader::dimldrblk()
   OdTvDbLeader::setDimldrblk()
   </table>
   
   \sa
   <link LWDEFAULT, LWDEFAULT>

   <group TD_SysVars_D>
   */
//<dom_var_def>OdDb::LineWeight DIMLWD;
VAR_DEF(ODTDB_LINEWEIGHT,     lwd,    371,    (OdDb::kLnWtByBlock), (OdDb::kLnWtByBlock), (),        TvValidateLineWeight())

/**
  <title DIMLWE>
  <toctitle DIMLWE>
   
   <table>
   <b>Type</b>            OdDb::LineWeight
   <b>Initial value</b>   OdDb::kLnWtByBlock
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
   </table>
   
   DIMLWE specifies the lineweight for extension lines. Some
   specific values:
   
   <table>
   <b>Value</b>             <b>Description</b>
   OdDb::kLnWtByLayer       Lightweight is set to "ByLayer"
   OdDb::kLnWtByBlock       Lightweight is set to "ByBlock"
   OdDb::kLnWtByLwDefault   Lightweight is set to "Default", which is controlled by LWDEFAULT system variable
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimlwe()
   OdTvDbDatabase::setDimlwe()
   &nbsp; 
   OdTvDbDimension::dimlwe()
   OdTvDbDimension::setDimlwe()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimlwe()
   OdTvDbDimStyleTableRecord::setDimlwe()
   </table>
   
   \sa
   <link LWDEFAULT, LWDEFAULT>
   
   <group TD_SysVars_D>
*/
//<dom_var_def>OdDb::LineWeight DIMLWE;
VAR_DEF(ODTDB_LINEWEIGHT,     lwe,    372,    (OdDb::kLnWtByBlock), (OdDb::kLnWtByBlock), (),        TvValidateLineWeight())

/**
  <title DIMPOST>
  <toctitle DIMPOST>
   
   <table>
   <b>Type</b>            OdString
   <b>Initial value</b>   ""
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMPOST specifies a prefix and/or suffix for the measurement
   text in dimensions. DIMPOST is in the form prefix\<\>suffix.
   The '\<\>' in DIMPOST is replaced by the alternate
   measurements text.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimpost()
   OdTvDbDatabase::setDimpost()
   &nbsp; 
   OdTvDbDimension::dimpost()
   OdTvDbDimension::setDimpost()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimpost()
   OdTvDbDimStyleTableRecord::setDimpost()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdString DIMPOST;
VAR_DEF(OdString,             post,   3,      (OD_T("")),                 (OD_T("")),                 (),        TvValidateNone())

/**
  <title DIMRND>
  <toctitle DIMRND>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMRND specifies the rounding of measurements in dimensions.
   If DIMRND == 0.0, no rounding is performed.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimrnd()
   OdTvDbDatabase::setDimrnd()
   &nbsp; 
   OdTvDbDimension::dimrnd()
   OdTvDbDimension::setDimrnd()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimrnd()
   OdTvDbDimStyleTableRecord::setDimrnd()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMRND;
VAR_DEF(ODTDIST,              rnd,    45,     (0.0),                (0.0),                (),        TvValidatePositive())

/**
  <title DIMSAH>
  <toctitle DIMSAH>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMSAH controls the generation of separate arrowheads for
   dimension lines.
   
   <table>
   <b>Value</b>   <b>Arrowhead Blocks</b>
   false          DIMBLK
   true           DIMBLK1 and DIMBLK2
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimsah()
   OdTvDbDatabase::setDimsah()
   &nbsp;
   OdTvDbDimension::dimsah()
   OdTvDbDimension::setDimsah()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimsah()
   OdTvDbDimStyleTableRecord::setDimsah()
   &nbsp; 
   OdTvDbLeader::dimsah()
   OdTvDbLeader::setDimsah()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMSAH;
VAR_DEF(bool,                 sah,    173,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMSCALE>
  <toctitle DIMSCALE>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   1.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMSCALE is an scale factor applied to all dimension
   variables that regulate sizes, offsets, and distances.
   DIMSCALE serves as an overall "volume control" for dimensions
   and leaders.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0.0            A "reasonable" value is computed for model space viewports.
   &gt;0.0        If set to the inverse of the plot scale, plotted dimensions will be at the sizes specified by the other dimension variables.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimscale()
   OdTvDbDatabase::setDimscale()
   &nbsp; 
   OdTvDbDimension::dimscale()
   OdTvDbDimension::setDimscale()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimscale()
   OdTvDbDimStyleTableRecord::setDimscale()
   &nbsp; 
   OdTvDbFcf::dimscale()
   OdTvDbFcf::setDimscale()
   &nbsp; 
   OdTvDbLeader::dimscale()
   OdTvDbLeader::setDimscale()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMSCALE;
VAR_DEF(double,               scale,  40,     (1.0),                (1.0),                (),        TvValidatePositive())

/**
  <title DIMSD1>
   <toctitle DIMSD1>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMSD1 controls the suppression of the first dimension line
   and arrowhead in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Not suppressed
   true           Suppressed
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimsd1()
   OdTvDbDatabase::setDimsd1()
   &nbsp; 
   OdTvDbDimension::dimsd1()
   OdTvDbDimension::setDimsd1()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimsd1()
   OdTvDbDimStyleTableRecord::setDimsd1()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMSD1;
VAR_DEF(bool,                 sd1,    281,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMSD2>
   <toctitle DIMSD2>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMSD2 controls the suppression of the second dimension line
   and arrowhead in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Not suppressed
   true           Suppressed
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimsd2
   OdTvDbDatabase::setDimsd2()
   &nbsp; 
   OdTvDbDimension::dimsd2()
   OdTvDbDimension::setDimsd2()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimsd2()
   OdTvDbDimStyleTableRecord::setDimsd2()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMSD2;
VAR_DEF(bool,                 sd2,    282,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMSE1>
   <toctitle DIMSE1>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMSE1 controls the suppression of the first extension line
   in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Not suppressed
   true           Suppressed
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimse1()
   OdTvDbDatabase::setDimse1()
   &nbsp; 
   OdTvDbDimension::dimse1()
   OdTvDbDimension::setDimse1()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimse1()
   OdTvDbDimStyleTableRecord::setDimse1()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMSE1;
VAR_DEF(bool,                 se1,    75,     (false),              (false),              (),        TvValidateNone())

/**
  <title DIMSE2>
   <toctitle DIMSE2>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMSE2 controls the suppression of the second extension line in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Not suppressed
   true           Suppressed
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimse2()
   OdTvDbDatabase::setDimse2()
   &nbsp; 
   OdTvDbDimension::dimse2()
   OdTvDbDimension::setDimse2()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimse2()
   OdTvDbDimStyleTableRecord::setDimse2()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMSE2;
VAR_DEF(bool,                 se2,    76,     (false),              (false),              (),        TvValidateNone())

/**
  <title DIMSOXD>
  <toctitle DIMSOXD>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMSOXD controls the suppression of dimension lines outside
   the extension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Not suppressed
   true           Suppressed
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimsoxd()
   OdTvDbDatabase::setDimsoxd()
   &nbsp; 
   OdTvDbDimension::dimsoxd()
   OdTvDbDimension::setDimsoxd()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimsoxd()
   OdTvDbDimStyleTableRecord::setDimsoxd()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMSOXD;
ANNOVAR_DEF(bool,             soxd,   175,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMTAD>
   <toctitle DIMTAD>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0 | 1
   <b>Range</b>           0 ... 4
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTAD specifies the dimension text vertical position.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Centered about the dimension line.
   1              Above the dimension line, unless DIMTIH==1 and the dimension line is not horizontal.
   2              Side of the dimension line farthest from the defining points.
   3              JIS standard.
   4              Text below the dimension line.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtad()
   OdTvDbDatabase::setDimtad()
   &nbsp;
   OdTvDbDimension::dimtad()
   OdTvDbDimension::setDimtad()
   &nbsp;
   OdTvDbDimStyleTableRecord::dimtad()
   OdTvDbDimStyleTableRecord::setDimtad()
   &nbsp; 
   OdTvDbLeader::dimtad()
   OdTvDbLeader::setDimtad()
   </table>  
   
<group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMTAD;
VAR_DEF(OdInt16,              tad,    77,     (0),                  (1),                  (),        TvValidateRange(0,4))

/**
  <title DIMTDEC>
   <toctitle DIMTDEC>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   4 | 2
   <b>Range</b>           0 ... 8
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMTDEC specifies the number of decimal places in tolerance
   values for primary units in dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtdec()
   OdTvDbDatabase::setDimtdec()
   &nbsp; 
   OdTvDbDimension::dimtdec()
   OdTvDbDimension::setDimtdec()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtdec()
   OdTvDbDimStyleTableRecord::setDimtdec()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMTDEC;
VAR_DEF(OdInt16,              tdec,   272,    (4),                  (2),                  (),        TvValidateRange(0,8))

/**
  <title DIMTFAC>
   <toctitle DIMTFAC>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   1.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTFAC specifies, as a factor of DIMTXT, the size of tolerance and fraction text in dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtfac()
   OdTvDbDatabase::setDimtfac()
   &nbsp; 
   OdTvDbDimension::dimtfac()
   OdTvDbDimension::setDimtfac()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtfac()
   OdTvDbDimStyleTableRecord::setDimtfac()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMTFAC;
VAR_DEF(double,               tfac,   146,    (1.0),                (1.0),                (),        TvValidatePositiveNonZero())

/**
  <title DIMTIH>
   <toctitle DIMTIH>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   true | false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTIH controls the orientation of dimension text inside the
   extension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Aligned with dimension line.
   true           Horizonta
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtih()
   OdTvDbDatabase::setDimtih()
   &nbsp; 
   OdTvDbDimension::dimtih()
   OdTvDbDimension::setDimtih()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtih()
   OdTvDbDimStyleTableRecord::setDimtih()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMTIH;
VAR_DEF(bool,                 tih,    73,     (true),               (false),              (),        TvValidateNone())

/**
  <title DIMTIX>
   <toctitle DIMTIX>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTIX controls the placement of dimension text inside the
   extension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Inside extension lines if there is room.
   true           Inside extension lines.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtix()
   OdTvDbDatabase::setDimtix()
   &nbsp; 
   OdTvDbDimension::dimtix()
   OdTvDbDimension::setDimtix()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtix()
   OdTvDbDimStyleTableRecord::setDimtix()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMTIX;
ANNOVAR_DEF(bool,             tix,    174,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMTM>
   <toctitle DIMTM>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTM specifies the negative of the lower tolerance limit for
   dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtm()
   OdTvDbDatabase::setDimtm()
   &nbsp; 
   OdTvDbDimension::dimtm()
   OdTvDbDimension::setDimtm()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtm()
   OdTvDbDimStyleTableRecord::setDimtm()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMTM;
VAR_DEF(ODTDIST,              tm,     48,     (0.0),                (0.0),                (),        TvValidateNone())

/**
  <title DIMTMOVE>
  <toctitle DIMTMOVE>
   
  <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 2
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2000+
  </table>
   
   DIMTMOVE controls the updating of associative dimension
   objects while dragging.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Moving dimension text moves the dimension line.
   1              Moving dimension text adds a leader.
   2              Moving dimension text does not add a leader.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtmove()
   OdTvDbDatabase::setDimtmove()
   &nbsp;
   OdTvDbDimension::dimtmove()
   OdTvDbDimension::setDimtmove()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtmove()
   OdTvDbDimStyleTableRecord::setDimtmove()
   </table>
   
   <b>Note: </b>DIMTMOVE is obsolete, but is included for compatibility purposes.

   <group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMTMOVE;
ANNOVAR_DEF(OdInt16,          tmove,  279,    (0),                  (0),                  (),        TvValidateRange(0,2))

/**
  <title DIMTOFL>
  <toctitle DIMTOFL>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false | true
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTOFL controls the drawing of dimension lines between extension lines when text is outside the dimension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Disabled
   true           Enabled
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtofl()
   OdTvDbDatabase::setDimtofl()
   &nbsp; 
   OdTvDbDimension::dimtofl()
   OdTvDbDimension::setDimtofl()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtofl()
   OdTvDbDimStyleTableRecord::setDimtofl()
   </table> 
   
<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMTOFL;
ANNOVAR_DEF(bool,             tofl,   172,    (false),              (true),               (),        TvValidateNone())

/**
  <title DIMTOH>
  <toctitle DIMTOH>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   true | false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTOH controls the orientation of dimension text outside the extension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Aligned with dimension line.
   true           Horizontal
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtoh()
   OdTvDbDatabase::setDimtoh()
   &nbsp; 
   OdTvDbDimension::dimtoh()
   OdTvDbDimension::setDimtoh()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtoh()
   OdTvDbDimStyleTableRecord::setDimtoh()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMTOH;
VAR_DEF(bool,                 toh,    74,     (true),               (false),              (),        TvValidateNone())

/**
  <title DIMTOL>
  <toctitle DIMTOL>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTOL controls the generation of tolerance text in dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Disabled
   true           Enabled
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtol()
   OdTvDbDatabase::setDimtol()
   &nbsp; 
   OdTvDbDimension::dimtol()
   OdTvDbDimension::setDimtol()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtol()
   OdTvDbDimStyleTableRecord::setDimtol()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMTOL;
VAR_DEF(bool,                 tol,    71,     (false),              (false),              (),        TvValidateNone())

/**
  <title DIMTOLJ>
  <toctitle DIMTOLJ>
   
   <table>
   <b>Type</b>            OdUInt8
   <b>Initial value</b>   1 | 0
   <b>Range</b>           0 ... 2
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMTOLJ controls the vertical justification of tolerance values with respect to the nominal dimension text.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Bottom
   1              Middle
   2              Top
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtolj()
   OdTvDbDatabase::setDimtolj()
   &nbsp; 
   OdTvDbDimension::dimtolj()
   OdTvDbDimension::setDimtolj()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtolj()
   OdTvDbDimStyleTableRecord::setDimtolj()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>OdUInt8 DIMTOLJ;
VAR_DEF(OdUInt8,              tolj,   283,    (1),                  (0),                  (),        TvValidateRange(0,2))

/**
  <title DIMTP>
  <toctitle DIMTP>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTP specifies the upper tolerance limit for dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtp()
   OdTvDbDatabase::setDimtp()
   &nbsp; 
   OdTvDbDimension::dimtp()
   OdTvDbDimension::setDimtp()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtp()
   OdTvDbDimStyleTableRecord::setDimtp()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMTP;
VAR_DEF(ODTDIST,              tp,     47,     (0.0),                (0.0),                (),        TvValidateNone())

/** * VARDOCS:
  <properties>
    <remarks>
      "\n    DIMTSZ specifies the size of architectural tics are "
      "\n    to be drawn instead of arrowheads for linear, radial, and diameter dimensions."
      "\n"
      "\n    DIMTSZ is the distance, parallel to the dimension line,"
      "\n    that the tics extends beyond the extension lines."
      "\n"
      "\n    @table"
      "\n    Value    Description"
      "\n    0.0      Arrowheads"
      "\n    > 0.0    Tics"
    </remarks>
    <see_also>
      "\n    DIMDLE"
    </see_also>
  </properties>
*/

/** <title DIMTSZ>
   <toctitle DIMTSZ>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTSZ specifies the size of architectural tics are to be
   drawn instead of arrowheads for linear, radial, and diameter
   dimensions. DIMTSZ is the distance, parallel to the dimension
   line, that the tics extends beyond the extension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0.0            Arrowheads
   &gt; 0.0       Tics
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtsz()
   OdTvDbDatabase::setDimtsz()
   &nbsp; 
   OdTvDbDimension::dimtsz()
   OdTvDbDimension::setDimtsz()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtsz()
   OdTvDbDimStyleTableRecord::setDimtsz()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMTSZ;
VAR_DEF(ODTDIST,              tsz,    142,    (0.0),                (0.0),                (),        TvValidatePositive())

/**
  <title DIMTVP>
  <toctitle DIMTVP>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTVP specifies, as a factor of DIMTXT, the vertical
   distance of the middle of the dimension text with respect to
   the dimension line.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtvp()
   OdTvDbDatabase::setDimtvp()
   &nbsp; 
   OdTvDbDimension::dimtvp()
   OdTvDbDimension::setDimtvp()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtvp()
   OdTvDbDimStyleTableRecord::setDimtvp()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMTVP;
VAR_DEF(double,               tvp,    145,    (0.0),                (0.0),                (),        TvValidateNone())

/**
  <title DIMTXSTY>
  <toctitle DIMTXSTY>
   
   <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   "Standard" text style object ID
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   The DIMTXSTY variable specifies the text style for dimension text.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimtxsty()
   OdTvDbDatabase::setDimtxsty()
   &nbsp; 
   OdTvDbDimension::dimtxsty()
   OdTvDbDimension::setDimtxsty()
   &nbsp; 
   OdTvDbLeader::dimtxsty()
   OdTvDbLeader::setDimtxsty()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMTXSTY;
VAR_DEF(ODTTEXTSTYLEID,       txsty,  340,    (OdTvDbObjectId::kNull),(OdTvDbObjectId::kNull),(),        TvValidateTextStyle(NullIdAllowed))

/**
  <title DIMTXT>
  <toctitle DIMTXT>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   0.18 | 2.5
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMTXT specifies the size of the dimension text.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtxt()
   OdTvDbDatabase::setDimtxt()
   &nbsp; 
   OdTvDbDimension::dimtxt()
   OdTvDbDimension::setDimtxt()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtxt()
   OdTvDbDimStyleTableRecord::setDimtxt()
   &nbsp; 
   OdTvDbFcf::dimtxt()
   OdTvDbFcf::setDimtxt()
   &nbsp; 
   OdTvDbLeader::dimtxt()
   OdTvDbLeader::setDimtxt()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMTXT;
VAR_DEF(ODTDIST,              txt,    140,    (0.18),               (2.5),                (),        TvValidatePositiveNonZero())

/**
  <title DIMTZIN>
  <toctitle DIMTZIN>
   
   <table>
   <b>Type</b>            OdUInt8
   <b>Initial value</b>   0 | 8
   <b>Range</b>           0 ... 15
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
  DIMTZIN controls zero suppression in tolerance values in linear dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Suppress zero feet and exactly zero inches.
   1              Include zero feet and exactly zero inches.
   2              Include zero feet and suppress exactly zero inches.
   3              Suppress zero feet and include exactly zero inches.
   4              Suppress leading decimal zeros.
   8              Suppress trailing decimal zeros.
   12             Suppress leading and trailing decimal zeros.
   </table>
   
   Values 0-3 affect only feet-and-inch dimensions, and may be combined with values 4-12.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtzin()
   OdTvDbDatabase::setDimtzin()
   &nbsp; 
   OdTvDbDimension::dimtzin()
   OdTvDbDimension::setDimtzin()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtzin()
   OdTvDbDimStyleTableRecord::setDimtzin()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdUInt8 DIMTZIN;
VAR_DEF(OdUInt8,              tzin,   284,    (0),                  (8),                  (),        TvValidateRange(0,15))

/**
  <title DIMUPT>
  <toctitle DIMUPT>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R13+
   </table>
   
   DIMUPT controls the movement of user-positioned text when dimension lines are moved.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Moves only the dimension line.
   true           Moves the dimension line and the text.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimupt()
   OdTvDbDatabase::setDimupt()
   &nbsp; 
   OdTvDbDimension::dimupt()
   OdTvDbDimension::setDimupt()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimupt()
   OdTvDbDimStyleTableRecord::setDimupt()
   </table>   

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMUPT;
VAR_DEF(bool,                 upt,    288,    (false),              (false),              (),        TvValidateNone())

/**
  <title DIMZIN>
  <toctitle DIMZIN>
   
   <table>
   <b>Type</b>            OdUInt8
   <b>Initial value</b>   0 | 8
   <b>Range</b>           0 ... 15
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        R12+
   </table>
   
   DIMZIN controls zero suppression in linear dimensions.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Suppress zero feet and exactly zero inches.
   1              Include zero feet and exactly zero inches.
   2              Include zero feet and suppress exactly zero inches.
   3              Suppress zero feet and include exactly zero inches.
   4              Suppress leading decimal zeros.
   8              Suppress trailing decimal zeros.
   12             Suppress leading and trailing decimal zeros.
   </table>
   
   Values 0-3 affect only feet-and-inch dimensions, and may be combined with values 4-12.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimzin()
   OdTvDbDatabase::setDimzin()
   &nbsp; 
   OdTvDbDimension::dimzin()
   OdTvDbDimension::setDimzin()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimzin()
   OdTvDbDimStyleTableRecord::setDimzin()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdUInt8 DIMZIN;
VAR_DEF(OdUInt8,              zin,    78,     (0),                  (8),                  (),        TvValidateRange(0,15))


//--------------------------------------------new in R21------------------------------------------------------

/**
  <title DIMFXL>
   <toctitle DIMFXL>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   1.0
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
   DIMFXL specifies the fixed length of extension lines from the
   dimension line towards the dimension origin. DIMFXL is
   ignored when DIMFXLON == false.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimfxl()
   OdTvDbDatabase::setDimfxl()
   &nbsp; 
   OdTvDbDimension::dimfxl()
   OdTvDbDimension::setDimfxl()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimfxl()
   OdTvDbDimStyleTableRecord::setDimfxl()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMFXL;
VAR_DEF(ODTDIST,              fxl,    49,     (1.0),                  (1.0),                  (),        TvValidateNone())

/**
  <title DIMFXLON>
   <toctitle DIMFXLON>
   
   <table>
   <b>Type</b>            bool
   <b>Initial value</b>   false
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
   DIMFXLON controls the generation of fixed-length extension lines.
   
   <table>
   <b>Value</b>   <b>Description</b>
   false          Variable length.
   true           Fixed length.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimfxlon()
   OdTvDbDatabase::setDimfxlon()
   &nbsp; 
   OdTvDbDimension::dimfxlon()
   OdTvDbDimension::setDimfxlon()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimfxlon()
   OdTvDbDimStyleTableRecord::setDimfxlon()
   </table>
   
   \sa
   <link DIMFXL, DIMFXL> 

<group TD_SysVars_D>
   */
//<dom_var_def>bool DIMFXLON;
VAR_DEF(bool,              fxlon,    290,     (false),                  (false),                  (),       TvValidateBOOL())

/**
  <title DIMJOGANG>
   <toctitle DIMJOGANG>
   
   <table>
   <b>Type</b>            double
   <b>Initial value</b>   pi/4
   <b>Range</b>           pi/36 ... pi/2
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
   DIMJOGANG specifies the jog angle of dimension lines in
   jogged radius dimensions.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimjogang()
   OdTvDbDatabase::setDimjogang()
   &nbsp; 
   OdTvDbDimension::dimjogang()
   OdTvDbDimension::setDimjogang()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimjogang()
   OdTvDbDimStyleTableRecord::setDimjogang()
   </table>
   
   <b>Note: </b>All angles are expressed in radians.

<group TD_SysVars_D>
   */
//<dom_var_def>double DIMJOGANG;
VAR_DEF(ODTORIENT,         jogang,    50,     (OdaPI4),                  (OdaPI4),                  (),     TvValidateDouble(  5.0*OdaPI/180.0, OdaPI2))

/**
  <title DIMTFILL>
   <toctitle DIMTFILL>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 2
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
   DIMTFILL specifies the background fill of dimension text.
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              No fill
   1              Drawing background color
   2              Color specified by DIMTFILLCLR
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtfill()
   OdTvDbDatabase::setDimtfill()
   &nbsp;
   OdTvDbDimension::dimtfill()
   OdTvDbDimension::setDimtfill()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtfill()
   OdTvDbDimStyleTableRecord::setDimtfill()
   </table>
   
   \sa
   <link DIMTFILLCLR, DIMTFILLCLR>
   
<group TD_SysVars_D>   
   */
//<dom_var_def>OdInt16 DIMTFILL;
VAR_DEF(OdInt16,              tfill,    69,     (0),                  (0),                  (),        TvValidateRange(0, 2))

/**
  <title DIMTFILLCLR>
  <toctitle DIMTFILLCLR>
   
  <table>
   <b>Type</b>            OdTvCmColor
   <b>Initial value</b>   OdCmEntityColor::kByBlock
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
  </table>
   
  DIMTFILLCLR specifies the background fill color of dimension text when DIMTFILL == 2.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimtfillclr()
   OdTvDbDatabase::setDimtfillclr()
   &nbsp; 
   OdTvDbDimension::dimtfillclr()
   OdTvDbDimension::setDimtfillclr()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimtfillclr()
   OdTvDbDimStyleTableRecord::setDimtfillclr()
   </table>
   
   \sa
   <link DIMTFILL, DIMTFILL> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvCmColor DIMTFILLCLR;
VAR_DEF(OdTvCmColor,              tfillclr,    70,     (OdCmEntityColor::kByBlock),                  (OdCmEntityColor::kByBlock),                  (),        TvValidateNone())

/**
  <title DIMARCSYM>
  <toctitle DIMARCSYM>
   
   <table>
   <b>Type</b>            OdInt16
   <b>Initial value</b>   0
   <b>Range</b>           0 ... 2
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
   DIMARCSYM specifies the placement of arc symbols in arc length dimensions
   
   <table>
   <b>Value</b>   <b>Description</b>
   0              Before the dimension text.
   1              Above the dimension text.
   2              Not displayed.
   </table>
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp;
   OdTvDbDatabase::dimarcsym()
   OdTvDbDatabase::setDimarcsym()
   &nbsp; 
   OdTvDbDimension::dimarcsym()
   OdTvDbDimension::setDimarcsym()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimarcsym()
   OdTvDbDimStyleTableRecord::setDimarcsym()
   </table>

<group TD_SysVars_D>
   */
//<dom_var_def>OdInt16 DIMARCSYM;
VAR_DEF(OdInt16,              arcsym,    90,     (0),                  (0),                  (),        TvValidateRange(0, 2))

/**
  <title DIMLTYPE>
  <toctitle DIMLTYPE>
   
  <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
  </table>
   
  DIMLTYPE specifies the linetype of dimension lines.
   
  <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimltype()
   OdTvDbDatabase::setDimltype()
   &nbsp; 
   OdTvDbDimension::dimltype()
   OdTvDbDimension::setDimltype()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimltype()
   OdTvDbDimStyleTableRecord::setDimltype()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMLTYPE;
VAR_DEF(ODTLINETYPEID,              ltype,    345,     (OdTvDbObjectId::kNull),                  (OdTvDbObjectId::kNull),                  (),        TvValidateLinetype(true))

/**
  <title DIMLTEX1>
  <toctitle DIMLTEX1>
   
   <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
  DIMLTEX1 specifies the linetype of first extension lines.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimltex1()
   OdTvDbDatabase::setDimltex1()
   &nbsp; 
   OdTvDbDimension::dimltex1()
   OdTvDbDimension::setDimltex1()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimltex1()
   OdTvDbDimStyleTableRecord::setDimltex1()
   </table> 

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMLTEX1;
VAR_DEF(ODTLINETYPEID,              ltex1,    346,     (OdTvDbObjectId::kNull),                  (OdTvDbObjectId::kNull),                  (),        TvValidateLinetype(true))

/**
  <title DIMLTEX2>
  <toctitle DIMLTEX2>
   
   <table>
   <b>Type</b>            OdTvDbObjectId
   <b>Initial value</b>   OdTvDbObjectId::kNull
   <b>Read-Only</b>       No
   <b>Saved In</b>        Database
   <b>Versions</b>        2007+
   </table>
   
   DIMLTEX2 specifies the linetype of second extension lines.
   
   <table>
   <b>Access Methods</b>
   OdTvDbDatabase::getSysVar()
   OdTvDbDatabase::setSysVar()
   &nbsp; 
   OdTvDbDatabase::dimltex2()
   OdTvDbDatabase::setDimltex2()
   &nbsp; 
   OdTvDbDimension::dimltex2()
   OdTvDbDimension::setDimltex2()
   &nbsp; 
   OdTvDbDimStyleTableRecord::dimltex2()
   OdTvDbDimStyleTableRecord::setDimltex2()
   </table>  

<group TD_SysVars_D>
   */
//<dom_var_def>OdTvDbObjectId DIMLTEX2;
VAR_DEF(ODTLINETYPEID,              ltex2,    347,     (OdTvDbObjectId::kNull),                  (OdTvDbObjectId::kNull),                  (),        TvValidateLinetype(true))

//--------------------------------------------new in R24------------------------------------------------------

/** * VARDOCS:
  <properties>
    <remarks>
      "\n    DIMTXTDIRECTION controls the text direction."
      "\n"
      "\n    @table"
      "\n    Value    Description"
      "\n    false    "
      "\n    true     "
    </remarks>
      <see_also>
      "\n    DIMTXTDIRECTION"
      </see_also>
  </properties>
*/
VAR_DEF(bool,         txtdirection,   294,          (false),                  (false),          (),  TvValidateBOOL())

/** * VARDOCS:
  <properties>
    <remarks>
      "\n    DIMMZF."
    </remarks>
  </properties>
*/
VAR_DEF(double,                mzf,   297,          (100.0),                  (100.0),          (),  TvValidateNone())

/** * VARDOCS:
  <properties>
    <remarks>
      "\n    DIMMZS."
    </remarks>
  </properties>
*/
VAR_DEF(OdString,              mzs,   298,       (OD_T("")),               (OD_T("")),          (),  TvValidateNone())

/** * VARDOCS:
  <properties>
    <remarks>
      "\n    DIMALTMZF."
    </remarks>
  </properties>
*/
VAR_DEF(double,             altmzf,   295,          (100.0),                  (100.0),          (),  TvValidateNone())

/** * VARDOCS:
  <properties>
    <remarks>
      "\n    DIMALTMZS."
    </remarks>
  </properties>
*/
VAR_DEF(OdString,           altmzs,   296,       (OD_T("")),               (OD_T("")),          (),  TvValidateNone())


#ifdef DOUNDEF_ODTDB_LINEWEIGHT
#undef ODTDB_LINEWEIGHT
#undef DOUNDEF_ODTDB_LINEWEIGHT
#endif

#ifdef DOUNDEF_ODTDIST
#undef ODTDIST
#undef DOUNDEF_ODTDIST
#endif

#ifdef DOUNDEF_ODTUNITLESS
#undef ODTUNITLESS
#undef DOUNDEF_ODTUNITLESS
#endif

#ifdef DOUNDEF_ODTORIENT
#undef ODTORIENT
#undef DOUNDEF_ODTORIENT
#endif

#ifdef DOUNDEF_ODTDECSEP
#undef ODTDECSEP
#undef DOUNDEF_ODTDECSEP
#endif

#ifdef DOUNDEF_ODTARROWBLK
#undef ODTARROWBLK
#undef DOUNDEF_ODTARROWBLK
#endif

#ifdef DOUNDEF_ODTTEXTSTYLEID
#undef ODTTEXTSTYLEID
#undef DOUNDEF_ODTTEXTSTYLEID
#endif

#ifdef DOUNDEF_ODTLINETYPEID
#undef ODTLINETYPEID
#undef DOUNDEF_ODTLINETYPEID
#endif

#ifdef DOUNDEF_NullIdAllowed
#undef NullIdAllowed
#undef DOUNDEF_NullIdAllowed
#endif

