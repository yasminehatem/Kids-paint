#ifndef DELETE_ACTION_H
#define DELETE_ACTION_H

#include "Actions\Action.h"

class DeleteAction : public Action
{Point P1;
public :
	DeleteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif