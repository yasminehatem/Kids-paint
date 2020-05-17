#include "DeleteAction.h"
#include "ApplicationManager.h"

DeleteAction::DeleteAction(ApplicationManager *pApp):Action(pApp)
{
}
 
void DeleteAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("Delete action: Selected figures will be deleted");
}
void DeleteAction::Execute() 
{
	ReadActionParameters();
	pManager->Delete();
}




	