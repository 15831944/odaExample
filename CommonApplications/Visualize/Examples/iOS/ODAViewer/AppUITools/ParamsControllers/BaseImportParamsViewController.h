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
#import "../../FilesViewController.h"
#include "OdaCommon.h"
#include "OdPlatform.h"
#include "../../AppCore/TviImportParameters.hpp"

NS_ASSUME_NONNULL_BEGIN

@interface BaseImportParamsViewController : UIViewController

@property (nonatomic, weak) UIViewController* currentParentController;

-(void)showAnimate;
-(void)removeAnimate;

@end

/////////////////////////////////////////////////////
///      DwgParamsViewController interface        ///
/////////////////////////////////////////////////////
@interface DwgParamsViewController : BaseImportParamsViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;

- (void)showInView:(UIView *)aView parameters:(TviDrwImportParams*)dwgParams;

// controls
@property (strong, nonatomic) IBOutlet UISwitch *objNamingSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *storeSourceSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *clearEmptyObjSwitch;

@property (strong, nonatomic) IBOutlet UISwitch *enableMTSwitch;
@property (strong, nonatomic) IBOutlet UILabel *maxThreadsLbl;
@property (strong, nonatomic) IBOutlet UILabel *cntThreadsLbl;
@property (strong, nonatomic) IBOutlet UIStepper *threadsCntStepper;

@property (strong, nonatomic) IBOutlet UISwitch *useAdvTessSwitch;
@property (strong, nonatomic) IBOutlet UILabel *facetResLbl;
@property (strong, nonatomic) IBOutlet UILabel *cntFacetResLbl;
@property (strong, nonatomic) IBOutlet UIStepper *facetResStepper;

// dc rect
@property (strong, nonatomic) IBOutlet UILabel *xMinValue;
@property (strong, nonatomic) IBOutlet UILabel *xMaxValue;
@property (strong, nonatomic) IBOutlet UILabel *yMinValue;
@property (strong, nonatomic) IBOutlet UILabel *yMaxValue;

@property (strong, nonatomic) IBOutlet UISwitch *lowMemorySwitch;
@property (strong, nonatomic) IBOutlet UIView *backgroundColor;

@end

/////////////////////////////////////////////////////
///      ObjParamsViewController interface        ///
/////////////////////////////////////////////////////
@interface ObjParamsViewController : BaseImportParamsViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;
@property (strong, nonatomic) IBOutlet UISwitch *calcNormalsSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *flipUVSwitch;
@property (strong, nonatomic) IBOutlet UIView *defaultColorView;

-(void)showInView:(UIView*)aView parameters:(TviObjImportParams*)objParams;

@end

/////////////////////////////////////////////////////
///      StlParamsViewController interface        ///
/////////////////////////////////////////////////////
@interface StlParamsViewController : BaseImportParamsViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;
@property (strong, nonatomic) IBOutlet UISwitch *fixNormalsSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *UnifyDuplVertSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *calcVertNormalsSwitch;
@property (strong, nonatomic) IBOutlet UIView *defaultColor;

-(void)showInView: (UIView*)aView parameters:(TviStlImportParams*)stlParams;

@end

/////////////////////////////////////////////////////
///      PrcParamsViewController interface        ///
/////////////////////////////////////////////////////
@interface PrcParamsViewController : BaseImportParamsViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;

@property (strong, nonatomic) IBOutlet UISwitch *objectNamingSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *storeSourceSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *clearEmptyObjects;
// dc rect
@property (strong, nonatomic) IBOutlet UILabel *xMinValue;
@property (strong, nonatomic) IBOutlet UILabel *xMaxValue;
@property (strong, nonatomic) IBOutlet UILabel *yMinValue;
@property (strong, nonatomic) IBOutlet UILabel *yMaxValue;

-(void)showInView: (UIView*)aView parameters:(TviPrcImportParams*)prcParams;

@end

/////////////////////////////////////////////////////
///      DgnParamsViewController interface        ///
/////////////////////////////////////////////////////
@interface DgnParamsViewController : BaseImportParamsViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;

@property (strong, nonatomic) IBOutlet UISwitch *objectNamingSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *storeSourceSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *clearEmptyObjects;
// dc rect
@property (strong, nonatomic) IBOutlet UILabel *xMinValue;
@property (strong, nonatomic) IBOutlet UILabel *xMaxValue;
@property (strong, nonatomic) IBOutlet UILabel *yMinValue;
@property (strong, nonatomic) IBOutlet UILabel *yMaxValue;

-(void)showInView: (UIView*)aView parameters:(TviDgnImportParams*)dgnParams;

@end


NS_ASSUME_NONNULL_END
