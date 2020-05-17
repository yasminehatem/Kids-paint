#include "AddCircAction.h"
#include "..\Figures\CCircle.h"
#include "..\ApplicationManager.h"


AddCircAction::AddCircAction(ApplicationManager * pApp):Action(pApp)
{}

void AddCircAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at first point");
	
	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Circle: Click at second point");

	pIn->GetPointClicked(P2.x, P2.y);
	P1.x /= sqrt(UI.ZoomFactor);//Zoom factor default value = 1 if not zoomed
	P1.y /= sqrt(UI.ZoomFactor);
	P2.x /= sqrt(UI.ZoomFactor);
	P2.y /= sqrt(UI.ZoomFactor);

	
	CircGfxInfo.isFilled = false;	//default is not filled
	

	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
    CircGfxInfo.FillClr = pOut->getCrntFillColor();
	CircGfxInfo.BorderWdth = pOut->getCrntPenWidth();
	CircGfxInfo.SborderClr = pOut -> getCrntBordClrString();
	CircGfxInfo.SfillClr = pOut ->getCrntFillClrString();
	if(pManager -> getFillClrChanged() == false)  //if the fill clr is not changed in the application manager by the user
	{
		CircGfxInfo.isFilled = false;             // set is filled to false
	}

	else if (pManager -> ChangeFillColor(pOut->getCrntFillColor(),pOut->getCrntFillClrString()) == true)    //else if the function changet fill color was used
	{
		CircGfxInfo.isFilled = true;                            //set is filled to be true       

	}

	pOut->ClearStatusBar();

}

//Execute the action
void AddCircAction::Execute() 
{
	//Get a Pointer to the Output Interface
	Output* pOut = pManager->GetOutput();

	//This action needs to read some parameters first
	ReadActionParameters();

	radius = sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2));
	
	//Create a line with the parameters read from the user
	CFigure *C = new CCircle(P1, radius,CircGfxInfo);
	Point X;
	X.x=P1.x - radius;
	X.y=P1.y - radius ;
	Point Y;
	Y.x=P1.x + radius;
	Y.y=P1.y + radius;
	Point Z;
	Z.x=100;
	Z.y=100;


	if (C->CheckForBound(X,Y,Z))
		{
			//Add the Circle to the list of figures
			pManager->AddFigure(C);
		}
	else
		{
			pOut->PrintMessage("Can't draw circle: Out of range!");
			C->decID_C();
			delete C;
		}
}
