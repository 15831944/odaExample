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

#import "SaveFileViewController.h"
#import "../BaseViewController.h"

@interface SaveFileViewController ()

@end

@implementation SaveFileViewController

@synthesize popUpView;

- (void)viewDidLoad
{
    self.view.backgroundColor=[[UIColor blackColor] colorWithAlphaComponent:.4];
    popUpView.layer.cornerRadius = 5;
    popUpView.layer.shadowOpacity = 0.8;
    popUpView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
    [super viewDidLoad];
}

-(void)showInView:(UIView *)aView withName:(NSString *)initName
{
    [self.view setFrame:[aView frame]];
    [aView addSubview:self.view];
    //[_saveNameField becomeFirstResponder];
    _saveNameField.text = initName;
    [self showAnimate];
}

- (IBAction)onCancelClick:(UIButton *)sender
{
    [self removeAnimate];
}

- (IBAction)onOkClick:(UIButton *)sender
{
    [ (BaseViewController*)self.currentParentController 
		saveFile:_saveNameField.text 
		partialIndexing:[_partialIndexingSwitch isOn] 
      VSFNotPDF:_fileTypeSwitch.selectedSegmentIndex != 1];
    [self removeAnimate];
}

@end
