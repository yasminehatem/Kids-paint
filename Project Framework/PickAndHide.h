#ifndef PICKANDHIDE_H
#define PICKANDHIDE_H

#include "Actions\Action.h"

class PickAndHide: public Action
{

private:
	Point P1;

public:
	PickAndHide(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};


#endif