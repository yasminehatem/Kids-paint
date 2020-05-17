#ifndef CLINE_H
#define CLINE_H

#include "CFigure.h"

class CLine : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
	Point NewCorner1;	//new coordinates for zoom
	Point NewCorner2;
public:
	CLine(Point , Point, GfxInfo FigureGfxInfo );
	virtual void Draw(Output* pOut) const;
	Point GetCenter() ;
	bool Move(int x,int y);
	bool CheckCoordinates(int x, int y);
	void Resize(float,float);
	virtual CFigure* Copy();
	virtual CFigure*Paste();
	void Save (string filename);
	void Zoom();
	void Rotate(int);
	bool CheckLine();

	//Play Mode Functions//
	virtual void DeleteFig(Output *pOut) const;
	virtual string returntype()const ;
    virtual int getarea();
	virtual void Shift(float);
	bool ChangePlace(int X,int Y);
	void DrawSF(Output* pOut)const;
	bool CheckCoordinates_SF(int x, int y);

};

#endif