#include "AddTriAction.h"
#include "..\Figures\CTriangle.h"
#include "..\ApplicationManager.h"


AddTriAction::AddTriAction(ApplicationManager * pApp):Action(pApp)
{}

void AddTriAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first point");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Triangle: Click at second point");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	pOut->PrintMessage("New Triangle: Click at third point");

	//Read 2nd corner and store in point P3
	pIn->GetPointClicked(P3.x, P3.y);
	P1.x /= sqrt(UI.ZoomFactor);   //Zoom factor default value = 1 if not zoomed
	P1.y /= sqrt(UI.ZoomFactor);
	P2.x /= sqrt(UI.ZoomFactor);
	P2.y /= sqrt(UI.ZoomFactor);
	P3.x /= sqrt(UI.ZoomFactor);
	P3.y /= sqrt(UI.ZoomFactor);


	TriGfxInfo.isFilled = false;	//default is not filled
	
	//get drawing, filling colors and pen width from the interface
	TriGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriGfxInfo.FillClr = pOut->getCrntFillColor();
	TriGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	TriGfxInfo.SborderClr = pOut -> getCrntBordClrString();
	TriGfxInfo.SfillClr = pOut ->getCrntFillClrString();


	if(pManager -> getFillClrChanged() == false)  //if the fill clr is not changed in the application manager by the user
	{
		TriGfxInfo.isFilled = false;             // set is filled to false
	}

	else if (pManager -> ChangeFillColor(pOut->getCrntFillColor(),pOut->getCrntFillClrString()) == true)    //else if the function changet fill color was used
	{
		TriGfxInfo.isFilled = true;                            //set is filled to be true       
	}


	pOut->ClearStatusBar();

}

//Execute the action
void AddTriAction::Execute() 
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();
	
	//Create a line with the parameters read from the user
	CFigure *T=new CTriangle(P1, P2, P3,TriGfxInfo);

	//Check if the points clicked ar within the drawing area
	if(T->CheckForBound(P1,P2,P3)==true)
	{
		//Add the rectangle to the list of figures
		pManager->AddFigure(T);
	}
	else
	{
		pOut->PrintMessage("Can't draw triangle: Out of range!");
		T->decID_C();
		delete T;
	}
}
