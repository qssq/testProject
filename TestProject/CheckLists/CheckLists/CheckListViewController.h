//
//  ViewController.h
//  CheckLists
//
//  Created by gongxun on 15/10/25.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ItemDetailViewController.h"

@class Checklist;

@interface CheckListViewController : UITableViewController<ItemDetailViewControllerDelegate>

- (IBAction)addItem:(id)sender;

@property (strong, nonatomic) Checklist *checklist;

@end

