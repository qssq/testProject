//
//  ItemDetailViewController.m
//  CheckLists
//
//  Created by gongxun on 15/11/7.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "ItemDetailViewController.h"
#import "ChecklistItem.h"

@interface ItemDetailViewController ()

@end

@implementation ItemDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if (self.mEditItem != nil)
    {
        self.title = @"Edit Item";
        self.textField.text = self.mEditItem.text;
    }
    
    self.doneBarButton.enabled = self.textField.text > 0;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Table view data source

-(NSIndexPath*)tableView:(UITableView *)tableView willSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    return nil;
}

- (void)viewWillAppear:(BOOL)animated{
    [super viewWillAppear:animated];
    
    [self.textField becomeFirstResponder];
}

-(BOOL)textField:(UITextField *)textField shouldChangeCharactersInRange:(NSRange)range replacementString:(NSString *)string{
    NSString *newText = [textField.text stringByReplacingCharactersInRange:range withString:string];
    
    self.doneBarButton.enabled = newText.length > 0;
    return YES;
}

- (IBAction)done:(id)sender {
    if (self.mEditItem == nil)
    {
        ChecklistItem *item = [[ChecklistItem alloc] init];
        item.text = self.textField.text;
        item.checked = NO;
        [self.delegate ItemDetailViewController:self didFinishAddingItem:item];
    }
    else
    {
        self.mEditItem.text = self.textField.text;
        [self.delegate ItemDetailViewController:self didFinishEditingItem:self.mEditItem];
    }
}

- (IBAction)cancel:(id)sender {
    [self.delegate ItemDetailViewControllerDidCancel:self];
}
@end






















