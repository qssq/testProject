//
//  ViewController.m
//  CheckLists
//
//  Created by gongxun on 15/10/25.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "CheckListViewController.h"
#import "ChecklistItem.h"
#import "Checklist.h"

@interface CheckListViewController ()

@end

@implementation CheckListViewController{
    NSMutableArray *mItems;
}

- (void)saveChecklistItems
{
    NSMutableData *data = [[NSMutableData alloc]init];
    NSKeyedArchiver *archiver = [[NSKeyedArchiver alloc]initForWritingWithMutableData:data];
    [archiver encodeObject:mItems forKey:@"ChecklistItems"];
    [archiver finishEncoding];
    [data writeToFile:[self dataFilePath] atomically:YES];
}

- (void)loadChecklistItems
{
    NSString *path = [self dataFilePath];
    if ([[NSFileManager defaultManager]fileExistsAtPath:path])
    {
        NSData *data = [[NSData alloc]initWithContentsOfFile:path];
        
        NSKeyedUnarchiver *unarchiver = [[NSKeyedUnarchiver alloc]initForReadingWithData:data];
        mItems = [unarchiver decodeObjectForKey:@"ChecklistItems"];
        [unarchiver finishDecoding];
    }
    else
    {
        mItems = [[NSMutableArray alloc]initWithCapacity:20];
    }
}

- (id)initWithCoder:(NSCoder *)aDecoder
{
    if ((self = [super initWithCoder:aDecoder]))
    {
        [self loadChecklistItems];
    }
    
    return self;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    NSLog(@"文件夹的目录是:%@",[self documentsDirectory]);
    NSLog(@"数据文件的最终路径是:%@",[self dataFilePath]);
    
    self.title = self.checklist.name;
}

- (NSString*)documentsDirectory
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths firstObject];
    return documentsDirectory;
}

- (NSString*)dataFilePath
{
    return [[self documentsDirectory]stringByAppendingPathComponent:@"Checklists.plist"];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

//返回行数
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return mItems.count;
}

//设置cell
- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ChecklistItem"];
    ChecklistItem *item = (ChecklistItem*)mItems[indexPath.row];
    
    [self configureTextForCell:cell withChecklistItem:item];
    [self configureCheckmarkForCell:cell withChecklistItem:item];
    
    return cell;
}

//点击某行
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    ChecklistItem *item = (ChecklistItem*)mItems[indexPath.row];
    [item toggleChecked];
    [self saveChecklistItems];
    
    [self configureCheckmarkForCell:cell withChecklistItem:item];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

//删除
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath{
    [mItems removeObjectAtIndex:indexPath.row];
    [self saveChecklistItems];
    
    NSArray *indexPaths = @[indexPath];
    [tableView deleteRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

//同步text
-(void)configureTextForCell:(UITableViewCell *)cell withChecklistItem:(ChecklistItem *)item{
    UILabel *label = (UILabel*)[cell viewWithTag:1000];
    label.text = item.text;
}

//同步check
-(void)configureCheckmarkForCell:(UITableViewCell *)cell withChecklistItem:(ChecklistItem *)tiem{
    UILabel *lable = (UILabel*)[cell viewWithTag:1001];
    lable.text = tiem.checked ? @"✅" : @"☑️";
}

- (void)addItem:(ChecklistItem *)item {
    NSInteger newRowIndex = mItems.count;
    [mItems addObject:item];
    [self saveChecklistItems];
    
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:newRowIndex inSection:0];
    NSArray *indexPaths = @[indexPath];
    [self.tableView insertRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

- (void)updateItem:(ChecklistItem *)item
{
    NSInteger index = [mItems indexOfObject:item];
    [self saveChecklistItems];
    
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:index inSection:0];
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    
    [self configureCheckmarkForCell:cell withChecklistItem:item];
    [self configureTextForCell:cell withChecklistItem:item];
}

//-----------------
//ItemDetailViewControllerDelegate
//-----------------

- (void)ItemDetailViewController:(ItemDetailViewController *)controller didFinishAddingItem:(ChecklistItem *)item{
    [self addItem:item];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)ItemDetailViewController:(ItemDetailViewController *)controller didFinishEditingItem:(ChecklistItem *)item{
    [self updateItem:item];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)ItemDetailViewControllerDidCancel:(ItemDetailViewController *)controller{
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender{
    if ([segue.identifier isEqualToString:@"AddItem"])
    {
        UINavigationController *navigationController = segue.destinationViewController;
        
        ItemDetailViewController *controller = (ItemDetailViewController*)navigationController.topViewController;
        
        controller.delegate = self;
        controller.mEditItem = nil;
    }
    else if ([segue.identifier isEqualToString:@"EditItem"])
    {
        NSIndexPath *indexPath = [self.tableView indexPathForCell:sender];
        ChecklistItem *item = mItems[indexPath.row];
        
        UINavigationController *navigationController = segue.destinationViewController;
        
        ItemDetailViewController *controller = (ItemDetailViewController*)navigationController.topViewController;
        
        controller.delegate = self;
        controller.mEditItem = item;
    }
}

@end









