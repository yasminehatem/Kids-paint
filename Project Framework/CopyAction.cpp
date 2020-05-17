#include "CopyAction.h"

#include "ApplicationManager.h"

CopyAction::CopyAction(ApplicationManager * pApp) : Action(pApp)
{
}

void CopyAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Copy action : The selected figures were added to the clipboard");

}

void CopyAction::Execute()
{
	Output* pOut = pManager->GetOutput();

	if (UI.ZoomFactor!=1)
	{
		pOut-> PrintMessage("Can't copy, Please zoom out 1st..");
	}
	else
	{
		ReadActionParameters();
		pManager->CopyAll(); //calling function in the App manager to copy figures
	}
}

