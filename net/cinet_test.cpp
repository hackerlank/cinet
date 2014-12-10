#include "listen.h"
#include "../base/include/error.h"
#include "event.h"
#include "eventlist.h"

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
	CiNetEvent* pEvent = new CiNetEvent();
	KSocketData* pData = new KSocketData();

	// check data right
	bool bRight = pEvent->CheckDataRight();
	if (bRight != false)
	{
		K_ERROR_QUIT("Event Check Data Right Error");
	}

	// type error
	int errcode = pEvent->Init(CiNetEvent::E_CINET_EVENT_CONNECT_NONE, pData);
	if (errcode != 1)
	{
		K_ERROR_QUIT("Event Init error: %d", errcode);
	}

	// socket empty
	errcode = pEvent->Init(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, NULL);
	if (errcode != 2)
	{
		K_ERROR_QUIT("Event Init error: %d", errcode);
	}

	// success
	errcode = pEvent->Init(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, pData);
	if (errcode != 0)
	{
		K_ERROR_QUIT("Event Init Error: %d", errcode);
	}

	// check data right
	bRight = pEvent->CheckDataRight();
	if (bRight != true)
	{
		K_ERROR_QUIT("Event Check Data Right Error");
	}

	// init twice
	errcode = pEvent->Init(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, pData);
	if (errcode != 3)
	{
		K_ERROR_QUIT("Event Init Error: %d", errcode);
	}

	delete pData;
	pEvent->DestroyEvent();
}

CiNetEventList ThreadList;
KExclusive PopNumLock;
int nPopNum;

void TestThreadFunc_AddTail(void* pData)
{
	CiNetEvent* pNewEvent = ThreadList.CreateEventObj(CiNetEvent::E_CINET_EVENT_DISCONNECT, (KSocketData*)(pData));
	ThreadList.AddTail(pNewEvent);
}

void TestThreadFunc_PopHeader(void* pData)
{
	CiNetEvent* pEvent = ThreadList.PopHeader();
	if (pEvent)
	{
		pEvent->DestroyEvent();
		
		PopNumLock.EnterExclusive();
		nPopNum--;
		std::cout << "destroy one:" << nPopNum << std::endl;
		PopNumLock.LeaveExclusive();
	}
	else
	{
		PopNumLock.EnterExclusive();
		std::cout << "empty one" << std::endl;
		PopNumLock.LeaveExclusive();
	}
}

void TestEventList()
{
	// test for single interface
	// CreateEvent
	CiNetEventList list;
	KSocketData* pData = new KSocketData();
	CiNetEvent* pEvent = list.CreateEventObj(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, NULL);
	if (pEvent != NULL)
	{
		K_ERROR_QUIT("Event List Create Event Error");
	}
	pEvent = list.CreateEventObj(CiNetEvent::E_CINET_EVENT_CONNECT_NONE, pData);
	if (pEvent != NULL)
	{
		K_ERROR_QUIT("Event List Create Event Error");
	}
	pEvent = list.CreateEventObj(CiNetEvent::E_CINET_EVENT_CONNECT_FAIL, pData);
	if (pEvent == NULL)
	{
		K_ERROR_QUIT("Event List Create Event Error");
	}

	// AddTail & IsEmpty
	CiNetEvent* pEvent2 = NULL;
	int errorcode = list.AddTail(pEvent2);
	if (errorcode != 1)
	{
		K_ERROR_QUIT("Event List Add Tail Error: %d", errorcode);
	}

	pEvent2 = new CiNetEvent();
	errorcode = list.AddTail(pEvent2);
	if (errorcode != 2)
	{
		K_ERROR_QUIT("Event List Add Tail Error: %d", errorcode);
	}
	pEvent2->DestroyEvent();

	bool bIsEmpty = list.IsEmpty();
	if (bIsEmpty != true)
	{
		K_ERROR_QUIT("Event List Is Empty Error");
	}

	errorcode = list.AddTail(pEvent);
	if (errorcode != 0)
	{
		K_ERROR_QUIT("Event List Add Tail Error: %d", errorcode);
	}

	bIsEmpty = list.IsEmpty();
	if (bIsEmpty != false)
	{
		K_ERROR_QUIT("Event List Is Empty Error");
	}

	CiNetEvent* pEvent3 = list.CreateEventObj(CiNetEvent::E_CINET_EVENT_CONNECT_SUCCESS, pData);
	errorcode = list.AddTail(pEvent3);
	if (errorcode != 0)
	{
		K_ERROR_QUIT("Event List Add Tail Error :%d", errorcode);
	}

	// test for Delete Modul
	CiNetEvent* pEvent4 = list.PopHeader();
	if (pEvent != pEvent4)
	{
		K_ERROR_QUIT("Event List Pop Header Error");
	}
	pEvent4->DestroyEvent();

	CiNetEvent* pEvent5 = list.PopHeader();
	if (pEvent3 != pEvent5)
	{
		K_ERROR_QUIT("Event List Pop Header Error");
	}
	pEvent5->DestroyEvent();

	CiNetEvent* pEvent6 = list.PopHeader();
	if (pEvent6 != NULL)
	{
		K_ERROR_QUIT("Event List Pop Header Error");
	}

	CiNetEvent* pEvent7 = list.CreateEventObj(CiNetEvent::E_CINET_EVENT_CONNECT_FAIL, pData);
	errorcode = list.AddTail(pEvent7);
	if (errorcode != 0)
	{
		K_ERROR_QUIT("Event List Add Tail Error");
	}

	CiNetEvent* pEvent8 = list.PopHeader();
	if (pEvent8 != pEvent7)
	{
		K_ERROR_QUIT("Event List Pop Header Error");
	}

	// test for threads
	int nSum = 50;
	nPopNum = nSum;
	KThread* pThreadList[50];
	for (int i = 0; i < nSum; i ++)
	{
		pThreadList[i] = new KThread();
		pThreadList[i]->Create(TestThreadFunc_AddTail, &pData);
	}

	KThread* pThreadList2[100];
	for (int i = 0; i < nSum * 2; i++)
	{
		pThreadList2[i] = new KThread();
		pThreadList2[i]->Create(TestThreadFunc_PopHeader, &pData);
	}

	KThread_Sleep(1000 * 3);

	if (nPopNum != 0)
	{
		K_ERROR_QUIT("Event List Threads Run Error, %d", 50 - nPopNum);
	}

	for (int i = 0; i < nSum; i++)
	{
		pThreadList[i]->Destroy();
		delete pThreadList[i];
	}

	for (int i = 0; i < nSum * 2; i++)
	{
		pThreadList2[i]->Destroy();
		delete pThreadList2[i];
	}
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
