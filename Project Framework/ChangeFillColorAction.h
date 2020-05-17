#ifndef CHNGFILLCLR_ACTION_H
#define CHNGFILLCLR_ACTION_H
#include <string>

#include "Actions\Action.h"

class ChangeFillColorAction: public Action
{Point P1;
 color C; //Define color
 string clr; //the color defined as a string
public :
	ChangeFillColorAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif