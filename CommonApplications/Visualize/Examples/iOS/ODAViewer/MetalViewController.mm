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

#import "MetalViewController.h"
#import "BaseViewController.h"

@interface MetalViewController ()
{
    BaseViewController* pBaseController;
}

@end

@implementation MetalViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    MTKView* mtkView = (MTKView*)self.view;
    mtkView.delegate = self;
    pBaseController = (BaseViewController*)self.parentViewController;
    [self.openFileThread start];
}

// destructor
-(void)dealloc
{
    pBaseController = nil;
}

- (void)drawInMTKView:(nonnull MTKView *)view {
    if(pBaseController)
        [pBaseController update];
}

- (void)mtkView:(nonnull MTKView *)view drawableSizeWillChange:(CGSize)size {
    if(pBaseController)
        [pBaseController update];
}


-(NSThread*)openFileThread
{
    if(!_openFileThread)
    {
        _openFileThread = [[NSThread alloc] initWithTarget:self selector:@selector(loadFile) object:nil];
    }
    
    return _openFileThread;
}

-(void)loadFile
{
    if(pBaseController)
        [pBaseController openFile: (MTKView*)self.view];
    [self performSelector:@selector(onLoadFileDone) onThread:[NSThread mainThread] withObject:nil waitUntilDone:YES];
}


-(void)onLoadFileDone
{
    if(pBaseController)
        [pBaseController loadFileDone];
}

@end
