#include "CFigure.h"
int CFigure::ID_C = 0; //virtual ID

CFigure::CFigure(GfxInfo FigureGfxInfo):ID(ID_C++)
{ 
	FigGfxInfo.SborderClr = "BLUE"; //default border color
	FigGfxInfo.SfillClr = "GREEN"; //default fill color
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	choosen=false;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngBrdWdth(int width)
{
	FigGfxInfo.BorderWdth = width;
}

bool CFigure::CheckForBound(Point p1,Point p2,Point p3)
{
	return(UI.ToolBarHeight<p1.y&&p1.y<UI.height-UI.StatusBarHeight &&UI.ToolBarHeight<p2.y&&p2.y<UI.height-UI.StatusBarHeight &&UI.ToolBarHeight<p3.y&&p3.y<UI.height-UI.StatusBarHeight       
		&&p1.x>0&&p1.x<UI.width&&p2.x>0&&p2.x<UI.width&&p3.x>0&&p3.x<UI.width);
}

int CFigure::getID()
{
	return ID;
}


void CFigure::setFillClr(string fillC)
{
	FigGfxInfo.SfillClr = fillC;
}

void CFigure::setBorderClr(string BordC)
{
	FigGfxInfo.SborderClr = BordC;
}

void CFigure::decID_C()
{	
	if(ID_C>0)
	{
		ID_C--; 
	}
}

void CFigure::setID(int rID)
{
	ID = rID;
}

void CFigure::setID_C(int totalCount)
{
	ID_C = totalCount;
}

void CFigure::setchoosen(bool B)
{
	choosen=B;
}
bool CFigure:: ischoosen()
{
	return choosen;
}

bool CFigure::CompareFilled(CFigure*Pointed) const
{
	if (FigGfxInfo.isFilled==false)
	{
		if (Pointed->FigGfxInfo.isFilled==false)
			return true;
	}
	else
	{
		if (Pointed->FigGfxInfo.isFilled==false)
			return false ;
		if(FigGfxInfo.FillClr.ucBlue==Pointed->FigGfxInfo.FillClr.ucBlue && FigGfxInfo.FillClr.ucGreen==Pointed->FigGfxInfo.FillClr.ucGreen && FigGfxInfo.FillClr.ucRed==Pointed->FigGfxInfo.FillClr.ucRed )
			return true;
	}
	return false;
}

Point CFigure::rotatebypoint(Point rotatedpoint, Point Center, int Angdegrees)
{
	rotatedpoint.x -= Center.x;
	rotatedpoint.y -= Center.y;
	if (Angdegrees == 270)
	{
		int p = rotatedpoint.x;
		rotatedpoint.x = -rotatedpoint.y;
		rotatedpoint.y = p;
	}
	else if (Angdegrees == 90)
	{
		int p = rotatedpoint.x;
		rotatedpoint.x = rotatedpoint.y;
		rotatedpoint.y = -p;
	}
	else
	{
		rotatedpoint.x = -rotatedpoint.x;
		rotatedpoint.y = -rotatedpoint.y;
	}
	rotatedpoint.x += Center.x;
	rotatedpoint.y += Center.y;

	return rotatedpoint;
}
