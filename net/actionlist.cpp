#include "actionlist.h"
#include "../base/include/error.h"
#include "../base/include/function.h"

CiNetActionList::CiNetActionList()
{

}

CiNetActionList::~CiNetActionList()
{

}

// success 0
int CiNetActionList::AddAction(CiNetAction::E_CINET_ACTION_TYPE nType, KSocketData* pData)
{
	int nRet = 1;

	// check arg
	// new
	CiNetAction* pNewAction = new CiNetAction();
	nRet = pNewAction->Init(nType, pData);
	KF_PROCESS_ERROR(nRet == 0);

	// lock & add
	m_Lock.EnterExclusive();
	m_ActionList.push_back(pNewAction);
	m_Lock.LeaveExclusive();

	nRet = 0;
ExitFailed:
	if (nRet != 0 && pNewAction)
	{
		delete pNewAction;
	}
	return nRet;
}

int CiNetActionList::CheckActionList()
{
	int nRet = 1;

	// while (lock & pop & delete)
	int bBreak = false;
	while (!bBreak)
	{
		m_Lock.EnterExclusive();
		if (m_ActionList.empty() == false)
		{
			CiNetAction* pAction = m_ActionList.front();
			nRet = takeAction(pAction);
			m_ActionList.pop_front();

			delete pAction;
		}
		else
		{
			bBreak = true;
		}
		m_Lock.LeaveExclusive();

		KF_PROCESS_ERROR(nRet == 0);
	}

	nRet = 0;
ExitFailed:
	return nRet;
}

bool CiNetActionList::IsEmpty()
{
	bool bRet = false;
	m_Lock.EnterExclusive();
	bRet = m_ActionList.empty();
	m_Lock.LeaveExclusive();

	return bRet;
}

int CiNetActionList::takeAction(CiNetAction* pAction)
{
	int nRet = 1;

	// check arg
	KF_PROCESS_ERROR(pAction != NULL); // todo : check the value of action

	nRet = 0;
ExitFailed:
	return nRet;
}