#include "event.h"

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
	// check arg
	if (nType <= CiNetEvent::E_CINET_EVENT_CONNECT_NONE || nType > CiNetEvent::E_CINET_EVENT_MESSAGE)
	{
		return 1;
	}

	if (pData == NULL)
	{
		return 2;
	}

	// check self
	if (m_Type != CiNetEvent::E_CINET_EVENT_CONNECT_NONE || m_SocketData != NULL)
	{
		return 3;
	}

	// set value
	m_Type = nType;
	m_SocketData = pData;

	return 0;
}

// success 0
int CiNetEvent::Uninit()
{
	m_Type = CiNetEvent::E_CINET_EVENT_CONNECT_NONE;
	m_SocketData = NULL;
	
	return 0;
}