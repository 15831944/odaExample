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

#import "MarkupsDialogsViewController.h"
#import "../../BaseViewController.h"

/////////////////////////////////////////////////////
///   SaveMarkupDialogViewController interface    ///
/////////////////////////////////////////////////////
@interface SaveMarkupDialogViewController ()

@end

@implementation SaveMarkupDialogViewController

@synthesize popUpView;

- (void)viewDidLoad {
    self.view.backgroundColor=[[UIColor blackColor] colorWithAlphaComponent:.4];
    popUpView.layer.cornerRadius = 5;
    popUpView.layer.shadowOpacity = 0.8;
    popUpView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
    [super viewDidLoad];
}

- (void)showInView:(nonnull UIView *)aView { 
    [self.view setFrame:[aView frame]];
    [aView addSubview:self.view];
    [self showAnimate];
    [_markupName becomeFirstResponder];
}

- (IBAction)onOkClick:(UIButton *)sender {
    BaseViewController* pRndCtrl = (BaseViewController*)self.currentParentController;
    if(pRndCtrl)
    {
        if([pRndCtrl saveMarkup:_markupName.text])
            [self removeAnimate];
    }
}

- (IBAction)onCancelClick:(UIButton *)sender {
    [self removeAnimate];
}

@end


/////////////////////////////////////////////////////
///   LoadMarkupDialogViewController interface    ///
/////////////////////////////////////////////////////
@interface LoadMarkupDialogViewController ()
{
    NSMutableArray *dataArray;
    NSString *selectedStr;
}

@end

@implementation LoadMarkupDialogViewController

@synthesize popUpView;

- (void)viewDidLoad {
    self.view.backgroundColor=[[UIColor blackColor] colorWithAlphaComponent:.4];
    popUpView.layer.cornerRadius = 5;
    popUpView.layer.shadowOpacity = 0.8;
    popUpView.layer.shadowOffset = CGSizeMake(0.0f, 0.0f);
    [super viewDidLoad];
}

- (void)showInView:(nonnull UIView *)aView {
    [self.view setFrame:[aView frame]];
    [aView addSubview:self.view];
    [self showAnimate];
}

- (IBAction)onCloseClick:(UIButton *)sender {
    [self removeAnimate];
}

- (IBAction)onLoadClick:(UIButton *)sender {
    BaseViewController* pRndCtrl = (BaseViewController*)self.currentParentController;
    if(pRndCtrl)
    {
        if([pRndCtrl loadMarkup:selectedStr ])
            [self removeAnimate];
    }
}

- (IBAction)onDeleteClick:(UIButton *)sender
{
    BaseViewController* pRndCtrl = (BaseViewController*)self.currentParentController;
    if(pRndCtrl)
    {
        if([pRndCtrl removeMarkup:selectedStr])
        {
            [dataArray removeObject:selectedStr];
            [_tableView reloadData];
        }
    }
}

- (void)setTableSource:(nonnull NSMutableArray *)arr
{
    dataArray = arr;
    [_tableView reloadData];
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell* cell = [tableView cellForRowAtIndexPath:indexPath];
    selectedStr = cell.textLabel.text;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [dataArray count];
}

-(UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if(dataArray == nil)
        return nil;
    
    static NSString *ident = @"LoadMarkupTableCell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:ident];
    if (cell == nil) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:ident];
    }
    [cell.textLabel setText: [dataArray objectAtIndex:indexPath.row]];
     return cell;
}

@end

