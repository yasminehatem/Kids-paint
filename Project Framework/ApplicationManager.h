#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "Figures\CRectangle.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include <vector>
#include <string>


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	int CBcount; //Actual number of figures in the clipboard
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure *Clipboard[MaxFigCount]; //List of Clipboard(for copying)

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;
	
	bool FillClrChanged;  //Checks if the fill color is changed

public:	
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction() const;
	void MoveAll(Point);
	void ResizeAll(float);
	void RotateAll(int degrees);
	void Delete();
	void CopyAll();
	void CutAll();
	void PasteAll(Point P1);
	void ResetAllIDs(); //function used to reset all ID's after cut, copy & paste
	void Save(string filename);
	vector <string> split(string str1); //function used to split the string read from saved files while loading
	bool Is_Empty(std::ifstream& filename); //function that checks if the file to be loaded is empty or not
	color setColor(string clr); //function used to return the color from the string read
	void Load(string &filename);
	void ChangeBorderColor(color C,string);
	bool ChangeFillColor(color C,string);
	bool getFillClrChanged();
	void ChangeBorderWidth(int width);
	void ChangeBkGrndColor(color C, string);
	void ExecuteAction(ActionType) ; //Creates an action and executes it
	void ZoomAll();
	void BackFrontSwap();
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	

	//--pick and hide functions
	int MaxNumberByType(CFigure*specific) const;
	int MaxNumberByColor(CFigure*specific) const;
	int MaxNumberByColorAndType(CFigure*specific) const;
	int MaxNumberByArea(CFigure*specific)const;
	void ResetChoosen();
	bool TypeFunction(CFigure*pointed,CFigure*specificfigure);
	bool ColorFunction(CFigure*pointed,CFigure*specificfigure);
	bool AreaFunction(CFigure*pointed,CFigure*specificfigure);
	bool TypeAndColorFunction(CFigure*pointed,CFigure*specificfigure);
	void TypeMode(CFigure *specificfigure);
	void ColorMode(CFigure *specificfigure);
	void TypeAndColorMode(CFigure *specificfigure);
	void AreaMode(CFigure *specificfigure);
	void UnSelectAll();
	void UpdateInterface_PM() const; //Update interface for play mode

	//--scramble and find functions
	void ScrambleAndFindGame();


};

#endif