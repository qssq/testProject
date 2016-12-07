//
//  GzipHelper.cpp
//  MacHelper
//
//  Created by gongxun on 16/11/14.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#include "GzipHelper.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>

using namespace std;

GzipHelper::GzipHelper()
{
    
}

GzipHelper::~GzipHelper()
{
    
}

void GzipHelper::start()
{
    namespace bio = boost::iostreams;
    
    vector<int> params = {bio::gzip::no_compression, bio::gzip::best_speed, bio::gzip::best_compression, bio::gzip::default_compression};
    
    for (int i = 0; i < 4; i++)
    {
        std::stringstream compressed;
        std::stringstream origin("dc483e80a7a0bd9ef71d8cf973673924");
        
        bio::filtering_streambuf<bio::input> out;
        out.push(bio::gzip_compressor(bio::gzip_params(params[i])));
        out.push(origin);
        bio::copy(out, compressed);
        
        string test = compressed.str();
        for (int i = 0; i < test.size(); ++i)
        {
            int a = 0;
            unsigned char b = test[i];
            int c = b;
            cout<<c<<",";
        }
        cout<<endl;
        cout<<"结果为:"<<test<<"长度是:"<<test.size()<<endl;
        
        cout<<"--------------------------------"<<endl;
    }
}















