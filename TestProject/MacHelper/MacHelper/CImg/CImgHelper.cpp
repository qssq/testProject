//
//  GILHelper.c
//  MacHelper
//
//  Created by gongxun on 16/5/3.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#include "CImgHelper.h"
#include <iostream>
#include "XMLHelper.h"

#define cimg_use_png
#include "CImg.h"
using namespace cimg_library;
#include "png.h"

const string gPath = "/Users/gongxun/GitHub/testProject/TestProject/MacHelper/resources/";

CImgHelper::CImgHelper()
{
    cimg::imagemagick_path("/usr/local/bin/convert");
}

CImgHelper::~CImgHelper()
{
    
}

void CImgHelper::test01()
{
//    //创建2个窗口 第一个图片 第二个二维图片
//    CImg<unsigned char> image(getFullName("test01.png").c_str()), visu(500,300,1,3,0);
//    //用于绘图
//    const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
//    //高斯模糊 也可以get_blur
//    image.blur(5);
//    //显示2两个窗口
//    CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
//    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
//        main_disp.wait();
//        if (main_disp.button() && main_disp.mouse_y()>=0) {
//            const int y = main_disp.mouse_y();
//            visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
//            visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
//            visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
//        }
//    }
//    image.save("temp.png");
    
//    GaussianBlur("test01.png");
    
//    CreateImage();
    
//    copyFile("girlAnimPin.png");
    
//    copyFiles();
    
//    copyLodingFiles();
    
//    ImgRect rect0 = {0, 0, 532, 86, "img_dengdai"};
//    vector<ImgRect> rects = {rect0};
//    copyFiles(rects, "UINiuNiu1.png");
//    copyTimerFiles();
//    copyChiFiles();
    
//    texturePacker(gPath + "fish_net.plist", "fish_net.png");
//    texturePacker(gPath + "ddz_result11.plist", "ddz_result11.png");
//    texturePacker(gPath + "tableresult.plist", "tableresult.png");
//    texturePacker(gPath + "fish_frame_1_1.plist", "fish_frame_1_1.png");
//    texturePacker(gPath + "fish_frame_1_2.plist", "fish_frame_1_2.png");
//    texturePacker(gPath + "fish_frame_1_3.plist", "fish_frame_1_3.png");
//    texturePacker(gPath + "fish_frame_1_4.plist", "fish_frame_1_4.png");
//    texturePacker(gPath + "fish_frame_1_5.plist", "fish_frame_1_5.png");
//    texturePacker(gPath + "fish_frame_1_6.plist", "fish_frame_1_6.png");
    //    texturePacker(gPath + "fish_frame_1_7.plist", "fish_frame_1_7.png");
//        texturePacker(gPath + "fish_frame_1_7.plist", "fish_frame_1_7.png");
//            texturePacker(gPath + "dbjdCards.plist", "dbjdCards.png");
//    texturePacker(gPath + "dbjdCards.plist", "dbjdCards.png");
//    texturePacker(gPath + "bigCards2.plist", "bigCards2.png");
        texturePacker(gPath + "cymjCards.plist", "cymjCards.png");
//            texturePacker(gPath + "dbjdCards.plist", "dbjdCards.png");
//            texturePacker(gPath + "bigCards.plist", "bigCards.png");
    
    
//    texturePacker(gPath + "fish_net.plist", "fish_net.png");
//    texturePacker(gPath + "fish_net4.plist", "fish_net4.png");
    //    texturePacker(gPath + "fish_zidan.plist", "fish_zidan.png");
//        texturePacker(gPath + "tileImage.plist", "tileImage.png");
//    texturePacker(gPath + "gametrayImage.plist", "gametrayImage.png");
    
    
    //创建麻将牌纹理
//    createCards();
    
    
//    cleanWhite();
    
    
    //裁切
//    vector<ImgRect> rects;
//    int index = 0;
//    for(int i = 0; i < 5; i++)
//    {
//        for (int j = 0; j < 6; j++)
//        {
//            char name[20];
//            sprintf(name, "emoji_%d", i * 6 + j);
//            ImgRect rect = {i * 100, j * 100, 100, 100, 0, 0, 100, 100, false, name};
//            rects.push_back(rect);
//        }
//    }
//    copyFiles(rects, "faceq_res.png");
    
    //裁切
//    vector<ImgRect> rects;
//    int index = 0;
//    for(int i = 0; i < 5; i++)
//    {
//        for (int j = 0; j < 6; j++)
//        {
//            char name[20];
//            sprintf(name, "emoji_%d", i * 6 + j);
//            ImgRect rect = {i * 100, j * 100, 100, 100, 0, 0, 100, 100, false, name};
//            rects.push_back(rect);
//        }
//    }
//    copyFiles(rects, "dice_left.png");
}

void CImgHelper::GaussianBlur(const string &file)
{
    cout<<"开始高斯模糊 file:"<<file<<endl;
    CImg<unsigned char> image(getFullName(file).c_str());
    image.blur(10);
    image.save("temp.png");
    cout<<"完成高斯模糊 file:"<<"temp.png"<<endl;
}

void CImgHelper::CreateImage()
{
    cout<<"开始创建文件"<<endl;
    CImg<unsigned char> img(640,400,1,3);
    img.fill(0);
    unsigned char purple[] = { 255,0,255 };
    img.draw_text(100, 100, "Hello World",purple);
    img.display("My first CImg code");
    img.save("hello.png");
    cout<<"完成创建文件"<<endl;
}

void CImgHelper::copyFile(const string &file)
{
    cout<<"开始复制文件"<<endl;
    CImg<unsigned char> imgSource(getFullName(file).c_str());
    cout<<"深度:"<<imgSource.spectrum()<<endl;
//    imgSource.display();
    
    ImgRect rect = {636, 2, 332, 517};
    CImg<unsigned char> imgOut(rect.width, rect.height, 1, 4);
    
    for (int x = rect.x, ox = 0; x < imgSource.width(); ++x, ++ox)
    {
        for (int y = rect.y, oy = 0; y < imgSource.height(); ++y, ++oy)
        {
            for (int c = 0; c < 4; ++c)
            {
                auto temp = imgSource.atXYZC(x, y, 1, c);
                imgOut.atXYZC(ox, oy, 1, c) = temp;
            }
        }
    }
    cout<<"深度:"<<imgOut.spectrum()<<endl;
    imgOut.save_png("girlFailed1.png");
    cout<<"结束复制文件"<<endl;
}

void CImgHelper::copyFiles(const vector<ImgRect> &rects, const string &file)
{
    cout<<"开始复制文件"<<endl;
    CImg<unsigned char> imgSource(getFullName(file).c_str());
    for (auto it : rects)
    {
        if (!it.isRotated)
        {
            CImg<unsigned char> img(it.width, it.height, 1, 4);
            for (int i = 0; i < it.width; ++i)
            {
                for (int j = 0; j < it.height; ++j)
                {
                    int x = i - it.offsetX;
                    int y = j - it.offsetY;
                    if ((x >= 0 && x < it.offsetWidth) && (y >= 0 && y < it.offsetHeight))
                    {
                        for (int c = 0; c < 4; ++c)
                        {
                            auto temp = imgSource.atXYZC(it.x + x, it.y + y, 1, c);
                            img.atXYZC(i, j, 1, c) = temp;
                        }
                    }
                    else
                    {
                        for (int c = 0; c < 4; ++c)
                        {
                            img.atXYZC(i, j, 1, c) = 0;
                        }
                    }
                }
            }
            char name[100];
            sprintf(name, "%s.png", it.name.c_str());
            img.save_png(name);
            cout<<"复制文件:"<<name<<endl;
        }
        else
        {
            CImg<unsigned char> img(it.width, it.height, 1, 4);
            for (int i = 0; i < it.width; ++i)
            {
                for (int j = 0; j < it.height; ++j)
                {
                    int x = i - it.offsetX;
                    int y = (it.height - j) - (it.height - it.offsetY - it.offsetHeight) - 1;
                    if ((x >= 0 && x < it.offsetWidth) && (y >= 0 && y < it.offsetHeight))
                    {
                        for (int c = 0; c < 4; ++c)
                        {
                            auto temp = imgSource.atXYZC(it.x + y, it.y + x, 1, c);
                            img.atXYZC(i, j, 1, c) = temp;
                        }
                    }
                    else
                    {
                        for (int c = 0; c < 4; ++c)
                        {
                            img.atXYZC(i, j, 1, c) = 0;
                        }
                    }
                }
            }
            char name[100];
            sprintf(name, "%s.png", it.name.c_str());
            img.save_png(name);
            cout<<"复制文件:"<<name<<endl;
        }
    }
    cout<<"结束复制文件"<<endl;
}

void CImgHelper::copyLodingFiles()
{
//    ImgRect rect0 = {2, 370, 100, 100, "loading1"};
//    ImgRect rect1 = {2, 268, 100, 100, "loading2"};
//    ImgRect rect2 = {104, 166, 100, 100, "loading3"};
//    ImgRect rect3 = {2, 166, 100, 100, "loading4"};
//    ImgRect rect4 = {344, 104, 100, 100, "loading5"};
//    ImgRect rect5 = {242, 104, 100, 100, "loading6"};
//    ImgRect rect6 = {344, 2, 100, 100, "loading7"};
//    ImgRect rect7 = {242, 2, 100, 100, "loading8"};
//    ImgRect rect8 = {2, 2, 238, 162, "loading_bg"};
//    vector<ImgRect> rects = {rect0, rect1, rect2, rect3, rect4, rect5, rect6, rect7, rect8};
//    copyFiles(rects, "LoadingPin.png");
}

void CImgHelper::copyTimerFiles()
{
//    ImgRect rect0 = {158, 0, 114, 114, "TimerProgress"};
//    ImgRect rect1 = {0, 0, 156, 156, "Timer_blackBack"};
//    ImgRect rect2 = {0, 298, 56, 140, "Timer_wind0"};
//    ImgRect rect3 = {140, 274, 140, 56, "Timer_wind1"};
//    ImgRect rect4 = {140, 216, 140, 56, "Timer_wind2"};
//    ImgRect rect5 = {140, 158, 140, 56, "Timer_wind3"};
//    ImgRect rect6 = {0, 158, 138, 138, "Timer_windBack"};
//    ImgRect rect7 = {274, 0, 138, 104, "Timer_windBack_DP"};
//    vector<ImgRect> rects = {rect0, rect1, rect2, rect3, rect4, rect5, rect6, rect7};
//    copyFiles(rects, "TimerImage.png");
}

void CImgHelper::copyChiFiles()
{
//    vector<ImgRect> rects;
//    auto add = [](int x, int y, int width, int height, string name, vector<ImgRect> &rects)
//    {
//        ImgRect rect = {x, y, width, height, name};
//        rects.push_back(rect);
//    };
//    add(338, 98, 48, 73, "chipenggang", rects);
//    add(0, 276, 126, 92, "tray_cancel", rects);
//    add(398, 179, 81, 152, "tray_focus_cpgh", rects);
//    add(411, 0, 100, 177, "tray_focus_guoting", rects);
//    add(0, 370, 99, 93, "tray_guo", rects);
//    add(308, 375, 150, 132, "tray_hu", rects);
//    add(158, 238, 148, 136, "tray_ting", rects);
//    add(0, 0, 172, 136, "tray_word_chi", rects);
//    add(174, 98, 162, 138, "tray_word_gang", rects);
//    add(0, 138, 156, 136, "tray_word_peng", rects);
//    add(460, 375, 46, 63, "tray_pai_mask", rects);
//    add(338, 173, 46, 70, "tray_pai_back", rects);
//    add(174, 0, 235, 96, "tray_back_cpg", rects);
//
//    copyFiles(rects, "gametrayImage.png");
}

void CImgHelper::copyFishFiles()
{
    
}

string CImgHelper::getFullName(const string &file)
{
//    return  file;
    return gPath + file;
}

void CImgHelper::texturePacker(const string &plist, const string &png)
{
    vector<TexturePackerInfo> infos;
    
    XMLHelper::singleton()->getTexturePackets(plist, infos);
    
    cout<<infos.size()<<endl;
    
    vector<ImgRect> rects;
    for (int i = 0; i < infos.size(); ++i)
    {
        ImgRect rect = {infos[i].x, infos[i].y, infos[i].width, infos[i].height, infos[i].offsetX, infos[i].offsetY, infos[i].offsetWidth, infos[i].offsetHeight, infos[i].isRotated, infos[i].name};
        rects.push_back(rect);
    }
    copyFiles(rects, png);
}

void CImgHelper::createCards()
{
    int xp = 27;
    int yp = 216;
    
    vector<string> files;
    for (int i = 1; i <= 34; ++i)
    {
        int num = i;
        if (num <= 9)
        {
            num += 20;
        }
        else if (num <= 18)
        {
            num += (40 - 9);
        }
        else if (num <= 27)
        {
            num += (60 - 18);
        }
        else
        {
            num += (80 - 27);
        }
        string file;
        ostringstream oss;
        oss<<gPath<<"card/card"<<num<<".png";
        file = oss.str();
        files.push_back(file);
    }
    
    for (int i = 0 ; i < files.size(); ++i)
    {
        string file = files[i];
        CImg<unsigned char> imgSource(getFullName("card/cardTexture.png").c_str());
        CImg<unsigned char> img(file.c_str());
        
        int xStart = xp - (int)(img.width() / 2);
        int xEnd = xStart + img.width();
        int yStart = yp - (int)(img.height() / 2);
        int yEnd = yStart + img.height();
        
        for (int x = xStart; x < xEnd; ++x)
        {
            for (int y = yStart; y < yEnd; ++y)
            {
                if (x >= 0 && x < imgSource.width() && y >= 0 && y < imgSource.height())
                {
                    if (img.atXYZC(x - xStart, y - yStart, 1, 3) != 0)
                    {
                        for (int c = 0; c < 3; ++c)
                        {
                            int temp = img.atXYZC(x - xStart, y - yStart, 1, c);
                            imgSource.atXYZC(x, y, 1, c) = temp;
                        }
                    }
                }
            }
        }
        char name[100];
        sprintf(name, "%s", file.substr(gPath.size(), file.size() - gPath.size()).c_str());
        imgSource.save_png(name);
        cout<<"index:"<<i + 1<<" 保存图片:"<<name<<endl;
    }
}

void CImgHelper::cleanWhite()
{
    CImg<unsigned char> imgSource(getFullName("r1.png").c_str());
    for (int x = 0; x < imgSource.width(); ++x)
    {
        for (int y = 0; y < imgSource.height(); ++y)
        {
            if (imgSource.atXYZC(x, y, 1, 0) > 250 && imgSource.atXYZC(x, y, 1, 1) > 250 && imgSource.atXYZC(x, y, 1, 2) > 250)
            {
                imgSource.atXYZC(x, y, 1, 0) = 255;
                imgSource.atXYZC(x, y, 1, 1) = 0;
                imgSource.atXYZC(x, y, 1, 2) = 0;
//                imgSource.atXYZC(x, y, 1, 3) = 255;
            }
        }
    }
    
    char name[100];
    sprintf(name, "%s", "r1.png");
    imgSource.save_png(name);
    cout<<"index:"<<1<<" 保存图片:"<<name<<endl;
}

















