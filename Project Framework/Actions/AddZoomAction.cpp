#include "AddZoomAction.h"
#include "..\ApplicationManager.h"

AddZoomAction::AddZoomAction(ApplicationManager*pApp):Action(pApp)
{
}

void AddZoomAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y;
	pOut->DrawZoomBar();
	pOut->PrintMessage("Choose zooming in or out..");
	pIn->GetPointClicked(x, y);

	if(y>(1*UI.ToolBarHeight)&& y<(2*UI.ToolBarHeight)) //check point clicked in zoom in icon in tool bar
	{
		UI.ZoomFactor = UI.ZoomFactor*2;
		pOut->PrintMessage("Zoom in");
	}
	if(y>(2*UI.ToolBarHeight)&& y<(3*UI.ToolBarHeight))   //check point clicked in zoom out icon in tool bar
	{
		UI.ZoomFactor = UI.ZoomFactor*0.5;
		pOut->PrintMessage("Zoom out");
		if (UI.ZoomFactor==1)       //condition added to check if we max zoom out was reached so normal tool bar is re-drawn
		{
			pOut->CreateDrawToolBar();
		}
	}
}
void AddZoomAction::Execute()
{
	ReadActionParameters();
	if (UI.ZoomFactor < 1)
	{
		UI.ZoomFactor = 1;
		return;
	}
	pManager->ZoomAll();   //call application manager to loop for figures
}

AddZoomAction::~AddZoomAction()
{
}