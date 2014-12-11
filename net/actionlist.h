#ifndef __ACTIONLIST_H__
#define __ACTIONLIST_H__

#include "action.h"
#include "../thread/exclusive.h"
#include <list>

class CiNetActionList
{
public:
	CiNetActionList();
	~CiNetActionList();

	int AddAction(CiNetAction::E_CINET_ACTION_TYPE nType, KSocketData* pData);
	int CheckAction();

protected:
private:

	KExclusive m_Lock;
	std::list<CiNetAction*> m_ActionList;
};

#endif // __actionlist_h__
