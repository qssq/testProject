//
//  ItemDetailViewController.h
//  CheckLists
//
//  Created by gongxun on 15/11/7.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ItemDetailViewController;
@class ChecklistItem;

@protocol ItemDetailViewControllerDelegate <NSObject>

-(void)ItemDetailViewControllerDidCancel:(ItemDetailViewController*)controller;

-(void)ItemDetailViewController:(ItemDetailViewController*)controller didFinishAddingItem:(ChecklistItem*)item;

-(void)ItemDetailViewController:(ItemDetailViewController*)controller didFinishEditingItem:(ChecklistItem*)item;

@end

@interface ItemDetailViewController : UITableViewController<UITextFieldDelegate>

@property (weak, nonatomic)id <ItemDetailViewControllerDelegate> delegate;

@property (weak, nonatomic) IBOutlet UIBarButtonItem *doneBarButton;

@property (weak, nonatomic) IBOutlet UITextField *textField;

@property (strong, nonatomic) ChecklistItem *mEditItem;

- (IBAction)done:(id)sender;

- (IBAction)cancel:(id)sender;

@end
