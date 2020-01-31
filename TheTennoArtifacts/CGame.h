/*********************************************************************
* Assignment: Project 3 - GUI Move and Match Game                    *
* Author: Marc Baello                                                *
* Date: Fall 2017                                                    *
* File: CGame.h                                                      *
*                                                                    *
* Description: This file contains the prototypes for the CGame class.*
*********************************************************************/

#ifndef GAME_H
#define GAME_H

#include <afxwin.h>
#include <string>

using namespace std;

#define NUMIMAGES 40
#define DEFAULT_TIME 60
#define DEFAULT_ROWS 7
#define DEFAULT_COLS 10
#define DEFAULT_VALUE 2
#define DEFAULT_COOLDOWN 5

/**********************************************************************
* Type: sType                                                         *
*                                                                     *
* Description: The sType enumerated type is used to identify the type *
*              of the information stored in a CGameSquare object.     *
**********************************************************************/

enum sTypes {BORDER, ME, SYMBOL, EMPTY};

/*********************************************************************
* Class: CGame                                                       *
*                                                                    *
* Description: This class is designed to simulate a game board. It   *
*              has the same features of a game board, such as a grid *
*              which is comprised of different pieces, and a score.  *
*              It contains a variable which keeps track of time,     *
*              allowing the user to move as many times as they want  *
*              within a defined amount of time. The game board is    *
*              represented as a grid which is a 2D array of          *
*              CGameSquare objects.                                  *
*********************************************************************/

class CGame
{
	public:
		CGame ();
		CGame (const CGame & other);
		~CGame ();
		CGame & operator = (const CGame & other);
		void Init (int R, int C);
		void Instructions (CFrameWnd * windowP);
		void Display (CFrameWnd * windowP);
		void Click (int x, int y, CFrameWnd * windowP);
		void Move (char dir, CFrameWnd * windowP);
		void KeyDown (char key, CFrameWnd * windowP);
		void UpdateTime (CFrameWnd * windowP, int whichTimer);		
		int TimerEvaluateAndUpdate (CFrameWnd * windowP);
		void Message (CFrameWnd * windowP);
		void TransferenceWave(CFrameWnd * windowP);
		void DarkenMatches(CFrameWnd * windowP);
	private:	
		struct CGameSquare
		{
			CGameSquare ();
			CGameSquare (const CGameSquare & other);
			void Fill ();
			void Display (CDC * deviceContextP);
			void Swap (CGameSquare & other, CFrameWnd * windowP);
			void SetWhere (CRect whereRect);
			sTypes what;
			int whichSymbol;
			bool matched;
			CRect where;
		};
		void SetUp (CRect window);
		void GameDisplay (CDC * deviceContextP);
		void DataDisplay (CDC * deviceContextP);
		void ButtonDisplay (CDC * deviceContextP);
		void FillIn ();
		void PlaceMe (); 
		int FindMatches (CFrameWnd * windowP);
		void RemoveMatches (CFrameWnd * windowP);
		void UpdateGrid (int row, int col, CFrameWnd * windowP);

		CGameSquare ** grid;
		int numRows, numCols;
		int myRow, myCol, skillRow, skillCol;
		int score;
		int state;
		bool finished;
		int elapsedTime;
		int elapsedSkillTime;
		char lastDirectionMoved;
		char animationDirection;
		bool animationOn;

		CRect thisRect;
		CRect gameRect;
		CRect newButton;
		CRect restartButton;
		CRect scoreRect;
		CRect timeRect;
		CRect skillRect;
		CRect dataRect1;
		CRect dataRect2;
		CRect dataRect3;
		CBitmap bgImage;
};

#endif
