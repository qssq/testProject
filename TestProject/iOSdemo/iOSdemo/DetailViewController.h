//
//  DetailViewController.h
//  iOSdemo
//
//  Created by gongxun on 15/10/15.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DetailViewController : UIViewController

@property (strong, nonatomic) id detailItem;
@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;

@end

