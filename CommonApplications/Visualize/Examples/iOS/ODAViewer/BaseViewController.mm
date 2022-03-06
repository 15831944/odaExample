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

#import "BaseViewController.h"
#import "AppUITools/ParamsControllers/OptionsDlgViewController.h"
#import "AppUITools/Markups/MarkupsDialogsViewController.h"
#import "AppUITools/BaseDialogViewController.h"
#import "AppUITools/SaveFileViewController.h"
#import "FilesViewController.h"
#import "AppCore/TviDraggers.hpp"

@interface BaseViewController ()
{
    TviCore tvCore;
    OdTvBaseImportParams *importParams;
    
    // text field for text markup dragger
    UITextField *txtField;
    OdTvVector backDelta;
    BaseDialogViewController* pDialog;
    NSMutableArray* savedMarkups;
    BOOL isBlocked;
    
    // timer for the auto update
    NSTimer* pAutoUpdateTimer;
    
    // rect
    int xMin, xMax, yMin, yMax;
    
    // layer for the bottom border, need for indication of current dragger
    CALayer *bottomBorderLayer;
}

@end

@implementation BaseViewController

@synthesize cadFileName;
@synthesize viewsBtn;
@synthesize navBtn;
@synthesize markupsBtn;
@synthesize sectioningBtn;
@synthesize styleBtn;
@synthesize firstViewsMenuToolbar;
@synthesize secondViewsMenuToolbar;
@synthesize navigationMenuToolbar;
@synthesize markupMenuToolbar;
@synthesize toolsToolbar;
@synthesize styleMenuToolbar;
// loading indicator property
@synthesize loadingIndicator;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
    // set bottom border
    bottomBorderLayer = [CALayer layer];
    bottomBorderLayer.backgroundColor = [UIColor colorWithRed:84/255. green:0. blue:1. alpha:1.].CGColor;

    isBlocked = NO;
    
    tvCore.attach(self);
    
    savedMarkups = [[NSMutableArray alloc] init];
    
    [self.view setUserInteractionEnabled:NO];
    
    // set file extension
    NSString* ext = [[cadFileName pathExtension] lowercaseString];
    if(ext == nil)
        return;
    if([ext isEqualToString:@"dwg"])
        tvCore.setFileExtension(TviCore::Drw);
    else if([ext isEqualToString:@"obj"])
        tvCore.setFileExtension(TviCore::Obj);
    else if([ext isEqualToString:@"dgn"])
        tvCore.setFileExtension(TviCore::Dgn);
    else if([ext isEqualToString:@"prc"])
        tvCore.setFileExtension(TviCore::Prc);
    else if([ext isEqualToString:@"stl"])
        tvCore.setFileExtension(TviCore::Stl);
    else if([ext isEqualToString:@"rcs"])
        tvCore.setFileExtension(TviCore::Rcs);
    else if([ext isEqualToString:@"vsf"])
        tvCore.setFileExtension(TviCore::Vsf);
    else if([ext isEqualToString:@"ifc"])
        tvCore.setFileExtension(TviCore::Ifc);
    
    // set filename label
    _filenameLbl.text = [cadFileName lastPathComponent];
    
    // set device label
    _deviceLabel.text = tvCore.getGlobalParameters()->getDevice() == TviGlobalParameters::OpenGLES2 ? @"OpenGLES2" : @"Metal";
    
    // load file
    [loadingIndicator startAnimating];
    _fileOpenTimeLbl.text = @"Loading...";
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(receiveRegenAbortNotification:) name:@"RegenAbortNotification" object:nil];
    
    UIViewController* vc = self.childViewControllers.firstObject;
    if(vc)
    {
        double scaleF = [[UIScreen mainScreen] scale];
        int headerHeight = _headerToolbar.frame.size.height;
        int footerHeight = _footerToolbar.frame.size.height;
        int statusBarHeight = _statusBarMenu.frame.size.height;
        xMin = 0;
        yMax = 0;
        
        [_renderView setBounds: CGRectMake(0, 0, self.view.frame.size.width, (self.view.frame.size.height - footerHeight - headerHeight - statusBarHeight*2))];
        [_renderView addSubview:vc.view];
        vc.view.frame = _renderView.bounds;
        xMax = vc.view.frame.size.width * scaleF;
        yMin = vc.view.frame.size.height * scaleF;
    }
}

- (void) receiveRegenAbortNotification:(NSNotification *) notification
{
    if ([[notification name] isEqualToString:@"RegenAbortNotification"])
    {
        //tvCore.setRegenAbort(true);
    }
}

-(void)update
{
    tvCore.update();
}

-(void)openFile:(NSObject *)context
{
    bool bImport = ![[[cadFileName pathExtension] lowercaseString] isEqualToString:@"vsf"];
    tvCore.openFile(NSString2OdString(cadFileName), importParams, bImport, context, OdTvDCRect(xMin, xMax, yMin, yMax) );
}


-(void)stopLoadingIndicator:(double)time
{
    _fileOpenTimeLbl.text = [NSString stringWithFormat:@"Total time: %.2f s", time];
    [loadingIndicator stopAnimating];
}

-(void)loadFileDone
{
    if(!tvCore.isValid()) {
        [self onFilesClick:nil];
        return;
    }
    
    [self.view setUserInteractionEnabled:YES];
    
    // add file to table in FileViewController
    OdTvDwgImportParams* dwgParams = dynamic_cast<OdTvDwgImportParams*>(importParams);
    if(dwgParams && dwgParams->getOpenSourcePartial())
    {
        FilesViewController *filesCtrl = self.navigationController.viewControllers[0];
        if([filesCtrl isKindOfClass: [FilesViewController class] ])
        {
            [filesCtrl reloadFilesList];
        }
    }
    
    // check projection
    OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
    if(!pView.isNull())
    {
        if(pView->isPerspective())
            [_projectionItm setImage:[UIImage imageNamed:@"projection_perspective"] forState:UIControlStateNormal];
        else
            [_projectionItm setImage:[UIImage imageNamed:@"projection_isometric"] forState:UIControlStateNormal];
    }
    
    // set current dragger indicator
    [self resetDraggerIndicator];
}

- (IBAction)onProjectionClick:(UIBarButtonItem *)sender
{
    TviCore::ProjectionType type;
    {
        OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
        if(pView.isNull())
            return;
        type = pView->isPerspective() ? TviCore::Isometric : TviCore::Perspective;
    }
    tvCore.setProjection( type );
    
    if(type == TviCore::Perspective)
        [_projectionItm setImage:[UIImage imageNamed:@"projection_perspective"] forState:UIControlStateNormal];
    else
        [_projectionItm setImage:[UIImage imageNamed:@"projection_isometric"] forState:UIControlStateNormal];
}

- (void)showMessage:(nonnull NSString *)title message:(nonnull NSString *)msg
{
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:title message:msg                                                                     preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *actionOk = [UIAlertAction actionWithTitle:@"Ok" style:UIAlertActionStyleDefault handler:nil];
    [alertController addAction:actionOk];
    [self presentViewController:alertController animated:YES completion:nil];
}

-(void)showSaveMarkupDialog
{
    pDialog = [[SaveMarkupDialogViewController alloc] initWithNibName:@"SaveMarkupDialogViewController" bundle:nil];
    pDialog.currentParentController = self;
    [(SaveMarkupDialogViewController*)pDialog showInView:self.view];
}

-(void)showLoadMarkupDialog
{
    if ([savedMarkups count] == 0)
    {
        // try fill list with markups from model
        OdTvModelId markupModelId = tvCore.getMarkupModelId();
        if (!markupModelId.isNull())
        {
            for ( OdTvEntitiesIteratorPtr pEnIt = markupModelId.openObject()->getEntitiesIterator(); !pEnIt->done(); pEnIt->step() )
            {
                OdTvEntityId enId = pEnIt->getEntity();
                OdTvEntityPtr pEn = enId.openObject();
                if (pEn->getName().compare(OD_TV_MARKUP_TEMP_ENTITY) != 0)
                {
                    [savedMarkups addObject: OdString2NSString(pEn->getName())];
                }
            }
        }
        
        if([savedMarkups count] == 0)
        {
            [self showMessage:@"Error" message:@"No one markup for load"];
            return;
        }
    }
    
    pDialog = [[LoadMarkupDialogViewController alloc] initWithNibName:@"LoadMarkupDialogViewController" bundle:nil];
    pDialog.currentParentController = self;
    [(LoadMarkupDialogViewController*)pDialog setTableSource:savedMarkups];
    [(LoadMarkupDialogViewController*)pDialog showInView:self.view];
}

-(BOOL)saveMarkup:(NSString *)name
{
    if(name.length == 0)
    {
        [self showMessage:@"Error" message:@"Markup name is empty"];
        return NO;
    }
    
    if(tvCore.saveMarkup(name))
    {
        [savedMarkups addObject:name];
        return YES;
    }
    
    [self showMessage:@"Error" message:@"Error during saving markup"];
    return NO;
}

-(BOOL)loadMarkup:(NSString *)name
{
    if(!name || name.length == 0)
    {
        [self showMessage:@"Error" message:@"Markup name is empty"];
        return NO;
    }
    
    if(tvCore.loadMarkup(name))
    {
        return YES;
    }
    
    [self showMessage:@"Error" message:@"Error during load markup"];
    return NO;
}

-(BOOL)removeMarkup:(NSString *)name
{
    if(!name || name.length == 0)
    {
        [self showMessage:@"Error" message:@"Markup name is empty"];
        return NO;
    }
    
    if(tvCore.removeMarkup(name))
    {
        return YES;
    }
    
    [self showMessage:@"Error" message:@"Error during removing markup"];
    return NO;
}

// destructor
-(void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self];
}

// set global parameters
-(void)setGlobalParams:(TviGlobalParameters *)globalParams
{
    tvCore.setGlobalParams(globalParams);
}

-(void)setImportParams:(OdTvBaseImportParams *)pImportParams
{
    importParams = pImportParams;
}

-(void)applyGlobalParams
{
    tvCore.applyGlobalParams();
}

-(void)startTimer
{
    if(!pAutoUpdateTimer)
        pAutoUpdateTimer = [NSTimer scheduledTimerWithTimeInterval:1 target:self selector:@selector(timeOut:) userInfo:nil repeats:NO];
}

-(void)timeOut: (NSTimer*)timer
{
    [pAutoUpdateTimer invalidate];
    pAutoUpdateTimer = nil;
    tvCore.autoUpdate();
}

// UI events

-(void)hideMenus: (UIToolbar*)activeBar
{
    if(activeBar != firstViewsMenuToolbar) {
        [firstViewsMenuToolbar setHidden:YES];
        [secondViewsMenuToolbar setHidden:YES];
    }
    if(activeBar != navigationMenuToolbar)
        [navigationMenuToolbar setHidden:YES];
    if(activeBar != markupMenuToolbar)
        [markupMenuToolbar setHidden:YES];
    if(activeBar != toolsToolbar)
        [toolsToolbar setHidden:YES];
    if(activeBar != styleMenuToolbar)
        [styleMenuToolbar setHidden:YES];
}

-(void)setActiveButton: (UIBarButtonItem *)activeBtn {
    [viewsBtn setTintColor:[UIColor whiteColor]];
    [navBtn setTintColor:[UIColor whiteColor]];
    [markupsBtn setTintColor:[UIColor whiteColor]];
    [sectioningBtn setTintColor:[UIColor whiteColor]];
    [styleBtn setTintColor:[UIColor whiteColor]];
    
    [activeBtn setTintColor:[[UIColor alloc]initWithRed:0.831f green:0.545f blue:0.341f alpha:1.0f]];
}

- (IBAction)onViewsButtonClick:(UIBarButtonItem *)sender {
    [self hideMenus: firstViewsMenuToolbar];
    [firstViewsMenuToolbar setHidden: ![firstViewsMenuToolbar isHidden]];
    [secondViewsMenuToolbar setHidden: ![secondViewsMenuToolbar isHidden]];
    [self setActiveButton:sender];
    [_panelNameLbl setTitle:@"Views" forState:UIControlStateNormal];
    tvCore.onAppearSectioningPanel(![toolsToolbar isHidden]);
}

- (IBAction)onNavigationBtnClick:(UIBarButtonItem *)sender {
    [self hideMenus: navigationMenuToolbar];
    [navigationMenuToolbar setHidden: ![navigationMenuToolbar isHidden]];
    [self setActiveButton:sender];
    [_panelNameLbl setTitle:@"Navigation" forState:UIControlStateNormal];
    tvCore.onAppearSectioningPanel(![toolsToolbar isHidden]);
}

- (IBAction)onMarkupsBtnClick:(UIBarButtonItem *)sender {
    [self hideMenus: markupMenuToolbar];
    [markupMenuToolbar setHidden: ![markupMenuToolbar isHidden]];
    [self setActiveButton:sender];
    [_panelNameLbl setTitle:@"Markups" forState:UIControlStateNormal];
    tvCore.onAppearSectioningPanel(![toolsToolbar isHidden]);
}

- (IBAction)onToolsBtnClick:(UIBarButtonItem *)sender {
    [self hideMenus: toolsToolbar];
    [toolsToolbar setHidden: ![toolsToolbar isHidden]];
    [self setActiveButton:sender];
    [_panelNameLbl setTitle:@"Tools" forState:UIControlStateNormal];
    tvCore.onAppearSectioningPanel(![toolsToolbar isHidden]);
}

- (IBAction)onStyleBtnClick:(UIBarButtonItem *)sender {
    [self hideMenus: styleMenuToolbar];
    [styleMenuToolbar setHidden: ![styleMenuToolbar isHidden]];
    [self setActiveButton:sender];
    [_panelNameLbl setTitle:@"Style" forState:UIControlStateNormal];
    tvCore.onAppearSectioningPanel(![toolsToolbar isHidden]);
}

// setting button event
- (IBAction)onOptionsBtnClick:(UIBarButtonItem *)sender
{
    pDialog = [[OptionsRenderDlgViewController alloc] initWithNibName:@"OptionsRenderDlgViewController" bundle:nil];
    pDialog.currentParentController = self;
    [(OptionsRenderDlgViewController*)pDialog setModelStatistic:tvCore.getModelStatistic()];
    [(OptionsRenderDlgViewController*)pDialog showInView:self.view animated:YES parameters:tvCore.getGlobalParameters()];
}

// navigation evens
-(OdGePoint3d)toEyeToWorld: (int)x yPos: (int)y viewPtr: (OdTvGsViewPtr)pView
{
    OdGePoint3d wcsPt(x, y, 0.0);
    
    if (pView->isPerspective())
    {
        wcsPt.z = pView->projectionMatrix()(2,3);
    }
    wcsPt.transformBy((pView->screenMatrix() * pView->projectionMatrix()).inverse());
    wcsPt.z = 0.;
    // eye CS at this point.
    
    //transform to world coordinate system
    wcsPt.transformBy(pView->eyeToWorldMatrix());
    
    return wcsPt;
}

-(CGPoint)setupPoint: (CGPoint)point
{
    double scale = [[UIScreen mainScreen] scale];
    return CGPointMake(point.x * scale, (point.y * scale) + 30 /*Value for correction touch position*/);
}

- (IBAction)onTouchEvent:(UITapGestureRecognizer *)sender
{
    OdTvDragger* pDragger = tvCore.getActiveDragger();
    if(!pDragger)
        return;
    
    OdTvTextMarkupDragger* pTxt = dynamic_cast<OdTvTextMarkupDragger*>(pDragger);
    TviCuttingPlaneDragger* pCut = dynamic_cast<TviCuttingPlaneDragger*>(pDragger);
    TviCollideDragger* pCollide = dynamic_cast<TviCollideDragger*>(pDragger);
    if(!pTxt && !pCut && !pCollide)
        return;
    
    UIView* touchView = sender.view;
    [sender setNumberOfTapsRequired:1];
    [sender setNumberOfTouchesRequired:1];
    CGPoint touchPnt = [self setupPoint:[sender locationInView:touchView]];
    
    eDraggerResult res = pDragger->activate();
    tvCore.actionsAfterDragger(res);
    res = pDragger->nextpoint( touchPnt.x, touchPnt.y );
    tvCore.actionsAfterDragger(res);
    
    if(!pTxt)
        return;
    
    if(!txtField)
    {
        // start dragger
        CGRect someRect = CGRectMake(0.0, 0.0, 100.0, 30.0);
        txtField = [[UITextField alloc] initWithFrame:someRect];
        [txtField addTarget:self action:@selector(textChanged:) forControlEvents:UIControlEventEditingChanged];
        [_renderView addSubview:txtField];
        [txtField becomeFirstResponder];
        [txtField setHidden:YES];
        txtField.delegate = self;
        
        OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
        if(!pView.isNull())
        {
            OdTvPoint screenPrevPt = pView->position().transformBy(pView->worldToDeviceMatrix());
            OdTvPoint prevPt = [self toEyeToWorld:screenPrevPt.x yPos:screenPrevPt.y viewPtr:pView] - pView->position().asVector();
            OdTvPoint curPt = [self toEyeToWorld:touchPnt.x yPos:touchPnt.y viewPtr:pView];
            OdTvVector delta = ( prevPt - (curPt - pView->position()) ).asVector();
            backDelta = ( prevPt + (pView->position() - curPt) ).asVector();
            pView->dolly(-delta.transformBy(pView->viewingMatrix()));
        }
    }
    else
    {
        // finish dragger
        OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
        if(!pView.isNull())
        {
            pView->dolly(backDelta.transformBy(pView->viewingMatrix()));
            backDelta.set(0., 0., 0.);
        }
        
        [txtField resignFirstResponder];
        [txtField removeFromSuperview];
        txtField = nil;
        [self resetDraggerIndicator];
    }
    
    tvCore.actionsAfterDragger(res);
}
-(void)textChanged:(UITextField *)textField
{
    OdTvDragger* pDragger = tvCore.getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res = pDragger->processText(NSString2OdString(textField.text));
    textField.text = @"";
    tvCore.actionsAfterDragger(res);
}
-(BOOL)textFieldShouldReturn:(UITextField *)textField
{
    OdTvDragger* pDragger = tvCore.getActiveDragger();
    if(!pDragger)
        return NO;
    eDraggerResult res = pDragger->processEnter();
    tvCore.actionsAfterDragger(res);
    return NO;
}

- (IBAction)panEvent:(UIPanGestureRecognizer *)sender
{
    UIView* panView = sender.view;
    [sender setMaximumNumberOfTouches:1];
    CGPoint touchPnt = [self setupPoint:[sender locationInView:panView]];
    OdTvDragger* pDragger = tvCore.getActiveDragger();
    if(!pDragger)
        return;
    eDraggerResult res;
    switch(sender.state)
    {
        case UIGestureRecognizerStateBegan:
        {
            res = pDragger->activate();
            tvCore.actionsAfterDragger(res);
            res = pDragger->nextpoint( touchPnt.x, touchPnt.y );
            
            if(dynamic_cast<TviOrbitDragger*>(pDragger) != NULL)
                tvCore.disableMarkups();
            
            break;
        }
        case  UIGestureRecognizerStateChanged:
            res = pDragger->drag( touchPnt.x, touchPnt.y );
            break;
        case UIGestureRecognizerStateEnded:
            res = pDragger->nextpointup( touchPnt.x, touchPnt.y );
            tvCore.setRegenAbort(false);
            // after finish markup dragger, perform reset indcator
            if( (dynamic_cast<OdTvRectangleMarkupDragger*>(pDragger)) != NULL || (dynamic_cast<OdTvCircleMarkupDragger*>(pDragger)) != NULL
               || (dynamic_cast<OdTvHandleMarkupDragger*>(pDragger)) != NULL)
                [self resetDraggerIndicator];
            break;
    }
    
    tvCore.actionsAfterDragger(res);
}

- (IBAction)rotationEvent:(UIRotationGestureRecognizer *)sender
{
    if ([sender state] == UIGestureRecognizerStateBegan || [sender state] == UIGestureRecognizerStateChanged)
    {
        OdTvExtendedView *pExtView = tvCore.getActiveTvExtendedView();
        if(pExtView)
        {
            pExtView->roll(sender.rotation);
        }
        sender.rotation = 0.;
    }
    else if([sender state] == UIGestureRecognizerStateEnded)
        tvCore.setRegenAbort(false);
}

- (IBAction)zoomEvent:(UIPinchGestureRecognizer *)sender
{
    UIView *pinchView = sender.view;
    CGPoint pinchCenter = [self setupPoint:[sender locationInView:pinchView]];
    
    switch(sender.state)
    {
        case UIGestureRecognizerStateBegan:
            tvCore.performFixedFrameRate();
            break;
        case  UIGestureRecognizerStateChanged:
            tvCore.zoom(sender.scale, pinchCenter.x, pinchCenter.y);
            break;
        case UIGestureRecognizerStateEnded:
            tvCore.finishFixedFrameRate();
            tvCore.setRegenAbort(false);
            break;
    }
    
    sender.scale = 1.;
}

// method for the adding bottom border layer to any view
-(void)addBottomBorder: (UIView*)parentView
{
    [bottomBorderLayer removeFromSuperlayer];
    if(parentView == nil)
        return;
    bottomBorderLayer.frame = CGRectMake(0, CGRectGetMaxY(parentView.frame) - 1, parentView.frame.size.width, 3.0f);
    [parentView.layer addSublayer:bottomBorderLayer];
}

// view buttons clicks
- (IBAction)onTopClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kTop);
}
- (IBAction)onBottomClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kBottom);
}
- (IBAction)onLeftClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kLeft);
}
- (IBAction)onRightClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kRight);
}
- (IBAction)onFrontClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kFront);
}
- (IBAction)onBackClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kBack);
}
- (IBAction)onSWClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kSW);
}
- (IBAction)onSEClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kSE);
}
- (IBAction)onNWClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kNW);
}
- (IBAction)onNEClick:(id)sender {
    tvCore.set3DView(OdTvExtendedView::kNE);
}

// navigation buttons clicks
- (IBAction)onPanClick:(UIButton*)sender {
    tvCore.runNavigationAction(TviCore::Pan);
    [self addBottomBorder:[sender superview]];
}
- (IBAction)onOrbitClick:(UIButton*)sender {
    tvCore.runNavigationAction(TviCore::Orbit);
    [self addBottomBorder:[sender superview]];
}
- (IBAction)onZoomWindowClick:(UIButton*)sender {
    tvCore.runNavigationAction(TviCore::ZoomWindow);
    [self addBottomBorder:[sender superview]];
}
- (IBAction)onZoomExtentsClick:(UIButton*)sender {
    tvCore.runNavigationAction(TviCore::ZoomExtents);
}

// markups
- (IBAction)onRectMarkupClick:(UIButton*)sender {
    tvCore.runMarkupAction(TviCore::Rectangle);
    [self addBottomBorder:[sender superview]];
    [_doneBtn setHidden:YES];
}
- (IBAction)onCircMarkupClick:(UIButton*)sender {
    tvCore.runMarkupAction(TviCore::Circle);
    [self addBottomBorder:[sender superview]];
    [_doneBtn setHidden:YES];
}
- (IBAction)onHandleMarkupClick:(UIButton*)sender {
    tvCore.runMarkupAction(TviCore::Handle);
    [self addBottomBorder:[sender superview]];
    [_doneBtn setHidden:YES];
}
- (IBAction)onCloudMarkupClick:(UIButton*)sender {
    tvCore.runMarkupAction(TviCore::Cloud);
    [self addBottomBorder:[sender superview]];
    [_doneBtn setHidden:NO];
}
- (IBAction)onDoneBtnClick:(UIButton *)sender {
    OdTvDragger* pDragger = tvCore.getActiveDragger();
    if(!pDragger)
        return;
    
    OdTvCloudMarkupDragger* pCloud = dynamic_cast<OdTvCloudMarkupDragger*>(pDragger);
    TviCollideDragger* pCollide = dynamic_cast<TviCollideDragger*>(pDragger);
    if(pCloud)
    {
        eDraggerResult res = pDragger->processEnter();
        tvCore.actionsAfterDragger(res);
    }
    else if(pCollide)
        tvCore.finishDragger();
    
    [sender setHidden:YES];
    [self resetDraggerIndicator];
}
- (IBAction)onTextMarkupClick:(UIButton*)sender {
    tvCore.runMarkupAction(TviCore::Text);
    [self addBottomBorder:[sender superview]];
    [_doneBtn setHidden:YES];
}
- (IBAction)onSaveMarkupClick:(id)sender {
    tvCore.runMarkupAction(TviCore::Save);
    [_doneBtn setHidden:YES];
}
- (IBAction)onLoadMarkupClick:(id)sender {
    tvCore.runMarkupAction(TviCore::Load);
    [_doneBtn setHidden:YES];
}

// regen
- (IBAction)onRegenAllClick:(id)sender {
    tvCore.runRegenAction(TviCore::All);
}
- (IBAction)onRegenVisibleClick:(id)sender {
    tvCore.runRegenAction(TviCore::Visible);
}
- (IBAction)onRegenViewportClick:(id)sender {
    tvCore.runRegenAction(TviCore::View);
}

// visual styles
- (IBAction)on2DWireClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::k2DOptimized);
}
- (IBAction)on3DWireClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::kWireframe);
}
- (IBAction)onHiddenLineClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::kHiddenLine);
}
- (IBAction)onShadedClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::kFlatShaded);
}
- (IBAction)onGouShadedClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::kGouraudShaded);
}
- (IBAction)onShadedWithEdgesClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::kFlatShadedWithWireframe);
}
- (IBAction)onGouShadedWithEdgesClick:(id)sender {
    tvCore.runRenderMode(OdTvGsView::kGouraudShadedWithWireframe);
}

- (IBAction)onFilesClick:(UIBarButtonItem *)sender {
    tvCore.detach();
    UIViewController *childVC = [self.childViewControllers firstObject];
    if(childVC)
        [childVC removeFromParentViewController];
    [self.navigationController popToRootViewControllerAnimated:YES];
}

-(BOOL)gestureRecognizer:(UIGestureRecognizer *)gestureRecognizer shouldReceiveTouch:(UITouch *)touch
{
    if(!isBlocked)
        return YES;
    
    return NO;
}

-(void)setBlocked:(BOOL)bBlocked
{
    isBlocked = bBlocked;
}

// save button click
- (IBAction)onSaveClick:(UIBarButtonItem *)sender
{
    if(cadFileName.length == 0)
    {
        [self showMessage:@"Error" message:@"Filename is empty"];
        return;
    }
    
    pDialog = [[SaveFileViewController alloc] initWithNibName:@"SaveFileViewController" bundle:nil];
    pDialog.currentParentController = self;
    NSString* fileName = [[cadFileName lastPathComponent] stringByDeletingPathExtension];
    //fileName = [fileName stringByAppendingPathExtension:@"vsf"];
    [(SaveFileViewController*)pDialog showInView:self.view withName:fileName];
}

-(void)saveFile:(NSString *)fileName 
	partialIndexing:(BOOL)bPartialIndexing
	VSFNotPDF:(BOOL)bVSFNotPDF
{
	if(bVSFNotPDF)
	{
		NSString* documentPath = [cadFileName stringByDeletingLastPathComponent];
		NSString* fullPath = [documentPath stringByAppendingPathComponent:fileName];
		if(![[fullPath pathExtension] isEqualToString:@"vsf"])
			fullPath = [fullPath stringByAppendingPathExtension:@"vsf"];
		if(!tvCore.saveFile(fullPath, bPartialIndexing))
			return;
		
		FilesViewController *filesCtrl = self.navigationController.viewControllers[0];
		if([filesCtrl isKindOfClass: [FilesViewController class] ])
		{
			[filesCtrl addFile:fileName];
		}
	}
    else
		tvCore.exportToPdf(false);
}

-(void)resetDraggerIndicator
{
    [self addBottomBorder:[_panButton valueForKey:@"view"]];
}

-(IBAction)onCollideClick:(UIButton*)sender
{
    if(tvCore.runCollide())
    {
        [self addBottomBorder:sender];
        [_doneBtn setHidden:NO];
    }
}

- (IBAction)onShowCuttingPlanesClick:(UIButton *)sender
{
    bool bOldShowState = tvCore.getSectioningOptions()->getShown();
    tvCore.setShowCuttingPlanes(!bOldShowState);
    
    if(!bOldShowState)
        [sender setImage:[UIImage imageNamed:@"CuttingPlane"] forState:UIControlStateNormal];
    else
        [sender setImage:[UIImage imageNamed:@"CuttingPlaneOff"] forState:UIControlStateNormal];
}

-(void)addCuttingPlane: (const OdTvVector&)axis
{
    OdTvResult res = tvOk;
    if (!tvCore.addCuttingPlane(axis))
    {
        if (res == tvOk)
        {
            [self showMessage:@"Error" message:[NSString stringWithFormat:@"There are can not be more than %d cutting planes.", ODTVUI_CUTTINGPLANESMAXNUM]];
            return;
        }
    }
}

- (IBAction)onAddCuttingPlanesByXClick:(UIButton *)sender
{
    OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
    if(pView.isNull())
        return;
    OdTvVector viewVector = pView->position() - pView->target();
    double xDot = viewVector.dotProduct(OdTvVector::kXAxis);
    if (OdZero(xDot))
        xDot = 1.;
    
    OdTvVector axis = OdTvVector::kXAxis;
    axis *= -xDot;
    axis.normalize();
    [self addCuttingPlane:axis];
}

- (IBAction)onAddCuttingPlanesByYClick:(UIButton *)sender
{
    OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
    if(pView.isNull())
        return;
    OdTvVector viewVector = pView->position() - pView->target();
    double yDot = viewVector.dotProduct(OdTvVector::kYAxis);
    if (OdZero(yDot))
        yDot = 1.;
    
    OdTvVector axis = OdTvVector::kYAxis;
    axis *= -yDot;
    axis.normalize();
    [self addCuttingPlane:axis];
}

- (IBAction)onAddCuttingPlanesByZClick:(UIButton *)sender
{
    OdTvGsViewPtr pView = tvCore.getActiveTvViewPtr();
    if(pView.isNull())
        return;
    OdTvVector viewVector = pView->position() - pView->target();
    double zDot = viewVector.dotProduct(OdTvVector::kZAxis);
    if (OdZero(zDot))
        zDot = 1.;
    
    OdTvVector axis = OdTvVector::kZAxis;
    axis *= -zDot;
    axis.normalize();
    [self addCuttingPlane:axis];
}

- (IBAction)onFillCuttingPlanesClick:(UIButton *)sender
{
    bool bOldFillState = tvCore.getSectioningOptions()->getFilled();
    tvCore.setCuttingPlanesFilled(!bOldFillState);
    
    if(!bOldFillState)
        [sender setImage:[UIImage imageNamed:@"FillCuttingPlane"] forState:UIControlStateNormal];
    else
        [sender setImage:[UIImage imageNamed:@"FillCuttingPlaneOff"] forState:UIControlStateNormal];
}

- (IBAction)onRemoveCuttingPlanesClick:(UIButton *)sender
{
    tvCore.removeCuttingPlanes();
}


@end


@implementation UIView (ExtCategory)

-(UIView*)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    if (!self.isUserInteractionEnabled || self.isHidden || self.alpha <= 0.01) {
        return nil;
    }
    
    if ([self pointInside:point withEvent:event]) {
        for (UIView *subview in [self.subviews reverseObjectEnumerator]) {
            CGPoint convertedPoint = [subview convertPoint:point fromView:self];
            UIView *hitTestView = [subview hitTest:convertedPoint withEvent:event];
            if (hitTestView) {
                [[NSNotificationCenter defaultCenter]
                 postNotificationName:@"RegenAbortNotification"
                 object:self];
                return hitTestView;
            }
        }
        return self;
    }
    return nil;
}

@end

