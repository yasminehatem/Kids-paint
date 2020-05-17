#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#include "Actions\Action.h"

class SaveAction : public Action
{Point P1;
string filename;
public :
	SaveAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif