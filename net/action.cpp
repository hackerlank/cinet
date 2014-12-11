#include "action.h"
#include "../base/include/error.h"
#include "../base/include/function.h"

CiNetAction::CiNetAction()
{
	m_Type = E_NET_ACTION_NONE;
	m_SocketData = NULL;
}

CiNetAction::~CiNetAction()
{

}

// success 0
// typeerror 1
// socketerror 2
// alreadyinit 3
int CiNetAction::Init(CiNetAction::E_CINET_ACTION_TYPE nType, KSocketData* pData)
{
	int nRet = 1;
	// check arge
	KF_PROCESS_ERROR(nType > E_NET_ACTION_NONE && nType <= E_NET_ACTION_SEND);

	nRet = 2;
	KF_PROCESS_ERROR(pData != NULL);

	// check this
	nRet = 3;
	KF_PROCESS_ERROR(m_Type == E_NET_ACTION_NONE && m_SocketData == NULL);

	m_Type = nType;
	m_SocketData = pData;

	nRet = 0;
ExitFailed:
	return nRet;
}

// success 0
int CiNetAction::Uninit()
{
	m_Type = E_NET_ACTION_NONE;
	m_SocketData = NULL;

	return 0;
}