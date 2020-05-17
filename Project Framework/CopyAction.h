#ifndef COPY_H
#define COPY_H

#include "Actions\Action.h"


class CopyAction :public Action
{
private:

public:
	CopyAction(ApplicationManager*pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
};

#endif
