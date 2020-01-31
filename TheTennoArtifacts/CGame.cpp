/*********************************************************************
* Assignment: Project 3 - GUI Move and Match Game                    *
* Author: Marc Baello                                                *
* Date: Fall 2017                                                    *
* File: CGame.cpp                                                    *
*                                                                    *
* Description: This file contains the implementations for the CGame  *
*              class. It also contains implementations for the       *
*              CGameSquare struct which resides in the CGame class.  *
*********************************************************************/

#include "CGame.h"
#include <time.h>
#include <mmsystem.h>
#include <fstream>

using namespace std;

static CBitmap images [NUMIMAGES];
static CBitmap masks [2];
CGame * savedGame = NULL;

/*********************************************************************
* Function: CGame::CGameSquare::CGameSquare ()                       *
*                                                                    *
* Parameters: 1 CGameSquare object                                   *
* Return value: N/A                                                  *
* Description: This function is the default constructor for the      *
*              CGameSquare struct.                                   *
*********************************************************************/

CGame::CGameSquare::CGameSquare ()
{
	what = BORDER;
	whichSymbol = 0;
	matched = false;
}

/*********************************************************************
* Function: CGame::CGameSquare::CGameSquare                          *
*                              (const CGameSquare & other)           *
*                                                                    *
* Parameters: 2 CGameSquare objects                                  *
* Return value: N/A                                                  *
* Description: This function is the copy constructor for the         *
*              CGameSquare struct.                                   *
*********************************************************************/

CGame::CGameSquare::CGameSquare(const CGameSquare & other)
{
	this->what = other.what;
	this->whichSymbol = other.whichSymbol;
	this->matched = other.matched;
	this->where = other.where;
}

/*********************************************************************
* Function: void CGame::CGameSquare::Fill ()                         *
*                                                                    *
* Parameters: 1 CGameSquare                                          *
* Return value: N/A                                                  *
* Description: This function will set a CGameSquare to a SYMBOL and  *
*              assign it a random symbol.                            *
*********************************************************************/

void CGame::CGameSquare::Fill ()
{
	what = SYMBOL;
	whichSymbol = ((rand() % 5) + 1);
}

/*********************************************************************
* Function: void CGame::CGameSquare::Display (CDC * deviceContextP)  *
*                                                                    *
* Parameters: 1 CGameSquare object, 1 CDC object pointer             *
* Return value: N/A                                                  *
* Description: This function is responsible for drawing a            *
*              particular CGameSquare object each time it is called. *
*********************************************************************/

void CGame::CGameSquare::Display (CDC * deviceContextP)
{
	if (what == EMPTY)
		return;
	deviceContextP->Rectangle (where);
	CDC memDC;
	memDC.CreateCompatibleDC(deviceContextP);
	memDC.SelectObject(&images[whichSymbol]);
	int res = deviceContextP->TransparentBlt (where.left + 1, where.top + 1, where.Width() - 2, where.Height() - 2,
					&memDC, 0, 0, 200, 200, SRCCOPY); 
	DeleteDC (memDC);
}

/*********************************************************************
* Function: void CGame::CGameSquare::Swap                            *
*                      (CGame::CGameSquare & other,                  *
*                       CFrameWnd * windowP)                         *
*                                                                    *
* Parameters: 2 CGameSquare objects, 1 CFrameWnd object pointer      *
* Return value: N/A                                                  *
* Description: This function will swap the data between two          *
*              CGameSquare objects. It does not swap the "where"     *
*              variable. This function also redraws the two swapped  *
*              CGameSquare objects.                                  *
*********************************************************************/

void CGame::CGameSquare::Swap (CGame::CGameSquare & other, CFrameWnd * windowP)
{
	CGameSquare temp = *this;

	this->what = other.what;
	this->whichSymbol = other.whichSymbol;
	this->matched = other.matched;

	other.what = temp.what;
	other.whichSymbol = temp.whichSymbol;
	other.matched = temp.matched;

	windowP->InvalidateRect (this->where);
	windowP->InvalidateRect (other.where);
}

/*********************************************************************
* Function: void CGame::CGameSquare::SetWhere (CRect whereRect)      *
*                                                                    *
* Parameters: 1 CGameSquare object, 1 CRect object                   *
* Return value: N/A                                                  *
* Description: This function is the mutator/setter for the variable  *
*              where in the CGameSquare struct.                      *
*********************************************************************/

void CGame::CGameSquare::SetWhere (CRect whereRect)
{
	where = whereRect;
}

/*********************************************************************
* Function: CGame::CGame ()                                          *
*                                                                    *
* Parameters: 1 CGame object                                         *
* Return value: N/A                                                  *
* Description: This function is the default constructor for the      *
*              CGame class.                                          *
*********************************************************************/

CGame::CGame ()
{
	srand (unsigned (time (NULL)));
	numRows = numCols = 1;
	grid = new CGameSquare * [numRows + 2];
	for (int r = 0; r < numRows + 2; r++)
		grid[r] = new CGameSquare [numCols + 2];
	savedGame = new CGame (*this);
	Init (DEFAULT_ROWS, DEFAULT_COLS);
	int res = bgImage.LoadBitmap(CString("BACKGROUND_BMP"));
	res = images[0].LoadBitmap(CString("ME_BMP"));
	res = images[1].LoadBitmap(CString("SYMBOL1_BMP"));
	res = images[2].LoadBitmap(CString("SYMBOL2_BMP"));
	res = images[3].LoadBitmap(CString("SYMBOL3_BMP"));
	res = images[4].LoadBitmap(CString("SYMBOL4_BMP"));
	res = images[5].LoadBitmap(CString("SYMBOL5_BMP"));
	res = images[6].LoadBitmap(CString("SYM1DARK_BMP"));
	res = images[7].LoadBitmap(CString("SYM2DARK_BMP"));
	res = images[8].LoadBitmap(CString("SYM3DARK_BMP"));
	res = images[9].LoadBitmap(CString("SYM4DARK_BMP"));
	res = images[10].LoadBitmap(CString("SYM5DARK_BMP"));
}

/*********************************************************************
* Function: CGame::~CGame ()                                         *
*                                                                    *
* Parameters: 1 CGame object                                         *
* Return value: N/A                                                  *
* Description: This function is the destructor for the CGame class.  *
*********************************************************************/

CGame::~CGame ()
{
	for (int r = 0; r < numRows + 2; r++)
		delete[] grid[r];
	delete[] grid;
	if (this != savedGame  && savedGame != NULL)
		delete savedGame;
	savedGame = NULL;
}

/*********************************************************************
* Function: CGame::CGame (const CGame & other)                       *
*                                                                    *
* Parameters: 2 CGame objects                                        *
* Return value: N/A                                                  *
* Description: This function is the copy constructor for the CGame   *
*              class.                                                *
*********************************************************************/

CGame::CGame (const CGame & other)
{
	*this = other;
}

/*********************************************************************
* Function: CGame & CGame::operator = (const CGame & other)          *
*                                                                    *
* Parameters: 2 CGame objects                                        *
* Return value: N/A                                                  *
* Description: This function is the overloaded assignment operator   *
*              for the CGame class.                                  *
*********************************************************************/

CGame & CGame::operator = (const CGame & other)
{
	if (this == &other)
		return *this;
	for (int r = 0; r < numRows; r++)
		delete[] grid[r];
	delete[] grid;
	numRows = other.numRows;
	numCols = other.numCols;
	myRow = other.myRow;
	myCol = other.myCol;
	skillRow = other.skillRow;
	skillCol = other.skillCol;
	score = other.score;
	state = other.state;
	finished = other.finished;
	elapsedTime = other.elapsedTime;
	elapsedSkillTime = other.elapsedSkillTime;
	animationOn = other.animationOn;
	lastDirectionMoved = other.lastDirectionMoved;
	animationDirection = other.animationDirection;
	thisRect = other.thisRect;
	grid = new CGameSquare * [numRows + 2];
	for (int r = 0; r < numRows + 2; r++)
		grid[r] = new CGameSquare [numCols + 2];
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
		{
			grid[r][c].what = other.grid[r][c].what;
			grid[r][c].whichSymbol = other.grid[r][c].whichSymbol;
			grid[r][c].matched = other.grid[r][c].matched;
		}
	return *this;
}

/*********************************************************************
* Function: void CGame::Init (int R, int C)                          *
*                                                                    *
* Parameters: 1 CGame object, 2 integers                             *
* Return value: N/A                                                  *
* Description: This function initializes the 2D CGameSquare array    *
*              found in the CGame class, as well as other variables  *
*              like state, score, elapsedTime, finished, and         *
*              thisRect. A deep copy of the particular game          *
*              configuration is saved in another CGame object        *
*              called savedGame.                                     *
*********************************************************************/

void CGame::Init (int R, int C)
{
	for (int r = 0; r < numRows + 2; r++)
		delete[] grid[r];
	delete[] grid;
	numRows = R;
	numCols = C;
	grid = new CGameSquare * [numRows + 2];
	for (int r = 0; r < numRows + 2; r++)
		grid[r] = new CGameSquare[numCols + 2];
	FillIn  ();
	PlaceMe ();
	skillRow = myRow;
	skillCol = myCol;
	state = 0;
	score = 0;
	elapsedTime = 0;
	elapsedSkillTime = DEFAULT_COOLDOWN;
	lastDirectionMoved = 'x';
	animationOn = false;
	finished = 0;
	thisRect = CRect (0,0,0,0);
	*savedGame = *this;
}

/*********************************************************************
* Function: void CGame::Instructions (CFrameWnd * windowP)           *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function will display the backstory and          *
*              instructions for the game on a separate pop-up        *
*              window.                                               *
*********************************************************************/

void CGame::Instructions (CFrameWnd * windowP)
{
	CString message = "The Tenno Artifacts\n\n";
	message += "Tenno! The balance has shifted. Artifacts have begun appearing that\n"
		"resemble the polarities displayed by the schools of the Tenno.\n"
		"As a result, the solar system is being plunged into chaos. Opposing\n"
		"factions have been displaying extremely hostile behaviors since the\n"
		"appearance of these artifacts.\n\n"
		"Your task is to realign these artifacts through a simulation. Proper\n"
		"re-alignment will spark a reaction, causing the artifacts to disintegrate.\n"
		"Since direct contact with these objects can damage one's body, I have\n"
		"devised a method that allows one to move a pseudo-artifact in order to\n"
		"manipulate nearby objects.\n\n"
		"Use the W, A, S, and D keys on your console to move the pseudo-artifact up,\n"
		"left, down, and right. Doing so will allow you to swap your pseudo-artifact\n"
		"with the adjacent artifact. Try to align the artifacts in rows or columns of\n"
		"3 or more to get them to disintegrate. You will have 60 seconds to move the\n"
		"pseudo-artifact before it corrodes away completely. Try to match as many\n"
		"artifacts as you can before the pseudo-artifact fully corrodes. Your\n"
		"progress will be recorded as a score. Should you feel like trying again,\n"
		"you can press the N key to switch to a new template. If you want to\n"
		"re-attempt the same template, you can press the R key to try again.\n"
		"You can also press the I key to bring up this dialogue again. Lastly, you\n"
		"can disrupt these artifacts using your Transference Wave. Use the Q key to\n"
		"simulate the effects of the Transference Wave. Remember to first face in\n"
		"the direction you want your Transference Wave to extend.\n\n"
		"I have gathered other Tenno to aid us in this mission. It's up to you now\n"
		"to restore balance to the solar system.\n\n"
		"[Use W, A, S, or D to move; N = New Template; R = Restart Current Template]\n"
		"[I = Show This Dialogue; Q = Transference Wave]\n\n"
		"(All images, concepts, and most audio belong to Digital Extremes)\n";
	CString title = "[TRANSMISSION FROM THE LOTUS]";
	windowP->MessageBox (message, title);
}

/*********************************************************************
* Function: void CGame::Display (CFrameWnd * windowP)                *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function acts as an intemediary function before  *
*              making a call to GameDisplay and DataDisplay. If this *
*              function is called for the first time, it also makes  *
*              a call to the function SetUp.                         *
*********************************************************************/

void CGame::Display (CFrameWnd * windowP)
{
	CPaintDC dc (windowP);
	CRect rect;
	windowP->GetClientRect (&rect);
	if (rect != thisRect)
		SetUp (rect);
	CDC memDC;
	int res = memDC.CreateCompatibleDC(&dc);
	memDC.SelectObject(&bgImage);
	dc.TransparentBlt (0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, 1800, 880, SRCCOPY); 
	DeleteDC (memDC);
	
	dc.SetBkMode(TRANSPARENT);	
	CFont font;
	CString fontName = "Calibri";
	font.CreatePointFont(rect.Width() / 10, fontName, &dc);
	CFont* def_font = dc.SelectObject(&font);
	COLORREF def_color = dc.SetTextColor (RGB (212, 175, 55));
	GameDisplay(&dc);
	DataDisplay(&dc);
	dc.SetTextColor (RGB (65, 105, 225));
	ButtonDisplay (&dc);
	dc.SelectObject(def_font);
	dc.SetTextColor(def_color);
}

/*********************************************************************
* Function: void CGame::SetUp (CRect rect)                           *
*                                                                    *
* Parameters: 1 CGame object, 1 CRect object                         *
* Return value: N/A                                                  *
* Description: This function will initialize the rectangles to be    *
*              displayed to the window. Some of these rectangles are *
*              the game board, the new button, and the restart       *
*              buttons. It also initializes the where variables in   *
*              the 2D CGameSquare array.                             *
*********************************************************************/

void CGame::SetUp (CRect rect)
{
	thisRect = rect;

	int halfW = rect.Width() / 2;
	int halfH = rect.Height() / 2;
	int thirdW = rect.Width() / 3;
	int thirdH = rect.Height() / 3;
	int fourthW = rect.Width() / 4;
	int fourthH = rect.Height() / 4;
	int sixthW = rect.Width() / 6;
	int sixthH = rect.Height() / 6;
	int eighthW = rect.Width() / 8;
	int eighthH = rect.Height() / 8;
	int twelfthW = rect.Width() / 12;
	int twelfthH = rect.Height() / 12;
	int twentyfourthW = rect.Width() / 24;
	int twentyfourthH = rect.Height() / 24;

	// Rectangle for the Game board
	gameRect = CRect(twentyfourthW, twentyfourthH, (twentyfourthW * 17), (twentyfourthH * 23));
	// Rectangle for the New button
	newButton = CRect((fourthW * 3), (twentyfourthH * 21), (sixthW * 5), (twentyfourthH * 23));
	// Rectangle for the Restart button
	restartButton = CRect((eighthW * 7), (twentyfourthH * 21), (twentyfourthW * 23), (twentyfourthH * 23));
	// Rectangle for the text "Score"
	scoreRect = CRect((fourthW * 3), (thirdH * 2), (sixthW * 5), (fourthH * 3));
	// Rectangle for the text "Time Left"
	timeRect = CRect((eighthW * 7), (thirdH * 2), (twentyfourthW * 23), (fourthH * 3));
	// Rectangle for the text "Transference Wave"
	skillRect = CRect((fourthW * 3), (twentyfourthH * 13), (eighthW * 7), (eighthH * 5));
	// Rectangle for the actual score
	dataRect1 = CRect((fourthW * 3), (fourthH * 3), (sixthW * 5), (sixthH * 5));
	// Rectangle for the actual number of moves left
	dataRect2 = CRect((eighthW * 7), (fourthH * 3), (twentyfourthW * 23), (sixthH * 5));
	// Rectangle for the cool down of Transference Wave
	dataRect3 = CRect((eighthW * 7), (twentyfourthH * 13), (twentyfourthW * 23), (eighthH * 5));

	int sqHeight = gameRect.Height() / numRows;
	int sqWidth = gameRect.Width() / numCols;
	int top = gameRect.top + (gameRect.Height() - sqHeight * numRows) / 2;
	int left = gameRect.left + (gameRect.Width() - sqWidth * numCols) / 2;
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid[r][c].SetWhere (CRect(left + (c-1)*sqWidth, top + (r-1)*sqHeight, left + (c)*sqWidth, top + (r)*sqHeight));
}

/*********************************************************************
* Function: void CGame::GameDisplay (CDC * deviceContextP)           *
*                                                                    *
* Parameters: 1 CGame object, 1 CDC object pointer                   *
* Return value: N/A                                                  *
* Description: This function call CGameSquare's Display function     *
*              with non-BORDER CGameSquare objects
*********************************************************************/

void CGame::GameDisplay (CDC * deviceContextP)
{
	deviceContextP->Rectangle(gameRect);
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid [r][c].Display (deviceContextP);
}

/*********************************************************************
* Function: void CGame::DataDisplay(CDC * deviceContextP)            *
*                                                                    *
* Parameters: 1 CGame object, 1 CDC object pointer                   *
* Return value: N/A                                                  *
* Description: This function updates the region of the window where  *
*              the time left and the score are displayed.            *
*********************************************************************/

void CGame::DataDisplay(CDC * deviceContextP)
{
		char buffer1[50];
		deviceContextP->DrawText(CString("Score"), scoreRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		sprintf_s(buffer1, "%d", score);
		deviceContextP->DrawText(CString(buffer1), dataRect1, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		char buffer2[50];
		deviceContextP->DrawText(CString("Time Left"), timeRect, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		sprintf_s(buffer2, "%d", (DEFAULT_TIME - elapsedTime));
		deviceContextP->DrawText(CString(buffer2), dataRect2, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		char buffer3[50];
		deviceContextP->DrawText(CString("Transference Wave"), skillRect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
		sprintf_s(buffer3, "Cooldown: %d", (DEFAULT_COOLDOWN - elapsedSkillTime));
		if (elapsedSkillTime >= DEFAULT_COOLDOWN)
			deviceContextP->DrawText(CString("Press Q"), dataRect3, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		else
			deviceContextP->DrawText(CString(buffer3), dataRect3, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

/*********************************************************************
* Function: void CGame::ButtonDisplay (CDC * deviceContextP)         *
*                                                                    *
* Parameters: 1 CGame object, 1 CDC object pointer                   *
* Return value: N/A                                                  *
* Description: This function is responsible for displaying the New   *
*              and Restart buttons.                                  *
*********************************************************************/

void CGame::ButtonDisplay (CDC * deviceContextP)
{
	CPoint corner1 = CPoint (newButton.Width() / 50, newButton.Height() / 50);
	deviceContextP->RoundRect (newButton, corner1);
	deviceContextP->DrawText(CString ("New"), newButton, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
	CPoint corner2 = CPoint(restartButton.Width() / 50, restartButton.Height() / 50);
	deviceContextP->RoundRect(restartButton, corner2);
	deviceContextP->DrawText(CString("Restart"), restartButton, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

/*********************************************************************
* Function: void CGame::Click (int y, int x, CFrameWnd * windowP)    *
*                                                                    *
* Parameters: 1 CGame object, 2 integers, 1 CFrameWnd object pointer *
* Return value: N/A                                                  *
* Description: This function processes whether a user has clicked    *
*              either the New button or the Restart button. It will  *
*              then create a new template or restart the current     *
*              template as necessary.                                *
*********************************************************************/

void CGame::Click (int y, int x, CFrameWnd * windowP)
{
	if (newButton.PtInRect(CPoint (x, y)))
	{
		Init (numRows, numCols);
		windowP->SetTimer (1, 1000, NULL);
		windowP->Invalidate(true);
	}
	if (restartButton.PtInRect(CPoint(x, y)))
	{
		*this = *savedGame;
		windowP->SetTimer(1, 1000, NULL);
		windowP->Invalidate(true);
	}
}

/*********************************************************************
* Function: void CGame::Move(char direction, CFrameWnd * windowP)    *
*                                                                    *
* Parameters: 1 CGame object, 1 character, 1 CFrameWnd object pointer*
* Return value: N/A                                                  *
* Description: This function will process whether the "Me"           *
*              CGameSquare will move either up, left, down, or right.*
*              It also verifies that a move is valid and that the    *
*              "Me" doesn't go off and swap with a BORDER.           *
*********************************************************************/

void CGame::Move(char direction, CFrameWnd * windowP)
{
	CString LOAD = "open\"TennoArtifactsMOV.mp3\" type mpegvideo";
	CString PLAY = "play TennoArtifactsMOV.mp3 from 100";
	mciSendString(LOAD, NULL, 0, 0);
	if (finished)
		return;
	int row = myRow;
	int col = myCol;
	switch (direction)
	{
	case 'a': // Move "Me" Left
		if (grid[row][col - 1].what != BORDER)
		{
			--col;
			lastDirectionMoved = 'a';
		}
		break;
	case 'w': // Move "Me" Up
		if (grid[row - 1][col].what != BORDER)
		{
			--row;
			lastDirectionMoved = 'w';
		}
		break;
	case 'd': // Move "Me" Right
		if (grid[row][col + 1].what != BORDER)
		{
			++col;
			lastDirectionMoved = 'd';
		}
		break;
	case 's': // Move "Me" Down
		if (grid[row + 1][col].what != BORDER)
		{
			++row;
			lastDirectionMoved = 's';
		}
		break;
	}
	if (row != myRow || col != myCol)
	{
		grid[myRow][myCol].Swap(grid[row][col], windowP);
		mciSendString(CString("stop TennoArtifactsMOV.mp3"), NULL, 0, 0);
		mciSendString(PLAY, NULL, 0, 0);
		myRow = row;
		myCol = col;
		if (!animationOn)
		{
			skillRow = row;
			skillCol = col;
		}
		windowP->InvalidateRect(dataRect1);
		windowP->InvalidateRect(dataRect2);
		if (elapsedTime == DEFAULT_TIME)
			finished = true;
		if (state == 0)
		{
			state = 1;
			TimerEvaluateAndUpdate(windowP);
		}
	}
}

/*********************************************************************
* Function: void CGame::KeyDown(char key, CFrameWnd * windowP)       *
*                                                                    *
* Parameters: 1 CGame object, 1 character, 1 CFrameWnd object pointer*
* Return value: N/A                                                  *
* Description: This function will process a key pressed by the user  *
*              that is not W, A, S, or D. Specifically, it will      *
*              only processes key presses that are I, N, or R.       *
*********************************************************************/

void CGame::KeyDown(char key, CFrameWnd * windowP)
{
	switch(key)
	{
	case 'i':
		Instructions(windowP);
		break;
	case 'n':
		Init(numRows, numCols);
		windowP->SetTimer(1, 1000, NULL);
		windowP->Invalidate(true);
		break;
	case 'r':
		*this = *savedGame;
		windowP->SetTimer(1, 1000, NULL);
		windowP->Invalidate(true);
		break;
	case 'q':
		if (elapsedSkillTime >= DEFAULT_COOLDOWN)
		{
			TransferenceWave(windowP);
			elapsedSkillTime = 0;
			windowP->SetTimer(2, 1000, NULL);
			windowP->InvalidateRect(dataRect3);
		}
	}
}

/*********************************************************************
* Function: void CGame::Message(CFrameWnd * windowP)                 *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function displays a message at the end of the    *
*              game once the time limit has been reached. Incldued   *
*              in the message is the score accumulated for the past  *
*              round.                                                *
*********************************************************************/

void CGame::Message(CFrameWnd * windowP)
{
	char buffer[100];
	sprintf_s(buffer, "You've accumulated a score of %d.\n\n", score);
	CString message = CString(buffer) + "The simulation has ended. Thank you for your\n"
		"contributions, Tenno.";
	CString title = "[SIMULATION OVER]";
	windowP->KillTimer(1);
	windowP->MessageBox(message, title);
}

/*********************************************************************
* Function: void CGame::UpdateTime(CFrameWnd * windowP)              *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function will add 1 second to the elapsedTime    *
*              variable. It will also stop the game once a certain   *
*              time limit has been reached.                          *
*********************************************************************/

void CGame::UpdateTime(CFrameWnd * windowP, int whichTimer)
{
	if (whichTimer == 1)
	{
		if (elapsedTime < DEFAULT_TIME)
		{
			++elapsedTime;
			windowP->InvalidateRect(dataRect2);
		}
		if (elapsedTime >= DEFAULT_TIME)
		{
			state = 1;
			finished = true;
			TimerEvaluateAndUpdate(windowP);
		}
	}
	else if (whichTimer == 2)
	{
		++elapsedSkillTime;
		windowP->InvalidateRect(dataRect3);
		windowP->SetTimer(2, 1000, NULL);
	}
}

/*********************************************************************
* Function: void CGame::FillIn()                                     *
*                                                                    *
* Parameters: 1 CGame object                                         *
* Return value: N/A                                                  *
* Description: This function is an intermediary function which calls *
*              CGame's Fill function, but only for non-BORDER        *
*              CGameSquare objects.                                  *
*********************************************************************/

void CGame::FillIn()
{
	for (int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			grid[r][c].Fill();
}

/*********************************************************************
* Function: void CGame::PlaceMe()                                    *
*                                                                    *
* Parameters: 1 CGame object                                         *
* Return value: N/A                                                  *
* Description: This function will assign one of the CGameSquare      *
*              objects in the grid as the "Me" CGameSquare. The "Me" *
*              CGameSquare is the one that is controlled by the user.*
*********************************************************************/

void CGame::PlaceMe()
{
	myRow = numRows / 2;
	myCol = numCols / 2;
	grid[myRow][myCol].what = ME;
	grid[myRow][myCol].whichSymbol = 0;
	grid[myRow][myCol].matched = false;
}
/*********************************************************************
* Function: int CGame::FindMatches(CFrameWnd * windowP)              *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: An integer                                           *
* Description: This function will check the grid of CGameSquare      *
*              to see if any classify as a "match" (as in, lined up  *
*              in a row or column of 3 or more). As it validates     *
*              whether or not a CGameSquare object is a match, it    *
*              also counts the total number of matches found. This   *
*              is used to calculate the score.                       *
*********************************************************************/

int CGame::FindMatches(CFrameWnd * windowP)
{
	// Check for horizontal matches
	int matchesFound = 0;
	for (int r = 1; r <= numRows; r++)
		for (int c = 2; c < numCols; c++)
			if ((grid[r][c].whichSymbol == grid[r][c - 1].whichSymbol) &&
				(grid[r][c].whichSymbol == grid[r][c + 1].whichSymbol))
			{
				if (grid[r][c].matched || grid[r][c - 1].matched || grid[r][c + 1].matched)
				{
					if (grid[r][c].matched)
						--matchesFound;
					if (grid[r][c - 1].matched)
						--matchesFound;
					if (grid[r][c + 1].matched)
						--matchesFound;
				}
				grid[r][c].matched = true;
				grid[r][c - 1].matched = true;
				grid[r][c + 1].matched = true;
				matchesFound += 3;
			}
	// Check for vertical matches
	for (int c = 1; c <= numCols; c++)
		for (int r = 2; r < numRows; r++)
			if ((grid[r][c].whichSymbol == grid[r - 1][c].whichSymbol) &&
				(grid[r][c].whichSymbol == grid[r + 1][c].whichSymbol))
			{
				if (grid[r][c].matched || grid[r - 1][c].matched || grid[r + 1][c].matched)
				{
					if (grid[r][c].matched)
						--matchesFound;
					if (grid[r - 1][c].matched)
						--matchesFound;
					if (grid[r + 1][c].matched)
						--matchesFound;
				}
				grid[r][c].matched = true;
				grid[r - 1][c].matched = true;
				grid[r + 1][c].matched = true;
				matchesFound += 3;
			}
	return matchesFound;
}

/*********************************************************************
* Function: void CGame::RemoveMatches (CFrameWnd * windowP)          *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function checks the CGameSquare grid for         *
*              CGameSquare objects that were matched by FindMatches. *
*              It sets the matched CGameSquare objects to EMPTY.     *
*********************************************************************/

void CGame::RemoveMatches (CFrameWnd * windowP)
{	
	for(int r = 1; r <= numRows; r++)
		for(int c = 1; c <= numCols; c++)
			if (grid[r][c].matched == true)
			{
				grid[r][c].matched = false;
				grid[r][c].what = EMPTY;
			}
}

/*********************************************************************
* Function: void CGame::UpdateGrid (int row, int col                 *
*                                   CFrameWnd * windowP)             *
*                                                                    *
* Parameters: 1 CGame object, 2 integers, 1 CFrameWnd object pointer *
* Return value: N/A                                                  *
* Description: This function will convert all EMPTY CGameSquare      *
*              objects back into SYMBOLS and assign them a new       *
*              symbol. This function also re-draws the region on the *
*              window where the CGameSquare object resides.          *
*********************************************************************/

void CGame::UpdateGrid (int row, int col, CFrameWnd * windowP)
{
	for(int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
			if (grid[r][c].what == EMPTY)
			{
				grid[r][c].whichSymbol = ((rand() % 5) + 1);
				grid[r][c].what = SYMBOL;
				windowP->InvalidateRect(grid[r][c].where);
			}
}

/*********************************************************************
* Function: void CGame::DarkenMatches(CFrameWnd * windowP)           *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function simply turns all matched CGameSquare    *
*              objects dark while a sound effect is played.          *
*********************************************************************/

void CGame::DarkenMatches(CFrameWnd * windowP)
{
	for(int r = 1; r <= numRows; r++)
		for (int c = 1; c <= numCols; c++)
		{
			if (grid[r][c].matched == true)
			{
				if (grid[r][c].whichSymbol == 1)
					grid[r][c].whichSymbol = 6;
				else if (grid[r][c].whichSymbol == 2)
					grid[r][c].whichSymbol = 7;
				else if (grid[r][c].whichSymbol == 3)
					grid[r][c].whichSymbol = 8;
				else if (grid[r][c].whichSymbol == 4)
					grid[r][c].whichSymbol = 9;
				else if (grid[r][c].whichSymbol == 5)
					grid[r][c].whichSymbol = 10;
				windowP->InvalidateRect(grid[r][c].where);
			}
		}
}

/*********************************************************************
* Function: void CGame::TransferenceWave(CFrameWnd * windowP)        *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: N/A                                                  *
* Description: This function implements the "Transference Wave"      *
*              ability, which allows the user to clear out a row     *
*              or columnfrom the "Me" CGameSquare to the BORDER. The *
*              direction of the row or column that is cleared is     *
*              determined by the last direction the user moved right *
*              before activating this ability.                       *
*********************************************************************/

void CGame::TransferenceWave(CFrameWnd * windowP)
{
	CString LOAD = "open\"TennoArtifactsTWS.mp3\" type mpegvideo";
	CString PLAY = "play TennoArtifactsTWS.mp3 from 80";
	mciSendString(LOAD, NULL, 0, 0);
	mciSendString(CString("stop TennoArtifactsTWS.mp3"), NULL, 0, 0);
	mciSendString(PLAY, NULL, 0, 0);
	if (!animationOn)
	{
		animationDirection = lastDirectionMoved;
		animationOn = true;
	}
	switch (animationDirection)
	{
	case 'a':
		while (grid[skillRow][skillCol + 1].what != BORDER)
		{
			--skillCol;
			grid[skillRow][skillCol].whichSymbol = ((rand() % 5) + 1);
			score += 2;
			windowP->InvalidateRect(dataRect1);
			windowP->InvalidateRect(grid[skillRow][skillCol].where);
			if (grid[skillRow][skillCol - 1].what != BORDER)
				windowP->SetTimer(3, 75, NULL);
			else
				break;
			return;
		}
		break;
	case 'w':
		while (grid[skillRow - 1][skillCol].what != BORDER)
		{
			--skillRow;
			grid[skillRow][skillCol].whichSymbol = ((rand() % 5) + 1);
			score += 2;
			windowP->InvalidateRect(dataRect1);
			windowP->InvalidateRect(grid[skillRow][skillCol].where);
			if (grid[skillRow - 1][skillCol].what != BORDER)
				windowP->SetTimer(3, 75, NULL);
			else
				break;
			return;
		}
		break;
	case 's':
		while (grid[skillRow + 1][skillCol].what != BORDER)
		{
			++skillRow;
			grid[skillRow][skillCol].whichSymbol = ((rand() % 5) + 1);
			score += 2;
			windowP->InvalidateRect(dataRect1);
			windowP->InvalidateRect(grid[skillRow][skillCol].where);
			if (grid[skillRow + 1][skillCol].what != BORDER)
				windowP->SetTimer(3, 75, NULL);
			else
				break;
			return;
		}
		break;
	case 'd':
		while (grid[skillRow][skillCol - 1].what != BORDER)
		{
			++skillCol;
			grid[skillRow][skillCol].whichSymbol = ((rand() % 5) + 1);
			score += 2;
			windowP->InvalidateRect(dataRect1);
			windowP->InvalidateRect(grid[skillRow][skillCol].where);
			if (grid[skillRow][skillCol + 1].what != BORDER)
				windowP->SetTimer(3, 75, NULL);
			else
				break;
			return;
		}
		break;
	}
	windowP->KillTimer(3);
	animationOn = false;
	skillRow = myRow;
	skillCol = myCol;
}

/*********************************************************************
* Function: int CGame::TimerEvaluateAndUpdate (CFrameWnd * windowP)  *
*                                                                    *
* Parameters: 1 CGame object, 1 CFrameWnd object pointer             *
* Return value: An integer                                           *
* Description: This function will drive the application through its  *
*              different "states," as determined by the state        *
*              variable. The state starts off at 0 until a move is   *
*              made that leads to a match. The function then makes   *
*              several other functions to validate the matched       *
*              CGameSquare objects, update the score, re-draw the    *
*              previously matched CGameSquare objects with new       *
*              symbols, and repeat the process for any new matched   *
*              CGameSquare objects. Once there are no more matches to*
*              be made, the state is set back to 0 and the program   *
*              waits again for more user input.                      *
*********************************************************************/

int CGame::TimerEvaluateAndUpdate (CFrameWnd * windowP)
{
	int matchesFound = 0;
	static int row, col;
	CString LOAD = "open\"TennoArtifactsMAT.mp3\" type mpegvideo";
	CString PLAY = "play TennoArtifactsMAT.mp3 from 100";
	mciSendString(LOAD, NULL, 0, 0);
	switch (state)
	{
	case 1:
		matchesFound = FindMatches (windowP);
		if (matchesFound == 0)
		{
			state = 0;
			if (finished)
			{
				Message(windowP);
				*this = *savedGame;
				windowP->SetTimer(1, 1000, NULL);
				windowP->Invalidate(true);
			}
			return 0;
		}
		mciSendString(CString("stop TennoArtifactsMAT.mp3"), NULL, 0, 0);
		mciSendString(PLAY, NULL, 0, 0);
		score += (matchesFound * DEFAULT_VALUE);
		windowP->InvalidateRect (dataRect1);
		state = 2;
		windowP->SetTimer(4, 100, NULL);
		break;
	case 2:
		DarkenMatches(windowP);
		state = 3;
		break;
	case 3:
		RemoveMatches (windowP);
		state = 4;
		break;
	case 4:
		UpdateGrid (row, col, windowP);
		state = 5;
		break;
	case 5:
		matchesFound = FindMatches (windowP);
		if (matchesFound == 0)
		{
			state = 0;
			windowP->KillTimer(3);
			if (finished)
			{
				Message(windowP);
				*this = *savedGame;
				windowP->SetTimer(1, 1000, NULL);
				windowP->Invalidate(true);
			}
			return 0;
		}
		mciSendString(CString("stop TennoArtifactsMAT.mp3"), NULL, 0, 0);
		mciSendString(PLAY, NULL, 0, 0);
		score += (matchesFound * DEFAULT_VALUE);
		windowP->InvalidateRect (dataRect1);
		state = 2;
		break;
	}
	return 0;
}
