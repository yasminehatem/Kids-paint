#pragma once
#include "Action.h"
class AddResizeAction : public Action
{
	float R;
public:
	AddResizeAction(ApplicationManager*pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	~AddResizeAction();
};

