#pragma once
#include "Actions\Action.h"
class RotateAction : public Action
{
	int degree;
public:
	RotateAction(ApplicationManager*pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

};


