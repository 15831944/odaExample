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

#import "FilesViewController.h"

#import "BaseViewController.h"
#import "MetalViewController.h"
#import "RenderViewController.h"

#import "AppUITools/ParamsControllers/OptionsDlgViewController.h"
#import "AppCore/TviGlobalParameters.hpp"
#import "AppUITools/ParamsControllers/BaseImportParamsViewController.h"
#import "AppCore/TviImportParameters.hpp"

@interface FilesViewController ()
{
    TviGlobalParameters globalParams;
    TviImportParamsController importController;
    BaseImportParamsViewController* pParams;
}
@end

@implementation FilesViewController
{
    NSMutableArray *allFilesList;
    NSMutableArray *fileList;
    NSString *documentsFolder;
    OptionsDlgViewController *popViewController;
}

@synthesize tableView;

- (void)viewDidLoad {
    [super viewDidLoad];
    // Allocate memory for files storage
    allFilesList = [[NSMutableArray alloc] init];
    fileList = [[NSMutableArray alloc] init];
    // Get files from app documents directory
    NSArray* path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    documentsFolder = [path objectAtIndex:0];
    NSLog(@"Documents folder: %@", documentsFolder);
    
    [self reloadFilesList];
    
    popViewController = NULL;
    // set dc rect for import parameters
    double scaleF = [[UIScreen mainScreen] scale];
    importController.setRect(self.view.frame.size.width*scaleF, self.view.frame.size.height*scaleF);
    
    // setup search bar
    _searchBar.delegate = self;
    
#ifdef METAL_ENABLED
    UIAlertController *alertController = [UIAlertController alertControllerWithTitle:@"Choose device" message:@"What device do you want to draw?"                                                                     preferredStyle:UIAlertControllerStyleAlert];
    UIAlertAction *gles2 = [UIAlertAction actionWithTitle:@"OpenGLES2" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        globalParams.setDevice(TviGlobalParameters::OpenGLES2);
    }];
    UIAlertAction *metal = [UIAlertAction actionWithTitle:@"Metal" style:UIAlertActionStyleDefault handler:^(UIAlertAction * _Nonnull action) {
        globalParams.setDevice(TviGlobalParameters::Metal);
    }];
    [alertController addAction:gles2];
    [alertController addAction:metal];
    [self presentViewController:alertController animated:YES completion:nil];
#else
	globalParams.setDevice(TviGlobalParameters::OpenGLES2);
#endif
}

// search bar text changed
-(void)searchBar:(UISearchBar *)searchBar textDidChange:(NSString *)searchText
{
    [fileList removeAllObjects];
    if(searchText.length == 0)
        [fileList addObjectsFromArray:allFilesList];
    else
    {
        for(NSString* str in allFilesList)
        {
            NSRange range = [str rangeOfString:searchText options:NSCaseInsensitiveSearch];
            if(range.location != NSNotFound)
                [fileList addObject:str];
        }
    }
    [tableView reloadData];
}

-(void)searchBarSearchButtonClicked:(UISearchBar *)pSearchBar
{
    [_searchBar resignFirstResponder];
}

// refresh files list
-(void)reloadFilesList
{
    [fileList removeAllObjects];
    [allFilesList removeAllObjects];
    
    NSArray* fileNames = [[NSFileManager defaultManager] contentsOfDirectoryAtPath:documentsFolder error:NULL];
    for (NSString* filename in fileNames) {
        NSString* ext = [[filename pathExtension] lowercaseString];
        if([ext isEqualToString:@"dwg"]
		|| [ext isEqualToString:@"vsf"] 
#ifdef COMPONENTS_IMPORTS_ENABLED
		|| [ext isEqualToString:@"obj"] 
		|| [ext isEqualToString:@"stl"]
#endif
#ifdef DGN_ENABLED
		|| [ext isEqualToString:@"dgn"]
#endif
#ifdef PRC_ENABLED
        || [ext isEqualToString:@"prc"] 
#endif
#ifdef POINTCLOUD_ENABLED
		|| [ext isEqualToString:@"rcs"]
#endif
#ifdef IFC_ENABLED
		|| [ext isEqualToString:@"ifc"]
#endif
		)
        {
            [fileList addObject:filename];
            [allFilesList addObject:filename];
        }
    }
    
    [fileList sortUsingSelector:@selector(localizedCaseInsensitiveCompare:)];
    [allFilesList sortUsingSelector:@selector(localizedCaseInsensitiveCompare:)];
    
    [tableView reloadData];
}

// add file to list
-(void)addFile:(NSString *)fileName
{
    if(fileName.length == 0)
        return;
    
    if(![fileList containsObject:fileName])
        [fileList addObject:fileName];
    if(![allFilesList containsObject:fileName])
        [allFilesList addObject:fileName];
    
    [fileList sortUsingSelector:@selector(localizedCaseInsensitiveCompare:)];
    [allFilesList sortUsingSelector:@selector(localizedCaseInsensitiveCompare:)];
    
    [tableView reloadData];
}

// core methods
-(void)openFile: (OdTvBaseImportParams*)pImportParams
{
    BaseViewController* baseVC = [self.storyboard instantiateViewControllerWithIdentifier:@"BaseViewController"];
    NSIndexPath* indexPath = [self.tableView indexPathForSelectedRow];
    NSString* dataPath = [documentsFolder stringByAppendingPathComponent:[fileList objectAtIndex:indexPath.row]];
    NSLog(@"Selected path: %@", dataPath);
    // set params for opening
    baseVC.cadFileName = dataPath;
    [baseVC setGlobalParams:&globalParams];
    [baseVC setImportParams:pImportParams];
    
    UIViewController* childVC = nil;
    if(globalParams.getDevice() == TviGlobalParameters::Metal)
        childVC = [self.storyboard instantiateViewControllerWithIdentifier:@"MetalViewController"];
    else if(globalParams.getDevice() == TviGlobalParameters::OpenGLES2)
        childVC = [self.storyboard instantiateViewControllerWithIdentifier:@"RenderViewController"];
    
    [baseVC addChildViewController:childVC];
    [childVC didMoveToParentViewController:baseVC];
    
    [self.navigationController pushViewController:baseVC animated:YES];
}

#pragma mark - Table view data source

//click on file in list
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString* path = [documentsFolder stringByAppendingPathComponent:[fileList objectAtIndex:indexPath.row]];
    NSString* ext = [[path pathExtension] lowercaseString];
    if(ext == nil)
        return;
    
    if([ext isEqualToString:@"dwg"]){
        pParams = [[DwgParamsViewController alloc] initWithNibName:@"DwgParamsViewController" bundle:nil];
        pParams.currentParentController = self;
        [(DwgParamsViewController*)pParams showInView:self.view parameters:importController.getDwgImportParams()];
    }
    else if([ext isEqualToString:@"obj"]){
        pParams = [[ObjParamsViewController alloc] initWithNibName:@"ObjParamsViewController" bundle:nil];
        pParams.currentParentController = self;
        [(ObjParamsViewController*)pParams showInView:self.view parameters:importController.getObjImportParams()];
    }
    else if([ext isEqualToString:@"dgn"]){
        pParams = [[DgnParamsViewController alloc] initWithNibName:@"DgnParamsViewController" bundle:nil];
        pParams.currentParentController = self;
        [(DgnParamsViewController*)pParams showInView:self.view parameters:importController.getDgnImportParams()];
    }
    else if([ext isEqualToString:@"prc"]){
        pParams = [[PrcParamsViewController alloc] initWithNibName:@"PrcParamsViewController" bundle:nil];
        pParams.currentParentController = self;
        [(PrcParamsViewController*)pParams showInView:self.view parameters:importController.getPrcImportParams()];
    }
    else if([ext isEqualToString:@"stl"]){
        pParams = [[StlParamsViewController alloc] initWithNibName:@"StlParamsViewController" bundle:nil];
        pParams.currentParentController = self;
        [(StlParamsViewController*)pParams showInView:self.view parameters:importController.getStlImportParams()];
    }
    else if([ext isEqualToString:@"rcs"]){
        [self openFile: importController.getRcsImportParams()];
    }
    else if([ext isEqualToString:@"vsf"]){
        [self openFile: importController.getRcsImportParams()];
    }
    else if([ext isEqualToString:@"ifc"]){
        [self openFile: importController.getIfcImportParams()];
    }
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [fileList count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    static NSString* fileCellIdentifier = @"FileCell";
    TableFilenameCell *cell = [tableView dequeueReusableCellWithIdentifier:fileCellIdentifier];
    
    if(cell == nil) {
        cell = [[TableFilenameCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:fileCellIdentifier];
    }
    
    cell.fileName.text = [fileList objectAtIndex:indexPath.row];
    NSString* dataPath = [documentsFolder stringByAppendingPathComponent:[fileList objectAtIndex:indexPath.row]];
    unsigned long long fileSize = [[[NSFileManager defaultManager] attributesOfItemAtPath:dataPath error:nil] fileSize];
    cell.fileSize.text = [NSByteCountFormatter stringFromByteCount:fileSize countStyle:NSByteCountFormatterCountStyleBinary];
    
    return cell;
}


#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
//    if ([segue.identifier isEqualToString:@"ShowFile"])
//    {
//        NSIndexPath* indexPath = [self.tableView indexPathForSelectedRow];
//        NSString* dataPath = [documentsFolder stringByAppendingPathComponent:[fileList objectAtIndex:indexPath.row]];
//        NSLog(@"Selected path: %@", dataPath);
//        RenderViewController *destViewController = segue.destinationViewController;
//        // set params for opening
//        destViewController.cadFileName = dataPath;
//        [destViewController setGlobalParams:&globalParams];
//    }
}


// UI events

- (IBAction)onOptionsBtnClick:(UIBarButtonItem *)sender {
    popViewController = [[OptionsDlgViewController alloc] initWithNibName:@"OptionsDlgViewController" bundle:nil];
    [popViewController showInView:self.view animated:YES parameters:&globalParams];
}


@end


@interface TableFilenameCell ()
@end

@implementation TableFilenameCell
{
    
}

@synthesize fileName;
@synthesize fileSize;

@end
