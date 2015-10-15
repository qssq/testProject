//
//  ViewController.m
//  ISOdemo
//
//  Created by gongxun on 15/10/16.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)showAlert:(id)sender {
    NSLog(@"hehe");
    [[[UIAlertView alloc]initWithTitle:@"你点到我了" message:@"你为什么要点我呢" delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil, nil]show];
}
@end
