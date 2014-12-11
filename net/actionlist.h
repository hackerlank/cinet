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
	int CheckActionList();

	bool IsEmpty();

protected:
private:
	int takeAction(CiNetAction* pAction);

	KExclusive m_Lock;
	std::list<CiNetAction*> m_ActionList;
};

#endif // __actionlist_h__
