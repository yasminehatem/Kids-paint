  #ifndef	SCRAMBLEANDFIND_H
#define SCRAMBLEANDFIND_H


#include "Actions\Action.h"


class ScrambleAndFind: public Action
{

private:
	Point P1;

public:
	ScrambleAndFind(ApplicationManager *pApp);
	virtual void ReadActionParameters();
	virtual void Execute();

};

#endif