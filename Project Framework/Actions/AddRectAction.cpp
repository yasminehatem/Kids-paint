#include "AddRectAction.h"
#include "..\Figures\CRectangle.h"

#include "..\ApplicationManager.h"


AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);
		P1.x /= sqrt(UI.ZoomFactor);
	P1.y /= sqrt(UI.ZoomFactor);
	P2.x /= sqrt(UI.ZoomFactor);
	P2.y /= sqrt(UI.ZoomFactor);


	RectGfxInfo.isFilled = false;	//default is not filled

	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	RectGfxInfo.SborderClr = pOut -> getCrntBordClrString();
	RectGfxInfo.SfillClr = pOut ->getCrntFillClrString();

	
	if(pManager -> getFillClrChanged() == false)  //if the fill clr is not changed in the application manager by the user
	{
		RectGfxInfo.isFilled = false;             // set is filled to false
	}

	else if (pManager -> ChangeFillColor(pOut->getCrntFillColor(),pOut ->getCrntFillClrString()) == true)    //else if the function changet fill color was used
	{
		RectGfxInfo.isFilled = true;                            //set is filled to be true       
	}

	pOut->ClearStatusBar();

}

//Execute the action
void AddRectAction::Execute() 
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CFigure *R=new CRectangle(P1, P2, RectGfxInfo);

	//Check if the points clicked ar within the drawing area
	if(R->CheckForBound(P1,P2,P2)==true)
	{
		//Add the rectangle to the list of figures
		pManager->AddFigure(R);
	}
	else
	{
		pOut->PrintMessage("Can't draw rectangle: Out of range!");
		R->decID_C();
		delete R;
	}
}
