#include "ODSocket6.h"
#include <stdio.h>

ODSocket6::ODSocket6(SOCKET sock)
{
	m_sock = sock;
}

ODSocket6::~ODSocket6()
{

}

int ODSocket6::Init()
{
#ifdef WIN32
	/*
	http://msdn.microsoft.com/zh-cn/vstudio/ms741563(en-us,VS.85).aspx

	typedef struct WSAData { 
		WORD wVersion;								//winsock version
		WORD wHighVersion;							//The highest version of the Windows Sockets specification that the Ws2_32.dll can support
		char szDescription[WSADESCRIPTION_LEN+1]; 
		char szSystemStatus[WSASYSSTATUS_LEN+1]; 
		unsigned short iMaxSockets; 
		unsigned short iMaxUdpDg; 
		char FAR * lpVendorInfo; 
	}WSADATA, *LPWSADATA; 
	*/
	WSADATA wsaData;
	//#define MAKEWORD(a,b) ((WORD) (((BYTE) (a)) | ((WORD) ((BYTE) (b))) << 8)) 
	WORD version = MAKEWORD(2, 0);
	int ret = WSAStartup(version, &wsaData);//win sock start up
	if ( ret ) {
//		cerr << "Initilize winsock error !" << endl;
		return -1;
	}
#endif
	
	return 0;
}
//this is just for windows
int ODSocket6::Clean()
{
#ifdef WIN32
		return (WSACleanup());
#endif
		return 0;
}

ODSocket6& ODSocket6::operator = (SOCKET s)
{
	m_sock = s;
	return (*this);
}

ODSocket6::operator SOCKET ()
{
	return m_sock;
}
//create a socket object win/lin is the same
// af:
bool ODSocket6::Create()
{
    int type = SOCK_STREAM;
	m_sock = socket(AF_INET6, type, IPPROTO_TCP);
	if ( m_sock == INVALID_SOCKET )
    {
		return false;
	}
    if(type == SOCK_DGRAM)//udp
    {
        int opt = 1;
        //设置该套接字为广播类型，
        setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(char *)&opt,sizeof(opt));
        //recv timeout 2 sec
        struct timeval tv_recv_timeout;
        tv_recv_timeout.tv_sec = 2;
        tv_recv_timeout.tv_usec = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		int nTvlen = 2000;  //1s
		setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char *)&nTvlen, sizeof(tv_recv_timeout));
#else
		setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&tv_recv_timeout, sizeof(tv_recv_timeout));
#endif
    }
    if(type == SOCK_STREAM)//tcp
    {
        struct timeval tv_recv_timeout;
        struct timeval tv_send_timeout;
        tv_recv_timeout.tv_sec = 0;
        tv_recv_timeout.tv_usec = 500000;
        tv_send_timeout.tv_sec = 0;
        tv_send_timeout.tv_usec = 500000;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		int nTvlen = 500;  //0.6s
		setsockopt(m_sock,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nTvlen, sizeof(tv_send_timeout));
		setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char *)&nTvlen, sizeof(tv_recv_timeout));
#else
		setsockopt(m_sock,SOL_SOCKET,SO_SNDTIMEO,(void *)&tv_send_timeout, sizeof(tv_send_timeout));
		setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&tv_recv_timeout, sizeof(tv_recv_timeout));
#endif
    }
    return true;
}

bool ODSocket6::CreateServer()
{
    int type = SOCK_STREAM;
    m_sock = socket(PF_INET6, type, 0);
    if ( m_sock == INVALID_SOCKET )
    {
        return false;
    }
    if(type == SOCK_DGRAM)//udp
    {
        int opt = 1;
        //设置该套接字为广播类型，
        setsockopt(m_sock,SOL_SOCKET,SO_BROADCAST,(char *)&opt,sizeof(opt));
        //recv timeout 2 sec
        struct timeval tv_recv_timeout;
        tv_recv_timeout.tv_sec = 2;
        tv_recv_timeout.tv_usec = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        int nTvlen = 2000;  //1s
        setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char *)&nTvlen, sizeof(tv_recv_timeout));
#else
        setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&tv_recv_timeout, sizeof(tv_recv_timeout));
#endif
    }
    if(type == SOCK_STREAM)//tcp
    {
        struct timeval tv_recv_timeout;
        struct timeval tv_send_timeout;
        tv_recv_timeout.tv_sec = 0;
        tv_recv_timeout.tv_usec = 500000;
        tv_send_timeout.tv_sec = 0;
        tv_send_timeout.tv_usec = 500000;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        int nTvlen = 500;  //0.6s
        setsockopt(m_sock,SOL_SOCKET,SO_SNDTIMEO,(const char *)&nTvlen, sizeof(tv_send_timeout));
        setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char *)&nTvlen, sizeof(tv_recv_timeout));
#else
        setsockopt(m_sock,SOL_SOCKET,SO_SNDTIMEO,(void *)&tv_send_timeout, sizeof(tv_send_timeout));
        setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(void *)&tv_recv_timeout, sizeof(tv_recv_timeout));
#endif
    }
    return true;
}

bool ODSocket6::Connect(const char* ip, unsigned short port)
{
    struct sockaddr_in6 svraddr;
    svraddr.sin6_family = AF_INET6;
    inet_pton(AF_INET6, ip, &svraddr.sin6_addr);
    svraddr.sin6_port = htons(port);
	int ret = connect(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

int ODSocket6::Setsockopt()
{
	bool bOpt = true;  
	int iopt =setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));  
	return iopt;
}

int ODSocket6::SetsockoptUdp()
{
	bool bOpt = true;  
	int iopt =setsockopt(m_sock, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));  
	return iopt;
}
bool ODSocket6::Bind(unsigned short port)
{
	struct sockaddr_in6 svraddr;
	svraddr.sin6_family = AF_INET6;
    svraddr.sin6_addr = in6addr_any;
	svraddr.sin6_port = htons(port);
    
    char buf[1024 + 1];
    printf("%s\n", inet_ntop(AF_INET6, &svraddr.sin6_addr, buf, sizeof(buf)));
    
	int opt =  1;
	if ( setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt)) < 0 ) 
		return false;

	int ret = bind(m_sock, (struct sockaddr*)&svraddr, sizeof(svraddr));
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}
//for server
bool ODSocket6::Listen(int backlog)
{
	int ret = listen(m_sock, backlog);
	if ( ret == SOCKET_ERROR ) {
		return false;
	}
	return true;
}

bool ODSocket6::Accept(ODSocket6& s, char* fromip)
{
	struct sockaddr_in6 cliaddr;
	socklen_t addrlen = sizeof(cliaddr);
	SOCKET sock = accept(m_sock, (struct sockaddr*)&cliaddr, &addrlen);
	if ( sock == SOCKET_ERROR ) {
		return false;
	}

	s = sock;
	if ( fromip != NULL )
    {
        char buf[1024 + 1];
        sprintf(fromip, "%s", inet_ntop(AF_INET6, &cliaddr.sin6_addr, buf, sizeof(buf)));
    }

	return true;
}

int ODSocket6::Send(const char* buf, int len, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len ) {

		bytes = send(m_sock, buf + count, len - count, flags);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
		
	} 
	return count;
}

int ODSocket6::Sendto(const char* buf, int len,const struct sockaddr *to, int tolen, int flags)
{
	int bytes;
	int count = 0;

	while ( count < len ) {

		bytes = sendto(m_sock, buf + count, len - count,flags,to,tolen);
		if ( bytes == -1 || bytes == 0 )
			return -1;
		count += bytes;
		
	} 

	return count;
}

int ODSocket6::Send_broadcast(const char* buf,int len,unsigned short port)
{
    struct sockaddr_in addrto;
    socklen_t addrlen = sizeof(addrto);
    addrto.sin_family=AF_INET;
    addrto.sin_addr.s_addr=INADDR_BROADCAST;
    addrto.sin_port=htons(port);
    
    int bytes = sendto(m_sock,buf,len,0,(struct sockaddr*)&addrto,addrlen);
    if(SOCKET_ERROR == bytes)
    {
        return -1;
    }
    return bytes;
}

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
int ODSocket6::Recvfrom(char* buf, int len,struct sockaddr * to, unsigned int tolen, int flags)
{
	int bytes;
	bytes= recvfrom(m_sock, buf, len, flags,to,&tolen);
	if(bytes==-1||bytes==0)
		return -1;
	else
		return bytes;
}
#else
int ODSocket6::Recvfrom(char* buf, int len,struct sockaddr * to, int tolen, int flags)
{
    int bytes;
    bytes= recvfrom(m_sock, buf, len, flags,to,&tolen);
    if(bytes==-1||bytes==0)
        return -1;
    else
        return bytes;
}
#endif

int ODSocket6::Recv(char* buf, int len, int flags)
{
	return (recv(m_sock, buf, len, flags));
}


int ODSocket6::Close()
{
#ifdef WIN32
	return (closesocket(m_sock));
#else
	return (close(m_sock));
#endif
}

int ODSocket6::GetError()
{
#ifdef WIN32
	return (WSAGetLastError());
#else
	return (errno);
#endif
}

bool ODSocket6::DnsParse(const char* domain, char* ip)
{
	struct hostent* p;
	if ( (p = gethostbyname(domain)) == NULL )
		return false;
		
	sprintf(ip, 
		"%u.%u.%u.%u",
		(unsigned char)p->h_addr_list[0][0], 
		(unsigned char)p->h_addr_list[0][1], 
		(unsigned char)p->h_addr_list[0][2], 
		(unsigned char)p->h_addr_list[0][3]);
	
	return true;
}
