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
#
#  ExSimpleApp executable
#

ifc_sources(ExSimpleApp

  ExSimpleApp.h
  ExSimpleApp.cpp
)
  
if(MSVC)
  ifc_sources(OdIfcReadFile

    #ExIfcDump.rc
  )
endif(MSVC)


include_directories(

  ${IFC_ROOT}/Include
  ${IFC_ROOT}/Include/Spf
  ${IFC_ROOT}/Include/Common
  
  #${TKERNEL_ROOT}/Extensions/ExServices
  #${IFC_ROOT}/Extensions/ExServices
  #${IFC_ROOT}/Examples/Common/
)


if(ODA_SHARED)

message("ExSimpleApp dynamic configuration")
set ( _ExSimpleApp_libs

	${IFC2X3_LIB}
	${IFCCORE_LIB}

	${TD_GI_LIB}
	#${TD_GS_LIB}
	${TD_GE_LIB}
	${TD_ROOT_LIB}
	${TD_DBROOT_LIB}
	${TD_KEY_LIB}
)
else(ODA_SHARED)

message("ExSimpleApp static configuration")
set ( _ExSimpleApp_libs

	${SPF_LIB}
	#${IFC2X3_LIB}
	#${IFCCORE_LIB}

	#${TD_GI_LIB} ${TD_SPATIALINDEX_LIB}
	#${TD_GE_LIB}
	#${TD_ROOT_LIB}
	#${TD_DBROOT_LIB}

	#${TH_CONDITIONAL_LIBCRYPTO}
)
endif(ODA_SHARED)

ifc_executable( _ExSimpleApp_libs

  ${_ExSimpleApp_libs}
  #${TD_EXLIB}
  #${TD_ALLOC_LIB} 
)

ifc_project_group(ExSimpleApp "Examples")
