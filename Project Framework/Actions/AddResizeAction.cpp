#include "AddResizeAction.h"
#include "..\ApplicationManager.h"


AddResizeAction::AddResizeAction(ApplicationManager*pApp):Action(pApp)
{
}

void AddResizeAction::ReadActionParameters()
{   
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y;
	pOut->DrawResizeBar();
	pOut->PrintMessage("Choose the ratio to resize");
	pIn->GetPointClicked(x, y);
	
	if(y>(1*UI.ToolBarHeight)&& y<(2*UI.ToolBarHeight)) //check for clicked point clicked in desired ratio
	{
		R=0.25;
			pOut->PrintMessage("Resize by 1/4");
	}
	if(y>(2*UI.ToolBarHeight)&& y<(3*UI.ToolBarHeight))
	{
		R=0.5;
			pOut->PrintMessage("Resize by 1/2");
	}
	if(y>(3*UI.ToolBarHeight)&& y<(4*UI.ToolBarHeight))
	{
		R=2;
			pOut->PrintMessage("Resize by 2");
	}
	if(y>(4*UI.ToolBarHeight)&& y<(5*UI.ToolBarHeight))
	{
		R=4;
			pOut->PrintMessage("resize by 4");
	}
}

void AddResizeAction::Execute()
{
	ReadActionParameters();
	pManager->ResizeAll(R); //call application manager to loop for figures
}

AddResizeAction::~AddResizeAction()
{
}
