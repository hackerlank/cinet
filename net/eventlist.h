#ifndef __EVENTLIST_H__
#define __EVENTLIST_H__

#include "event.h"
#include "../thread/exclusive.h"
#include <list>

class CiNetEventList
{
public:
	CiNetEventList();
	~CiNetEventList();

	CiNetEvent* CreateEventObj(CiNetEvent::E_CINET_EVENT_TYPE nType, KSocketData* pData);

	int AddTail(CiNetEvent* pEvent);
	CiNetEvent* PopHeader();

	bool IsEmpty();

protected:
private:
	int init();
	int uninit();

	int clearList();

	std::list<CiNetEvent*> m_EventList;
	KExclusive m_Lock;
};

#endif // __eventlist_h__
