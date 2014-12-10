#include "listen.h"
#include "../base/include/error.h"
#include "event.h"

void TestEventListPart();
void TestListen();
void TestStopListen();

int main()
{
	std::cout << "hello, Test" << std::endl;
	TestEventListPart();
	std::cout << "Test Success" << std::endl;

	int nEnd;
	std::cin >> nEnd ;
}

//////////////////////////////////////////////////////////////////////////
// EventList
void TestEvent()
{
	CiNetEvent event;

	KSocketData* pData = new KSocketData();

	// type error
	int errcode = event.Init(CiNetEvent::E_CINET_EVENT_CONNECT_NONE, pData);
	if (errcode != 1)
	{
		K_ERROR_QUIT("Event Init error: %d", errcode);
	}

	// socket empty
	errcode = event.Init(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, NULL);
	if (errcode != 2)
	{
		K_ERROR_QUIT("Event Init error: %d", errcode);
	}

	// success
	errcode = event.Init(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, pData);
	if (errcode != 0)
	{
		K_ERROR_QUIT("Event Init Error: %d", errcode);
	}

	// init twice
	errcode = event.Init(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, pData);
	if (errcode != 3)
	{
		K_ERROR_QUIT("Event Init Error: %d", errcode);
	}

	delete pData;
}

void TestEventList()
{

}

void TestEventListPart()
{
	TestEvent();

	TestEventList();
}

//////////////////////////////////////////////////////////////////////////
// KListen
void TestListenPart()
{
	TestListen();

	TestStopListen();
}

void TestListen()
{
	KListen* pl = new KListen();
	int errorcode;
#ifdef WIN32
	errorcode = pl->Listen("", 8080);	//  IP Error
#else
	errorcode = pl->Listen("127.0.0.0", 8080);	//  IP Error
#endif
	if(errorcode != 1)
	{
		K_ERROR_SYS("listen error : %d", errorcode);
	}

	errorcode = pl->Listen("127.0.0.1", 0);	// Part Error
	if (errorcode != 2)
	{
		K_ERROR_SYS("Listen error: %d", errorcode);
	}

	errorcode = pl->Listen("127.0.0.1", 8080);	// success

	errorcode = pl->Listen("127.0.0.1", 8080);	// 已经起动

	KListen* pl2 = new KListen();
	errorcode = pl->Listen("127.0.0.1", 8080);	// Part already use

	delete pl;
	pl = NULL;
	delete pl2;
	pl2 = NULL;

	pl = new KListen();
	errorcode = pl->Listen("127.0.0.1", 8080);	// 应该也是 success，但注意这里面有可能会遇上 WAIT 这个状态
	pl = NULL;
}

void TestStopListen()
{
	KListen* pl = new KListen();
	pl->StopListen();	// 未起动

	pl->Listen("127.0.0.1", 8080);
	pl->StopListen();	// success

	pl->StopListen();	// 未
}
