//
//  ListDetailViewController.m
//  CheckLists
//
//  Created by gongxun on 15/11/9.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "ListDetailViewController.h"
#import "Checklist.h"

@interface ListDetailViewController ()

@end

@implementation ListDetailViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    if (self.mEditItem != nil)
    {
        self.title = @"Edit Checklist";
        self.textField.text = self.mEditItem.name;
    }
    
    self.doneBarButton.enabled = self.textField.text > 0;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

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
        Checklist *item = [[Checklist alloc] init];
        item.name = self.textField.text;
        [self.delegate ListDetailViewController:self didFinishAddingChecklist:item];
    }
    else
    {
        self.mEditItem.name = self.textField.text;
        [self.delegate ListDetailViewController:self didFinishEditingChecklist:self.mEditItem];
    }
}

- (IBAction)cancel:(id)sender {
    [self.delegate ListDetailViewControllerDidCancel:self];
}

@end
