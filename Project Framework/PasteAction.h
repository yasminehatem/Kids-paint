#ifndef PASTE_H
#define PASTE_H


#include "Actions\Action.h"


class PasteAction : public Action
{

private:
	Point P1; //class has only one member which is the paste centre

public:
	PasteAction(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif

