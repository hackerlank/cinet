#ifndef __SOCKET_DATA_H__
#define __SOCKET_DATA_H__

#include "../base/include/commondefine.h"

// 双全工 handle
// 记录本地的 ip port
// 记录远程的 ip port
class KSocketData {
public:
	KSocketData();
	~KSocketData();

private:
	unsigned int	m_hSocketHandle;
	DWORD			m_nLocalIP;
	int				m_nLocalPort;
	DWORD			m_nRemoteIP;
	int				m_nRemotePort;
}

#endif
