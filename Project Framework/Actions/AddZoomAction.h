#ifndef ZOOM_
#define ZOOM_
#include"Action.h"

class AddZoomAction:public Action
{
public:
	AddZoomAction(ApplicationManager*pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual void Execute();

	~AddZoomAction();
};



#endif