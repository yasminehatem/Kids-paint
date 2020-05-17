#ifndef CHNGBRDCLR_ACTION_H
#define CHNGBRDCLR_ACTION_H

#include "Actions\Action.h"

class ChangeBorderColorAction: public Action
{Point P1;
 color C; //Define color
 string clr; //the color defined as a string

public :
	ChangeBorderColorAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif