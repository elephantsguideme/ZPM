#include <Windows.h>
#include <stdio.h>
#include "res.h"

INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM IParam)
{
	//INT x, y;
	//CHAR buffer[50];
  switch (uMsg)
  {
	/*
  case WM_CREATE:
	   x = 1, y = 1000;
	  
	  wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
	  MessageBox(0, buffer, "Pytanie", MB_OK);
	  return FALSE;
	  */
  case WM_COMMAND:
	  switch (HIWORD(wParam)) {
	  case BN_CLICKED:
		  switch (LOWORD(wParam))
		  {
		  case IDC_BUTTON1:
			 // y = (x + y) / 2 - 1;
			//wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
			 // MessageBox(0, buffer, "Pytanie", MB_OK);

			  return TRUE;
		  case IDC_BUTTON2:

			  return TRUE;
		  case IDC_BUTTON3:
			 // x = (x + y) / 2 + 1;
			 // wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
			//  MessageBox(0, buffer, "Pytanie", MB_OK);

			  return TRUE;
		  }

	  }

  case WM_LBUTTONDOWN:
	  CHAR szText[100];
	  wsprintf(szText, "Kliknales punkt x=%d, y=%d", LOWORD(IParam), HIWORD(IParam));
	  MessageBox(hwndDig, szText, TEXT("Klikniecie"), MB_OK);
	  return TRUE;
  case WM_CLOSE:
    DestroyWindow(hwndDig);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}


  int WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
  {
    HWND hwndMainWindow = CreateDialog(histance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
    ShowWindow(hwndMainWindow, iCmdShow);

	
   

    

    
   
    return 0;
  }

