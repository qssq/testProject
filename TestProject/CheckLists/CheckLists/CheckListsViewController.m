//
//  ViewController.m
//  CheckLists
//
//  Created by gongxun on 15/10/25.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "CheckListsViewController.h"
#import "ChecklistItem.h"

@interface CheckListsViewController ()

@end

@implementation CheckListsViewController{
    NSMutableArray *mItems;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    mItems = [[NSMutableArray alloc]initWithCapacity:20];
    
    NSArray *texts = @[@"观看嫦娥 天和 兔升空的视频",
                      @"了解Sony a7和MBP的最新价格",
                      @"复习苍 师的经典视频教程",
                      @"去电影院看地 引 ",
                      @"看 甲巴萨新败的 赛回放"];
    
    for (int i = 0; i < texts.count; ++i)
    {
        ChecklistItem *item = [[ChecklistItem alloc]init];
        item.text = texts[i];
        item.checked = arc4random() % 2 == 0;
        [mItems addObject:item];
    }
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section{
    return mItems.count;
}

- (UITableViewCell*)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"ChecklistItem"];
    ChecklistItem *item = (ChecklistItem*)mItems[indexPath.row];
    
    [self configureTextForCell:cell withChecklistItem:item];
    [self configureCheckmarkForCell:cell withChecklistItem:item];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
    ChecklistItem *item = (ChecklistItem*)mItems[indexPath.row];
    [item toggleChecked];
    
    [self configureCheckmarkForCell:cell withChecklistItem:item];
    
    [tableView deselectRowAtIndexPath:indexPath animated:YES];
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath{
    [mItems removeObjectAtIndex:indexPath.row];
    
    NSArray *indexPaths = @[indexPath];
    [tableView deleteRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

-(void)configureTextForCell:(UITableViewCell *)cell withChecklistItem:(ChecklistItem *)item{
    UILabel *label = (UILabel*)[cell viewWithTag:1000];
    label.text = item.text;
}

-(void)configureCheckmarkForCell:(UITableViewCell *)cell withChecklistItem:(ChecklistItem *)tiem{
    UILabel *lable = (UILabel*)[cell viewWithTag:1001];
    lable.text = tiem.checked ? @"✅" : @"☑️";
}

- (void)addItem:(ChecklistItem *)item {
    NSInteger newRowIndex = mItems.count;
    [mItems addObject:item];
    
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:newRowIndex inSection:0];
    NSArray *indexPaths = @[indexPath];
    [self.tableView insertRowsAtIndexPaths:indexPaths withRowAnimation:UITableViewRowAnimationAutomatic];
}

- (void)updateItem:(ChecklistItem *)item
{
    NSInteger index = [mItems indexOfObject:item];
    NSIndexPath *indexPath = [NSIndexPath indexPathForRow:index inSection:0];
    UITableViewCell *cell = [self.tableView cellForRowAtIndexPath:indexPath];
    
    [self configureCheckmarkForCell:cell withChecklistItem:item];
    [self configureTextForCell:cell withChecklistItem:item];
}

//-----------------
//AddItemViewControllerDelegate
//-----------------

- (void)addItemViewController:(ItemDetailViewController *)controller didFinishAddingItem:(ChecklistItem *)item{
    [self addItem:item];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)addItemViewController:(ItemDetailViewController *)controller didFinishEditingItem:(ChecklistItem *)item{
    [self updateItem:item];
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)addItemViewControllerDidCancel:(ItemDetailViewController *)controller{
    
    [self dismissViewControllerAnimated:YES completion:nil];
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender{
    if ([segue.identifier isEqualToString:@"AddItem"])
    {
        UINavigationController *navigationController = segue.destinationViewController;
        
        ItemDetailViewController *controller = (ItemDetailViewController*)navigationController.topViewController;
        
        controller.delegate = self;
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









