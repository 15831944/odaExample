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
//  VisualizeViewController
//  iVisualizeViewer
//
//  Copyright © 2022 ODA. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include <OdaCommon.h>
#include <Gs/Gs.h>
#include <DbDatabase.h>
#include <GiContextForDbDatabase.h>
#include <DbGsManager.h>
#include "TvDatabase.h"
#include "TvFactory.h"
#include "TvError.h"

typedef NS_ENUM(NSUInteger, FileType) {
    kNew,
    kBuiltIn,
    kFromFile,
    kImport,
    kImportRevisions ,
} ;

@interface VisualizeViewController : GLKViewController
{
    CGPoint viewStartLocation;
    
    OdTvDatabaseId dbId;
    OdTvGsDeviceId deviceId;
}

@property (nonatomic, strong) NSString *cadFileName;
@property (strong, nonatomic) EAGLContext *glContext;


- (void) setupGL;
- (IBAction)handlePan:(UIPanGestureRecognizer *)recognizer;
- (IBAction)handlePinch:(UIPinchGestureRecognizer *)recognizer;
- (IBAction)handleRotate:(UIRotationGestureRecognizer *)recognizer;

- (OdGePoint3d)toWCS: (CGFloat)x andY:(CGFloat) y;
- (bool)viewCanRotate;
- (void) ClearData;

@end
