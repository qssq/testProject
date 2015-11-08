//
//  ViewController.h
//  ISOdemo
//
//  Created by gongxun on 15/10/16.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

- (IBAction)showAlert:(id)sender;

- (IBAction)touchAbout:(id)sender;

//- (void)setNewCurrentScore;
//
//- (void)initSlider;
//
//- (void)playBackgroundMusic;

@property (strong, nonatomic) IBOutlet UISlider *slider;

@property (strong, nonatomic) IBOutlet UILabel *labelQuestion;

@property (strong, nonatomic) IBOutlet UILabel *labelScore;

@end

