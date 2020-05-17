#include "CRectangle.h"
#include <fstream>

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	NewCorner1 = Corner1;
	NewCorner2 = Corner2;
	ID++;
}
	
void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(NewCorner1, NewCorner2, FigGfxInfo, Selected);  //draw new corners always in case not zoomed new corners = original
}

void CRectangle::DrawSF(Output* pOut) const
{
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

Point CRectangle::GetCenter()
{
	Point PCenter;
	PCenter.x = (Corner1.x + Corner2.x) / 2;
	PCenter.y = (Corner1.y + Corner2.y) / 2;
	return PCenter;

}
bool CRectangle::Move(int Xdiff, int Ydiff)
{
	Corner1.x += Xdiff;
	Corner2.x += Xdiff;
	Corner1.y += Ydiff;
	Corner2.y += Ydiff;
	Point p;
	p.x = 100;
	p.y = 100;
	if (CheckForBound(Corner1, Corner2, p))
		return true;
	else
	{
		Corner1.x -= Xdiff;
		Corner2.x -= Xdiff;
		Corner1.y -= Ydiff;
		Corner2.y -= Ydiff;
		return false;
	}
}

bool CRectangle::CheckCoordinates(int x, int y)
{
	Point Left = NewCorner1;
	Point Right = NewCorner2;
	if (Left.x > Right.x) { Left.x = Right.x; Right.x = Left.x; }
	if (Left.y > Right.y) { Left.y = Right.y; Right.y = Left.y; }

	return ((x >= Left.x) && (x <= Right.x) && (y >= Left.y) && (y <= Right.y));    // if the given x & y are within the corners of the rectangle
}

bool CRectangle::CheckCoordinates_SF(int x, int y)
{
	Point Left = Corner1;
	Point Right = Corner2;

	if (Left.x > Right.x) 
	{ 
		Left.x = Right.x; 
		Right.x = Left.x; 
	}

	if (Left.y > Right.y) 
	{ 
		Left.y = Right.y; 
		Right.y = Left.y; 
	}

	return ((x >= Left.x) && (x <= Right.x) && (y >= Left.y) && (y <= Right.y));    // if the given x & y are within the corners of the rectangle
}

void CRectangle::Resize(float R,float r)
{ 
	Point pcenter=GetCenter();
	Point pnew1;
	Point pnew2;
	if(R>1)//resize to bigger shape line equation
	{
		pnew1.x=((r*pcenter.x)-(R*Corner1.x))/(r-R);
		pnew1.y=((r*pcenter.y)-(R*Corner1.y))/(r-R);
		pnew2.x=((r*pcenter.x)-(R*Corner2.x))/(r-R);
		pnew2.y=((r*pcenter.y)-(R*Corner2.y))/(r-R);
	}
	else//resize to smaller shape line equation
	{
		pnew1.x=((r*pcenter.x)+(R*Corner1.x))/(r+R);
		pnew1.y=((r*pcenter.y)+(R*Corner1.y))/(r+R);
		pnew2.x=((r*pcenter.x)+(R*Corner2.x))/(r+R);
		pnew2.y=((r*pcenter.y)+(R*Corner2.y))/(r+R);
	}
	Point pnew3;
	pnew3.x=100;
	pnew3.y=100;
	if(CheckForBound(pnew1,pnew2,pnew3))
	{
		Corner1=pnew1;
		Corner2=pnew2;
	} 
}

void CRectangle::Zoom()
{
	//new corners=corners in case not zoomed because default zoom factor = 1
	NewCorner1.x=Corner1.x*sqrt(UI.ZoomFactor);
	NewCorner1.y= Corner1.y*sqrt(UI.ZoomFactor);
	NewCorner2.x= Corner2.x*sqrt(UI.ZoomFactor);
	NewCorner2.y= Corner2.y*sqrt(UI.ZoomFactor);
	
}

CFigure * CRectangle::Copy()
{
	CFigure*New = new CRectangle(NewCorner1, NewCorner2, FigGfxInfo);
	return New;
}

CFigure *CRectangle::Paste()
{
	/*CFigure *R = new CRectangle(NewCorner1, NewCorner2, FigGfxInfo);
	return R;*/
	CFigure *R = new CRectangle(Corner1, Corner2, FigGfxInfo);
	if(R!=NULL)
		return  R;
}


void CRectangle::Save(string filename)
{
	ofstream outfile(filename,std::ios::app);
	outfile<<"\n";
	outfile<<"Rectangle ";
	outfile <<ID<<" "<< Corner1.x << " " << Corner1.y << " "<< Corner2.x << " "<< Corner2.y << " " << FigGfxInfo.BorderWdth << " " << FigGfxInfo.SborderClr << " " << FigGfxInfo.isFilled << " " << FigGfxInfo.SfillClr;
	outfile.close();
}

bool CRectangle::CheckLine()
{
	return false;
}

void CRectangle:: DeleteFig(Output *pOut) const
{
	pOut->DeleteRect(Corner1,Corner2,FigGfxInfo);
}

string CRectangle:: returntype()const 
{
	return "Rectangle";	
}

int CRectangle:: getarea()
{
	int height;
	int width;
	if(Corner1.y>Corner2.y)
		height=Corner1.y-Corner2.y;
	else
		height=Corner2.y-Corner1.y;

	if (Corner1.x>Corner2.x)
		width	 =Corner1.x-Corner2.x;
	else
		width=  Corner2.x-Corner1.x;
	return height*width;
}

bool CRectangle::ChangePlace(int X,int Y)
{	 int DiffX=Corner2.x-Corner1.x;
     int DiffY=abs(Corner2.y-Corner1.y);
	 Point P1,P2;
    P1=Corner1;
    P2=Corner2;
	 Corner1.x=X;
	 Corner2.x=X+DiffX;
	 Corner2.y=	Y+DiffY;
	 Corner1.y=Y;
	 Point Corner3;
	Corner3.x=Corner3.y=100;
	if (CheckForBound(Corner1,Corner2,Corner3))
		return true;
	else
	{
		Corner1=P1;
		Corner2=P2;
		return false;
	}
 }

void CRectangle:: Shift(float r)
{	  
	int X;
	X=Corner1.x*r;
	Corner2.x=Corner2.x-abs(Corner1.x-X);
	Corner1.x=X;
}

void CRectangle::Rotate(int Angdegrees)
{
	Point p1;
	Point p2;
	Point p3;
	p3.x=100;
	p3.y=100;
	Point PCenter=GetCenter();
	p1=rotatebypoint(Corner1,PCenter,Angdegrees);//send original corner  to calculate on it and rotate it
	
	p2=rotatebypoint(Corner2,PCenter,Angdegrees);

	if(CheckForBound(p1,p2,p3))// check if obtained points points are in boundaries then rotate
	{	Corner1=p1;
	    Corner2=p2;
	} 
}
