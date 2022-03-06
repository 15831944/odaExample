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

#import "RenderViewController.h"
#import "BaseViewController.h"

@interface RenderViewController ()
{
    BaseViewController* pBaseController;
}

@end

@implementation RenderViewController

@synthesize glContext;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.

    self.glContext = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2 ];

    if (!self.glContext) {
        NSLog(@"Failed to create OpenGL ES 2.0 context");
        return;
    }

    // setup GL
    [EAGLContext setCurrentContext:self.glContext];
    glClearColor(.0f, .0f, .0f, .0f);
    GLKView *view = (GLKView *)self.view;
    view.context = self.glContext;
    view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
    [view setOpaque:NO];
    [view setBackgroundColor:[UIColor whiteColor]];
    
    pBaseController = (BaseViewController*)self.parentViewController;
    [self.openFileThread start];
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
        [pBaseController openFile:self.glContext];
    [self performSelector:@selector(onLoadFileDone) onThread:[NSThread mainThread] withObject:nil waitUntilDone:YES];
}

-(void)onLoadFileDone
{
    if(pBaseController)
        [pBaseController loadFileDone];
}

// destructor
-(void)dealloc
{
    if ([EAGLContext currentContext] == self.glContext)
    {
        [EAGLContext setCurrentContext:nil];
    }

    self.glContext = nil;
    pBaseController = nil;
}

// paint event, called every frame
-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect
{
    if(pBaseController)
        [pBaseController update];
}
// called on action
-(void)glkViewControllerUpdate:(GLKViewController *)controller
{
    //tvCore.update();
}

@end
