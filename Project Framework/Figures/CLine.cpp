#include "CLine.h"
#include <fstream>

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Corner1 = P1;
	Corner2 = P2;
	NewCorner1 = Corner1;
	NewCorner2 = Corner2;
	ID++;
}

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawLine(NewCorner1, NewCorner2, FigGfxInfo, Selected);//draw new corners always in case not zoomed new corners = original
}

void CLine::DrawSF(Output* pOut) const
{
	pOut->DrawLine(Corner1, Corner2, FigGfxInfo, Selected);
}

Point CLine::GetCenter() 
{
	Point PCenter;
	PCenter.x=(Corner1.x+Corner2.x)/2;
	PCenter.y=(Corner1.y+Corner2.y)/2;
	return PCenter;
}

bool CLine::Move(int Xdiff,int Ydiff)
{  
	Corner1.x+= Xdiff;
    Corner2.x+=Xdiff;
    Corner1.y+=Ydiff;
    Corner2.y+=Ydiff;
    Point p;
    p.x=100;
    p.y=100;
    if(CheckForBound(Corner1,Corner2,p))
	{
		return true;
	}
   else
   {
	    Corner1.x-= Xdiff;
		Corner2.x-=Xdiff;
		Corner1.y-=Ydiff;
		Corner2.y-=Ydiff;
		return false;
   }
}

bool CLine::CheckCoordinates(int x, int y)
{
	float m = float(NewCorner2.y - NewCorner1.y) / (NewCorner2.x - NewCorner1.x);

	float c= NewCorner1.y - m * NewCorner1.x;

	float c1=NewCorner1.y +1 -m * NewCorner1.x +1;   //check if the line satfies the equation of the line above it

	float c2=NewCorner1.y -1 -m * NewCorner1.x -1;   //check if the line satfies the equation of the line below it

	float c3=Corner1.y +2 -m * Corner1.x +2;

	float c4=Corner1.y -2 -m * Corner1.x -2;

	return ((int)(m*x + c) == y||(int)(m*x + c1) == y||(int)(m*x + c2) == y||(int)(m*x + c3) == y||(int)(m*x + c4) == y);    // if the point given satisfies the equation of the line

}

bool CLine::CheckCoordinates_SF(int x, int y)
{
	float m = float(Corner2.y - Corner1.y) / (Corner2.x - Corner1.x);

	float c= Corner1.y - m * Corner1.x;

	float c1=Corner1.y +1 -m * Corner1.x +1;   //check if the line satfies the equation of the line above it

	float c2=Corner1.y -1 -m * Corner1.x -1;   //check if the line satfies the equation of the line below it

	float c3=Corner1.y +2 -m * Corner1.x +2;

	float c4=Corner1.y -2 -m * Corner1.x -2;

	float c5=Corner1.y +3 -m * Corner1.x +3;

	float c6=Corner1.y -3 -m * Corner1.x -3;

	float c7=Corner1.y +4 -m * Corner1.x +4;

	float c8=Corner1.y -4 -m * Corner1.x -4;

	return ((int)(m*x + c) == y||(int)(m*x + c1) == y||(int)(m*x + c2) == y ||(int)(m*x + c3) == y||(int)(m*x + c4) == y||(int)(m*x + c5) == y||(int)(m*x + c6) == y||(int)(m*x + c7) == y||(int)(m*x + c8) == y);    // if the point given satisfies the equation of the line

}

void CLine::Resize(float R,float r)
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

void CLine::Zoom()
{
	//new corners=corners in case not zoomed because default zoom factor =1
	NewCorner1.x=Corner1.x*sqrt(UI.ZoomFactor);
	NewCorner1.y= Corner1.y*sqrt(UI.ZoomFactor);
	NewCorner2.x= Corner2.x*sqrt(UI.ZoomFactor);
	NewCorner2.y= Corner2.y*sqrt(UI.ZoomFactor);
	
}	

CFigure * CLine::Copy()
{
	CFigure*New = new CLine(Corner1, Corner2, FigGfxInfo);
	return New;
}

CFigure * CLine::Paste()
{
	/*CFigure *L = new CLine(NewCorner1, NewCorner2, FigGfxInfo);
	return L;*/
	CFigure *L = new CLine(Corner1, Corner2, FigGfxInfo);
	if(L!=NULL)
		return L;

}


void CLine::Save(string filename)
{
	ofstream outfile(filename,std::ios::app);
	outfile<<"\n";
	outfile<<"Line ";
	outfile <<ID<<" "<< Corner1.x << " " << Corner1.y << " "<< Corner2.x << " "<< Corner2.y << " " << FigGfxInfo.BorderWdth << " " << FigGfxInfo.SborderClr << " " << FigGfxInfo.isFilled << " " << FigGfxInfo.SfillClr;
	outfile.close();
}

bool CLine::CheckLine()
{
	return true;
}

int CLine:: getarea()
{
	return((Corner2.x-Corner1.x)+(Corner1.y-Corner2.y));
}

void CLine::DeleteFig(Output *pOut) const
{
	pOut->DeleteLine(Corner1, Corner2, FigGfxInfo); 
}

string CLine:: returntype()const 
{
	return "Line";	
}

bool CLine::ChangePlace(int X,int Y)
   { 
	 int DiffX=abs(Corner2.x-Corner1.x);
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
 void CLine:: Shift(float r)
 {
		int X;
	    X=Corner1.x*r;
		Corner2.x=Corner2.x-(Corner1.x-X);
		Corner1.x=X;
 }

 void CLine::Rotate(int Angdegrees)
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
		{
			Corner1=p1;
	    Corner2=p2;
	}
 
}
