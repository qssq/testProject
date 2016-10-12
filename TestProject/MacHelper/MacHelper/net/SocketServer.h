//
//  SocketServer.hpp
//  MacHelper
//
//  Created by gongxun on 16/9/28.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#ifndef SocketServer_hpp
#define SocketServer_hpp

#include "ODSocket6.h"
#include "ODSocket.h"
#include <iostream>
#include <string>

using namespace std;

class SocketServer
{
public:
    SocketServer();
    ~SocketServer();
    void start();
};

#endif /* SocketServer_hpp */
