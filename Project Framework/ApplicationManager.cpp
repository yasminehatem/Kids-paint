#include "ApplicationManager.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddMoveAction.h"
#include "Actions\AddResizeAction.h"
#include"Actions\AddCircAction.h"
#include "Actions\AddLineAction.h"
#include "Actions\AddTriAction.h"
#include "Actions\SelectAction.h"
#include "DeleteAction.h"
#include "CopyAction.h"
#include "CutAction.h"
#include "PasteAction.h"
#include "SaveAction.h"
#include "LoadAction.h"
#include "Actions\AddZoomAction.h"
#include "ChangeBorderColorAction.h"
#include "ChangeFillColorAction.h"
#include "ChangeBorderWidthAction.h"
#include "ChangeBkGrndColorAction.h"
#include "Figures\CCircle.h"
#include "Figures\CTriangle.h"
#include "Figures\CLine.h"
#include"PickAndHide.h"
#include "ScrambleAndFind.h"
#include "RotateAction.h"
#include "SendBackAndBringFront.h"
#include <iostream>
#include <fstream>
#include "time.h"
using namespace std;


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();
	
	FillClrChanged = false;
	FigCount = 0;
		
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType) 
{
	Action* pAct = NULL;
	
	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
		case DRAW_RECT:
			pAct = new AddRectAction(this);
			break;

		case DRAW_LINE:
			///create AddLineAction here
			pAct = new AddLineAction(this);
			break;
		case DRAW_CIRC:
			pAct = new AddCircAction(this);
			break;

		case DRAW_TRI:
			pAct = new AddTriAction(this);
			break;

		case SELECT:
			pAct = new SelectAction(this);
			break;
		
		case MOVE :
			pAct= new AddMoveAction(this);
			break;

		case RESIZE:
			pAct = new AddResizeAction(this);
			break;

		case DEL:
			pAct = new DeleteAction(this);
			break;

		case CPY:
			pAct = new CopyAction(this);
			break;

		case CUT:
			pAct = new CutAction(this);
			break;

		case PASTE:
			pAct = new PasteAction(this);
			break;

		case SAVE:
			pAct = new SaveAction(this);
			break;

		case LOAD:
			pAct = new LoadAction(this);
			break;

		case CHNG_DRAW_CLR:
			pAct = new ChangeBorderColorAction(this);
			break;

		case CHNG_FILL_CLR:
			pAct = new ChangeFillColorAction(this);
			break;

		case CHNG_BORDER_WDTH:
			pAct = new ChangeBorderWidthAction(this);
			break;

		case CHNG_BK_CLR:
			pAct = new ChangeBkGrndColorAction(this);
			break;

		case ZOOM:
			pAct= new AddZoomAction(this);
			break;

		case ROTATE:
			pAct = new RotateAction(this);
			break; 

		case PICK_HIDE:
			pAct= new PickAndHide(this);
			break;

		case  SCRAMBLE_FIND:
			pAct=new ScrambleAndFind(this);
			break;
		
		case BACK_FRONT_SWAP:
			pAct = new SendBackAndBringFrontAction(this);
			break;

		case EXIT:
			///create ExitAction here		
			break;

		case TO_DRAW:
			pOut->CreateDrawToolBar();
			break;

		case TO_PLAY:
			if (UI.ZoomFactor!=1)
			{
				pOut-> PrintMessage("Can't go to play mode, Please zoom out 1st..");
			}
			else if (FigCount==0)
			{
				pOut-> PrintMessage("Can't go to play mode, no figures are drawn..");
			}
			else
			{
				UnSelectAll();   //unselect any selected figures when entering play mode
				pOut->CreatePlayToolBar();
				break;
			}

		case STATUS:	//a click on the status bar ==> no action
			return;
	}
	
	//Execute the created action
	if(pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;
		ZoomAll();//always call zoom function in all cases so it call zoom figures function that set newcorners = corners if zoomfactor equal 1 
		//because it is not zoomed
		pAct = NULL;
	}
}
//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
			
}
////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL


	///Add your code here to search for a figure given a point x,y	

	for (int i = FigCount - 1; i >=0; i--)
		if (FigList[i]->CheckCoordinates(x,y))
			return FigList[i];

	return NULL;
}
//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

void ApplicationManager::MoveAll(Point P1)
{ 

	/*P1.x = P1.x/ UI.ZoomFactor;
	P1.y = P1.y / UI.ZoomFactor;*/
	Point PCenter;
	PCenter.x=0;
	PCenter.y=0;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			PCenter = FigList[i]->GetCenter();
			break;
		}
	}
	int diffX=P1.x-PCenter.x;
	int diffY=P1.y-PCenter.y;
	/*for(int i=0; i<FigCount; i++)
	{    
		if(FigList[i]->IsSelected())

		FigList[i]->Move(diffX,diffY);
	}*/

	int Count=0;
	int count1=0;
	vector<CFigure*> SelectedItems;
	for(int i=0; i<FigCount; i++)
	{
		if (FigList[i]->IsSelected()==true)
		{
			SelectedItems.push_back(FigList[i]->Copy());
			Count++;
		}
	}
	for(int i=0; i<Count; i++)
	{
		if (SelectedItems[i]->Move(diffX,diffY)==true)
		{
			count1++;
		}
	}
	if(Count==count1)
	{
		for(int i=0; i<FigCount; i++)
		{    
			if(FigList[i]->IsSelected())

			FigList[i]->Move(diffX,diffY);
		}
	}
	//CFigure *SelectedItems[Count];
	
}

void ApplicationManager::ResizeAll(float R)
{ 
	float r;
	if (R>1)
		r=R-1;
	else
		r=1-R;

	 for(int i=0; i<FigCount; i++)
	 {    if(FigList[i]->IsSelected())
		 FigList[i]->Resize(R,r);
	 }
}
void ApplicationManager::ZoomAll()
{
	 for(int i=0; i<FigCount; i++)  //loop for figures to zoom them
	 {
		 FigList[i]->Zoom();
		 
	 }

	 if (UI.ZoomFactor!=1)
	 {
		 pOut->DrawZoomToolBar();
	 }	 
}

void ApplicationManager::RotateAll(int degrees)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->IsSelected())
		{
			FigList[i]->Rotate(degrees);
		}
	}

}

void ApplicationManager::BackFrontSwap()
{
	int count=0;    //count the number of selected figures to make sure they are only two
	CFigure* Fig;
	for(int i=0; i<FigCount; i++)
	{
		if (FigList[i]->IsSelected()==true)
		{
			count++;
		}
	}
	if (count!=2)
	{
		pOut->PrintMessage("Please choose two figures..");
		return;
	}
	else
	{
		count=0;
		int index1;
		int index2;
		for(int i=0; i<FigCount; i++)
		{
			if (FigList[i]->IsSelected()==true)
			{
				if(count==0)
				{
					index1=i;
					count=1;
				}
				else
				{
					index2=i;
				}
			}
		}
		Fig = FigList[index1];
		FigList[index1] = FigList[index2];
		FigList[index2]=Fig;
		ResetAllIDs();
		pOut->PrintMessage("Figures have been successfully swapped!");
	}
}

void ApplicationManager::Delete()
{
	int count=0;               //Count the number of figures to delete(selected)

	for(int i=0;i<FigCount;i++)
	{
		if (FigList[i]->IsSelected()==true)     //If the figure is selected the set it to NULL
		{
			FigList[i] = NULL;
			count++;
		}
	}

	if (FigCount == count)                     //If all figures are to be deleted set ID_C (virtual ID) = 0
	{
		FigList[0]->setID_C(0);
	}

	for(int i=0;i<FigCount;i++)
	{
		if (FigList[i] == NULL)     //If the figure is set to NULL 
		{	
			for(int j=i;j<FigCount-1;j++)
			{
				int x=j;                                     // create pointer x = j
				while(FigList[x+1]==NULL&& x<FigCount-1)    // while the element after is equal to NULL && x<FigCount-1 to avoid entering in an infinite loop
				{
					x++;									//increment the pointer
				}
				FigList[j]=FigList[x+1];                // move the 1st element that's != NULL to location j
				FigList[x+1]=NULL;                      // set it to NULL
			} //end 1st for loop
		} //end if
	} //end 2nd for loop

	//FigList[FigCount-1] = NULL;
	FigCount-=count;                           //Subtract the count of deleted figures from the total figure count

	for (int n=0; n<FigCount; n++)             //re-arrange ID's
	{
		FigList[n] -> setID(n+1);
	}

	if (FigList[0] != NULL)
	{
		FigList[0]->setID_C(FigCount);     //Set virtual ID by new Fig count
	}
}

void ApplicationManager::CopyAll()
{
	
	for (int i = 0;i < CBcount;i++)
	{
		delete Clipboard[i];            // delete the figures in the clipboard and set their pointer to null
		Clipboard[i] = NULL;
	}
	CBcount = 0;
	for (int i = 0;i < FigCount;i++)
	{
		if (FigList[i]->IsSelected())       //check if the figure is selected, if it is then call function copy in CFigure
		{
			Clipboard[CBcount] = FigList[i]->Copy();
			CBcount++;
		}
	}
	if(CBcount==0)
	{
		pOut->PrintMessage("No selected figures");
	}

	ResetAllIDs();
	
}

void ApplicationManager::CutAll()
{
	CopyAll();
	Delete();
	ResetAllIDs();
}

void ApplicationManager::ResetAllIDs()
{
	for (int i=0; i<FigCount; i++)
	{
		FigList[i]->setID(i+1);
	}
	FigList[0] -> setID_C(FigCount);
}


void ApplicationManager::PasteAll(Point P1)
{
	Point PCenter;
	if (CBcount > 0)
	{
		PCenter = Clipboard[0]->GetCenter();
		int counter=0;
		int diffX = P1.x - PCenter.x;
		int diffY = P1.y - PCenter.y;
		//FigList[0]->setID_C(FigList[0]->getID_C() - CBcount);
		CFigure* Fig;
		for (int i = 0; i < CBcount; i++)
		{
			Fig = Clipboard[i]->Paste();
		  	if(Fig->Move(diffX,diffY))
			{
				AddFigure(Fig);
			}
			else
			{
				pOut->PrintMessage("This point is out of range..");
				for(int j=FigCount-i;j<FigCount;j++)
				{
						FigList[j] = NULL;
				}
				FigCount-=i;
				break;
			}
		}
		ResetAllIDs();
	}
	else
	{
		pOut->PrintMessage("The clipboard is empty");
	}
	
}

void ApplicationManager::Save(string filename)
{
	//create new file
	ofstream ofs;
	ofs.open(filename +".txt",ofstream::out| ofstream::trunc);
	ofs.close();
	//ofstream outfile(filename +".txt");

	ofstream outfile(filename+".txt",std::ios::app);

	outfile << UI.drawClr << "\t" << UI.fillClr << "\t" << UI.BkGrndClr;

	outfile <<"\n";

	outfile << FigCount;

	outfile.close();

	for(int i=0;i<FigCount;i++)
	{
		FigList[i]->Save(filename +".txt");
	}
}

vector<string> ApplicationManager::split(string str1)
{
	vector<string> sp;
	char * pch;
	char str[1024];
    strncpy(str, str1.c_str(),str1.size());
	str[str1.size() ] = 0;

	//printf ("Splitting string \"%s\" into tokens:\n",str);
	pch = strtok (str," ,.- \t");
    while (pch != NULL)
    {
		//printf ("%s\n",pch);
		sp.push_back(pch);
		pch = strtok (NULL, " ,.- \t");
    }

	return sp;
}

color ApplicationManager::setColor(string clr)
{
	if (clr == "WHITE")
	{
		return WHITE;
	}
	else if (clr == "GRAY")
	{
		return GRAY;
	}
	else if (clr == "BLACK")
	{
		return BLACK;
	}
	else if (clr == "SADDLEBROWN")
	{
		return SADDLEBROWN;
	}
	else if (clr == "RED")
	{
		return RED;
	}
	else if (clr == "ORANGE")
	{
		return ORANGE;
	}
	else if (clr == "YELLOW")
	{
		return YELLOW;
	}
	else if (clr == "LIGHTGOLDENRODYELLOW")
	{
		return LIGHTGOLDENRODYELLOW;
	}
	else if (clr == "GREEN")
	{
		return GREEN;
	}
	else if (clr == "TURQUOISE")
	{
		return TURQUOISE;
	}
	else if (clr == "SKYBLUE")
	{
		return SKYBLUE;
	}
	else if (clr == "BLUE")
	{
		return BLUE;
	}
}

bool ApplicationManager::Is_Empty(std::ifstream& filename)
{
    return filename.peek() == std::ifstream::traits_type::eof();
}

void ApplicationManager::Load(string &filename)
{
	if (FigCount>0)
	{
		FigList[0]->setID_C(0);       //set virtual ID to 0
	}

	for (int n=0; n<FigCount; n++)    //delete all figures before loading
	{
		FigList[n] = NULL;
	}

	FigCount = 0; //set fig count equal 0 when deleting 

    std::ifstream file(filename+".txt");        //open file

	if (Is_Empty(file))                         //check if file doesn't exist or is empty
	{ 
		pOut -> PrintMessage("Requested file doesn't exist or is empty, please re-check file name");
	}

	else
	{
		std::string str1; 
		vector<vector<string>> fileLines;          //read file lines in vector form
		vector<string> sp;
		while (std::getline(file, str1))           //while the file didn't end
		{
			//std::cout<<str1<<std::endl;
			sp=split(str1);                        //call function split
			fileLines.push_back(sp);
			sp.clear();
		}

		UI.DrawColor = setColor(fileLines[0][0]);       
		UI.FillColor = setColor(fileLines[0][1]);
		UI.BkGrndColor = setColor(fileLines[0][2]);

		int count = atoi(fileLines[1][0].c_str());   //function that converts from string to integer
	
		for (int i=0; i<count;i++)
		{
			if (fileLines[i+2][0]== "Rectangle")
			{
				//According to Action Type, create the corresponding action object
				//pAct = new LoadRectAction(this);
				Point P1;
				Point P2;
				GfxInfo RectGfxInfo;
				P1.x = atoi(fileLines[i+2][2].c_str());
				P1.y = atoi(fileLines[i+2][3].c_str());
				P2.x = atoi(fileLines[i+2][4].c_str());
				P2.y = atoi(fileLines[i+2][5].c_str());
				RectGfxInfo.BorderWdth = atoi(fileLines[i+2][6].c_str());
				RectGfxInfo.DrawClr = setColor(fileLines[i+2][7]);
				RectGfxInfo.SborderClr = fileLines[i+2][7];
				RectGfxInfo.isFilled = atoi(fileLines[i+2][8].c_str());
				RectGfxInfo.FillClr = setColor(fileLines[i+2][9]);
				RectGfxInfo.SfillClr = fileLines[i+2][9];

				CFigure *R = new CRectangle(P1,P2,RectGfxInfo);
				R-> setID(atoi(fileLines[i+2][1].c_str()));
				this->AddFigure(R);
			}
			else if (fileLines[i+2][0]== "Circle")
			{
				Point centre;
				double raduis;
				GfxInfo CircGfxInfo;
				centre.x = atoi(fileLines[i+2][2].c_str());
				centre.y = atoi(fileLines[i+2][3].c_str());
				raduis = atoi(fileLines[i+2][4].c_str());
				CircGfxInfo.BorderWdth = atoi(fileLines[i+2][5].c_str());
				CircGfxInfo.DrawClr = setColor(fileLines[i+2][6]);
				CircGfxInfo.SborderClr = fileLines[i+2][6];
				CircGfxInfo.isFilled = atoi(fileLines[i+2][7].c_str());
				CircGfxInfo.FillClr = setColor(fileLines[i+2][8]);
				CircGfxInfo.SfillClr = fileLines[i+2][8];

				CFigure *C = new CCircle (centre,raduis,CircGfxInfo);
				C -> setID(atoi(fileLines[i+2][1].c_str()));
				this->AddFigure(C);

			}
			else if (fileLines[i+2][0]=="Triangle")
			{
				Point corner1;
				Point corner2;
				Point corner3;
				GfxInfo TriGfxInfo;
				corner1.x = atoi(fileLines[i+2][2].c_str());
				corner1.y = atoi(fileLines[i+2][3].c_str());
				corner2.x = atoi(fileLines[i+2][4].c_str());
				corner2.y = atoi(fileLines[i+2][5].c_str());
				corner3.x = atoi(fileLines[i+2][6].c_str());
				corner3.y = atoi(fileLines[i+2][7].c_str());
				TriGfxInfo.BorderWdth = atoi(fileLines[i+2][8].c_str());
				TriGfxInfo.DrawClr = setColor(fileLines[i+2][9]);
				TriGfxInfo.SborderClr = fileLines[i+2][9];
				TriGfxInfo.isFilled = atoi(fileLines[i+2][10].c_str());
				TriGfxInfo.FillClr = setColor(fileLines[i+2][11]);
				TriGfxInfo.SfillClr = fileLines[i+2][11];

				CFigure *T = new CTriangle (corner1,corner2,corner3,TriGfxInfo);
				T -> setID(atoi(fileLines[i+2][1].c_str()));
				this->AddFigure(T);
			}
			else if (fileLines[i+2][0]=="Line")
			{
				Point P1;
				Point P2;
				GfxInfo LineGfxInfo;
				P1.x = atoi(fileLines[i+2][2].c_str());
				P1.y = atoi(fileLines[i+2][3].c_str());
				P2.x = atoi(fileLines[i+2][4].c_str());
				P2.y = atoi(fileLines[i+2][5].c_str());
				LineGfxInfo.BorderWdth = atoi(fileLines[i+2][6].c_str());
				LineGfxInfo.DrawClr = setColor(fileLines[i+2][7]);
				LineGfxInfo.SborderClr = fileLines[i+2][7];
				LineGfxInfo.isFilled = atoi(fileLines[i+2][8].c_str());
				LineGfxInfo.FillClr = setColor(fileLines[i+2][9]);
				LineGfxInfo.SfillClr = fileLines[i+2][9];

				CFigure *L = new CLine(P1,P2,LineGfxInfo);
				L -> setID(atoi(fileLines[i+2][1].c_str()));
				this->AddFigure(L);

			}
		}

		FigList[0] -> setID_C(count);        //set virtual ID with count read from file
		}
}

void ApplicationManager::ChangeBorderColor(color C, string clr)
{
	bool found = false; //to check if the user selected a user

	for (int i=0; i< FigCount; i++)
	{
		if (FigList[i]->IsSelected()==true)
		{
			found = true;
			FigList[i]->ChngDrawClr(C);
			FigList[i]->setBorderClr(clr);
		}
	}
	if (found == false)
	{
		pOut ->setCrntDrawColor(C,clr);
	}
}

bool ApplicationManager::getFillClrChanged()
{
	return FillClrChanged;
}

bool ApplicationManager::ChangeFillColor(color C, string clr)
{
	bool found = false; //to check if the user selected a user

	for (int i=0; i< FigCount; i++)
	{
		if (FigList[i]->IsSelected()==true)
		{
			if (FigList[i]->CheckLine()==true)
			{
				pOut->PrintMessage("Lines have no fill color, choose another figure..");
				found = true;
			}
			else
			{
				found = true;
				FigList[i]->ChngFillClr(C);
				FigList[i]->setFillClr(clr);
			}
		}
	}

	if (found == false)
	{
		pOut->setCrntFillColor(C, clr);
	    FillClrChanged = true;
		return true;
	}
	//in case of overlapping the figure created last has the priority and is sent to front
}

void ApplicationManager::ChangeBorderWidth(int W)
{
	bool found = false; //to check if the user selected a user

	for (int i=0; i< FigCount; i++)
	{
		if (FigList[i]->IsSelected()==true)
		{
			found = true;
			FigList[i]->ChngBrdWdth(W);
		}
	}
	if (found == false)
	{
		pOut->setCrntPenWidth(W);
	}
}

void ApplicationManager::ChangeBkGrndColor(color C,string clr)
{
	UI.BkGrndColor = C;
	UI.BkGrndClr = clr;
}

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
	{
			FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
	}
	//pOut->CreateStatusBar();   //Added to solve problem of shapes overlapping status bar during zooming
}
////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::UpdateInterface_PM() const
{
	pOut->ClearDrawArea();

	for(int i=0; i<FigCount; i++)
	{
		if(FigList[i]->ischoosen()==false)
		{FigList[i]->Draw(pOut);}		//Call Draw function (virtual member fn)
	}
}

int ApplicationManager::MaxNumberByType(CFigure*specific) const
{
	int max=0;
	for (int i=0;i<FigCount;i++)
	{
		if(FigList[i]->returntype()==specific->returntype())
		{
			max++;
		}

	}
	return max-1;
}
int ApplicationManager::MaxNumberByColor(CFigure*specific) const
{
	int max=0;
	for (int i=0;i<FigCount;i++)
	{
		if(specific->CompareFilled(FigList[i])==true)
		{
			max++;
		}

	}
	return max-1;
}
int ApplicationManager::MaxNumberByColorAndType(CFigure*specific) const
{
	int max=0;
	for (int i=0;i<FigCount;i++)
	{
		if(specific->CompareFilled(FigList[i])==true && specific->returntype()==FigList[i]->returntype())
		{
			max++;
		}

	}
	return max-1;
}
int ApplicationManager::MaxNumberByArea(CFigure*specific)const
{
	int max=0;
	for (int i=0;i<FigCount;i++)
	{
		if(FigList[i]->returntype()==specific->returntype())
		{
			max++;

	  }
		
	}

	
	return max-1;
}
void ApplicationManager:: ResetChoosen()
{
	for (int i=0;i<FigCount;i++)
		FigList[i]->setchoosen(false);
}
bool ApplicationManager::TypeFunction(CFigure*pointed,CFigure*specificfigure)
{

	if (pointed->returntype()==specificfigure->returntype())
				{
					if (pointed->ischoosen()!=true)
					{
						pointed->DeleteFig(pOut);
						pointed->setchoosen(true);
						UpdateInterface_PM();
						return true;
					}
					
				}
	
	return false ;
}
bool ApplicationManager::ColorFunction(CFigure*pointed,CFigure*specificfigure)
{
	
	if (specificfigure->CompareFilled(pointed)==true)
				{
					if (pointed->ischoosen()!=true)
					{
						pointed->DeleteFig(pOut);
						
						pointed->setchoosen(true);
						UpdateInterface_PM();
						return true;
					}
	             }
	
	return false ;
					
	
}
bool ApplicationManager::TypeAndColorFunction(CFigure*pointed,CFigure*specificfigure)
{

	if (pointed->returntype()==specificfigure->returntype() && specificfigure->CompareFilled(pointed)==true )
				{
					if (pointed->ischoosen()!=true)
					{
						pointed->DeleteFig(pOut);
						pointed->setchoosen(true);
						UpdateInterface_PM();
						return true;
					}
				}
	
	return false ;
}

bool ApplicationManager::AreaFunction(CFigure*pointed,CFigure*specificfigure)
{
	CFigure*nextchoosen;
		
	bool flag=false; //for checking if the picked figure is the smallest or the largest

	for (int i=0;i<FigCount;i++)
	{
		
		if(FigList[i]->returntype()==specificfigure->returntype())
		{

			if (FigList[i]->getarea()>specificfigure->getarea() && FigList[i]->ischoosen()==false)
			{
				nextchoosen=FigList[i];
				flag=true;
			}

			if (FigList[i]->getarea()<specificfigure->getarea() && FigList[i]->ischoosen()==false)
			{
				nextchoosen=FigList[i];
			}
	    }
	}

	if (flag==true)
	{
			
		for (int i=0;i<FigCount;i++)
		{
		
			if(FigList[i]->returntype()==specificfigure->returntype())
			{
				if (FigList[i]->getarea()<=nextchoosen->getarea() && FigList[i]->ischoosen()==false)
					nextchoosen=FigList[i];
			}
		}

	}
	else 
	{
	
		for (int i=0;i<FigCount;i++)
		{
		
			if(FigList[i]->returntype()==specificfigure->returntype())
			{
				if (FigList[i]->getarea()>=nextchoosen->getarea() && FigList[i]->ischoosen()==false)
					nextchoosen=FigList[i];
			}
		}
	}
	if (pointed==nextchoosen)
	{
		if (pointed->ischoosen()!=true)
		{
			pointed->DeleteFig(pOut);
			pointed->setchoosen(true);
			UpdateInterface_PM();
			return true;
		}
					
	}
	
	return false;

	/*if (specificfigure->returntype() == pointed -> returntype())
	{
		if (specificfigure->getarea()> pointed -> getarea())
		{
			pointed->DeleteFig(pOut);
			pointed->setchoosen(true);
			UpdateInterface_PM();
			return true;
		}
		else 
			return false;
	}*/

}

//////////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::TypeMode(CFigure *specificfigure)
{		
	Point P;
	CFigure*pointed;
	int valid=0;
	int invalid=0;
	int checkvalid=0;
	bool checker;
	checkvalid=MaxNumberByType(specificfigure);
	if(checkvalid==0)
	{
		ResetChoosen();
		pOut->PrintMessage("There is no figure having the same type as the picked one, try choosing another type. Click any where to go back..");
		pIn->GetPointClicked(P.x, P.y);
		return;
	}
	while (true)
	{		
		pIn->GetPointClicked(P.x, P.y);
		pointed=GetFigure(P.x,P.y);
		if (pointed!=NULL && pointed!=specificfigure)
		{	
			checker=TypeFunction(pointed,specificfigure);
			if (checker==true)
				valid++;
			else
				invalid++;
			pOut->PrintMessage("Number of valid picks is");
			pOut->PrintNumber(valid,200);
			pOut->PrintMessage("Number of invalid picks is",230);
			pOut->PrintNumber(invalid,430);
				
			if(checkvalid==valid)
			{	pOut->ClearStatusBar();
				UpdateInterface_PM();
				pOut->Drawstring(600,70,"your grade is");
				int grade=100*checkvalid;
				pOut->Drawint(770,70,(grade/(valid+invalid)));
				pOut->Drawstring(815,70,"/100");
				pOut->PrintMessage("Click any where to Restart  Pick & Hide Mode",460);
				pIn->GetPointClicked(P.x, P.y);
					
				break;	
					
			}
		}
		if (P.y<50)
			break;
	UpdateInterface_PM();
	
	}

}
void ApplicationManager::ColorMode(CFigure *specificfigure)
{
	Point P;
	CFigure*pointed;
	int valid=0;
	int invalid=0;
	int checkvalid=0;
	bool checker;
	checkvalid=MaxNumberByColor(specificfigure);
	if(checkvalid==0)
	{
		pOut->PrintMessage("There is no figure having the same Fill Color as the picked one, try choosing another color. Click any where to go back..");
		pIn->GetPointClicked(P.x, P.y);
		return;
	}
	while (true)
	{	
		pIn->GetPointClicked(P.x, P.y);
		pointed=GetFigure(P.x,P.y);
		if (pointed!=NULL)
		{
			checker=ColorFunction(pointed,specificfigure);
			if (checker==true)
			{
				valid++;
			}
			else
			{ 
				invalid++;
			}
			pOut->PrintMessage("Number of valid picks is");
			pOut->PrintNumber(valid,200);
			pOut->PrintMessage("Number of invalid picks is",230);
			pOut->PrintNumber(invalid,430);
				
			if(checkvalid==valid)
			{	 pOut->ClearStatusBar();
				UpdateInterface_PM();
				pOut->Drawstring(600,50,"your grade is");
				int grade=100*checkvalid;
				pOut->Drawint(770,50,(grade/(valid+invalid)));
				pOut->Drawstring(815,50,"/100");
				pOut->PrintMessage("Click any where to Restart to Pick & Hide Mode",460);
				pIn->GetPointClicked(P.x, P.y);
					
				break;							
			}
		}
		if (P.y<50)
			break;
	
	}

}

void ApplicationManager::TypeAndColorMode(CFigure *specificfigure)
{
	Point P;
	CFigure*pointed;
	int valid=0;
	int invalid=0;
	int checkvalid=0;
	bool checker;
	checkvalid=MaxNumberByColorAndType(specificfigure);
	if(checkvalid==0)
	{
		ResetChoosen();
		pOut->PrintMessage("There is no figure having the same type & fill color as the picked one, try choosing another one. Click any where to go back..");
		pIn->GetPointClicked(P.x, P.y);
		return;
	}
	while (true)
	{	
		pIn->GetPointClicked(P.x, P.y);
		pointed=GetFigure(P.x,P.y);
		if (pointed!=NULL && pointed!=specificfigure)
		{		
			checker=TypeAndColorFunction(pointed,specificfigure);
			if (checker==true)
			{
				valid++;
			}
			else
			{ 
				invalid++;
			}
			pOut->PrintMessage("Number of valid picks is");
			pOut->PrintNumber(valid,200);
			pOut->PrintMessage("Number of invalid picks is",230);
			pOut->PrintNumber(invalid,430);
				
			if(checkvalid==valid)
			{	 pOut->ClearStatusBar();
				UpdateInterface_PM();
				pOut->Drawstring(600,50,"your grade is");
				int grade=100*checkvalid;
				pOut->Drawint(770,50,(grade/(valid+invalid)));
				pOut->Drawstring(815,50,"/100");
				pOut->PrintMessage("Click any where to Restart to Pick & Hide Mode",460);
				pIn->GetPointClicked(P.x, P.y);
					
				break;	
			}
		}
		if (P.y<50)
			break;
		UpdateInterface_PM();
	
	}
}
void ApplicationManager::AreaMode(CFigure *specificfigure)
{		
	Point P;
	CFigure*pointed;
	int valid=0;
	int invalid=0;
	int checkvalid=0;
	bool checker;
	checkvalid=MaxNumberByArea(specificfigure);
	if(checkvalid==0)
	{
		ResetChoosen();
		pOut->PrintMessage("There is no figure having the same area as the picked one, try choosing another area. Click any where to go back..");
		pIn->GetPointClicked(P.x, P.y);
		return;
	}
	while (true)
	{
		pIn->GetPointClicked(P.x, P.y);
		pointed=GetFigure(P.x,P.y);
		if (pointed!=NULL && pointed!=specificfigure)
		{
				
			checker=AreaFunction(pointed,specificfigure);
			if (checker==true)
				valid++;
			else
				invalid++;
			pOut->PrintMessage("Number of valid picks is");
			pOut->PrintNumber(valid,200);
			pOut->PrintMessage("Number of invalid picks is",230);
			pOut->PrintNumber(invalid,430);
				
			if(checkvalid==valid)
			{
				UpdateInterface_PM();
				pOut->ClearStatusBar();
				pOut->Drawstring(600,50,"your grade is");
				int grade=100*checkvalid;
				pOut->Drawint(770,50,(grade/(valid+invalid)));
				pOut->Drawstring(815,50,"/100");
				pOut->PrintMessage("Click any where to Restart to Pick & Hide Mode",460);
				pIn->GetPointClicked(P.x, P.y);
					
				break;			
					
			}
		}
		if (P.y<50)
			break;
		UpdateInterface_PM();
	
	}
}

void ApplicationManager::UnSelectAll()
{
	for (int i=0; i<FigCount; i++)
	{
		FigList[i]->SetSelected(false);
	}
}

////////////////////////////////////////////////////////////////////////////////////

void ApplicationManager::ScrambleAndFindGame()
{
	if (FigCount == 0)
	{
		return;
	}
	CFigure*ScrambleAndFindList[200];  //create scramble and find list
	int SizeOfList=FigCount*2;         
	for(int i=0;i<200;i++)
	{
		ScrambleAndFindList[i]=NULL;
	}
	for(int i=0;i<FigCount;i++)        //copy figures from fig list to scramble and find list
	{
		ScrambleAndFindList[i]=FigList[i]->Paste();
		ScrambleAndFindList[FigCount+i]=FigList[i]->Paste();
	}
	pOut->ClearDrawArea();       
	for(int i=60;i<540;i+=20)
	{
		pOut->Drawstring(660,i,"|");
	}
	for(int i=0; i<FigCount; i++)
	{	
		if(ScrambleAndFindList[i]->returntype() == "Line")
				ScrambleAndFindList[i]->ChngBrdWdth(5);
	
		ScrambleAndFindList[i]->Resize(0.5,0.5);
		ScrambleAndFindList[i]->Shift(0.5);
		ScrambleAndFindList[i]->DrawSF(pOut);
		ScrambleAndFindList[i]->setchoosen(true);
	 }

	Point P1;    //define point P1
	srand(time(0));
	for(int i=FigCount;i<FigCount*2;i++)
	{ 
		P1.x=680+(rand()%(680));
		P1.y=0+(rand()%(600));
		while(!ScrambleAndFindList[i]->ChangePlace(P1.x,P1.y))
		{
			P1.x=657+(rand()%(657));
			P1.y=(rand()%(600));
		}
		if(ScrambleAndFindList[i]->returntype() == "Line")
				ScrambleAndFindList[i]->ChngBrdWdth(5);

		ScrambleAndFindList[i]->Resize(0.5,0.5);
		ScrambleAndFindList[i]->setchoosen(true);
		ScrambleAndFindList[i]->DrawSF(pOut);
	}

	Point P;
	CFigure*pointed;
	int valid=0;
	int invalid=0;
	int counter=0;
	while(true)
	{
		if(ScrambleAndFindList[counter]->returntype() == "Line")
			ScrambleAndFindList[counter]->ChngDrawClr(BLACK);
		else
		{
			ScrambleAndFindList[counter]->ChngFillClr(BLACK);
			ScrambleAndFindList[counter]->ChngDrawClr(BLACK);
		}

		for(int i=0;i<SizeOfList;i++)
		{
			if(ScrambleAndFindList[i]->ischoosen())
				ScrambleAndFindList[i]->DrawSF(pOut);
		}
		pIn->GetPointClicked(P.x, P.y); 
		if(P.y<50 && P.x>130 && P.x<195)
		{ 
			return;
		}
		for (int i = (SizeOfList/2); i < SizeOfList; i++)
		{
			if (ScrambleAndFindList[i]->CheckCoordinates_SF(P.x,P.y))
			{
				pointed=ScrambleAndFindList[i];	 
				break;
			}
			else
				pointed=NULL;
		}
		if (pointed!=NULL )
		{		
			if(pointed->getarea()==ScrambleAndFindList[counter]->getarea() && pointed->returntype()==ScrambleAndFindList[counter]->returntype())
			{
				pointed->setchoosen(false);
				ScrambleAndFindList[counter]->setchoosen(false);
				pOut->ClearDrawArea();
				for(int i=60;i<540;i+=20)
				{
					pOut->Drawstring(660,i,"|");
				}
				for(int i=0;i<SizeOfList;i++)
				{	
					if(ScrambleAndFindList[i]->ischoosen())
						ScrambleAndFindList[i]->DrawSF(pOut);
				}
				valid++;
				counter++;
				pointed=NULL;
			}
			else
				invalid++;

				pOut->PrintMessage("Number of valid picks is");
				pOut->PrintNumber(valid,200);
				pOut->PrintMessage("Number of invalid picks is",230);
				pOut->PrintNumber(invalid,430);
		}
	
		else
			pIn->GetPointClicked(P.x,P.y);

		if(counter==FigCount)
		{
		    pOut->ClearDrawArea();
			pOut->Drawstring(500,200,"your grade is");
			int grade=100*valid;
			pOut->Drawint(670,200,(grade/(valid+invalid)));
			pOut->Drawstring(715,200,"/100");
			pOut->ClearStatusBar();
			pOut->PrintMessage("Click any where to Return to draw Mode",460);
			pIn->GetPointClicked(P.x, P.y);
			break;
		}
	}
	//delete ScrambleAndFindList;
	for(int i=0;i<FigCount*2;i++)
	{
		delete ScrambleAndFindList[i];
		ScrambleAndFindList[i]=NULL;
	}
}	

//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
