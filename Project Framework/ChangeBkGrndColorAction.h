#ifndef CHNGBKGRNDCLR_ACTION_H
#define CHNGBKGRNDCLR_ACTION_H

#include "Actions\Action.h"

class ChangeBkGrndColorAction: public Action
{Point P1;
 color C; //Define color
 bool Check; //check if a color is chosen
 string clr;
public :
	ChangeBkGrndColorAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute() ;
};

#endif