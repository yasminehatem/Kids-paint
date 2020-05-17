#include "PickAndHide.h"
#include "ApplicationManager.h"

PickAndHide::PickAndHide(ApplicationManager * pApp) :Action(pApp)
{
}

void PickAndHide::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->CreatePandHToolBar();
	pOut->PrintMessage("Choose mode of playing..");
	
}

void PickAndHide::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	while(true)
	{
		pOut->PrintMessage("Point to the shape you want to play with..");
		pIn->GetPointClicked(P1.x, P1.y);
		ReadActionParameters();
		CFigure *Figure;
		Figure=pManager->GetFigure(P1.x,P1.y);
		if(Figure==NULL)
		{
			pOut->ClearStatusBar();
			pOut->CreatePlayToolBar();
			break;
		}

		Figure->DeleteFig(pOut);
		Figure->setchoosen(true);
		pManager->UpdateInterface_PM();
		pOut->PrintMessage("Choose mode of playing..") ;
		pIn->GetPointClicked(P1.x,P1.y);
		if(P1.y<50 && P1.x<65)
		{
			pOut->PrintMessage("You Choosed playing with type. Now pick some figures has the same type of the choosen one..");
			pManager->TypeMode(Figure);
		}
		else if(P1.y<50 && P1.x>60 && P1.x<120)
		{
			pOut->PrintMessage("You Choosed playing with Fill Color.Now pick some figures has the same Fill clr of the choosen one..");
			pManager->ColorMode(Figure);
		}
		else if (P1.y<50 && P1.x>120 && P1.x<180)
		{
			pOut->PrintMessage("You Choosed playing with Type and Fill Color. Now pick some figures has the same type and fill clr of the choosen one..");
			pManager->TypeAndColorMode(Figure);
		}
		else if (P1.y<50 && P1.x>180 && P1.x<240)
		{
			pOut->PrintMessage("You Choosed playing with Area. Now pick some figures has the same Area of the choosen one..");
			pManager->AreaMode(Figure);
		}
		else if (P1.y<50 && P1.x>240 && P1.x<300)
		{
			pOut->CreatePlayToolBar();
			pOut -> PrintMessage("Back to main play mode menu, choose mode of playing..");
			break;
		}

		pManager->ResetChoosen();
		pOut->ClearDrawArea();
		pManager->UpdateInterface_PM();
	}
}




