//
//  main.cpp
//  SocketClient
//
//  Created by gongxun on 15/9/14.
//  Copyright (c) 2015年 gongxun. All rights reserved.
//

#include <iostream>
#include "ODSocket.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    ODSocket cSocket;
    cSocket.Init();
    cSocket.Create(AF_INET,SOCK_STREAM,0);
    cSocket.Connect("192.168.2.175",7880);
    char recvBuf[64] = "\0";
    cSocket.Send("bbb",strlen("bbb")+1,0);
    cSocket.Recv(recvBuf,64,0);
    printf("%s was recived from server!\n",recvBuf);
    cSocket.Close();
    cSocket.Clean();
    
    system("Pause");
    
    return 0;
}
