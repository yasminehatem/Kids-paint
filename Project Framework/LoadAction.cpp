#include "LoadAction.h"
#include "ApplicationManager.h"

LoadAction::LoadAction(ApplicationManager *pApp):Action(pApp)
{
}
 
void LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Load Action: Enter file name");

	filename="";
	filename = pIn->GetSrting(pOut);

	pOut ->ClearStatusBar();
	pOut ->PrintMessage("Graph is being loaded..");

}

void LoadAction::Execute() 
{
	ReadActionParameters();
	pManager->Load(filename);
}
	