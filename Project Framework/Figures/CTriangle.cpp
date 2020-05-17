#include "CTriangle.h"
#include <fstream>


CTriangle::CTriangle(Point P1,Point P2,Point P3, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
	NewCorner1=Corner1;
	NewCorner2=Corner2;
	NewCorner3=Corner3;
	ID++;
}

 void CTriangle::Draw(Output* pOut) const
 {
	pOut->DrawTri(NewCorner1, NewCorner2, NewCorner3,FigGfxInfo, Selected);//draw new corners always in case not zoomed new corners = original

 }

 void CTriangle::DrawSF(Output* pOut) const
 {
	pOut->DrawTri(Corner1, Corner2, Corner3,FigGfxInfo, Selected);
 }

 Point CTriangle::GetCenter()
 {
	Point PCenter;
	PCenter.x=(Corner1.x+Corner2.x+Corner3.x)/3;
	PCenter.y=(Corner1.y+Corner2.y+Corner3.y)/3;
	return PCenter;
 }

bool CTriangle::Move(int Xdiff,int Ydiff)
{  
	Corner1.x+= Xdiff;
	Corner2.x+=Xdiff;
	Corner1.y+=Ydiff;
	Corner2.y+=Ydiff;
    Corner3.x+=Xdiff;
	Corner3.y+=Ydiff;

	if(CheckForBound(Corner1,Corner2,Corner3))
	{
		  return true;
	}
   else
   {
	   Corner1.x -= Xdiff;
	   Corner2.x -= Xdiff;
	   Corner1.y -= Ydiff;
	   Corner2.y -= Ydiff;
	   Corner3.x -= Xdiff;
	   Corner3.y -= Ydiff;
	   return false;
   }
}

float sign(Point p1, Point p2, Point p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool CTriangle::CheckCoordinates(int x, int y)
{
	bool b1, b2, b3;
	Point pt;
	pt.x = x; pt.y = y;
	b1 = sign(pt, NewCorner1, NewCorner2) < 0.0;
	b2 = sign(pt, NewCorner2, NewCorner3) < 0.0;
	b3 = sign(pt, NewCorner3, NewCorner1) < 0.0;

	return ((b1 == b2) && (b2 == b3));

}

bool CTriangle::CheckCoordinates_SF(int x, int y)
{
	bool b1, b2, b3;
	Point pt;
	pt.x = x; pt.y = y;
	b1 = sign(pt, Corner1, Corner2) < 0.0;
	b2 = sign(pt, Corner2, Corner3) < 0.0;
	b3 = sign(pt, Corner3, Corner1) < 0.0;

	return ((b1 == b2) && (b2 == b3));

}

void CTriangle::Resize(float R,float r)
{
	Point pcenter=GetCenter();
	Point pnew1;
		Point pnew2;
		Point pnew3;
	if(R>1) //resize to bigger shape line equations
	{
	
		pnew1.x=((r*pcenter.x)-(R*Corner1.x))/(r-R);
		pnew1.y=((r*pcenter.y)-(R*Corner1.y))/(r-R);
		pnew2.x=((r*pcenter.x)-(R*Corner2.x))/(r-R);
		pnew2.y=((r*pcenter.y)-(R*Corner2.y))/(r-R);
		pnew3.x=((r*pcenter.x)-(R*Corner3.x))/(r-R);
		pnew3.y=((r*pcenter.y)-(R*Corner3.y))/(r-R);
	}
	else //resize to smaller shape line equations
	{
		pnew1.x=((r*pcenter.x)+(R*Corner1.x))/(r+R);
		pnew1.y=((r*pcenter.y)+(R*Corner1.y))/(r+R);
		pnew2.x=((r*pcenter.x)+(R*Corner2.x))/(r+R);
		pnew2.y=((r*pcenter.y)+(R*Corner2.y))/(r+R);
		pnew3.x=((r*pcenter.x)+(R*Corner3.x))/(r+R);
		pnew3.y=((r*pcenter.y)+(R*Corner3.y))/(r+R);
	}
	if(CheckForBound(pnew1,pnew2,pnew3))
	{
	Corner1=pnew1;
	Corner2=pnew2;
	Corner3=pnew3;
	}
}
void CTriangle::Zoom()
{
	//new corners=corners in case not zoomed because default zoom factor =1
	NewCorner1.x=Corner1.x*sqrt(UI.ZoomFactor);  
	NewCorner1.y= Corner1.y*sqrt(UI.ZoomFactor);
	NewCorner2.x= Corner2.x*sqrt(UI.ZoomFactor);
	NewCorner2.y= Corner2.y*sqrt(UI.ZoomFactor);
	NewCorner3.x= Corner3.x*sqrt(UI.ZoomFactor);
	NewCorner3.y= Corner3.y*sqrt(UI.ZoomFactor);
	
}
CFigure * CTriangle::Copy()
{
	CFigure*New = new CTriangle(NewCorner1, NewCorner2,NewCorner3, FigGfxInfo);
	return New;
}

CFigure * CTriangle::Paste()
{
	CFigure *T = new CTriangle(NewCorner1, NewCorner2,NewCorner3, FigGfxInfo);
	return T;
}

void CTriangle::Save(string filename)
{
	ofstream outfile(filename,std::ios::app);
	outfile<<"\n";
	outfile<<"Triangle ";
	outfile <<ID<<" "<< Corner1.x << " " << Corner1.y << " "<< Corner2.x << " "<< Corner2.y << " "<< Corner3.x << " "<< Corner3.y << " " << FigGfxInfo.BorderWdth << " " << FigGfxInfo.SborderClr << " " << FigGfxInfo.isFilled << " " << FigGfxInfo.SfillClr;
	outfile.close();
}

bool CTriangle::CheckLine()
{
	return false;
}

void CTriangle:: DeleteFig(Output *pOut) const
{
	pOut->DeleteTri(Corner1,Corner2,Corner3,FigGfxInfo);

}

string CTriangle:: returntype()const 
{
	return "Triangle";	
}

int CTriangle:: getarea()
{
	int x1,x2,x3,y1,y2,y3;

	x1=Corner1.x;
	y1=Corner1.y;
	x2=Corner2.x;
	y2=Corner2.y;
	x3=Corner3.x;
	y3=Corner3.y;

	int area=abs(x1*(y2-y3)+x2*(y3-y1)+x3*(y1-y2));
	return area;
}

bool CTriangle::ChangePlace(int X,int Y)
{	  
	Point P1=Corner1;
    Point P2=Corner2;
    Point P3=Corner3;
	int diffX1=Corner2.x-Corner1.x;
    int diffY1=Corner2.y-Corner1.y;
	int diffX2=Corner3.x-Corner1.x;
    int diffY2=Corner3.y-Corner1.y;
    Corner1.x=X;
	Corner2.x=X+diffX1;
	Corner1.y=Y;
	Corner2.y=Y+diffY1;
	Corner3.x=X+diffX2;
	Corner3.y=Y+diffY2;
	if(CheckForBound(Corner1,Corner2,Corner3))
	   return true;
   else
   {
	   Corner1=P1;
	   Corner2=P2;
	   Corner3=P3;
	   return false;
   }   
}

void CTriangle::Shift(float r)
{
	int X;
	X=Corner1.x*r;
	Corner2.x=Corner2.x-(Corner1.x-X);
	Corner3.x=Corner3.x-(Corner1.x-X);
	Corner1.x=X;

}

void CTriangle::Rotate(int Angdegrees)
{
	Point p1;
	Point p2;
	Point p3;
	
	Point PCenter=GetCenter();
	p1 = rotatebypoint(Corner1,PCenter,Angdegrees);//send original corner  to calculate on it and rotate it
	
	p2 = rotatebypoint(Corner2,PCenter,Angdegrees);
	p3 = rotatebypoint(Corner3,PCenter,Angdegrees);

	if(CheckForBound(p1,p2,p3))// check if obtained points points are in boundaries then rotate
	{	Corner1=p1;
	    Corner2=p2;
		Corner3=p3;
	}
 
}

