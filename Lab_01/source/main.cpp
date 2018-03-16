#include <Windows.h>
#include <stdio.h>
#include "res.h"

HWND hwndText;
CHAR buffer[100];
int x, y;
HINSTANCE hinst;
INT_PTR CALLBACK DialogProc(HWND hwndDig, UINT uMsg, WPARAM wParam, LPARAM lParam)
{





  switch (uMsg)
  {

  case WM_CREATE:

    return TRUE;

  case WM_COMMAND:
    switch (HIWORD(wParam)) {
    case BN_CLICKED:
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:
        y = (x + y) / 2 - 1;
        wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
        SetWindowText(hwndText, buffer);

        return TRUE;

      case IDC_BUTTON2:

        wsprintf(buffer, "Dzieki za gre!");
        SetWindowText(hwndText, buffer);

        wsprintf(buffer, "Gramy od nowa?");
        if (MessageBox(0, buffer, "Pytanie", MB_YESNO) == IDYES) {

          x = 1;
          y = 2000;
          wsprintf(buffer, "Wybierz liczbe z zakresu %d%%%d", x, y);
          MessageBox(0, buffer, "Na druga nozke", MB_OK);

          wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
          SetWindowText(hwndText, buffer);
        }
        else {
          wsprintf(buffer, "Do zobaczenia!");
          MessageBox(0, buffer, "Koniec", MB_OK);

          DestroyWindow(hwndDig);
          PostQuitMessage(0);
        }
        return TRUE;

      case IDC_BUTTON3:

        x = (x + y) / 2 + 1;
        wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
        SetWindowText(hwndText, buffer);
        return TRUE;
      }

    }

  case WM_PAINT:
    //Rysowanie okna
    HDC hDC; // uchwyt do kontekstu urz¹dzenia 
    hDC = GetDC(hwndDig); // pobranie uchwytu do kontekstu okna 
    //BitBlt(hDC, 0, 0, 800, 600, GetDC(0), 0, 0, SRCCOPY);  //GetDC(0) pobranie kontekstu       
                                                           //ekranu 

    HBITMAP hBitmap;
    hBitmap = LoadBitmap(hinst, MAKEINTRESOURCE(IDB_BITMAP1));
    HDC hDCBitmap;
    hDCBitmap = CreateCompatibleDC(hDC); //Utworzenie kopatybilengo kontekstu  
    SelectObject(hDCBitmap, hBitmap); //Wybranie bitmapy w kontekscie 
    BitBlt(hDC, 0, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY); 
    BitBlt(hDC, 100, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY);//Skopiowanie obrazu 
    BitBlt(hDC, 200, 0, 900, 400, hDCBitmap, 0, 0, SRCCOPY);
    DeleteDC(hDCBitmap); //Usuniecie kontekstu 
    DeleteObject(hBitmap);
    //SelectObject(hDC, GetStockObject(ANSI_VAR_FONT));    //Pobranie i aktywacja                   
                                                         //czcionki 
    //SetTextColor(hDC, RGB(255, 0, 0));                   //Ustawienie koloru 
    //TextOut(hDC, 0, 0, TEXT("Text output to client area."), 27);


    ReleaseDC(hwndDig, hDC); // Zwolnienie kontekstu urz¹dzenia 
    break;



  case WM_LBUTTONDOWN:
    /*
    CHAR szText[100];
    wsprintf(szText, "Kliknales punkt x=%d, y=%d", LOWORD(lParam), HIWORD(lParam));
    MessageBox(hwndDig, szText, TEXT("Klikniecie"), MB_OK);
    */
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
  x = 1, y = 1000;
  HWND hwndMainWindow = CreateDialog(histance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  hwndText = GetDlgItem(hwndMainWindow, IDC_BUTTON4);
  ShowWindow(hwndMainWindow, iCmdShow);
  hinst = histance;
  wsprintf(buffer, "Wybierz liczbe z zakresu %d%%%d", x, y);
  MessageBox(0, buffer, "Na poczatek", MB_OK);

  wsprintf(buffer, "Czy Twoja liczba to %d?", (x + y) / 2);
  SetWindowText(hwndText, buffer);


  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

  }


  /*
  char buffer[50];
  int t = 1, iRetKey;
  int n, x = 1, y=4;

  while (t) {
  n = sprintf_s(buffer, "> %d ?", (x+y)/2);
  iRetKey = MessageBox(0, buffer, "Aplikacja", MB_YESNO);
  if (iRetKey == IDYES) {
  x = (x + y) / 2 + 1;
  }
  else {
  y = (x + y)/ 2;
  }
  if (x == y) {
  t = 0;
  }
  }
  sprintf_s(buffer, "Twoja liczba to %d", x);
  MessageBox(0, buffer, "Aplikacja", MB_OK);
  */



  return 0;
}