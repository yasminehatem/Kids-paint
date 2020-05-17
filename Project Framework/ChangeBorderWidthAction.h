#ifndef CHNGBRDWDTH_ACTION_H
#define CHNGBRDWDTH_ACTION_H

#include "Actions\Action.h"

class ChangeBorderWidthAction: public Action
{Point P1;
 int width; //Define width
public :
	ChangeBorderWidthAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif