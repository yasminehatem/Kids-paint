#ifndef SELECT_ACTION_H
#define SELECT_ACTION_H

#include "Action.h"

//Select Action class
class SelectAction: public Action
{
private:
	Point P1;
public:
	SelectAction(ApplicationManager *pApp);

	//Reads Selecting parameters
	virtual void ReadActionParameters();
	
	//Return the selected figure from the ApplicationManager
	virtual void Execute() ;
};

#endif