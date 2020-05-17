#include "AddLineAction.h"
#include "..\Figures\CLine.h"
#include "..\ApplicationManager.h"


AddLineAction::AddLineAction(ApplicationManager * pApp):Action(pApp)
{}

void AddLineAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click at first point");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Line: Click at second point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
	P1.x /= sqrt(UI.ZoomFactor);//Zoom factor default value = 1 if not zoomed
	P1.y /= sqrt(UI.ZoomFactor);
	P2.x /= sqrt(UI.ZoomFactor);
	P2.y /= sqrt(UI.ZoomFactor);
	
	LineGfxInfo.isFilled = false;	//default is not filled

	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.FillClr = pOut->getCrntFillColor();
	LineGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	LineGfxInfo.SborderClr = pOut -> getCrntBordClrString();
	LineGfxInfo.SfillClr = pOut -> getCrntFillClrString();

	pOut->ClearStatusBar();

}

//Execute the action
void AddLineAction::Execute() 
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a line with the parameters read from the user
	CFigure *L = new CLine(P1, P2,LineGfxInfo);

	//Check if the points clicked ar within the drawing area
	if(L->CheckForBound(P1,P2,P2)==true)
	{
		//Add the rectangle to the list of figures
		pManager->AddFigure(L);
	}
	else
	{
		pOut->PrintMessage("Can't draw line: Out of range!");
		L->decID_C();
		delete L;
	}
}
