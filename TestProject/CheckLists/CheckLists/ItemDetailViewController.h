//
//  AddItemViewController.h
//  CheckLists
//
//  Created by gongxun on 15/11/7.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ItemDetailViewController;
@class ChecklistItem;

@protocol AddItemViewControllerDelegate <NSObject>

-(void)addItemViewControllerDidCancel:(ItemDetailViewController*)controller;

-(void)addItemViewController:(ItemDetailViewController*)controller didFinishAddingItem:(ChecklistItem*)item;

-(void)addItemViewController:(ItemDetailViewController*)controller didFinishEditingItem:(ChecklistItem*)item;

@end

@interface ItemDetailViewController : UITableViewController<UITextFieldDelegate>

@property (weak, nonatomic)id <AddItemViewControllerDelegate> delegate;

@property (weak, nonatomic) IBOutlet UIBarButtonItem *doneBarButton;

@property (weak, nonatomic) IBOutlet UITextField *textField;

@property (strong, nonatomic) ChecklistItem *mEditItem;

- (IBAction)done:(id)sender;

- (IBAction)cancel:(id)sender;

@end
