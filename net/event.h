#ifndef __CINET_EVENT_H__
#define __CINET_EVENT_H__

#include <stdio.h>
#include "socketdata.h"

class CiNetEvent
{
public:
	enum E_CINET_EVENT_TYPE {
		E_CINET_EVENT_CONNECT_NONE = 1,
		E_CINET_EVENT_CONNECT_SUCCESS,
		E_CINET_EVENT_CONNECT_FAIL,
		E_CINET_EVENT_DISCONNECT,
		E_CINET_EVENT_LISTEN_SUCCESS,
		E_CINET_EVENT_LISTEN_FAIL,
		E_CINET_EVENT_SEND_SUCCESS,
		E_CINET_EVENT_SEND_FAIL,
		E_CINET_EVENT_MESSAGE,	// 得到消息
	};

	CiNetEvent();
	~CiNetEvent();

	// success 0
	// typeerror 1
	// socketdataerror 2
	// alreadyinit 3
	int Init(CiNetEvent::E_CINET_EVENT_TYPE nType, KSocketData* pData);

	// success 0
	int Uninit();

protected:
private:
	CiNetEvent::E_CINET_EVENT_TYPE m_Type;
	KSocketData *m_SocketData;
};
#endif // __CINET_EVENT_H__
