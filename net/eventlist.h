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

	int Init();

	int AddTail();
	CiNetEvent* RemoveHeader();

protected:
private:
	std::list<CiNetEvent*> m_EventList;
	KExclusive m_Lock;
};

#endif // __eventlist_h__
