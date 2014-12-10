#include "eventlist.h"

CiNetEventList::CiNetEventList()
{
	init();
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
int CiNetEventList::AddTail(CiNetEvent* pEvent)
{
	int nRet = 1;
	KF_PROCESS_ERROR(pEvent);

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

CiNetEvent* CiNetEventList::RemoveHeader()
{
	CiNetEvent* pRet = NULL;

	// lock
	m_Lock.EnterExclusive();

	KF_PROCESS_ERROR(m_EventList.empty() == false);

	pRet = m_EventList.front();
	// remove header
	m_EventList.pop_front();

	// unlock
	m_Lock.LeaveExclusive();

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