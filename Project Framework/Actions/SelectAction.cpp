#include "SelectAction.h"
#include "..\ApplicationManager.h"


SelectAction::SelectAction(ApplicationManager *pApp):Action(pApp)
{
}


void SelectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Click the point you want to select");
	
	//Read point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->ClearStatusBar();

}

//Execute the action
void SelectAction::Execute() 
{
	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Search for the figure & check boundaries
	while(P1.y >= UI.ToolBarHeight && P1.y < UI.height - UI.StatusBarHeight)
	{
		CFigure* C = NULL;
		C = pManager -> GetFigure(P1.x, P1.y);
		if (C != NULL)
		{
			if (C->IsSelected())
				C->SetSelected(0);
			else
				C->SetSelected(1);
			pManager->UpdateInterface();
		}
		ReadActionParameters();
	}
}
