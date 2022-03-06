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

#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import <MetalKit/MetalKit.h>
#import "AppCore/TviGlobalParameters.hpp"
#import "AppCore/TviTools.h"
#include "TvImport.h"
#import "AppUITools/TviProgressControl.h"

NS_ASSUME_NONNULL_BEGIN

@interface BaseViewController : UIViewController<UITextFieldDelegate, UIGestureRecognizerDelegate>

@property (strong, nonatomic) IBOutlet UIToolbar *headerToolbar;
@property (strong, nonatomic) IBOutlet UIToolbar *footerToolbar;
@property (strong, nonatomic) IBOutlet UIView *statusBarMenu;
@property (strong, nonatomic) IBOutlet UILabel *deviceLabel;

@property (nonatomic, strong) NSString *cadFileName;
@property (strong, nonatomic) IBOutlet UIActivityIndicatorView *loadingIndicator;
@property (strong, nonatomic) IBOutlet UILabel *filenameLbl;
@property (strong, nonatomic) IBOutlet UILabel *fileOpenTimeLbl;

// UI properties
@property (strong, nonatomic) IBOutlet UIBarButtonItem *viewsBtn;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *navBtn;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *markupsBtn;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *sectioningBtn;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *styleBtn;
@property (strong, nonatomic) IBOutlet UIToolbar *toolsToolbar;
@property (strong, nonatomic) IBOutlet UIToolbar *styleMenuToolbar;
@property (strong, nonatomic) IBOutlet UIToolbar *markupMenuToolbar;
@property (strong, nonatomic) IBOutlet UIToolbar *navigationMenuToolbar;
@property (strong, nonatomic) IBOutlet UIToolbar *firstViewsMenuToolbar;
@property (strong, nonatomic) IBOutlet UIToolbar *secondViewsMenuToolbar;
@property (strong, nonatomic) IBOutlet UIButton *doneBtn;
@property (strong, nonatomic) IBOutlet UIButton *projectionItm;
@property (strong, nonatomic) IBOutlet UIButton *panelNameLbl;
@property (strong, nonatomic) IBOutlet UIBarButtonItem *panButton;
@property (strong, nonatomic) IBOutlet UIView *renderView;

@property (strong, nonatomic) IBOutlet TviProgressControl *progressMeter;

-(void)setGlobalParams: (TviGlobalParameters*)globalParams;
-(void)applyGlobalParams;
-(void)setImportParams: (OdTvBaseImportParams*)pImportParams;

-(void)showMessage: (NSString*)title message:(NSString*)msg;
-(void)showSaveMarkupDialog;
-(void)showLoadMarkupDialog;
-(BOOL)saveMarkup: (NSString*)name;
-(BOOL)loadMarkup: (NSString*)name;
-(BOOL)removeMarkup: (NSString*)name;

-(void)setBlocked: (BOOL)bBlocked;

-(void)startTimer;

-(void)saveFile: (NSString*)fileName 
	partialIndexing: (BOOL)bPartialIndexing
	VSFNotPDF: (BOOL)bVSFNotPDF;

-(void)stopLoadingIndicator: (double)time;

// reset dragger indicator
-(void)resetDraggerIndicator;
// add active dragger indicator
-(void)addBottomBorder: (UIView*)parentView;

-(void)update;
-(void)loadFileDone;

-(void)openFile: (NSObject*)context;

@end


@interface UIView (ExtCategory)

-(UIView*)hitTest:(CGPoint)point withEvent:(UIEvent *)event;

@end


NS_ASSUME_NONNULL_END
