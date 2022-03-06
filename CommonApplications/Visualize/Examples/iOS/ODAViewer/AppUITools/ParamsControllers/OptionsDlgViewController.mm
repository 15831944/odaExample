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

#import "OptionsDlgViewController.h"
#import "../../BaseViewController.h"
#import "../TviRectangle.h"

@interface OptionsDlgViewController ()
{
    TviGlobalParameters *pGlobalParams;
}

@end

@implementation OptionsDlgViewController

@synthesize popUpView;

- (void)viewDidLoad {
    self.view.backgroundColor=[[UIColor blackColor] colorWithAlphaComponent:.4];
    self.popUpView.layer.cornerRadius = 5;
    self.popUpView.layer.shadowOpacity = 0.8;
    self.popUpView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
    [super viewDidLoad];
}

- (void)showInView:(UIView *)aView animated:(BOOL)animated parameters:(nonnull TviGlobalParameters *)params
{
    pGlobalParams = params;
    
    [self.view setFrame:[aView frame]];
    [aView addSubview:self.view];
    if (animated) {
        [self showAnimate];
    }
    
    [_wcsSwitch setOn: pGlobalParams->getWcsEnabled()];
    [_fpsSwitch setOn:pGlobalParams->getFpsEnabled()];
    [_animationSwitch setOn:pGlobalParams->getAnimationEnabled()];
    [_partialOpenSwitch setOn:pGlobalParams->getPartialOpen()];
    [_useLimitMngSwitch setOn:pGlobalParams->getUseLimitManager()];
    [_useLimitLabel setEnabled:pGlobalParams->getPartialOpen()];
    [_useLimitMngSwitch setEnabled:pGlobalParams->getPartialOpen()];
    [_sceneGraphSwitch setOn:pGlobalParams->getUseSceneGraph()];
    [_fxaaSwitch setOn:pGlobalParams->getUseFXAA()];
    
    [_limitValLbl setEnabled:[_useLimitMngSwitch isOn]];
    [_limitTxtField setEnabled:[_useLimitMngSwitch isOn]];
    [_limitStepper setEnabled:[_useLimitMngSwitch isOn]];
    [_limitStepper setValue:pGlobalParams->getMemoryLimit()];
    _limitTxtField.text = [NSString stringWithFormat:@"%lu", pGlobalParams->getMemoryLimit()];
    
    [_fixedFrameRateSwitch setOn:pGlobalParams->getFixedFrameRate()];
    [_fpsSlider setValue:pGlobalParams->getFpsValue()];
    [_fpsValue setText:[NSString stringWithFormat:@"%d", (int)pGlobalParams->getFpsValue()]];
    // on\off controlls
    [_fpsLabel setEnabled: [_fixedFrameRateSwitch isOn]];
    [_fpsSlider setEnabled:[_fixedFrameRateSwitch isOn]];
    [_fpsValue setEnabled:[_fixedFrameRateSwitch isOn]];
}

- (IBAction)onCancelBtnDown:(UIButton *)sender
{
    [self removeAnimate];
}

- (IBAction)onOkBtnDown:(UIButton *)sender
{
    pGlobalParams->setWcsEnabled([_wcsSwitch isOn]);
    pGlobalParams->setFpsEnabled([_fpsSwitch isOn]);
    pGlobalParams->setAnimationEnabled([_animationSwitch isOn]);
    pGlobalParams->setPartialOpen([_partialOpenSwitch isOn]);
    pGlobalParams->setUseLimitManager([_useLimitMngSwitch isOn]);
    pGlobalParams->setUseSceneGraph([_sceneGraphSwitch isOn]);
    pGlobalParams->setUseFXAA([_fxaaSwitch isOn]);
    pGlobalParams->setMemoryLimit([_limitStepper value]);
    pGlobalParams->setFixedFrameRate([_fixedFrameRateSwitch isOn]);
    pGlobalParams->setFpsValue([_fpsSlider value]);
    
    pGlobalParams->writeToDefaults();
    
    [self removeAnimate];
}

- (IBAction)onPartialOpenChanged:(UISwitch *)sender {
    [_useLimitMngSwitch setEnabled:[_partialOpenSwitch isOn]];
    [_useLimitLabel setEnabled:[_partialOpenSwitch isOn]];
    if([_useLimitMngSwitch isOn] && ! [_partialOpenSwitch isOn])
        [_useLimitMngSwitch setOn:NO];
    else if([_partialOpenSwitch isOn] && pGlobalParams->getUseLimitManager())
        [_useLimitMngSwitch setOn:YES];
    
    [_limitValLbl setEnabled:[_useLimitMngSwitch isOn]];
    [_limitTxtField setEnabled:[_useLimitMngSwitch isOn]];
    [_limitStepper setEnabled:[_useLimitMngSwitch isOn]];
}

- (IBAction)onUseLimitChanged:(UISwitch *)sender {
    [_limitValLbl setEnabled:[_useLimitMngSwitch isOn]];
    [_limitTxtField setEnabled:[_useLimitMngSwitch isOn]];
    [_limitStepper setEnabled:[_useLimitMngSwitch isOn]];
}

- (IBAction)onLimitValueChanged:(UIStepper *)sender {
    _limitTxtField.text = [NSString stringWithFormat:@"%lu", (unsigned long)[_limitStepper value]];
}

- (IBAction)onLimitEditingDone:(UITextField *)sender {
    int val = [_limitTxtField.text intValue];
    if(val <= 0) {
        _limitTxtField.text = [NSString stringWithFormat:@"%lu", (unsigned long)[_limitStepper value]];
    }
    else
        [_limitStepper setValue:val];
}

- (IBAction)onFixedFrameRateChanged:(UISwitch *)sender {
    [_fpsLabel setEnabled: [sender isOn]];
    [_fpsSlider setEnabled:[sender isOn]];
    [_fpsValue setEnabled:[sender isOn]];
}

- (IBAction)fpsChanged:(UISlider *)sender {
    [_fpsValue setText:[NSString stringWithFormat:@"%d", (int)[sender value]]];
}

@end


@interface OptionsRenderDlgViewController ()
{
    TviGlobalParameters *pGlobalParams;
    OdTvGeometryStatistic* pModelStatistic;
    int yOffset;
    int controlHeight;
    int headerGroupXOffset;
    int groupTopOffset, groupLeftOffset, groupWidth;
    int labelOffset;
    bool isInit;
}

@end

@implementation OptionsRenderDlgViewController

@synthesize popUpView;

- (void)viewDidLoad {
    self.view.backgroundColor=[[UIColor blackColor] colorWithAlphaComponent:.4];
    self.popUpView.layer.cornerRadius = 5;
    self.popUpView.layer.shadowOpacity = 0.8;
    self.popUpView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
    [super viewDidLoad];
    yOffset = 0;
    controlHeight = 30;
    headerGroupXOffset = 20;
    groupTopOffset = 5;
    groupLeftOffset = 10;
    labelOffset = 10;
    isInit = false;
}

-(void)setModelStatistic:(OdTvGeometryStatistic *)modelStatistic
{
    pModelStatistic = modelStatistic;
}

- (void)showInView:(UIView *)aView animated:(BOOL)animated parameters:(nonnull TviGlobalParameters *)params
{
    pGlobalParams = params;
    
    [self.view setFrame:[aView frame]];
    [aView addSubview:self.view];
    if (animated) {
        [self showAnimate];
    }
    
    [_wcsSwitch setOn: pGlobalParams->getWcsEnabled()];
    [_fpsSwitch setOn:pGlobalParams->getFpsEnabled()];
    [_animationSwitch setOn:pGlobalParams->getAnimationEnabled()];
    [_fxaaSwitch setOn:pGlobalParams->getUseFXAA()];
    
    [_fixedFrameRateSwitch setOn:pGlobalParams->getFixedFrameRate()];
    [_fpsSlider setValue:pGlobalParams->getFpsValue()];
    [_fpsValue setText:[NSString stringWithFormat:@"%d", (int)pGlobalParams->getFpsValue()]];
    // on\off controlls
    [_fpsLabel setEnabled: [_fixedFrameRateSwitch isOn]];
    [_fpsSlider setEnabled:[_fixedFrameRateSwitch isOn]];
    [_fpsValue setEnabled:[_fixedFrameRateSwitch isOn]];
}

- (IBAction)onCancelBtnDown:(UIButton *)sender
{
    [self removeAnimate];
}

- (IBAction)onOkBtnDown:(UIButton *)sender
{
    pGlobalParams->setWcsEnabled([_wcsSwitch isOn]);
    pGlobalParams->setFpsEnabled([_fpsSwitch isOn]);
    pGlobalParams->setAnimationEnabled([_animationSwitch isOn]);
    pGlobalParams->setUseFXAA([_fxaaSwitch isOn]);
    pGlobalParams->setFixedFrameRate([_fixedFrameRateSwitch isOn]);
    pGlobalParams->setFpsValue([_fpsSlider value]);
    
    if(self.currentParentController)
    {
        BaseViewController *pRenderCtrl = (BaseViewController*)self.currentParentController;
        if(pRenderCtrl) {
            [pRenderCtrl applyGlobalParams];
        }
    }
    
    pGlobalParams->writeToDefaults();
    
    [self removeAnimate];
}

- (IBAction)onFixedFrameRateChanged:(UISwitch *)sender {
    [_fpsLabel setEnabled: [sender isOn]];
    [_fpsSlider setEnabled:[sender isOn]];
    [_fpsValue setEnabled:[sender isOn]];
}

- (IBAction)fpsChanged:(UISlider *)sender {
    [_fpsValue setText:[NSString stringWithFormat:@"%d", (int)[sender value]]];
}

- (IBAction)onShowStatClick:(UIButton *)sender
{
    if(!isInit)
    {
        UIView *contentView = [[UIView alloc] initWithFrame: CGRectMake(0, 0, _scrollView.frame.size.width, 0)];
        [contentView setBackgroundColor:[[UIColor alloc] initWithRed:0.97 green:0.97 blue:0.97 alpha:1.]];
        [_scrollView addSubview:contentView];
        groupWidth = _scrollView.frame.size.width - 18;
        
        [self addEntitiesInfo:contentView];
        [self addGeometriesInfo:contentView];
        [self addSubGeomInfo:contentView];
        
        _scrollView.contentSize = CGSizeMake(_scrollView.frame.size.width, contentView.frame.size.height);
        isInit = true;
    }
    
    [_statisticView setHidden:NO];
    [popUpView setHidden:YES];
    
    _statisticView.transform = CGAffineTransformMakeScale(1.3, 1.3);
    _statisticView.alpha = 0;
    [UIView animateWithDuration:.25 animations:^{
        self->_statisticView.alpha = 1;
        self->_statisticView.transform = CGAffineTransformMakeScale(1, 1);
    }];
}

- (IBAction)onOkStatClick:(UIButton *)sender {
    [UIView animateWithDuration:.25 animations:^{
        self->_statisticView.transform = CGAffineTransformMakeScale(1.3, 1.3);
        self->_statisticView.alpha = 0.0;
    } completion:^(BOOL finished) {
        if (finished) {
            [self->_statisticView setHidden:YES];
            [self->popUpView setHidden:NO];
        }
    }];
}

-(void)addLabels: (NSString*)name count: (OdUInt64)count parentView:(UIView*)parentView
{
    UILabel *lbl1 = [[UILabel alloc] initWithFrame:CGRectMake(labelOffset, parentView.frame.size.height, (parentView.frame.size.width - labelOffset) * 0.75, controlHeight)];
    lbl1.text = name;
    UILabel *lbl2 = [[UILabel alloc] initWithFrame:CGRectMake(lbl1.frame.size.width, parentView.frame.size.height, (parentView.frame.size.width - labelOffset) * 0.25, controlHeight)];
    [lbl2 setTextAlignment:NSTextAlignmentRight];
    lbl2.text = [NSString stringWithFormat:@"%lu", count];
    
    CGRect rect = [parentView frame];
    rect.size.height += controlHeight;
    [parentView setFrame:rect];
    
    [parentView addSubview:lbl1];
    [parentView addSubview:lbl2];
}

-(void)addEntitiesInfo: (UIView*)parentView
{
    if(!pModelStatistic)
        return;
    OdUInt64 entity = pModelStatistic->getCount(OdTvGeometryStatistic::kEntity);
    OdUInt64 insert = pModelStatistic->getCount(OdTvGeometryStatistic::kInsert);
    OdUInt64 light = pModelStatistic->getCount(OdTvGeometryStatistic::kLight);
    if(entity == 0 && insert == 0 && light == 0)
        return;
    UILabel *header = [[UILabel alloc] initWithFrame:CGRectMake(headerGroupXOffset, yOffset, parentView.frame.size.width, controlHeight)];
    header.text = @"Entity objects";
    [parentView addSubview:header];
    yOffset += controlHeight;
    TviRectangle *entGroup = [[TviRectangle alloc] initWithFrame:CGRectMake(groupLeftOffset, yOffset, groupWidth, 0)];
    entGroup.borderColor = [UIColor darkGrayColor];
    entGroup.borderWidth = 1;
    if(entity > 0)
        [self addLabels:@"Num of entities:" count:entity parentView:entGroup];
    if(insert > 0)
        [self addLabels:@"Num of inserts:" count:insert parentView:entGroup];
    if(light > 0)
        [self addLabels:@"Num of lights:" count:light parentView:entGroup];
    
    yOffset += entGroup.frame.size.height;
    
    CGRect rect = parentView.frame;
    rect.size.height += entGroup.frame.size.height + controlHeight;
    [parentView setFrame:rect];
    
    [parentView addSubview:entGroup];
}

-(void)addGeometriesInfo: (UIView*)parentView
{
    if(!pModelStatistic)
        return;
    
    NSMutableArray *indexes = [[NSMutableArray alloc] init];
    for(int i = (int)OdTvGeometryStatistic::kPolyline; i < (int)OdTvGeometryStatistic::kPoints; i++) {
        if(pModelStatistic->getCount( (OdTvGeometryStatistic::Types)i) > 0 ) {
            [indexes addObject:[NSNumber numberWithInt:i]];
        }
    }
    if([indexes count] == 0)
        return;
    
    NSArray *names = [NSArray arrayWithObjects:@"Num of polylines", @"Num of circles", @"Num of circle wedges", @"Num of circle arcs", @"Num of ellipses", @"Num of elliptic arcs", @"Num of polygons", @"Num of text", @"Num of shells", @"Num of spheres", @"Num of cylinders", @"Num of boxes", @"Num of inserts", @"Num of sub entities", @"Num of nurbs", @"Num of raster images", @"Num of infinite lines", @"Num of meshes", @"Num of point clouds", @"Num of rcs point clouds", @"Num of grids", @"Num of colored shapes", @"Num of breps", nil];
    
    yOffset += groupTopOffset;
    UILabel *header = [[UILabel alloc] initWithFrame:CGRectMake(headerGroupXOffset, yOffset, parentView.frame.size.width, controlHeight)];
    header.text = @"Geometry objects";
    [parentView addSubview:header];
    yOffset += controlHeight;
    TviRectangle *geomGroup = [[TviRectangle alloc] initWithFrame:CGRectMake(groupLeftOffset, yOffset, groupWidth, 0)];
    geomGroup.borderColor = [UIColor darkGrayColor];
    geomGroup.borderWidth = 1;
    
    for(NSNumber *index in indexes) {
        int ind = [index intValue];
        [self addLabels:names[ind - (int)OdTvGeometryStatistic::kPolyline] count:pModelStatistic->getCount((OdTvGeometryStatistic::Types)ind) parentView:geomGroup];
    }
    
    yOffset += geomGroup.frame.size.height;
    
    CGRect rect = parentView.frame;
    rect.size.height += geomGroup.frame.size.height + controlHeight + groupTopOffset;
    [parentView setFrame:rect];
    
    [parentView addSubview:geomGroup];
}

-(void)addSubGeomInfo: (UIView*)parentView
{
    if(!pModelStatistic)
        return;
    
    OdUInt64 pnts = pModelStatistic->getCount(OdTvGeometryStatistic::kPoints);
    OdUInt64 faces = pModelStatistic->getCount(OdTvGeometryStatistic::kFace);
    if(pnts == 0 && faces == 0)
        return;
    yOffset += groupTopOffset;
    UILabel *header = [[UILabel alloc] initWithFrame:CGRectMake(headerGroupXOffset, yOffset, parentView.frame.size.width, controlHeight)];
    header.text = @"Geometry info";
    [parentView addSubview:header];
    yOffset += controlHeight;
    TviRectangle *subGeomGroup = [[TviRectangle alloc] initWithFrame:CGRectMake(groupLeftOffset, yOffset, groupWidth, 0)];
    subGeomGroup.borderColor = [UIColor darkGrayColor];
    subGeomGroup.borderWidth = 1;
    if(pnts > 0)
        [self addLabels:@"Num of points:" count:pnts parentView:subGeomGroup];
    if(faces > 0)
        [self addLabels:@"Num of faces:" count:faces parentView:subGeomGroup];
    
    yOffset += subGeomGroup.frame.size.height;
    
    CGRect rect = parentView.frame;
    rect.size.height += subGeomGroup.frame.size.height + controlHeight + groupTopOffset;
    [parentView setFrame:rect];
    
    [parentView addSubview:subGeomGroup];
}

@end

