//
//  NSObject+ChecklistItem.m
//  CheckLists
//
//  Created by gongxun on 15/11/7.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "ChecklistItem.h"

@interface ChecklistItem()

@end

@implementation ChecklistItem

-(void)toggleChecked
{
    self.checked = !self.checked;
}

@end