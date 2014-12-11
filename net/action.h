#ifndef __CINET_ACTION_H__
#define __CINET_ACTION_H__

#include <stdio.h>
#include "socketdata.h"

class CiNetAction
{
public:
	enum E_CINET_ACTION_TYPE {
		E_NET_ACTION_NONE = 1,
		E_NET_ACTION_CONNECT,
		E_NET_ACTION_DISCONNECT,
		E_NET_ACTION_LISTEN,
		E_NET_ACTION_STOPLISTEN,
		E_NET_ACTION_SEND,
	};
	CiNetAction();
	~CiNetAction();

	int Init(CiNetAction::E_CINET_ACTION_TYPE nType, KSocketData* pData);
	int Uninit();

protected:
private:
	CiNetAction::E_CINET_ACTION_TYPE m_Type;
	KSocketData *m_SocketData;
};

#endif