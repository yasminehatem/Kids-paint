#ifndef LOAD_ACTION_H
#define LOAD_ACTION_H

#include "Actions\Action.h"

class LoadAction : public Action
{ Point P1;
  string filename;
public :
	LoadAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif