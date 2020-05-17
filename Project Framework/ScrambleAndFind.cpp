#include "ScrambleAndFind.h"
#include "ApplicationManager.h"

ScrambleAndFind::ScrambleAndFind(ApplicationManager * pApp) :Action(pApp)
{
}

void ScrambleAndFind::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	pOut->PrintMessage("Now you will play Scramble and Find game");
	
}

void ScrambleAndFind::Execute()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	pOut->PrintMessage("Pick the similar shape..");
	pManager->ScrambleAndFindGame();
	pOut->ClearDrawArea();
	pOut->CreateDrawToolBar();
	pOut->ClearStatusBar();
	pManager->UpdateInterface();
}




