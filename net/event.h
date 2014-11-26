#ifndef __CINET_EVENT_H__
#define __CINET_EVENT_H__

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
protected:
private:
	KSocketData *m_SocketData;
};
#endif // __CINET_EVENT_H__
