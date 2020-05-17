#include "AddMoveAction.h"
#include "..\ApplicationManager.h"

AddMoveAction::AddMoveAction(ApplicationManager *pApp):Action(pApp)
{
}
 
void AddMoveAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Move action: Click at Move  corner");
	pIn->GetPointClicked(P1.x, P1.y);
	P1.x = P1.x / sqrt(UI.ZoomFactor);//Zoom factor default value = 1 if not zoomed
	P1.y = P1.y / sqrt(UI.ZoomFactor);
}
void AddMoveAction::Execute() 
{
	ReadActionParameters();
	pManager->MoveAll(P1); //call application manager to loop for figures
}




	