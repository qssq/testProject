//
//  SocketServer.cpp
//  MacHelper
//
//  Created by gongxun on 16/9/28.
//  Copyright © 2016年 gongxun. All rights reserved.
//

#include "SocketServer.h"

SocketServer::SocketServer()
{
    
}

SocketServer::~SocketServer()
{
    
}

void SocketServer::start()
{
    ODSocket6 mysocket, clientsocket;
    mysocket.Init();
    mysocket.CreateServer();
    mysocket.Bind(7880);
    mysocket.Listen();
    char ipClient[64];
    char recvBuf[64] = "\0";
    while(1)
    {
        mysocket.Accept(clientsocket,ipClient);
        printf("%s was log in!\n",ipClient);
        clientsocket.Recv(recvBuf,64,0);
        printf("%s was recived from Client:%s!\n",recvBuf,ipClient);
        recvBuf[0] = '\0';
        clientsocket.Send("aaa",strlen("aaa")+1,0);
    }
    printf("server close");
    mysocket.Close();
    mysocket.Clean();
    
    string input;
    cin>>input;
}
