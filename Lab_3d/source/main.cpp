#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")


#include <stdio.h>
#include <random>
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
      /*case IDC_BUTTON1:
        y = (x + y) / 2 - 1;
        wsprintf(buffer, "%d", rand());
        SetWindowText(hwndText, buffer);

        return TRUE;*/

      }

    }

  case WM_SIZE: {
    int width = LOWORD(lParam);
    int height = HIWORD(lParam);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / height, 0.1, 1000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity;
  }


  case WM_PAINT:
    /*
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


    ReleaseDC(hwndDig, hDC); // Zwolnienie kontekstu urz¹dzenia */
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

void Axis(float a=10.0) {


  glBegin(GL_LINES);

  glColor3f(0, 0, 0);
  glVertex3f(+a, 0, 0);
  glVertex3f(-a, 0, 0);

  glVertex3f(0, +a, 0);
  glVertex3f(0, -a, 0);

  glVertex3f(0, 0, +a);
  glVertex3f(0, 0, -a);
  glEnd();
}

void Cube(float a = 1.0) {

 float b = a / 2.0;
  glBegin(GL_TRIANGLES);
  glColor3f(0.5, 0.5, 0);
 
  glVertex3f(-b, -b, -b);
  glVertex3f(-b, -b, +b);
  glVertex3f(-b, +b, +b);

  glVertex3f(-b, -b, -b);
  glVertex3f(-b, +b, -b);
  glVertex3f(-b, +b, +b);

  glVertex3f(+b, -b, -b);
  glVertex3f(+b, -b, +b);
  glVertex3f(+b, +b, +b);
             
  glVertex3f(+b, -b, -b);
  glVertex3f(+b, +b, -b);
  glVertex3f(+b, +b, +b);



  glVertex3f(-b, -b, -b);
  glVertex3f(-b, -b, +b);
  glVertex3f(+b, -b, +b);

  glVertex3f(-b, -b, -b);
  glVertex3f(+b, -b, -b);
  glVertex3f(+b, -b, +b);

  glVertex3f(-b, +b, -b);
  glVertex3f(-b, +b, +b);
  glVertex3f(+b, +b, +b);

  glVertex3f(-b, +b, -b);
  glVertex3f(+b, +b, -b);
  glVertex3f(+b, +b, +b);



  glVertex3f(-b, -b, -b );
  glVertex3f(-b, +b, -b );
  glVertex3f(+b, +b, -b );

  glVertex3f(-b, -b, -b );
  glVertex3f(+b, -b, -b );
  glVertex3f(+b, +b, -b );

  glVertex3f(-b, -b, +b );
  glVertex3f(-b, +b, +b );
  glVertex3f(+b, +b, +b );

  glVertex3f(-b, -b, +b );
  glVertex3f(+b, -b, +b );
  glVertex3f(+b, +b,+ b );
  
  glEnd();

}


void DrawScene() {
  glClearColor(1.0,0.9,0.8,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
  glTranslatef(-2,-2,-10.0);

  Axis(10.0);


  static float fangle = 0.0;
  fangle += 0.01;
  glRotatef(fangle, 0, 1, 1);

  Axis(10.0);
  Cube(2);
  glBegin(GL_LINES);
  glColor3f(1, 0, 0);

  glVertex3f(+1.01, +1.01, -1.01);
  glVertex3f(-1.01, +1.01, +1.01);
                             
  glVertex3f(-1.01, +1.01, +1.01);
  glVertex3f(+1.01, -1.01, +1.01);
               
  glVertex3f(+1.01, -1.01, +1.01);
  glVertex3f(+1.01, +1.01, -1.01);

  glEnd();

  glBegin(GL_LINES);
  glColor3f(0, 0, 1);

  glVertex3f(1, -1, -1);
  glVertex3f(-1, 1, -1);

  glVertex3f(-1, 1, -1);
  glVertex3f(-1, -1, 1);

  glVertex3f(-1, -1, 1);
  glVertex3f(1, -1, -1);

  glEnd();

  
  
}








int WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
  x = 1, y = 1000;
  HWND hwndMainWindow = CreateDialog(histance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  hwndText = GetDlgItem(hwndMainWindow, IDC_BUTTON1);
  
  static PIXELFORMATDESCRIPTOR pfd=
  {
    sizeof(PIXELFORMATDESCRIPTOR),
    1,
    PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
    PFD_TYPE_RGBA,
    16,
    0,0,0,0,0,0,
    0,0,
    0,0,0,0,0,
    16,
    0,0,
    PFD_MAIN_PLANE,
    0,
    0,0,0
  };
  
  HDC hDC = GetDC(hwndMainWindow);
  GLuint PixelFormat = ChoosePixelFormat(hDC, &pfd);
  SetPixelFormat(hDC, PixelFormat, &pfd);
  
  HGLRC hRC = wglCreateContext(hDC);
  wglMakeCurrent(hDC, hRC);

  ShowWindow(hwndMainWindow, iCmdShow);
  hinst = histance;

  MSG msg = {};
  bool done = false;
  while (!done) {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) { //sprawdzanie czy jest komunikat
      if (msg.message == WM_QUIT) done = true;
      TranslateMessage(&msg);                           
      DispatchMessage(&msg);

    }
    else {
      //Rysuj
      DrawScene();
      SwapBuffers(hDC);

    }

  }



  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(hRC);
  ReleaseDC(hwndMainWindow, hDC);
  


  return 0;
}