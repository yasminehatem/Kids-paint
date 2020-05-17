#ifndef CIRC_H
#define CIRC_H

#include "CFigure.h"
#include <fstream>

class CCircle : public CFigure
{
private:
	Point Center;	
	double Radius;
	Point NewCenter;//new coordinates for zoom
	double NewRadius;
public:
	CCircle(Point , double, GfxInfo FigureGfxInfo);
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
