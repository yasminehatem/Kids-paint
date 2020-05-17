#include "ChangeBkGrndColorAction.h"
#include "ApplicationManager.h"

ChangeBkGrndColorAction::ChangeBkGrndColorAction(ApplicationManager *pApp):Action(pApp)
{
}
 
void ChangeBkGrndColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y;
	pOut->CreateColorPalette();
	pOut->PrintMessage("Change background color action: Select the color you want(default is pale yellow)");
	pIn->GetPointClicked(x, y);

	if(y>(UI.ToolBarHeight) && y<(1.5 * UI.ToolBarHeight))  //if the point is in the 1st row
	{
		if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127))  //define the conditions for each color
		{
			C = WHITE;    //set color to white
			clr = "WHITE";
			pOut->PrintMessage("Color: White");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252))
		{
			C = GRAY;
			clr = "GRAY";
			pOut->PrintMessage("Color: Gray");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376))
		{
			C = BLACK;
			clr = "BLACK";
			pOut->PrintMessage("Color: Black");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498))
		{
			C = SADDLEBROWN;
			clr = "SADDLEBROWN";
			pOut->PrintMessage("Color: Brown");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622))
		{
			C = RED;
			clr = "RED";
			pOut->PrintMessage("Color: Red");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.7))
		{
			C = ORANGE;
			clr = "ORANGE";
			pOut->PrintMessage("Color: Orange");
			Check = true;
		}
	}

	else if(y>(1.5 * UI.ToolBarHeight)&& y<(2 * UI.ToolBarHeight))
	{
		if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127))
		{
			C = YELLOW;
			clr = "YELLOW";
			pOut->PrintMessage("Color: Yellow");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252))
		{
			C = LIGHTGOLDENRODYELLOW;
			clr = "LIGHTGOLDENRODYELLOW";
			pOut->PrintMessage("Color: Pale yellow");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376))
		{
			C = GREEN;
			clr = "GREEN";
			pOut->PrintMessage("Color: Green");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498))
		{
			C = TURQUOISE;
			clr = "TURQUOISE";
			pOut->PrintMessage("Color: Turquoise");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622))
		{
			C = SKYBLUE;
			clr = "SKYBLUE";
			pOut->PrintMessage("Color: Sky Blue");
			Check = true;
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.7))
		{
			C = BLUE;
			clr = "BLUE";
			pOut->PrintMessage("Color: Blue");
			Check = true;
		}
	}
	else 
	{
		Check = false;
	}
}

void ChangeBkGrndColorAction::Execute() 
{
	ReadActionParameters();
	if (Check != false)                //if check is not equal to false call the function to change background color
	{
		pManager->ChangeBkGrndColor(C,clr);
	}
}
