//
//  AboutViewController.h
//  ISOdemo
//
//  Created by gongxun on 15/10/19.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AboutViewController : UIViewController

- (IBAction)close:(id)sender;

@property (strong, nonatomic) IBOutlet UIWebView *webView;

@end
