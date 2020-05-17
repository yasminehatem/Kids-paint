#include "RotateAction.h"

#include "ApplicationManager.h"


RotateAction::RotateAction(ApplicationManager* pApp): Action(pApp)
{
	degree = 0;
}


void RotateAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y;
	pOut->DrawRotateBar(); 
	pOut->PrintMessage("Rotate action.. ");
	pIn->GetPointClicked(x, y);
	degree=90;
	
	if(y>(1*UI.ToolBarHeight)&& y<(2*UI.ToolBarHeight)) //check for clicked point clicked in desired ratio
	{
		degree=90;
		pOut->PrintMessage("rotate by 90 degree");
	}
	if(y>(2*UI.ToolBarHeight)&& y<(3*UI.ToolBarHeight))
	{
		degree=180;
		pOut->PrintMessage("Rotate by 180 degree");
	}
	if(y>(3*UI.ToolBarHeight)&& y<(4*UI.ToolBarHeight))
	{
		degree=270;
		pOut->PrintMessage("Rotate by 270 degree");
	}
}

void RotateAction::Execute()
{
	ReadActionParameters();
	pManager->RotateAll(degree);

}