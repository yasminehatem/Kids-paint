#include "CutAction.h"
#include"ApplicationManager.h"

CutAction::CutAction(ApplicationManager * pApp) :Action(pApp)
{
}

void CutAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Cut action : The deleted figures were added to the clipboard ");
}

void CutAction::Execute()
{
		Output* pOut = pManager->GetOutput();

	if (UI.ZoomFactor!=1)
	{
		pOut-> PrintMessage("Can't cut, Please zoom out 1st..");
	}
	else
	{
		ReadActionParameters();
		pManager -> CutAll();
	}
}

