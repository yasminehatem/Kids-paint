#include "SaveAction.h"
#include "ApplicationManager.h"

SaveAction::SaveAction(ApplicationManager *pApp):Action(pApp)
{
}
 
void SaveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Save Action: Enter file name");

	filename="";
	filename = pIn->GetSrting(pOut);

	pOut->ClearStatusBar();
	pOut->PrintMessage("Graph Saved!");

}

void SaveAction::Execute() 
{
	ReadActionParameters();
	pManager->Save(filename);
}
	