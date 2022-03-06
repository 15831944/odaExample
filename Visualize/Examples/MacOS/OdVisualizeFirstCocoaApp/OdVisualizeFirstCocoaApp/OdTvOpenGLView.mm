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

#import "OdTvOpenGLView.h"
#include "TvCoreModulesNames.h"

// Static module map
#ifndef _TOOLKIT_IN_DLL_
// Visualize API
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRxCommonDataAccessModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbCoreModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(TvSCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvTfModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvDbPartialViewingModuleImpl );
//Visualize device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(VisualizeDeviceModule);

//Raster images
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRasterProcessingServicesImpl);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ExRasterModule);
//Device
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTrGL2RenderModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(GLES2Module);

//DWG
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdTvVisualizeDwgFilerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbIOModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ISMModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(SCENEOEModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(ModelerModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdDbEntitiesModule);
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT(OdRecomputeDimBlockModule);

//TvCore
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseModule );
ODRX_DECLARE_STATIC_MODULE_ENTRY_POINT( OdTvCoreDatabaseIOModule );

ODRX_BEGIN_STATIC_MODULE_MAP()
ODRX_DEFINE_STATIC_APPMODULE(OdTvModuleName, OdTvModule)
ODRX_DEFINE_STATIC_APPMODULE(RxCommonDataAccessModuleName, OdRxCommonDataAccessModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvDbCoreModuleName, OdTvDbCoreModule )
ODRX_DEFINE_STATIC_APPMODULE(L"TV_SCENEOE", TvSCENEOEModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvDbIOAppName, OdTvDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"TV_ISM", TvISMModule)
ODRX_DEFINE_STATIC_APPMODULE( OdTvTfModuleName, OdTvTfModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTvPartialViewingModuleName, OdTvDbPartialViewingModuleImpl )

ODRX_DEFINE_STATIC_APPMODULE(OdTvVisualizeDeviceModuleName, VisualizeDeviceModule)

ODRX_DEFINE_STATIC_APPMODULE(OdRasterProcessorModuleName, OdRasterProcessingServicesImpl)
ODRX_DEFINE_STATIC_APPMODULE(RX_RASTER_SERVICES_APPNAME, ExRasterModule)
ODRX_DEFINE_STATIC_APPMODULE(OdTrGL2ModuleName, OdTrGL2RenderModule)
ODRX_DEFINE_STATIC_APPMODULE(OdWinGLES2ModuleName, GLES2Module)

//DWG
ODRX_DEFINE_STATIC_APPMODULE(OdTvDwg2VisualizeModuleName, OdTvVisualizeDwgFilerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDbIOAppName, OdDbIOModule)
ODRX_DEFINE_STATIC_APPMODULE(L"ISM", ISMModule)
ODRX_DEFINE_STATIC_APPMODULE(L"SCENEOE", SCENEOEModule)
ODRX_DEFINE_STATIC_APPLICATION(OdModelerGeometryModuleName, ModelerModule)
ODRX_DEFINE_STATIC_APPMODULE(OdDbEntitiesAppName, OdDbEntitiesModule)
ODRX_DEFINE_STATIC_APPLICATION(OdRecomputeDimBlockModuleName, OdRecomputeDimBlockModule)

//TvCore
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseModuleName, OdTvCoreDatabaseModule )
ODRX_DEFINE_STATIC_APPMODULE( OdTvCoreDatabaseIOModuleName, OdTvCoreDatabaseIOModule )

ODRX_END_STATIC_MODULE_MAP()

#endif


@implementation OdTvOpenGLView
{
    bool _isDeviceInitialized;
}


-(void)activate
{
    // initialize static map
#ifndef _TOOLKIT_IN_DLL_
    ODRX_INIT_STATIC_MODULE_MAP();
#endif
    
    static const char* ActInfo[] = {
#ifdef TEIGHA_TRIAL
        "", ""
#else
        //"UserInfo", "UserSignature"
        
        // Before compiling, a ODA SDK activation file should be placed in a location that a compiler can access,
        // otherwise you get a compiler error such as "Kernel/Extensions/ExServices/ExSystemServices.h:43:10: fatal error: 'OdActivationInfo' file not found".
        // To learn about ODA SDK activation, see the activation guide at https://docs.opendesign.com/tkernel/oda_activation.html
#include "OdActivationInfo"
#endif
    };
    
    odActivate(ActInfo[0], ActInfo[1]); // ODA SDK initialize
    odTvInitialize();                   // Visualize SDK initialize
}
-(void)deactivate
{
    [self clearGLContext];
    
    odTvUninitialize();     // Visualize SDK uninitialize
    odCleanUpStaticData();  // ODA SDK uninitialize
}

// initialization
-(void)awakeFromNib
{
    _isDeviceInitialized = false;
    
    // ODA activate
    [self activate];
    
    NSOpenPanel* openDlg = [NSOpenPanel openPanel];
    
    [openDlg setCanChooseFiles:YES];
    [openDlg setAllowsMultipleSelection:NO];
    [openDlg setCanChooseDirectories:NO];
    NSMutableArray* filter = [NSMutableArray array];
    [filter addObject:@"dwg"];
    [openDlg setAllowedFileTypes:filter];
    
    // show open file dialog
    if ( [openDlg runModalForDirectory:nil file:nil] == NSOKButton )
    {
        NSArray* files = [openDlg filenames];
        for(int i = 0; i < [files count]; i++ )
        {
            NSString* fileName = [files objectAtIndex:i];
            OdString odFileName([fileName cStringUsingEncoding:[NSString defaultCStringEncoding]]);
            [self openFile:odFileName.c_str()];
        }
    }
}

-(void)openFile: (OdString)fileName
{
    if(fileName.isEmpty())
        return;
    
    //retrieve the factory id
    OdTvFactoryId factId = odTvGetFactory();
    
    // Try to import file
    OdTvResult rc = tvOk;
    try
    {
        // Declare import parameters for .obj file and set file path
        OdTvDwgImportParams  dwgParams;
        dwgParams.setFilePath(fileName);
        dwgParams.setDCRect( OdTvDCRect(0, [self bounds].size.width, [self bounds].size.height, 0) );
        
        // Import database
        TvDatabseId = factId.importFile(&dwgParams, &rc);
        
        if (rc != tvOk)
        {
            NSLog(@"Import of file was failed.");
        }
    }
    catch (const OdError& e)
    {
        NSString *errString = [self WCHARToString:(wchar_t*) e.description().c_str()];
        NSLog(@"%@\n", errString);
    }
    catch (OdTvError& e)
    {
        NSString *errString = [self WCHARToString:(wchar_t*) e.description().c_str()];
        NSLog(@"%@\n", errString);
    }
    catch(...)
    {
        NSLog(@"Error dyring import file");
    }
    
    // Get device (here it is always the first device) and setup
    if (TvDatabseId.isValid())
    {
        OdTvDatabasePtr pDb = TvDatabseId.openObject();
        if (!pDb.isNull())
        {
            OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
            if (!pIt.isNull())
            {
                TvDeviceId = pIt->getDevice();
                
                // Get rect from current window
                OdTvDCRect rect(0, self.frame.size.width, self.frame.size.height, 0);
                
                OdTvGsDevicePtr pDevice = TvDeviceId.openObject(OdTv::kForWrite);
                
                // Setup device
                pDevice->setOption(OdTvGsDevice::kCreateGLContext, false);
                pDevice->setupGs((__bridge void*)self, rect, OdTvGsDevice::kOpenGLES2, NULL);
                
                _isDeviceInitialized = true;
            }
        }
    }
}

-(void)windowWillClose:(NSNotification *)notification
{
    [self deactivate];
    [[NSApplication sharedApplication] terminate:self];
}

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
    if(_isDeviceInitialized == false)
        return;
    
    [[self openGLContext] makeCurrentContext];
    
    if (!TvDeviceId.isNull())
    {
        OdTvGsDevicePtr pDev = TvDeviceId.openObject();
        if(!pDev.isNull())
            pDev->update();
    }
    
    glFlush();
}

-(void)windowDidResize:(NSNotification *)notification
{
    [self resizeGL];
}

- (void) resizeGL
{
    if(_isDeviceInitialized == false)
        return;
    
    CGSize rectView = self.frame.size;
    if (!TvDeviceId.isNull())
    {
        OdTvDCRect screenRect(0, rectView.width, rectView.height, 0);
        OdTvGsDevicePtr pDevice = TvDeviceId.openObject();
        if(!pDevice.isNull())
            pDevice->onSize(screenRect);
    }
}

- (NSString*) WCHARToString: (wchar_t*) wcharIn {
    if (NSHostByteOrder() == NS_LittleEndian){
        return [NSString stringWithCString: (char *)wcharIn encoding:NSUTF32LittleEndianStringEncoding];
    }
    else{
        return [NSString stringWithCString: (char *)wcharIn encoding:NSUTF32BigEndianStringEncoding];
    }
}

@end

