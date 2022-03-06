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

%include "ODA_RXDirector_Python.i"

%RXDIRECTOR(OdRxSystemServices,%arg(DEF_ODA_SWIG_MODULE_NAME))
%RXDIRECTOR(RxSystemServicesImpl,%arg(DEF_ODA_SWIG_MODULE_NAME))

%feature("nodirector") RxSystemServicesImpl::createFile;
%feature("nodirector") RxSystemServicesImpl::isA;
%feature("nodirector") RxSystemServicesImpl::queryX;
%feature("nodirector") RxSystemServicesImpl::loadModule;

%feature("nodirector") OdDbBaseHostAppServices::createDatabase;
%feature("nodirector") OdDbBaseHostAppServices::databaseClass;
%feature("nodirector") OdDbBaseHostAppServices::educationalPlotStamp;
%feature("nodirector") OdDbBaseHostAppServices::doFullCRCCheck;
%feature("nodirector") OdDbBaseHostAppServices::newPageController;
%feature("nodirector") OdDbBaseHostAppServices::ttfFileNameByDescriptor;
%feature("nodirector") OdDbBaseHostAppServices::findFile;
%feature("nodirector") OdDbBaseHostAppServices::newProgressMeter;
%feature("nodirector") OdDbBaseHostAppServices::releaseProgressMeter;
%feature("nodirector") OdDbBaseHostAppServices::program;
%feature("nodirector") OdDbBaseHostAppServices::product;
%feature("nodirector") OdDbBaseHostAppServices::companyName;
%feature("nodirector") OdDbBaseHostAppServices::prodcode;
%feature("nodirector") OdDbBaseHostAppServices::releaseMajorMinorString;
%feature("nodirector") OdDbBaseHostAppServices::releaseMajorVersion;
%feature("nodirector") OdDbBaseHostAppServices::releaseMinorVersion;
%feature("nodirector") OdDbBaseHostAppServices::versionString;
%feature("nodirector") OdDbBaseHostAppServices::warning;
%feature("nodirector") OdDbBaseHostAppServices::getErrorDescription;
%feature("nodirector") OdDbBaseHostAppServices::formatMessage;
%feature("nodirector") OdDbBaseHostAppServices::newUndoController;
%feature("nodirector") OdDbBaseHostAppServices::newUndoStream;
%feature("nodirector") OdDbBaseHostAppServices::auditPrintReport;
%feature("nodirector") OdDbBaseHostAppServices::ttfFileNameByDescriptor;
%feature("nodirector") OdDbBaseHostAppServices::getAlternateFontName;
%feature("nodirector") OdDbBaseHostAppServices::getFontMapFileName;
%feature("nodirector") OdDbBaseHostAppServices::getPreferableFont;
%feature("nodirector") OdDbBaseHostAppServices::getSubstituteFont;
%feature("nodirector") OdDbBaseHostAppServices::getSubstituteFontByChar;
%feature("nodirector") OdDbBaseHostAppServices::getSystemFontFolders;
%feature("nodirector") OdDbBaseHostAppServices::collectFilePathsInDirectory;
%feature("nodirector") OdDbBaseHostAppServices::fileDialog;
%feature("nodirector") OdDbBaseHostAppServices::gsBitmapDevice;
%feature("nodirector") OdDbBaseHostAppServices::getTempPath;
%feature("nodirector") OdDbBaseHostAppServices::getMtMode;
%feature("nodirector") OdDbBaseHostAppServices::numThreads;
%feature("nodirector") OdDbBaseHostAppServices::brepBuilder;
%feature("nodirector") OdDbBaseHostAppServices::getEnv;
%feature("nodirector") OdDbBaseHostAppServices::setEnv;
%feature("nodirector") OdDbBaseHostAppServices::getAppUserName;