#ifndef ADD_MOVE_ACTION_H
#define ADD_MOVE_ACTION_H

#include "Action.h"

class AddMoveAction : public Action
{Point P1;
public :
	AddMoveAction(ApplicationManager *pApp);
		virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif