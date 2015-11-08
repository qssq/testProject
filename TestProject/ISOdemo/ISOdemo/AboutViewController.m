//
//  AboutViewController.m
//  ISOdemo
//
//  Created by gongxun on 15/10/19.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "AboutViewController.h"

@interface AboutViewController ()

@end

@implementation AboutViewController

@synthesize webView;

- (void)viewDidLoad {
    [super viewDidLoad];
    
//    NSString *htmlFile = [[NSBundle mainBundle]pathForResource:@"CrazyDrag" ofType:@"html"];
//    NSData *htmlData = [NSData dataWithContentsOfFile:htmlFile];
//    NSURL *baseURL = [NSURL fileURLWithPath:[[NSBundle mainBundle]bundlePath]];
//    
//    [self.webView loadData:htmlData MIMEType:@"text/html" textEncodingName:@"UTF-8" baseURL:baseURL];
    
    NSURL *url = [NSURL URLWithString:@"http://www.acfun.tv"];
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    [self.webView loadRequest:request];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)close:(id)sender {
    [self.presentingViewController dismissViewControllerAnimated:YES completion:nil];
}
@end
