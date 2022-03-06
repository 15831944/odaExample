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

#import "BaseImportParamsViewController.h"

/////////////////////////////////////////////////////
/// BaseImportParamsViewController implementation ///
/////////////////////////////////////////////////////
@interface BaseImportParamsViewController ()

@end

@implementation BaseImportParamsViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

-(void)showAnimate
{
    self.view.transform = CGAffineTransformMakeScale(1.3, 1.3);
    self.view.alpha = 0;
    [UIView animateWithDuration:.25 animations:^{
        self.view.alpha = 1;
        self.view.transform = CGAffineTransformMakeScale(1, 1);
    }];
}

-(void)removeAnimate
{
    [UIView animateWithDuration:.25 animations:^{
        self.view.transform = CGAffineTransformMakeScale(1.3, 1.3);
        self.view.alpha = 0.0;
    } completion:^(BOOL finished) {
        if (finished) {
            [self.view removeFromSuperview];
        }
    }];
}

-(void)setupView:(UIView*)popUpView
{
    self.view.backgroundColor=[[UIColor blackColor] colorWithAlphaComponent:.4];
    popUpView.layer.cornerRadius = 5;
    popUpView.layer.shadowOpacity = 0.8;
    popUpView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
}

-(void)addToView:(UIView*)aView
{
    [self.view setFrame:[aView frame]];
    [aView addSubview:self.view];
}

-(void)accept: (OdTvBaseImportParams*)params
{
    if(self.currentParentController)
    {
        FilesViewController *pFilesCtrl = (FilesViewController*)self.currentParentController;
        if(pFilesCtrl) {
            [pFilesCtrl openFile: params];
        }
    }
    
    [self removeAnimate];
}

@end

/////////////////////////////////////////////////////
///    DwgParamsViewController implementation     ///
/////////////////////////////////////////////////////
@interface DwgParamsViewController ()
{
    TviDrwImportParams* pDwgParams;
}

@end

@implementation DwgParamsViewController

@synthesize popUpView;

- (void)viewDidLoad {
    [self setupView:popUpView];
    [super viewDidLoad];
}

-(void)showInView:(UIView *)aView parameters:(nonnull TviDrwImportParams *)dwgParams
{
    [self addToView:aView];
    pDwgParams = dwgParams;
    // fill controls from params
    OdTvDCRect rect = pDwgParams->getDCRect();
    _xMinValue.text = [NSString stringWithFormat: @"%ld", rect.xmin];
    _xMaxValue.text = [NSString stringWithFormat: @"%ld", rect.xmax];
    _yMinValue.text = [NSString stringWithFormat: @"%ld", rect.ymin];
    _yMaxValue.text = [NSString stringWithFormat: @"%ld", rect.ymax];
    [self setControlsFromParams:pDwgParams];
    
    [self showAnimate];
}

-(void)setControlsFromParams:(OdTvDwgImportParams*)params
{
    [_objNamingSwitch setOn:params->getObjectNaming()];
    [_storeSourceSwitch setOn:params->getStoreSourceObjects()];
    [_clearEmptyObjSwitch setOn:params->getClearEmptyObjects()];
    [_enableMTSwitch setOn:params->getMultithreading()];
    [_threadsCntStepper setValue:(double)params->getCountOfThreads()];
    _cntThreadsLbl.text = [NSString stringWithFormat:@"%d", params->getCountOfThreads()];
    [_useAdvTessSwitch setOn:params->getUseAdvancedTess()];
    [_facetResStepper setValue:params->getFacetRes()];
    _cntFacetResLbl.text = [NSString stringWithFormat:@"%.2f", params->getFacetRes()];
    [_lowMemorySwitch setOn:params->getOpenSourcePartial()];
    OdUInt32 iColor = params->getBackground();
    UIColor* color = [[UIColor alloc]initWithRed:(ODGETRED(iColor)/255.) green:(ODGETGREEN(iColor)/255.) blue:(ODGETBLUE(iColor)/255.) alpha:1.];
    [_backgroundColor setBackgroundColor:color];
}

-(void)applyParams
{
    pDwgParams->setObjectNaming([_objNamingSwitch isOn]);
    pDwgParams->setStoreSourceObjects([_storeSourceSwitch isOn]);
    pDwgParams->setClearEmptyObjects([_clearEmptyObjSwitch isOn]);
    pDwgParams->setMultithreading([_enableMTSwitch isOn]);
    pDwgParams->setCountOfThreads((OdUInt16)[_threadsCntStepper value]);
    pDwgParams->setUseAdvancedTess([_useAdvTessSwitch isOn]);
    pDwgParams->setFacetRes([_facetResStepper value]);
    pDwgParams->setOpenSourcePartial([_lowMemorySwitch isOn]);
}

// enable muthithreading changed
- (IBAction)onMTEnabledChanged:(UISwitch *)sender {
    [_maxThreadsLbl setEnabled:[sender isOn]];
    [_cntThreadsLbl setEnabled:[sender isOn]];
    [_threadsCntStepper setEnabled:[sender isOn]];
}

// use advanced tess changed
- (IBAction)onUseAdvTessChanged:(UISwitch *)sender {
    [_facetResLbl setEnabled:[sender isOn]];
    [_cntFacetResLbl setEnabled:[sender isOn]];
    [_facetResStepper setEnabled:[sender isOn]];
}

- (IBAction)onThreadsCntChanged:(UIStepper *)sender {
    _cntThreadsLbl.text = [NSString stringWithFormat:@"%d", (int)[_threadsCntStepper value]];
}

- (IBAction)onFacetResValueChanged:(UIStepper *)sender {
    _cntFacetResLbl.text = [NSString stringWithFormat:@"%.2f", [_facetResStepper value] ];
}

// button events
- (IBAction)onResetDown:(UIButton *)sender {
    OdTvDwgImportParams params;
    [self setControlsFromParams:&params];
}

- (IBAction)onOkBtnDown:(UIButton *)sender {
    [self applyParams];
    pDwgParams->writeToDefaults();
    [self accept:pDwgParams];
}

- (IBAction)onCancelBtnDown:(UIButton *)sender {
    [self removeAnimate];
}
@end

/////////////////////////////////////////////////////
///     ObjParamsViewController implementation    ///
/////////////////////////////////////////////////////
@interface ObjParamsViewController ()
{
    TviObjImportParams* pObjParams;
}
@end

@implementation ObjParamsViewController

@synthesize popUpView;

- (void)viewDidLoad {
    [self setupView:popUpView];
    [super viewDidLoad];
}

-(void)showInView:(UIView *)aView parameters:(TviObjImportParams*)objParams
{
    [self addToView:aView];
    pObjParams = objParams;
    [self setControlsFromParams:objParams];
    
    [self showAnimate];
}

-(void)setControlsFromParams:(OdTvObjImportParams*)params
{
    [_calcNormalsSwitch setOn:params->getCalculateNormals()];
    [_flipUVSwitch setOn:params->getBrepFlipUVCoordinates()];
    OdUInt32 iColor = params->getDefaultColor();
    UIColor* color = [[UIColor alloc]initWithRed:(ODGETRED(iColor)/255.) green:(ODGETGREEN(iColor)/255.) blue:(ODGETBLUE(iColor)/255.) alpha:1.];
    [_defaultColorView setBackgroundColor:color];
}

-(void)applyParams
{
    pObjParams->setCalculateNormals([_calcNormalsSwitch isOn]);
    pObjParams->setBrepFlipUVCoordinates([_flipUVSwitch isOn]);
}

// buttons events

- (IBAction)onCancelClick:(UIButton *)sender {
    [self removeAnimate];
}

- (IBAction)onOkClick:(UIButton *)sender {
    [self applyParams];
    pObjParams->writeToDefaults();
    [self accept:pObjParams];
}

- (IBAction)onResetClick:(id)sender {
    OdTvObjImportParams params;
    [self setControlsFromParams:&params];
}

@end

/////////////////////////////////////////////////////
///     StlParamsViewController implementation    ///
/////////////////////////////////////////////////////
@interface StlParamsViewController ()
{
    TviStlImportParams* pStlParams;
}
@end

@implementation StlParamsViewController

@synthesize popUpView;

- (void)viewDidLoad {
    [self setupView:popUpView];
    [super viewDidLoad];
}

-(void)showInView:(UIView *)aView parameters:(TviStlImportParams *)stlParams
{
    [self addToView:aView];
    pStlParams = stlParams;
    [self setControlsFromParams:pStlParams];
    [self showAnimate];
}

-(void)setControlsFromParams:(OdTvStlImportParams*)params
{
    [_fixNormalsSwitch setOn:params->getFixNormals()];
    [_UnifyDuplVertSwitch setOn:params->getUnifyDuplicatedVertices()];
    [_calcVertNormalsSwitch setOn:params->getCalcNormalsAtVertices()];
    OdUInt32 iColor = params->getDefaultColor();
    UIColor* color = [[UIColor alloc]initWithRed:(ODGETRED(iColor)/255.) green:(ODGETGREEN(iColor)/255.) blue:(ODGETBLUE(iColor)/255.) alpha:1.];
    [_defaultColor setBackgroundColor:color];
}

-(void)applyParams
{
    pStlParams->setFixNormals([_fixNormalsSwitch isOn]);
    pStlParams->setUnifyDuplicatedVertices([_UnifyDuplVertSwitch isOn]);
    pStlParams->setCalcNormalsAtVertices([_calcVertNormalsSwitch isOn]);
}

// buttons events

- (IBAction)onCancelClick:(UIButton *)sender {
    [self removeAnimate];
}

- (IBAction)onOkClick:(UIButton *)sender {
    [self applyParams];
    pStlParams->writeToDefaults();
    [self accept:pStlParams];
}

- (IBAction)onResetClick:(UIButton *)sender {
    OdTvStlImportParams params;
    [self setControlsFromParams:&params];
}

@end

/////////////////////////////////////////////////////
///     PrcParamsViewController implementation    ///
/////////////////////////////////////////////////////
@interface PrcParamsViewController ()
{
    TviPrcImportParams* pPrcParams;
}
@end

@implementation PrcParamsViewController

@synthesize popUpView;

- (void)viewDidLoad {
    [self setupView:popUpView];
    [super viewDidLoad];
}

-(void)showInView:(UIView *)aView parameters:(TviPrcImportParams *)prcParams
{
    [self addToView:aView];
    pPrcParams = prcParams;
    OdTvDCRect rect = pPrcParams->getDCRect();
    _xMinValue.text = [NSString stringWithFormat: @"%ld", rect.xmin];
    _xMaxValue.text = [NSString stringWithFormat: @"%ld", rect.xmax];
    _yMinValue.text = [NSString stringWithFormat: @"%ld", rect.ymin];
    _yMaxValue.text = [NSString stringWithFormat: @"%ld", rect.ymax];
    // fill controls from params
    [self setControlsFromParams:pPrcParams];
    [self showAnimate];
}

-(void)setControlsFromParams:(OdTvPrcImportParams*)params
{
    [_objectNamingSwitch setOn:params->getObjectNaming()];
    [_storeSourceSwitch setOn:params->getStoreSourceObjects()];
    [_clearEmptyObjects setOn:params->getClearEmptyObjects()];
}

-(void)applyParams
{
    pPrcParams->setObjectNaming([_objectNamingSwitch isOn]);
    pPrcParams->setStoreSourceObjects([_storeSourceSwitch isOn]);
    pPrcParams->setClearEmptyObjects([_clearEmptyObjects isOn]);
}

// buttons events
- (IBAction)onCancelClick:(UIButton *)sender {
    [self removeAnimate];
}

- (IBAction)onOkClick:(UIButton *)sender {
    [self applyParams];
    pPrcParams->writeToDefaults();
    [self accept:pPrcParams];
}

- (IBAction)onResetClick:(UIButton *)sender {
    OdTvPrcImportParams params;
    [self setControlsFromParams:&params];
}

@end

/////////////////////////////////////////////////////
///     DgnParamsViewController implementation    ///
/////////////////////////////////////////////////////
@interface DgnParamsViewController ()
{
    TviDgnImportParams* pDgnParams;
}
@end

@implementation DgnParamsViewController

@synthesize popUpView;

- (void)viewDidLoad {
    [self setupView:popUpView];
    [super viewDidLoad];
}

-(void)showInView:(UIView *)aView parameters:(TviDgnImportParams *)dgnParams
{
    [self addToView:aView];
    pDgnParams = dgnParams;
    OdTvDCRect rect = pDgnParams->getDCRect();
    _xMinValue.text = [NSString stringWithFormat: @"%ld", rect.xmin];
    _xMaxValue.text = [NSString stringWithFormat: @"%ld", rect.xmax];
    _yMinValue.text = [NSString stringWithFormat: @"%ld", rect.ymin];
    _yMaxValue.text = [NSString stringWithFormat: @"%ld", rect.ymax];
    // fill controls from params
    [self setControlsFromParams:pDgnParams];
    [self showAnimate];
}

-(void)setControlsFromParams:(OdTvDgnImportParams*)params
{
    [_objectNamingSwitch setOn:params->getObjectNaming()];
    [_storeSourceSwitch setOn:params->getStoreSourceObjects()];
    [_clearEmptyObjects setOn:params->getClearEmptyObjects()];
}

-(void)applyParams
{
    pDgnParams->setObjectNaming([_objectNamingSwitch isOn]);
    pDgnParams->setStoreSourceObjects([_storeSourceSwitch isOn]);
    pDgnParams->setClearEmptyObjects([_clearEmptyObjects isOn]);
}

// buttons events
- (IBAction)onCancelClick:(UIButton *)sender {
    [self removeAnimate];
}

- (IBAction)onOkClick:(UIButton *)sender {
    [self applyParams];
    pDgnParams->writeToDefaults();
    [self accept:pDgnParams];
}

- (IBAction)onResetClick:(UIButton *)sender {
    OdTvDgnImportParams params;
    [self setControlsFromParams:&params];
}

@end

