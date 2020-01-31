/*********************************************************************
* Assignment: Project 3 - GUI Move and Match Game                    *
* Author: Marc Baello                                                *
* Date: Fall 2017                                                    *
* File: CGameApp.cpp                                                 *
*                                                                    *
* Description: This file contains the implementations for the        *
*              CGameApp class.                                       *
*********************************************************************/

#include <afxwin.h>
#include <fstream>
#include <mmsystem.h>
#include "CGameApp.h"

/*********************************************************************
* Function: BOOL CGameApp::InitInstance ()                           *
*                                                                    *
* Parameters: 1 CGameApp object                                      *
* Return value: A boolean                                            *
* Description: This function will display a window during the        *
*              program's execution. The function also attempts to    *
*              open an MP3 file called BGM. BGM will loop until the  *
*              program's termination. This function also makes       *
*              several calls to ExtractAudio.                        *
*********************************************************************/

BOOL CGameApp::InitInstance ()
{
		// Extract audio to the directory of the executable
		ExtractAudio(CString("TennoArtifactsBGM.mp3"), 1);
		ExtractAudio(CString("TennoArtifactsMOV.mp3"), 2);
		ExtractAudio(CString("TennoArtifactsMAT.mp3"), 3);
		ExtractAudio(CString("TennoArtifactsTWS.mp3"), 4);
		m_pMainWnd = new CGameWin();
		CString LOAD = "open \"TennoArtifactsBGM.mp3\" type mpegvideo";
		CString PLAY = "play TennoArtifactsBGM.mp3 repeat from 0";
		mciSendString(LOAD, NULL, 0, 0);
		mciSendString(PLAY, NULL, 0, 0);
		m_pMainWnd->ShowWindow (m_nCmdShow);
		m_pMainWnd->UpdateWindow ();
		return TRUE;
}

/*********************************************************************
* Function: void CGameApp::ExtractAudio(CString fileName,            *
*                                       int reference)               *
*                                                                    *
* Parameters: 1 CGameApp object, 1 CString, 1 integer                *
* Return value: N/A                                                  *
* Description: This function extracts the data necessary for audio   *
*              playback in this program. The data embedded in the    *
*              program is RCDATA, but it will be extracted and       *
*              written to the same directory as the executable in an *
*              MP3 file format.                                      *
*********************************************************************/

void CGameApp::ExtractAudio(CString fileName, int reference)
{
	HMODULE handleModule = GetModuleHandle(NULL); // Handle for the executable file
	HRSRC handleResource = FindResource(handleModule, MAKEINTRESOURCE(reference), RT_RCDATA); // Locates the resource in the exe
	HGLOBAL handleMemory = LoadResource(handleModule, handleResource);
	DWORD dwSize = SizeofResource(handleModule, handleResource); // Gets the size of the resource
	LPVOID lpAddress = LockResource(handleMemory);
	//Create the file
	HANDLE file;
	file = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//Write to the file
	WriteFile(file, lpAddress, dwSize, 0, NULL);
	CloseHandle(file);
}

CGameApp APP;
