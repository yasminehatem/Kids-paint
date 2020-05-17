#include "SendBackAndBringFront.h"

#include "ApplicationManager.h"

SendBackAndBringFrontAction::SendBackAndBringFrontAction(ApplicationManager* pApp): Action(pApp)
{
	
}

void SendBackAndBringFrontAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y; 
	pOut->PrintMessage("Send to back / Bring to front actions..");
	pIn->GetPointClicked(x,y);
}

void SendBackAndBringFrontAction::Execute()
{
	ReadActionParameters();
	pManager->BackFrontSwap();
}