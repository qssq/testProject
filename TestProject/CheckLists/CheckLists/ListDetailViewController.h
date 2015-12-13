//
//  ListDetailViewController.h
//  CheckLists
//
//  Created by gongxun on 15/11/9.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ListDetailViewController;
@class Checklist;

@protocol ListDetailViewControllerDelegate <NSObject>

-(void)ListDetailViewControllerDidCancel:(ListDetailViewController*)controller;

-(void)ListDetailViewController:(ListDetailViewController*)controller didFinishAddingChecklist:(Checklist*)checklist;

-(void)ListDetailViewController:(ListDetailViewController*)controller didFinishEditingChecklist:(Checklist*)checklist;

@end

@interface ListDetailViewController : UITableViewController<UITextFieldDelegate>

@property (weak, nonatomic)id <ListDetailViewControllerDelegate> delegate;

@property (weak, nonatomic) IBOutlet UIBarButtonItem *doneBarButton;

@property (weak, nonatomic) IBOutlet UITextField *textField;

@property (strong, nonatomic) Checklist *mEditItem;

- (IBAction)done:(id)sender;

- (IBAction)cancel:(id)sender;

@end
