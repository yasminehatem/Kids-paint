#include "ChangeBorderWidthAction.h"
#include "ApplicationManager.h"


ChangeBorderWidthAction::ChangeBorderWidthAction(ApplicationManager*pApp):Action(pApp)
{
}

void ChangeBorderWidthAction::ReadActionParameters()
{   
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y;
	pOut->CreateBorderWidthBar();
	pOut->PrintMessage("Change border width action: choose width (default is 3)");
	pIn->GetPointClicked(x, y);

	if(y>(1*UI.ToolBarHeight) && y<(2*UI.ToolBarHeight))
	{
		width=3;
		pOut->PrintMessage("Border Width: 3");
	}
	else if(y>(2*UI.ToolBarHeight)&& y<(3*UI.ToolBarHeight))
	{
		width=5;
		pOut->PrintMessage("Border Width: 5");
	}
	else if(y>(3*UI.ToolBarHeight)&& y<(4*UI.ToolBarHeight))
	{
		width=7;
		pOut->PrintMessage("Border Width: 7");
	}
	else if(y>(4*UI.ToolBarHeight)&& y<(5*UI.ToolBarHeight))
	{
		width=9;
		pOut->PrintMessage("Border Width: 9");
	}
	else if(y>(5*UI.ToolBarHeight)&& y<(6*UI.ToolBarHeight))
	{
		width=11;
		pOut->PrintMessage("Border Width: 11");
	}
	else
	{
		width=-1;                 //if the user clicks anywhere else set width to -1
	}
}

void ChangeBorderWidthAction::Execute()
{
	ReadActionParameters();
	if (width!=-1)                                     //don't call function change border width if width is -1
	{
		pManager->ChangeBorderWidth(width);
	}
}
