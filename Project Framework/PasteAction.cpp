#include "PasteAction.h"
#include "ApplicationManager.h"

PasteAction::PasteAction(ApplicationManager * pApp) :Action(pApp)
{
}

void PasteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Paste action: Click at Paste center");
	pIn->GetPointClicked(P1.x, P1.y);
	P1.x = P1.x / sqrt(UI.ZoomFactor);//Zoom factor default value = 1 if not zoomed
	P1.y = P1.y / sqrt(UI.ZoomFactor);

}

void PasteAction::Execute()
{
	Output* pOut = pManager->GetOutput();


	if (UI.ZoomFactor==1)
	{
		ReadActionParameters();
		if (UI.ToolBarHeight<P1.y && P1.y<UI.height-UI.StatusBarHeight && P1.x>0 && P1.x<UI.width)  //check if the point is inside drawing area
		{
			pManager->PasteAll(P1); //calling paste function in the app manager
		}
		else 
		{
			pOut->PrintMessage("Point is out of range!");
		}
	}
	else
	{
		pOut-> PrintMessage("Can't paste, Please zoom out 1st..");
	}
	

}
