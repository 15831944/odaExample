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

#ifdef IFCCORE_EXPORTS
  #define IFCCORE_EXPORT          OD_TOOLKIT_EXPORT
  #define IFCCORE_EXPORT_STATIC   OD_STATIC_EXPORT
#else                               
  #define IFCCORE_EXPORT          OD_TOOLKIT_IMPORT
  #define IFCCORE_EXPORT_STATIC   OD_STATIC_IMPORT
#endif

#ifdef IFCCORETOOLS_EXPORTS
  #define IFCCORETOOLS_EXPORT        OD_TOOLKIT_EXPORT
  #define IFCCORETOOLS_EXPORT_STATIC OD_STATIC_EXPORT
#else                               
  #define IFCCORETOOLS_EXPORT        OD_TOOLKIT_IMPORT
  #define IFCCORETOOLS_EXPORT_STATIC OD_STATIC_IMPORT
#endif

#ifdef IFCGEOM_EXPORTS
  #define IFCGEOM_EXPORT          OD_TOOLKIT_EXPORT
  #define IFCGEOM_EXPORT_STATIC   OD_STATIC_EXPORT
#else                               
  #define IFCGEOM_EXPORT          OD_TOOLKIT_IMPORT
  #define IFCGEOM_EXPORT_STATIC   OD_STATIC_IMPORT
#endif

#ifdef IFCBREPBUILDER_EXPORTS
  #define IFCBREPBUILDER_EXPORT         OD_TOOLKIT_EXPORT
  #define IFCBREPBUILDER_EXPORT_STATIC  OD_STATIC_EXPORT
#else
  #define IFCBREPBUILDER_EXPORT         OD_TOOLKIT_IMPORT
  #define IFCBREPBUILDER_EXPORT_STATIC  OD_STATIC_IMPORT
#endif

#ifdef BCF_EXPORTS
#define BCF_EXPORT          OD_TOOLKIT_EXPORT
#define BCF_EXPORT_STATIC   OD_STATIC_EXPORT
#else                               
#define BCF_EXPORT          OD_TOOLKIT_IMPORT
#define BCF_EXPORT_STATIC   OD_STATIC_IMPORT
#endif
