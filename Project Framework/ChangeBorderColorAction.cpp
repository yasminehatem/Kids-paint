#include "ChangeBorderColorAction.h"
#include "ApplicationManager.h"

ChangeBorderColorAction::ChangeBorderColorAction(ApplicationManager *pApp):Action(pApp)
{
}
 
void ChangeBorderColorAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	int x, y;
	pOut->CreateColorPalette();
	pOut->PrintMessage("Change border color action: Select the color you want");
	pIn->GetPointClicked(x, y);

	if(y>(UI.ToolBarHeight) && y<(1.5 * UI.ToolBarHeight))  //if the point is in the 1st row
	{
		if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127))  //define the conditions for each color
		{
			C = WHITE;    //set color to white
			clr="WHITE";
			pOut->PrintMessage("Color: White");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252))
		{
			C = GRAY;
			clr="GRAY";
			pOut->PrintMessage("Color: Gray");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376))
		{
			C = BLACK;
			clr="BLACK";
			pOut->PrintMessage("Color: Black");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498))
		{
			C = SADDLEBROWN;
			clr="SADDLEBROWN";
			pOut->PrintMessage("Color: Brown");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622))
		{
			C = RED;
			clr="RED";
			pOut->PrintMessage("Color: Red");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.7))
		{
			C = ORANGE;
			clr="ORANGE";
			pOut->PrintMessage("Color: Orange");
		}
	}

	else if(y>(1.5 * UI.ToolBarHeight)&& y<(2 * UI.ToolBarHeight))
	{
		if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127))
		{
			C = YELLOW;
			clr="YELLOW";
			pOut->PrintMessage("Color: Yellow");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.127) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252))
		{
			C = LIGHTGOLDENRODYELLOW;
			clr="LIGHTGOLDENRODYELLOW";
			pOut->PrintMessage("Color: Pale yellow");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.252) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376))
		{
			C = GREEN;
			clr="GREEN";
			pOut->PrintMessage("Color: Green");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.376) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498))
		{
			C = TURQUOISE;
			clr="TURQUOISE";
			pOut->PrintMessage("Color: Turquoise");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth   *1.498) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622))
		{
			C = SKYBLUE;
			clr="SKYBLUE";
			pOut->PrintMessage("Color: Sky Blue");
		}
		else if (x>(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.622) && x<(ITM_CHNGBK_CLR*UI.MenuItemWidth *1.7))
		{
			C = BLUE;
			clr="BLUE";
			pOut->PrintMessage("Color: Blue");
		}
	}
	else
	{
		clr="!";
	}

}

void ChangeBorderColorAction::Execute() 
{
	ReadActionParameters();
	if (clr != "!")
	{
		pManager->ChangeBorderColor(C,clr);   //call function change border color in the App Manager
	}
}




	