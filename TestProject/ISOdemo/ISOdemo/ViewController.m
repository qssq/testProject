//
//  ViewController.m
//  ISOdemo
//
//  Created by gongxun on 15/10/16.
//  Copyright © 2015年 gongxun. All rights reserved.
//

#import "ViewController.h"
#import "AboutViewController.h"
#import <AVFoundation/AVFoundation.h>

@interface ViewController (){
    int mCurrentScore;
    int mTotalScore;
    int mGameRound;
}

@property (strong, nonatomic) AVAudioPlayer *mAudioPlayer;

@end

@implementation ViewController

@synthesize slider, labelQuestion, labelScore, mAudioPlayer;

- (void)playBackgroundMusic {
    NSString *musicPath =[[NSBundle mainBundle]pathForResource:@"no" ofType:@"mp3"];
    NSURL *url = [NSURL fileURLWithPath:musicPath]; NSError *error;
    mAudioPlayer = [[AVAudioPlayer alloc]initWithContentsOfURL:url error:&error]; mAudioPlayer.numberOfLoops = -1;
    if(mAudioPlayer ==nil) {
        NSString *errorInfo = [NSString stringWithString:[error description]];
        NSLog(@"the error is:%@",errorInfo);
    }
    else {
        [mAudioPlayer play];
    }
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    //随机分数
    [self setNewCurrentScore];
    
    //slider
    [self initSlider];
    
    //播放背景音乐
    [self playBackgroundMusic];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)setNewCurrentScore{
    mCurrentScore = arc4random() % 101;
    labelQuestion.text = [NSString stringWithFormat:@"%d", mCurrentScore];
}

- (void)initSlider{
    [self.slider setThumbImage:[UIImage imageNamed:@"res/Images/SliderThumb-Normal.png"] forState:UIControlStateNormal];
    [self.slider setThumbImage:[UIImage imageNamed:@"res/Images/SliderThumb-Highlighted.png"] forState:UIControlStateHighlighted];
    [self.slider setMinimumTrackImage:[[UIImage imageNamed:@"res/Images/SliderTrackLeft.png"] stretchableImageWithLeftCapWidth:14 topCapHeight:0] forState:UIControlStateNormal];
    [self.slider setMaximumTrackImage:[[UIImage imageNamed:@"res/Images/SliderTrackRight.png"] stretchableImageWithLeftCapWidth:14 topCapHeight:0]forState:UIControlStateNormal];
}

- (IBAction)showAlert:(id)sender {
    ++mGameRound;
    int value = slider.value;
    int score = 100 - abs(mCurrentScore - value);
    mTotalScore += score;
    
    NSString *showMsg = [NSString stringWithFormat:@"你选择的数值时%d，目标数值时%d，你的得分是%d", value, mCurrentScore, score];
    [[[UIAlertView alloc]initWithTitle:@"提示" message:showMsg delegate:nil cancelButtonTitle:@"取消" otherButtonTitles:nil, nil]show];
    
    labelScore.text = [NSString stringWithFormat:@"游戏局数%d，得分%d", mGameRound, mTotalScore];
    [self setNewCurrentScore];
    
    //过度动画
    CATransition *transition = [CATransition animation];
    transition.type = kCATransitionFade;
    transition.duration = 1;
    transition.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseOut];
    [self.view.layer addAnimation:transition forKey:nil];
}

- (IBAction)touchAbout:(id)sender {
    AboutViewController *aboutController = [[AboutViewController alloc] initWithNibName:@"AboutViewController" bundle:nil];
    aboutController.modalTransitionStyle = UIModalTransitionStyleFlipHorizontal;
    [self presentViewController:aboutController animated:YES completion:nil];
}
@end















