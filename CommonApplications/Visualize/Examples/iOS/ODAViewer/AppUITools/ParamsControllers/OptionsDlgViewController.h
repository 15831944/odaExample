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
#import <QuartzCore/QuartzCore.h>
#include "OdaCommon.h"
#include "TvModel.h"
#import "../BaseDialogViewController.h"
#import "../../AppCore/TviGlobalParameters.hpp"

NS_ASSUME_NONNULL_BEGIN

@interface OptionsDlgViewController : BaseDialogViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;

@property (strong, nonatomic) IBOutlet UISwitch *wcsSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *fpsSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *animationSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *partialOpenSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *useLimitMngSwitch;
@property (strong, nonatomic) IBOutlet UILabel *useLimitLabel;
@property (strong, nonatomic) IBOutlet UISwitch *sceneGraphSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *fxaaSwitch;

@property (strong, nonatomic) IBOutlet UILabel *limitValLbl;
@property (strong, nonatomic) IBOutlet UITextField *limitTxtField;
@property (strong, nonatomic) IBOutlet UIStepper *limitStepper;

@property (strong, nonatomic) IBOutlet UISwitch *fixedFrameRateSwitch;
@property (strong, nonatomic) IBOutlet UILabel *fpsLabel;
@property (strong, nonatomic) IBOutlet UISlider *fpsSlider;
@property (strong, nonatomic) IBOutlet UITextField *fpsValue;

- (void)showInView:(UIView *)aView animated:(BOOL)animated parameters:(TviGlobalParameters*)params;


@end

@interface OptionsRenderDlgViewController : BaseDialogViewController

@property (strong, nonatomic) IBOutlet UIView *popUpView;
@property (strong, nonatomic) IBOutlet UIScrollView *scrollView;
@property (strong, nonatomic) IBOutlet UIView *statisticView;

@property (strong, nonatomic) IBOutlet UISwitch *wcsSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *fpsSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *animationSwitch;
@property (strong, nonatomic) IBOutlet UISwitch *fxaaSwitch;

@property (strong, nonatomic) IBOutlet UISwitch *fixedFrameRateSwitch;
@property (strong, nonatomic) IBOutlet UILabel *fpsLabel;
@property (strong, nonatomic) IBOutlet UISlider *fpsSlider;
@property (strong, nonatomic) IBOutlet UITextField *fpsValue;

-(void)setModelStatistic: (OdTvGeometryStatistic*)modelStatistic;

- (void)showInView:(UIView *)aView animated:(BOOL)animated parameters:(TviGlobalParameters*)params;

@end

NS_ASSUME_NONNULL_END
