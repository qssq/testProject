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

- (id)initWithCoder:(NSCoder *)aDecoder
{
    if ((self = [super init]))
    {
        self.text = [aDecoder decodeObjectForKey:@"Text"];
        self.checked = [aDecoder decodeBoolForKey:@"Checked"];
    }
    return self;
}

- (void)encodeWithCoder:(NSCoder *)aCoder
{
    [aCoder encodeObject:self.text forKey:@"Text"];
    [aCoder encodeBool:self.checked forKey:@"Checked"];
}

-(void)toggleChecked
{
    self.checked = !self.checked;
}

@end