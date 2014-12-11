#include "event.h"
#include "../base/include/error.h"
#include "../base/include/function.h"

CiNetEvent::CiNetEvent()
{
	Uninit();
}

CiNetEvent::~CiNetEvent()
{
	
}

// success 0
// typeerror 1
// socketdataerror 2
// alreadyinit 3
int CiNetEvent::Init(CiNetEvent::E_CINET_EVENT_TYPE nType, KSocketData* pData)
{
	int nRet = 1;
	// check arg
	KF_PROCESS_ERROR(nType > CiNetEvent::E_CINET_EVENT_CONNECT_NONE && nType <= CiNetEvent::E_CINET_EVENT_MESSAGE);

	nRet = 2;
	KF_PROCESS_ERROR(pData != NULL);

	// check self
	nRet = 3;
	KF_PROCESS_ERROR(m_Type == CiNetEvent::E_CINET_EVENT_CONNECT_NONE && m_SocketData == NULL);

	// set value
	m_Type = nType;
	m_SocketData = pData;

	nRet = 0;
ExitFailed:
	return nRet;
}

// success 0
int CiNetEvent::Uninit()
{
	m_Type = CiNetEvent::E_CINET_EVENT_CONNECT_NONE;
	m_SocketData = NULL;
	
	return 0;
}

// success 0
int CiNetEvent::DestroyEvent()
{
	delete this;
	return 0;
}

bool CiNetEvent::CheckDataRight()
{
	if (m_Type <= CiNetEvent::E_CINET_EVENT_CONNECT_NONE || m_Type > CiNetEvent::E_CINET_EVENT_MESSAGE || m_SocketData == NULL)
	{
		return false;
	}

	return true;
}