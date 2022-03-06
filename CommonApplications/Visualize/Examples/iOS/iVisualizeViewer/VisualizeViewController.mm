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
//
//  DwgViewController.m
//  iOdaApp
//
//  Created by Irina Bezruk on 03/11/15.
//  Copyright © 2015 ODA. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VisualizeViewController.h"

#include <Gs/GsBaseVectorizer.h>
#include <RxVariantValue.h>
#include <RxDictionary.h>
#include <ColorMapping.h>
#include <AbstractViewPE.h>

#include "iOdaAppServices.h"
#import "iStrConv.h"
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"

@interface VisualizeViewController ()
@end

@implementation VisualizeViewController

@synthesize cadFileName;
@synthesize glContext;


- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.

    NSLog(@"DwgViewController: %@", cadFileName);
    self.glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 ];
    
    if (!self.glContext) {
        NSLog(@"Failed to create OpenGL ES 2.0 context");
    }

    GLKView *view = (GLKView *)self.view;
    view.context = self.glContext;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    
    [self setupGL];
    [self LoadCadFile];
}

- (void)setupGL
{
    [EAGLContext setCurrentContext:self.glContext];
}

- (void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if (deviceId.isNull())
        return;
    // Set actual screen size for the generated geometry
    [self resizeGsDevice:rect];
    // Update device
    OdTvGsDevicePtr pDevice = deviceId.openObject();
    if(pDevice.isNull())
        return;
    pDevice->invalidate();
    pDevice->update();

}

static int backingWidth = 0;
static int backingHeight = 0;
-(void)resizeGsDevice: (CGRect)rect
{
    
    // Get size of our current window
    if (((GLint)rect.size.width != backingWidth) ||
        ((GLint)rect.size.height != backingHeight))
    {
      backingWidth = (GLint)rect.size.width;
      backingHeight = (GLint)rect.size.height;
      // Set the screen size for the generated geometry.
      double scaleF = [[UIScreen mainScreen] scale];
        
      OdGsDCRect screenRect( OdGsDCPoint(0, self.view.frame.size.height*scaleF),
                             OdGsDCPoint(self.view.frame.size.width*scaleF, 0) );
      //pDevice->onSize(screenRect);
    }
}

- (void)dealloc
{
    if ([EAGLContext currentContext] == self.glContext)
    {
        [EAGLContext setCurrentContext:nil];
    }
    
    self.glContext = nil;
}


- (OdGePoint3d)toWCS: (CGFloat)x andY:(CGFloat) y
{
    
    OdGePoint3d wcsPt((double)x*2, (double)y*2, 0.0);
    if(deviceId.isNull())
        return  wcsPt;
    OdTvGsDevicePtr pDevice = deviceId.openObject();
    if(pDevice.isNull())
        return wcsPt;
    OdTvGsViewId vId = pDevice->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    
    if (pView->isPerspective())
    {
        wcsPt.z = pView->projectionMatrix()(2, 3);
    }
    wcsPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    wcsPt.z =0.;
    wcsPt.transformBy(pView->eyeToWorldMatrix());
    return wcsPt;
}

- (IBAction)handlePan:(UIPanGestureRecognizer *)recognizer {
    if(deviceId.isNull())
        return;
    OdTvGsDevicePtr pDevice = deviceId.openObject();
    if(pDevice.isNull())
        return;
    
    CGPoint location = [recognizer translationInView:self.view];
    //(CGPoint)locationOfTouch:(NSUInteger)touchIndex inView:(nullable UIView*)view;
    CGPoint translation;
    switch(recognizer.state) {
        case UIGestureRecognizerStateBegan:
            viewStartLocation = location;
            translation.x = location.x - viewStartLocation.x;
            translation.y = location.y - viewStartLocation.y;
            break;
        case  UIGestureRecognizerStateChanged:
            translation.x = location.x - viewStartLocation.x;
            translation.y = location.y - viewStartLocation.y;
            viewStartLocation.x += translation.x;
            viewStartLocation.y += translation.y;
            break;
        default:
            break;
    }
    
    OdTvGsViewId vId = pDevice->getActiveView();
    OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
    
    OdGeVector3d delta = [self toWCS:-translation.x andY:-translation.y] - [self toWCS:0.0f andY:0.0f];
    delta.transformBy(pView->viewingMatrix());
    pView->dolly(delta.x, delta.y, delta.z);
    
    
    //OdGeVector3d delta ((double)translation.x, (double)translation.y, 0.0);
    //delta.transformBy(pView->viewingMatrix());
    //pView->orbit(delta.x, delta.y);
    
}


- (IBAction)handlePinch:(UIPinchGestureRecognizer *)recognizer
{
    if (!deviceId.isNull())
    {
        if ([recognizer state] == UIGestureRecognizerStateBegan || [recognizer state] == UIGestureRecognizerStateChanged)
        {
            OdTvGsDevicePtr pDevice = deviceId.openObject();
            if(pDevice.isNull())
                return;
            OdTvGsViewId vId = pDevice->getActiveView();
            OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
            
            pView->zoom((double)(recognizer.scale));
            
            recognizer.scale = 1.0;
        }
    }
}

- (bool)viewCanRotate
{
#if 0
    if (pDb.isNull())
    {
        return false;
    }
    return (pDb->getTILEMODE()) ? true : false;
#endif
    return true;
}


- (IBAction)handleRotate:(UIRotationGestureRecognizer *)recognizer
{
    if (!deviceId.isNull())
    {
        if ([recognizer state] == UIGestureRecognizerStateBegan || [recognizer state] == UIGestureRecognizerStateChanged)
        {
            OdTvGsDevicePtr pDevice = deviceId.openObject();
            if(pDevice.isNull())
                return;
            OdTvGsViewId vId = pDevice->getActiveView();
            OdTvGsViewPtr pView = vId.openObject(OdTv::kForWrite);
            
            double angle = (recognizer.rotation); //already in radians
            pView->roll(angle);
            recognizer.rotation = 0;
        }
    }
}

// Method for remove data from database
- (void) ClearData
{
    if (dbId.isNull() && deviceId.isNull())
        return;
    
    // clear views
    {
        OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);
        if(!pDevice.isNull())
            pDevice->eraseAllViews();
    }
    
    //retrieve the factory id
    OdTvFactoryId factId = odTvGetFactory();
    
    //remove all
    factId.clearDatabases();
    
    //flush id's
    dbId.setNull();
    deviceId.setNull();
}

-(BOOL) LoadCadFile
{
    BOOL rtn = false;
    // Remove previous data and create new
   [self ClearData];
    
    // retrieve the factory id
    OdTvFactoryId factId = odTvGetFactory();
    
    NSString *extension = [[cadFileName pathExtension] lowercaseString];
    if ([extension isEqualToString:@"obj"]) {
        // Try to import file
        OdTvResult rc = tvOk;
        try
        {
            // Declare import parameters for .obj file and set file path
            OdTvObjImportParams  m_objImportParam;
            m_objImportParam.setFilePath(NSString2OdString(cadFileName));
            
            // Import database
            dbId = factId.importFile(&m_objImportParam, &rc);
            
            if (rc != tvOk)
                NSLog(@"\nImport of file was failed");
        }
        catch (OdTvError& e)
        {
            NSLog(@"\nImport of file was failed");
            
        }
    } 
	else if ([extension isEqualToString:@"dwg"])
    {
        // Try to import file
        try
        {
            // Declare import parameters for .dwg file and set file path
            OdTvDwgImportParams dwgImportParam;
            dwgImportParam.setFilePath(NSString2OdString(cadFileName));
            CGRect clRrect  = self.view.frame;
            double scaleF = [[UIScreen mainScreen] scale];
            OdTvDCRect rect((long)clRrect.origin.x, (long)clRrect.size.width*scaleF,  (long)clRrect.size.height*scaleF, (long)clRrect.origin.y);
            dwgImportParam.setDCRect(rect);
            
            // Import database
            OdTvResult rc = tvOk;
            dbId = factId.importFile(&dwgImportParam, &rc);
            
            if (rc != tvOk)
                NSLog(@"\nImport of file was failed");
        }
        catch (...)
        {
            NSLog(@"\nImport of file was failed");
            
        }
    }
	else if ([extension isEqualToString:@"vsf"]) 
	{
        // Try to read file
        OdTvResult rc = tvOk;
        try
        {
            dbId = factId.readFile(NSString2OdString(cadFileName));
        }
        catch (OdTvError& e)
        {
            NSLog(@"\nFile read was failed");
            
        }
    }
    
    // Get device (here it is always the first device) and setup
    if (dbId.isValid())
    {
        OdTvDatabasePtr pDb = dbId.openObject();
        if (!pDb.isNull())
        {
            OdTvDevicesIteratorPtr pIt = pDb->getDevicesIterator();
            if (!pIt.isNull())
            {
                deviceId = pIt->getDevice();
                
                // Get rect from current window
                CGRect clRrect  = self.view.frame;
                
                double scaleF = [[UIScreen mainScreen] scale];
                OdTvDCRect rect((long)clRrect.origin.x,
                                (long)clRrect.size.width*scaleF,  (long)clRrect.size.height*scaleF, (long)clRrect.origin.y);

                OdTvGsDevicePtr pDevice = deviceId.openObject(OdTv::kForWrite);
                if(pDevice.isNull())
                    return NO;
                
                // Setup device
                pDevice->setupGsWithContext((void*)((OdIntPtr)self.glContext), rect, OdTvGsDevice::kOpenGLES2, NULL);
                pDevice->setOption(OdTvGsDevice::kUseOverlayBuffers, false);
                pDevice->setOption(OdTvGsDevice::kCreateGLContext, false);

                // Update device
                pDevice->onSize(rect);
                pDevice->update();
                
                return YES;
            }
        }
    }
    return rtn;
}


@end

