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

#ifndef _ODDXFV_H_
#define _ODDXFV_H_

#define BIGNUM 1.000000E+016
/*
char *dxfenthdrstr[35]= { "LINE",
                          "POINT",
                          "CIRCLE",
                          "SHAPE",
                          "ELLIPSE",
                          "SPLINE",
                          "TEXT",
                          "ARC",
                          "TRACE",
                          "REGION",
                          "SOLID",
                          "BLOCK",
                          "ENDBLK",
                          "INSERT",
                          "ATTDEF",
                          "ATTRIB",
                          "SEQEND",
                          "",
                          "POLYLINE",
                          "VERTEX",
                          "3DLINE",
                          "3DFACE",
                          "DIMENSION",
                          "VIEWPORT",
                          "3DSOLID",
                          "RAY",
                          "XLINE",
                          "MTEXT",
                          "LEADER",
                          "TOLERANCE",
                          "MLINE",
                          "",
                          "",
                          "",
                          "BODY"
 } ;
*/
#define HEADERSTR          OD_T("HEADER")
#define HDRACADVERSTR      OD_T("$ACADVER")
#define HDRACADMAINTVERSTR OD_T("$ACADMAINTVER")
#define HDRINSBASESTR      OD_T("$INSBASE")
#define HDREXTMINSTR       OD_T("$EXTMIN")
#define HDREXTMAXSTR       OD_T("$EXTMAX")
#define HDRLIMMINSTR       OD_T("$LIMMIN")
#define HDRLIMMAXSTR       OD_T("$LIMMAX")
#define HDRVIEWCTRSTR      OD_T("$VIEWCTR")
#define HDRVIEWSIZESTR     OD_T("$VIEWSIZE")
#define HDRSNAPMODESTR     OD_T("$SNAPMODE")
#define HDRSNAPUNITSTR     OD_T("$SNAPUNIT")
#define HDRSNAPBASESTR     OD_T("$SNAPBASE")
#define HDRSNAPANGSTR      OD_T("$SNAPANG")
#define HDRSNAPSTYLESTR    OD_T("$SNAPSTYLE")
#define HDRSNAPISOPAIRSTR  OD_T("$SNAPISOPAIR")
#define HDRGRIDMODESTR     OD_T("$GRIDMODE")
#define HDRGRIDUNITSTR     OD_T("$GRIDUNIT")
#define HDRORTHOMODESTR    OD_T("$ORTHOMODE")
#define HDRREGENMODESTR    OD_T("$REGENMODE")
#define HDRFILLMODESTR     OD_T("$FILLMODE")
#define HDRQTEXTMODESTR    OD_T("$QTEXTMODE")
#define HDRMIRRTEXTSTR     OD_T("$MIRRTEXT")
#define HDRDRAGMODESTR     OD_T("$DRAGMODE")
#define HDRLTSCALESTR      OD_T("$LTSCALE")
#define HDROSMODESTR       OD_T("$OSMODE")
#define HDRATTMODESTR      OD_T("$ATTMODE")
#define HDRTEXTSIZESTR     OD_T("$TEXTSIZE")
#define HDRTRACEWIDSTR     OD_T("$TRACEWID")
#define HDRTEXTSTYLESTR    OD_T("$TEXTSTYLE")
#define HDRCLAYERSTR       OD_T("$CLAYER")
#define HDRCELTYPESTR      OD_T("$CELTYPE")
#define HDRCECOLORSTR      OD_T("$CECOLOR")
#define HDRDIMSCALESTR     OD_T("$DIMSCALE")
#define HDRDIMASZSTR       OD_T("$DIMASZ")
#define HDRDIMEXOSTR       OD_T("$DIMEXO")
#define HDRDIMDLISTR       OD_T("$DIMDLI")
#define HDRDIMRNDSTR       OD_T("$DIMRND")
#define HDRDIMDLESTR       OD_T("$DIMDLE")
#define HDRDIMEXESTR       OD_T("$DIMEXE")
#define HDRDIMTPSTR        OD_T("$DIMTP")
#define HDRDIMTMSTR        OD_T("$DIMTM")
#define HDRDIMTXTSTR       OD_T("$DIMTXT")
#define HDRDIMCENSTR       OD_T("$DIMCEN")
#define HDRDIMTSZSTR       OD_T("$DIMTSZ")
#define HDRDIMTOLSTR       OD_T("$DIMTOL")
#define HDRDIMLIMSTR       OD_T("$DIMLIM")
#define HDRDIMTIHSTR       OD_T("$DIMTIH")
#define HDRDIMTOHSTR       OD_T("$DIMTOH")
#define HDRDIMSE1STR       OD_T("$DIMSE1")
#define HDRDIMSE2STR       OD_T("$DIMSE2")
#define HDRDIMTADSTR       OD_T("$DIMTAD")
#define HDRDIMZINSTR       OD_T("$DIMZIN")
#define HDRDIMBLKSTR       OD_T("$DIMBLK")
#define HDRDIMASOSTR       OD_T("$DIMASO")
#define HDRDIMSHOSTR       OD_T("$DIMSHO")
#define HDRDIMPOSTSTR      OD_T("$DIMPOST")
#define HDRDIMAPOSTSTR     OD_T("$DIMAPOST")
#define HDRDIMALTSTR       OD_T("$DIMALT")
#define HDRDIMALTDSTR      OD_T("$DIMALTD")
#define HDRDIMALTFSTR      OD_T("$DIMALTF")
#define HDRDIMLFACSTR      OD_T("$DIMLFAC")
#define HDRDIMTOFLSTR      OD_T("$DIMTOFL")
#define HDRDIMTVPSTR       OD_T("$DIMTVP")
#define HDRDIMTIXSTR       OD_T("$DIMTIX")
#define HDRDIMSOXDSTR      OD_T("$DIMSOXD")
#define HDRDIMSAHSTR       OD_T("$DIMSAH")
#define HDRDIMBLK1STR      OD_T("$DIMBLK1")
#define HDRDIMBLK2STR      OD_T("$DIMBLK2")
#define HDRDIMSTYLESTR     OD_T("$DIMSTYLE")
#define HDRDIMCLRDSTR      OD_T("$DIMCLRD")
#define HDRDIMCLRESTR      OD_T("$DIMCLRE")
#define HDRDIMCLRTSTR      OD_T("$DIMCLRT")
#define HDRDIMTFACSTR      OD_T("$DIMTFAC")
#define HDRDIMGAPSTR       OD_T("$DIMGAP")
#define HDRLUNITSSTR       OD_T("$LUNITS")
#define HDRLUPRECSTR       OD_T("$LUPREC")
#define HDRAXISMODESTR     OD_T("$AXISMODE")
#define HDRAXISUNITSTR     OD_T("$AXISUNIT")
#define HDRSKETCHINCSTR    OD_T("$SKETCHINC")
#define HDRFILLETRADSTR    OD_T("$FILLETRAD")
#define HDRAUNITSSTR       OD_T("$AUNITS")
#define HDRAUPRECSTR       OD_T("$AUPREC")
#define HDRMENUSTR         OD_T("$MENU")
#define HDRELEVATIONSTR    OD_T("$ELEVATION")
#define HDRPELEVATIONSTR   OD_T("$PELEVATION")
#define HDRTHICKNESSSTR    OD_T("$THICKNESS")
#define HDRVIEWDIRSTR      OD_T("$VIEWDIR")
#define HDRLIMCHECKSTR     OD_T("$LIMCHECK")
#define HDRBLIPMODESTR     OD_T("$BLIPMODE")
#define HDRCHAMFERASTR     OD_T("$CHAMFERA")
#define HDRCHAMFERBSTR     OD_T("$CHAMFERB")
#define HDRCHAMFERCSTR     OD_T("$CHAMFERC")
#define HDRCHAMFERDSTR     OD_T("$CHAMFERD")
#define HDRFASTZOOMSTR     OD_T("$FASTZOOM")
#define HDRSKPOLYSTR       OD_T("$SKPOLY")
#define HDRTDCREATESTR     OD_T("$TDCREATE")
#define HDRTDUPDATESTR     OD_T("$TDUPDATE")
#define HDRTDINDWGSTR      OD_T("$TDINDWG")
#define HDRTDUSRTIMERSTR   OD_T("$TDUSRTIMER")
#define HDRUSRTIMERSTR     OD_T("$USRTIMER")
#define HDRANGBASESTR      OD_T("$ANGBASE")
#define HDRANGDIRSTR       OD_T("$ANGDIR")
#define HDRPDMODESTR       OD_T("$PDMODE")
#define HDRPDSIZESTR       OD_T("$PDSIZE")
#define HDRPLINEWIDSTR     OD_T("$PLINEWID")
#define HDRCOORDSSTR       OD_T("$COORDS")
#define HDRSPLFRAMESTR     OD_T("$SPLFRAME")
#define HDRSPLINETYPESTR   OD_T("$SPLINETYPE")
#define HDRSPLINESEGSSTR   OD_T("$SPLINESEGS")
#define HDRATTDIASTR       OD_T("$ATTDIA")
#define HDRATTREQSTR       OD_T("$ATTREQ")
#define HDRHANDLINGSTR     OD_T("$HANDLING")
#define HDRHANDSEEDSTR     OD_T("$HANDSEED")
#define HDRSURFTAB1STR     OD_T("$SURFTAB1")
#define HDRSURFTAB2STR     OD_T("$SURFTAB2")
#define HDRSURFTYPESTR     OD_T("$SURFTYPE")
#define HDRSURFUSTR        OD_T("$SURFU")
#define HDRSURFVSTR        OD_T("$SURFV")
#define HDRFLATLANDSTR     OD_T("$FLATLAND")
#define HDRUCSNAMESTR      OD_T("$UCSNAME")
#define HDRUCSORGSTR       OD_T("$UCSORG")
#define HDRUCSXDIRSTR      OD_T("$UCSXDIR")
#define HDRUCSYDIRSTR      OD_T("$UCSYDIR")
#define HDRPUCSNAMESTR     OD_T("$PUCSNAME")
#define HDRPUCSORGSTR      OD_T("$PUCSORG")
#define HDRPUCSXDIRSTR     OD_T("$PUCSXDIR")
#define HDRPUCSYDIRSTR     OD_T("$PUCSYDIR")
#define HDRUSERISTR        OD_T("$USERI%d")
#define HDRUSERRSTR        OD_T("$USERR%d")
#define HDRWORLDVIEWSTR    OD_T("$WORLDVIEW")
#define HDRCYCLEKEEPSTR    OD_T("$CYCLEKEEP")
#define HDRCYCLECURRSTR    OD_T("$CYCLECURR")
#define HDRSHADEDGESTR     OD_T("$SHADEDGE")
#define HDRSHADEDIFSTR     OD_T("$SHADEDIF")
#define HDRTILEMODESTR     OD_T("$TILEMODE")
#define HDRMAXACTVPSTR     OD_T("$MAXACTVP")
#define HDRPINSBASESTR     OD_T("$PINSBASE")
#define HDRPLIMCHECKSTR    OD_T("$PLIMCHECK")
#define HDRPEXTMINSTR      OD_T("$PEXTMIN")
#define HDRPEXTMAXSTR      OD_T("$PEXTMAX")
#define HDRPLIMMINSTR      OD_T("$PLIMMIN")
#define HDRPLIMMAXSTR      OD_T("$PLIMMAX")
#define HDRUNITMODESTR     OD_T("$UNITMODE")
#define HDRVISRETAINSTR    OD_T("$VISRETAIN")
#define HDRPLINEGENSTR     OD_T("$PLINEGEN")
#define HDRPSLTSCALESTR    OD_T("$PSLTSCALE")
#define HDRTREEDEPTHSTR    OD_T("$TREEDEPTH")
#define HDRDWGCODEPAGESTR  OD_T("$DWGCODEPAGE")
#define HDRTITLESTR        OD_T("$TITLE")
#define HDRSUBJECTSTR      OD_T("$SUBJECT")
#define HDRAUTHORSTR       OD_T("$AUTHOR")
#define HDRKEYWORDSSTR     OD_T("$KEYWORDS")
#define HDRCOMMENTSSTR     OD_T("$COMMENTS")
#define HDRLASTSAVEDBYSTR  OD_T("$LASTSAVEDBY")
#define HDRREVISIONNUMBERSTR OD_T("$REVISIONNUMBER")
#define HDRCUSTOMPROPERTYTAGSTR OD_T("$CUSTOMPROPERTYTAG")
#define HDRCUSTOMPROPERTYSTR OD_T("$CUSTOMPROPERTY")
#define HDRPICKSTYLESTR    OD_T("$PICKSTYLE")
#define HDRCMLSTYLESTR     OD_T("$CMLSTYLE")
#define HDRCMLJUSTSTR      OD_T("$CMLJUST")
#define HDRCMLSCALESTR     OD_T("$CMLSCALE")
#define HDRSAVEIMAGESSTR   OD_T("$SAVEIMAGES")
#define HDRPROXYGRAPHICSSTR   OD_T("$PROXYGRAPHICS")
#define HDRCELTSCALESTR    OD_T("$CELTSCALE")
#define HDRDELOBJSTR       OD_T("$DELOBJ")
#define HDRDISPSILHSTR     OD_T("$DISPSILH")
#define HDRDIMJUSTSTR      OD_T("$DIMJUST")
#define HDRDIMSD1STR       OD_T("$DIMSD1")
#define HDRDIMSD2STR       OD_T("$DIMSD2")
#define HDRDIMTOLJSTR      OD_T("$DIMTOLJ")
#define HDRDIMTZINSTR      OD_T("$DIMTZIN")
#define HDRDIMALTZSTR      OD_T("$DIMALTZ")
#define HDRDIMALTTZSTR     OD_T("$DIMALTTZ")
#define HDRDIMFITSTR       OD_T("$DIMFIT")
#define HDRDIMUPTSTR       OD_T("$DIMUPT")
#define HDRDIMUNITSTR      OD_T("$DIMUNIT")
#define HDRDIMDECSTR       OD_T("$DIMDEC")
#define HDRDIMTDECSTR      OD_T("$DIMTDEC")
#define HDRDIMALTUSTR      OD_T("$DIMALTU")
#define HDRDIMALTTDSTR     OD_T("$DIMALTTD")
#define HDRDIMTXSTYSTR     OD_T("$DIMTXSTY")
#define HDRDIMAUNITSTR     OD_T("$DIMAUNIT")
#define HDRMEASUREMENTSTR  OD_T("$MEASUREMENT")
#define HDRCELWEIGHTSTR         OD_T("$CELWEIGHT")
#define HDRCEPSNIDSTR           OD_T("$CEPSNID")
#define HDRCEPSNTYPESTR         OD_T("$CEPSNTYPE")
#define HDRDIMADECSTR           OD_T("$DIMADEC")
#define HDRDIMALTRNDSTR         OD_T("$DIMALTRND")
#define HDRDIMATFITSTR          OD_T("$DIMATFIT")
#define HDRDIMAZINSTR           OD_T("$DIMAZIN")
#define HDRDIMDSEPSTR           OD_T("$DIMDSEP")
#define HDRDIMFRACSTR           OD_T("$DIMFRAC")
#define HDRDIMLDRBLKSTR         OD_T("$DIMLDRBLK")
#define HDRDIMLUNITSTR          OD_T("$DIMLUNIT")
#define HDRDIMLWDSTR            OD_T("$DIMLWD")
#define HDRDIMLWESTR            OD_T("$DIMLWE")
#define HDRDIMTMOVESTR          OD_T("$DIMTMOVE")
#define HDRENDCAPSSTR           OD_T("$ENDCAPS")
#define HDREXTNAMESSTR          OD_T("$EXTNAMES")
#define HDRFINGERPRINTGUIDSTR   OD_T("$FINGERPRINTGUID")
#define HDRHYPERLINKBASESTR     OD_T("$HYPERLINKBASE")
#define HDRSTYLESHEETSTR        OD_T("$STYLESHEET")
#define HDRINSUNITSSTR          OD_T("$INSUNITS")
#define HDRJOINSTYLESTR         OD_T("$JOINSTYLE")
#define HDRLWDISPLAYSTR         OD_T("$LWDISPLAY")
#define HDRPSTYLEMODESTR        OD_T("$PSTYLEMODE")
#define HDRPSVPSCALESTR         OD_T("$PSVPSCALE")
#define HDROLESTARTUPSTR        OD_T("$OLESTARTUP")
#define HDRPUCSBASESTR          OD_T("$PUCSBASE")
#define HDRPUCSORGBACKSTR       OD_T("$PUCSORGBACK")
#define HDRPUCSORGBOTTOMSTR     OD_T("$PUCSORGBOTTOM")
#define HDRPUCSORGFRONTSTR      OD_T("$PUCSORGFRONT")
#define HDRPUCSORGLEFTSTR       OD_T("$PUCSORGLEFT")
#define HDRPUCSORGRIGHTSTR      OD_T("$PUCSORGRIGHT")
#define HDRPUCSORGTOPSTR        OD_T("$PUCSORGTOP")
#define HDRPUCSORTHOREFSTR      OD_T("$PUCSORTHOREF")
#define HDRPUCSORTHOVIEWSTR     OD_T("$PUCSORTHOVIEW")
#define HDRTDUCREATESTR         OD_T("$TDUCREATE")
#define HDRTDUUPDATESTR         OD_T("$TDUUPDATE")
#define HDRUCSBASESTR           OD_T("$UCSBASE")
#define HDRUCSORGBACKSTR        OD_T("$UCSORGBACK")
#define HDRUCSORGBOTTOMSTR      OD_T("$UCSORGBOTTOM")
#define HDRUCSORGFRONTSTR       OD_T("$UCSORGFRONT")
#define HDRUCSORGLEFTSTR        OD_T("$UCSORGLEFT")
#define HDRUCSORGRIGHTSTR       OD_T("$UCSORGRIGHT")
#define HDRUCSORGTOPSTR         OD_T("$UCSORGTOP")
#define HDRUCSORTHOREFSTR       OD_T("$UCSORTHOREF")
#define HDRUCSORTHOVIEWSTR      OD_T("$UCSORTHOVIEW")
#define HDRVERSIONGUIDSTR       OD_T("$VERSIONGUID")
#define HDRXEDITSTR             OD_T("$XEDIT")

// new to acad2007 header veriables
#define HDRFIELDEVAL           OD_T("$FIELDEVAL")
#define HDRSOLIDHIST           OD_T("$SOLIDHIST")
#define HDRSHOWHIST            OD_T("$SHOWHIST")
#define HDRPSOLWIDTH           OD_T("$PSOLWIDTH")
#define HDRLOFTPARAM           OD_T("$LOFTPARAM")
#define HDRLOFTNORMALS         OD_T("$LOFTNORMALS")
#define HDRLOFTANG1            OD_T("$LOFTANG1")
#define HDRLOFTANG2            OD_T("$LOFTANG2")
#define HDRLOFTMAG1            OD_T("$LOFTMAG1")
#define HDRLOFTMAG2            OD_T("$LOFTMAG2")
#define HDRLATITUDE            OD_T("$LATITUDE")
#define HDRLONGITUDE           OD_T("$LONGITUDE")
#define HDRNORTHDIRECTION      OD_T("$NORTHDIRECTION")
#define HDRTIMEZONE            OD_T("$TIMEZONE")
#define HDRLIGHTGLYPHDISPLAY   OD_T("$LIGHTGLYPHDISPLAY")
#define HDRTILEMODELIGHTSYNCH  OD_T("$TILEMODELIGHTSYNCH")
#define HDRINTERFERECOLOR      OD_T("$INTERFERECOLOR")
#define HDRINTERFEREOBJVS      OD_T("$INTERFEREOBJVS")
#define HDRINTERFEREVPVS       OD_T("$INTERFEREVPVS")
#define HDRDRAGVS              OD_T("$DRAGVS")
#define HDRCSHADOW             OD_T("$CSHADOW")
#define HDRSHADOWPLANELOCATION OD_T("$SHADOWPLANELOCATION")

#define HDRCAMERADISPLAY       OD_T("$CAMERADISPLAY")
#define HDRLENSLENGTH          OD_T("$LENSLENGTH")
#define HDRCAMERAHEIGHT        OD_T("$CAMERAHEIGHT")
#define HDRSTEPSPERSEC         OD_T("$STEPSPERSEC")
#define HDRSTEPSIZE            OD_T("$STEPSIZE")
#define HDR3DDWFPREC           OD_T("$3DDWFPREC")
#define HDRPSOLHEIGHT          OD_T("$PSOLHEIGHT")
#define HDRCMATERIAL           OD_T("$CMATERIAL")
#define HDRDWFFRAME            OD_T("$DWFFRAME")
#define HDRDGNFRAME            OD_T("$DGNFRAME")
#define HDRREALWORLDSCALE      OD_T("$REALWORLDSCALE")

#define HDRDIMFXL              OD_T("$DIMFXL")
#define HDRDIMFXLON            OD_T("$DIMFXLON")
#define HDRDIMJOGANG           OD_T("$DIMJOGANG")
#define HDRDIMTFILL            OD_T("$DIMTFILL")
#define HDRDIMTFILLCLR         OD_T("$DIMTFILLCLR")
#define HDRDIMARCSYM           OD_T("$DIMARCSYM")
#define HDRDIMLTYPE            OD_T("$DIMLTYPE")
#define HDRDIMLTEX1            OD_T("$DIMLTEX1")
#define HDRDIMLTEX2            OD_T("$DIMLTEX2")

#define HDRDIMTXTDIRECTION     OD_T("$DIMTXTDIRECTION")
#define HDRDIMMZF              OD_T("$DIMMZF")
#define HDRDIMMZS              OD_T("$DIMMZS")
#define HDRDIMALTMZF           OD_T("$DIMALTMZF")
#define HDRDIMALTMZS           OD_T("$DIMALTMZS")

// new to acad2004 header veriables
// G. Udov, 19.05.2004
#define SORTENTS                OD_T("$SORTENTS")
#define INDEXCTL                OD_T("$INDEXCTL")
#define HIDETEXT                OD_T("$HIDETEXT")
#define XCLIPFRAME              OD_T("$XCLIPFRAME")
#define HALOGAP                 OD_T("$HALOGAP")
#define OBSCOLOR                OD_T("$OBSCOLOR")
#define OBSLTYPE                OD_T("$OBSLTYPE")
#define INTERSECTIONDISPLAY     OD_T("$INTERSECTIONDISPLAY")
#define INTERSECTIONCOLOR       OD_T("$INTERSECTIONCOLOR")
#define DIMASSOC                OD_T("$DIMASSOC")
#define PROJECTNAME             OD_T("$PROJECTNAME")

#define ENDOFSECSTR        OD_T("ENDSEC")
#define SECTIONSTR         OD_T("SECTION")
#define TABLESSTR          OD_T("TABLES")
#define BLOCKSSTR          OD_T("BLOCKS")
#define BLKRSTR            OD_T("BLOCK_RECORD")
//#define GROUPSTR           OD_T("GROUP")
#define ENTITIESSTR        OD_T("ENTITIES")
#define TABLESTR           OD_T("TABLE")
#define ENDTABSTR          OD_T("ENDTAB")
#define EOFSTR             OD_T("EOF")
//#define LAYERSTR           "LAYER"
//#define UCSSTR             "UCS"
//#define REGAPPSTR          OD_T("APPID")
//#define DIMSTYLESTR        OD_T("DIMSTYLE")
//#define VPORTSTR           OD_T("VPORT")
//#define LTYPESTR           OD_T("LTYPE")
//#define SHAPESTR           OD_T("STYLE")
//#define VIEWSTR            OD_T("VIEW")
//#define MLSTYLESTR         OD_T("MLINESTYLE")
#define CLASSSTR           OD_T("CLASS")
#define CLASSESSTR         OD_T("CLASSES")
#define OBJECTSSTR         OD_T("OBJECTS")
//#define DICTIONARYSTR      OD_T("DICTIONARY")
//#define ZOMBIEOBJSTR       OD_T("ACAD_ZOMBIE_OBJECT")
//#define PROXYOBJSTR        OD_T("ACAD_PROXY_OBJECT")
//#define XRECORDOBJSTR      OD_T("XRECORD")
//#define IDBUFFEROBJSTR     OD_T("IDBUFFER")
//#define IMAGEDEFREACTOROBJSTR     OD_T("IMAGEDEF_REACTOR")
//#define IMAGEDEFOBJSTR     OD_T("IMAGEDEF")
//#define RASTERVARIABLESOBJSTR     OD_T("RASTERVARIABLES")
//#define SORTENTSTABLEOBJSTR     OD_T("SORTENTSTABLE")
//#define DICTIONARYVAROBJSTR OD_T("DICTIONARYVAR")
//#define SPATIALFILTEROBJSTR OD_T("SPATIAL_FILTER")
//#define SPATIALINDEXOBJSTR OD_T("SPATIAL_INDEX")
//#define LAYERINDEXOBJSTR OD_T("LAYER_INDEX")
//#define OBJECTPTROBJSTR OD_T("OBJECT_PTR")
//#define DICTIONARYWDFLTOBJSTR OD_T("ACDBDICTIONARYWDFLT")
//#define PLACEHOLDEROBJSTR OD_T("ACDBPLACEHOLDER")
//#define LAYOUTOBJSTR OD_T("LAYOUT")
//#define VBAPROJECTOBJSTR OD_T("VBA_PROJECT")
//#define WIPEOUTVARIABLESOBJSTR OD_T("WIPEOUTVARIABLES")
//#define PLOTSETTINGSOBJSTR OD_T("PLOTSETTINGS")
#define TIMESTR9 OD_T("%.9f")
#define TIMESTR10 OD_T("%.10f")
//#define STANDARDSTR        OD_T("Standard")
/*
#ifndef AD_UNIXOS
char *READBINARY=OD_T("rb");
char *WRITEBINARY=OD_T("wb");
#ifdef macintosh
char *DECSTRSTR=OD_T("d\015");
char *BIGFLOATSTRSTR=OD_T("E\015");
char *ZEROPTZERO=OD_T("0.0\015");
char *PERCENT_S=OD_T("%s\015");
char *PERCENT9LONG=OD_T("%9ld\015");
char *PERCENT3SHORT=OD_T("%3d\015");
char *PERCENT_C=OD_T("%c\015");
char *UNNAMED=OD_T("*UNNAMED\015");
#else
char *DECSTRSTR=OD_T("d\r\n");
char *BIGFLOATSTRSTR=OD_T("E\r\n");
char *ZEROPTZERO=OD_T("0.0\r\n");
char *PERCENT_S=OD_T("%s\r\n");
char *PERCENT9LONG=OD_T("%9ld\r\n");
char *PERCENT3SHORT=OD_T("%3d\r\n");
char *PERCENT_C=OD_T("%c\r\n");
char *UNNAMED=OD_T("*UNNAMED\r\n");
#endif
#else
char *READBINARY=OD_T("r");
char *WRITEBINARY=OD_T("w");
char *DECSTRSTR=OD_T("d\n");
char *BIGFLOATSTRSTR=OD_T("lE\n");
char *ZEROPTZERO=OD_T("0.0\n");
char *PERCENT_S=OD_T("%s\n");
char *PERCENT9LONG=OD_T("%9ld\n");
char *PERCENT3SHORT=OD_T("%3d\n");
char *PERCENT_C=OD_T("%c\n");
char *UNNAMED=OD_T("*UNNAMED\n");
#endif
*/

#ifndef AD_UNIXOS

#ifdef TARGET_OS_MAC

#define INT16FORMAT "%6d\015"
#define UINT16FORMAT "%6u\015"

//#define OBJECTIDFORMAT "%X\015"
#define NEXTLINEFORMAT "\015"

#define BIGFLOATSTRSTR "E\015"
#define ZEROPTZERO "0.0\015"
#define PERCENT_S "%s\015"
#define PERCENT9LONG "%9d\015"
#define PERCENT9ULONG "%9u\015"
#define PERCENT3SHORT "%3d\015"
#define PERCENT_C "%c\015"
//#define UNNAMED "*UNNAMED\015"
//#define UNNAMED_T OD_T("*UNNAMED\015")
#define NEXTLINE "\015"
#define BOOLFORMAT "%6d\015"
#define INT8FORMAT "%6d\015"
#define UINT8FORMAT "%6u\015"

#else

#define INT16FORMAT "%6d\r\n"
#define UINT16FORMAT "%6u\r\n"
//#define OBJECTIDFORMAT "%X\r\n"
#define NEXTLINEFORMAT "\r\n"

#define BIGFLOATSTRSTR "E\r\n"
#define ZEROPTZERO "0.0\r\n"
#define PERCENT_S "%s\r\n"
#define PERCENT9LONG "%9d\r\n"
#define PERCENT9ULONG "%9u\r\n"
#define PERCENT3SHORT "%3d\r\n"
#define PERCENT_C "%c\r\n"
//#define UNNAMED "*UNNAMED\r\n"
//#define UNNAMED_T OD_T("*UNNAMED\r\n")
#define NEXTLINE "\r\n"
#define BOOLFORMAT "%6d\r\n"
#define INT8FORMAT "%6d\r\n"
#define UINT8FORMAT "%6u\r\n"

//#define DXFEPSION 0.0000005
#define BIGFLOATSTR OD_T("%.15lE")
#define FLOATSTR OD_T("%%.%df")
#endif
#else
#endif

/* unsigned short z */

#endif //_ODDXFV_H_
