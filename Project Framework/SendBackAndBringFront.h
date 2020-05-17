#pragma once
#include "Actions\Action.h"
class SendBackAndBringFrontAction : public Action
{

public:
	SendBackAndBringFrontAction(ApplicationManager*pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

};


