/*********************************************************************
* Assignment: Project 3 - GUI Move and Match Game                    *
* Author: Marc Baello                                                *
* Date: Fall 2017                                                    *
* File: CGameWin.h                                                   *
*                                                                    *
* Description: This file contains the prototypes for the CGameWin    *
*              class.                                                *
*********************************************************************/

#include <afxwin.h>
#include <mmsystem.h>
#include "CGame.h"

/*********************************************************************
* Class: CGameWin                                                    *
*                                                                    *
* Description: This class is designed to process user input (from    *
*              the keyboard and from the house) and indirectly       *
*              initialize the window by calling CGame's Display      *
*              function through OnPaint.                             *
*********************************************************************/

class CGameWin : public CFrameWnd
{
	public:
		CGameWin ();
		afx_msg void OnPaint ();
		afx_msg void OnLButtonDown( UINT nFlags, CPoint point );
		afx_msg void OnKeyDown (UINT achar, UINT repeat, UINT flags);
		afx_msg void OnTimer (UINT nIDEvent);
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	private:
		CGame myCGame;
		bool firstTime;
		DECLARE_MESSAGE_MAP ()
};
