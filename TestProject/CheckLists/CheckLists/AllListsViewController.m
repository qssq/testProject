//
//  AllListsViewControllerTableViewController.m
//  CheckLists
//
//  Created by gongxun on 15/11/9.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "AllListsViewController.h"
#import "Checklist.h"
#import "CheckListViewController.h"

@interface AllListsViewController ()

@end

@implementation AllListsViewController
{
    NSMutableArray *mLists;
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    if ((self = [super initWithCoder:aDecoder]))
    {
        mLists = [[NSMutableArray alloc]initWithCapacity:20];
        
        NSArray *names = @[@"娱乐", @"工作", @"学习", @"家庭"];
        for (NSInteger i = 0; i < names.count; ++i)
        {
            Checklist *list = [[Checklist alloc]init];
            list.name = names[i];
            
            [mLists addObject:list];
        }
    }
    
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}

//返回行数
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return mLists.count;
}

//设置cell
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    // Configure the cell...
    if(cell == nil)
    {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    
    Checklist *list = mLists[indexPath.row];
    cell.textLabel.text = list.name;
    cell.accessoryType = UITableViewCellAccessoryDetailDisclosureButton;
    
    return cell;
}

//选中某一行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    Checklist *list = [mLists objectAtIndex:indexPath.row];
    [self performSegueWithIdentifier:@"ShowChecklist" sender:list];
}

//删除
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    [mLists removeObjectAtIndex:indexPath.row];
//    [self saveChecklistItems];
    
    NSArray *indexPaths = @[indexPath];
    [tableView deleteRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

//默认按钮的回调
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath
{
    UINavigationController *navigationController = [self.storyboard instantiateViewControllerWithIdentifier:@"ListNavigationController"];
    ListDetailViewController *controller = (ListDetailViewController*)navigationController.topViewController;
    controller.delegate = self;
    Checklist *checklist = mLists[indexPath.row];
    controller.mEditItem = checklist;
    [self presentViewController:navigationController animated:YES completion:nil];
}

- (void)addItem:(Checklist *)list {
    NSInteger newRowIndex = mLists.count;
    [mLists addObject:list];
//    [self saveChecklistItems];
    
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:newRowIndex inSection:0];
    NSArray *indexPaths = @[indexPath];
    [self.tableView insertRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

- (void)updateItem:(Checklist *)list
{
    NSInteger index = [mLists indexOfObject:list];
//    [self saveChecklistItems];
    
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:index inSection:0];
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    
    cell.textLabel.text = list.name;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if ([segue.identifier isEqualToString:@"ShowChecklist"])
    {
        CheckListViewController *controller = segue.destinationViewController;
        controller.checklist = sender;
    }
    else if ([segue.identifier isEqualToString:@"AddChecklist"])
    {
        UINavigationController *navigationController = segue.destinationViewController;
        ListDetailViewController *controller = (ListDetailViewController*)navigationController.topViewController;
        controller.delegate = self;
        controller.mEditItem = nil;
    }
}

//-------------
//ListDetailViewControllerDelegate
//-------------

-(void)ListDetailViewControllerDidCancel:(ListDetailViewController *)controller
{
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(void)ListDetailViewController:(ListDetailViewController*)controller didFinishAddingChecklist:(Checklist*)checklist
{
    [self addItem:checklist];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

-(void)ListDetailViewController:(ListDetailViewController*)controller didFinishEditingChecklist:(Checklist*)checklist
{
    [self updateItem:checklist];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

@end




















