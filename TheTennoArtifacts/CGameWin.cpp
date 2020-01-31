/*********************************************************************
* Assignment: Project 3 - GUI Move and Match Game                    *
* Author: Marc Baello                                                *
* Date: Fall 2017                                                    *
* File: CGameWin.cpp                                                 *
*                                                                    *
* Description: This file contains the implementations for the        *
*              CGameWin class.                                       *
*********************************************************************/

#include <afxwin.h>
#include <mmsystem.h>
#include "CGameWin.h"


/*********************************************************************
* Function: CGameWin::CGameWin ()                                    *
*                                                                    *
* Parameters: 1 CGameWin object                                      *
* Return value: N/A                                                  *
* Description: This function is the default constructor for the      *
*              CGameWin class.                                       *
*********************************************************************/

CGameWin::CGameWin ()
{
	CString WindowTitle = "The Tenno Artifacts";
	Create (NULL, WindowTitle);
	firstTime = true;
}

/*********************************************************************
* Function: afx_msg void CGameWin::OnPaint ()                        *
*                                                                    *
* Parameters: 1 CGameWin object                                      *
* Return value: N/A                                                  *
* Description: This function will update the board visually by       *
*              making a call to CGame's Display. If this is the time *
*              OnPaint is called, the instructions for the game will *
*              be displayed.                                         *
*********************************************************************/

afx_msg void CGameWin::OnPaint ()
{
	myCGame.Display(this);
	if (firstTime)
	{
		myCGame.Instructions(this);
		firstTime = false;
		SetTimer (1, 1000, NULL);
	}
}

/*********************************************************************
* Function: afx_msg void CGameWin::OnLButtonDown( UINT nFlags,       *
*                                                 CPoint point )     *
*                                                                    *
* Parameters: 1 CGameWin object, 1 unsigned integer, 1 CPoint object *
* Return value: N/A                                                  *
* Description: This function calls CGame's Click function when it    *
*              detects a left-click from the user. It will pass the  *
*              coordinates of the point that the user clicked.       *
*********************************************************************/

afx_msg void CGameWin::OnLButtonDown( UINT nFlags, CPoint point )
{
	myCGame.Click (point.y, point.x, this);
}

/*********************************************************************
* Function: afx_msg void CGameWin::OnKeyDown (UINT achar,            *
*                                             UINT repeat,           *  
*                                             UINT flags)            *
*                                                                    *
* Parameters: 1 CGameWin object, 3 unsigned integers                 *
* Return value: N/A                                                  *
* Description: This function calls CGame's Move function when it     *
*              detects that the user has pressed W, A, S, or D.      *
*              Similarly, it makes a call to KeyDown if any other    *
*              keyboard character is pressed.                        *
*********************************************************************/

afx_msg void CGameWin::OnKeyDown (UINT achar, UINT repeat, UINT flags)
{
	switch(achar)
    {
		case VK_LEFT: case 'A':
			myCGame.Move ('a', this);
			break;
		case VK_RIGHT: case 'D':
			myCGame.Move ('d', this);
			break;
		case VK_UP: case 'W':
			myCGame.Move ('w', this);
			break;
		case VK_DOWN: case 'S':
			myCGame.Move ('s', this);
			break;
		default:
			myCGame.KeyDown(tolower(achar), this);
	}
}

/*********************************************************************
* Function: afx_msg void CGameWin::OnTimer (UINT nIDEvent)           *
*                                                                    *
* Parameters: 1 CGameWin object, 1 unsigned integer                  *
* Return value: N/A                                                  *
* Description: This function calls UpdateTime every second which     *
*              updates a variable in the CGame class called          *
*              elapsedTime.                                          *
*********************************************************************/

afx_msg void CGameWin::OnTimer (UINT nIDEvent)
{	
	if (nIDEvent == 1)
		myCGame.UpdateTime (this, 1);  
	if (nIDEvent == 2)
		myCGame.UpdateTime (this, 2);
	if (nIDEvent == 3)
		myCGame.TransferenceWave (this);
	if (nIDEvent == 4)
		myCGame.TimerEvaluateAndUpdate(this);
}

afx_msg BOOL CGameWin::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

/*********************************************************************
* Function: MESSAGE_MAP                                              *
*                                                                    *
* Parameters: 1 CGameWin object, 1 CFrameWnd object                  *
* Return value: N/A                                                  *
* Description: This function is responsible for the detection of     *
*              keyboard presses and mouse clicks from the user.      *
*              Depending on the type of input it receives, it will   *
*              call a particular function.                           *
*********************************************************************/

BEGIN_MESSAGE_MAP (CGameWin, CFrameWnd)
	ON_WM_PAINT ()
	ON_WM_ERASEBKGND ()
	ON_WM_LBUTTONDOWN ()
	ON_WM_KEYDOWN ()
	ON_WM_TIMER ()
END_MESSAGE_MAP ()
