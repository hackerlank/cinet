#include "eventlist.h"
#include "../base/include/error.h"
#include "../base/include/function.h"

CiNetEventList::CiNetEventList()
{
	init();
}

CiNetEventList::~CiNetEventList()
{
	uninit();
}

int CiNetEventList::init()
{
	// nothing to do

	// todo : 1. std::list have something do for init; 2. KExculsive for init
	return 0;
}

int CiNetEventList::uninit()
{
	// if anything in EventList, delete them
	clearList();

	return 0;
}

// success 0
// eventnull 1
// eventerror 2
int CiNetEventList::AddTail(CiNetEvent* pEvent)
{
	int nRet = 1;
	KF_PROCESS_ERROR(pEvent);

	nRet = 2;
	KF_PROCESS_ERROR(pEvent->CheckDataRight() == true);

	// lock
	m_Lock.EnterExclusive();

	// push it
	m_EventList.push_back(pEvent);

	// unlock
	m_Lock.LeaveExclusive();

	nRet = 0;
ExitFailed:
	return nRet;
}

CiNetEvent* CiNetEventList::PopHeader()
{
	CiNetEvent* pRet = NULL;
	bool bEmpty = false;

	// lock
	m_Lock.EnterExclusive();
	bEmpty = (m_EventList.empty() == true);
	if (!bEmpty)
	{
		pRet = m_EventList.front();
		// remove header
		m_EventList.pop_front();
	}
	// unlock
	m_Lock.LeaveExclusive();

ExitFailed:
	return pRet;
}

// success 0
int CiNetEventList::clearList()
{
	int nRet = 0;
	m_Lock.EnterExclusive();

	m_EventList.clear();

	m_Lock.LeaveExclusive();
	return nRet;
}

bool CiNetEventList::IsEmpty()
{
	bool bRet = false;
	m_Lock.EnterExclusive();

	bRet = m_EventList.empty();

	m_Lock.LeaveExclusive();
	return bRet;
}

CiNetEvent* CiNetEventList::CreateEventObj(CiNetEvent::E_CINET_EVENT_TYPE nType, KSocketData* pData)
{
	CiNetEvent* pRet = NULL;
	int errorcode = 0;

	pRet = new CiNetEvent();

	errorcode = pRet->Init(nType, pData);
	KF_PROCESS_ERROR(errorcode == 0);

ExitFailed:
	if (errorcode != 0 && pRet)
	{
		pRet->DestroyEvent();
		pRet = NULL;
	}
	return pRet;
}