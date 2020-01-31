/*********************************************************************
* Assignment: Project 3 - GUI Move and Match Game                    *
* Author: Marc Baello                                                *
* Date: Fall 2017                                                    *
* File: CGameApp.h                                                   *
*                                                                    *
* Description: This file contains the prototypes for the CGameApp    *
*              class.                                                *
*********************************************************************/
#include <afxwin.h>
#include <mmsystem.h>
#include "CGameWin.h"

/*********************************************************************
* Class: CGameApp                                                    *
*                                                                    *
* Description: This class is designed to display the main window and *
*              extract RCDATA embedded in the executable.            *
*********************************************************************/

class CGameApp : public CWinApp
{
	public:
		BOOL InitInstance ();
		void ExtractAudio(CString fileName, int reference);
};
