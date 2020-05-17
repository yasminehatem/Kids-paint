#include"CCircle.h"

CCircle::CCircle(Point P1,double R, GfxInfo FigureGfxInfo):CFigure(FigureGfxInfo)
{
	Center = P1;
	Radius = R;
	NewCenter=Center;
	NewRadius=Radius;
	ID++;
}
	
void CCircle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawCirc(NewCenter, NewRadius, FigGfxInfo, Selected);//draw new corners always in case not zoomed new corners = original
}

void CCircle::DrawSF(Output* pOut) const
{
	pOut->DrawCirc(Center, Radius, FigGfxInfo, Selected);

}

Point CCircle::GetCenter() 
{ return Center; }

bool CCircle::Move(int Xdiff,int Ydiff)
{
	Center.x+= Xdiff;
	Center.y+=Ydiff;
	Point p1, p2;
	p1.x = Center.x + Radius;
	p1.y = Center.y + Radius;
	p2.x = Center.x - Radius;
	p2.y = Center.y - Radius;
	Point p;
	p.x = 100;
	p.y = 100;

    if(CheckForBound(p1,p2,p))
	{
		return true;
    }
	else
	{
		Center.x-= Xdiff;
		Center.y-=Ydiff;
		return false;
	}

}

bool CCircle::CheckCoordinates(int x, int y)
{
	
	return(pow((x - NewCenter.x), 2) + pow((y - NewCenter.y), 2) <= pow(NewRadius, 2));    // if the point given satisfies the equation of the line
}

bool CCircle::CheckCoordinates_SF(int x, int y)
{
	return(pow((x - Center.x), 2) + pow((y - Center.y), 2) <= pow(Radius, 2));    // if the point given satisfies the equation of the line

}
void CCircle::Resize(float R,float r)
{
	Radius=Radius*R;
	Point p1, p2;
	p1.x = Center.x + Radius;
	p1.y = Center.y + Radius;
	p2.x = Center.x - Radius;
	p2.y = Center.y - Radius;
	Point p;
	p.x = 100;
	p.y = 100;

	if(CheckForBound(p1,p2,p))
	 return;
	else
	{ Radius=Radius/R;}

}
void CCircle::Zoom()
{
	//new corners=corners in case not zoomed because default zoom factor =1
	NewCenter.x=Center.x*sqrt(UI.ZoomFactor);
	NewCenter.y = Center.y*sqrt(UI.ZoomFactor);
	NewRadius=Radius*sqrt(UI.ZoomFactor);
}
void CCircle::Save(string filename)
{
    ofstream outfile(filename,std::ios::app);
	outfile<<"\n";
	outfile<<"Circle ";
	outfile <<ID<<" "<< Center.x << " " << Center.y << " "<< Radius << " " << FigGfxInfo.BorderWdth << " " << FigGfxInfo.SborderClr << " " << FigGfxInfo.isFilled << " " << FigGfxInfo.SfillClr;
	outfile.close();
}

CFigure * CCircle::Copy()
{
	CFigure*New = new CCircle(NewCenter, NewRadius, FigGfxInfo);
	return New;
}

CFigure * CCircle::Paste()
{
	/*CFigure *C = new CCircle(NewCenter,NewRadius, FigGfxInfo);
	return C;*/
	CFigure *C = new CCircle(Center,Radius, FigGfxInfo);
	if(C!=NULL)
		return C;

}

bool CCircle::CheckLine()
{
	return false;
}

void CCircle:: DeleteFig(Output *pOut)	const
{
	pOut->DeleteCirc(Center, Radius, FigGfxInfo);

}

string CCircle:: returntype()const 
{
	return "Circle";	
}

int CCircle:: getarea()
{
	float pi=3.14;
	float area=pi*Radius*Radius;
	return (int)area;
}

bool CCircle::ChangePlace(int X,int Y)
{	
	Point P=Center;
	Center.x=X-Radius;
	if(X-Radius<670)
		   return false;
	Point p1, p2;
	p1.x = Center.x + Radius;
	p1.y = Center.y + Radius;
	p2.x = Center.x - Radius;
	p2.y = Center.y - Radius;
	Point p;
	p.x = 100;
	p.y = 100;
   if(CheckForBound(p1,p2,p))
	 return true;
   else
   {
	   Center=P;
	   return false;
   }  
}

void CCircle:: Shift(float r)
{
	Center.x=Center.x*r;
}

void CCircle::Rotate(int degree)
{}