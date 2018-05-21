#define GL_GLEXT_PROTOTYPES
#include <Windows.h>
#include <GL\glew.h>
#include <gl\GL.h>
#include <gl\GLU.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glew32.lib")

#include <stdio.h>
#include <random>
#include "res.h"

int iStartTime;

HWND hwndText;
CHAR buffer[100];
int x, y;
HINSTANCE hinst;

GLuint iMyTextureEye;
GLuint iMyTextureWings;
GLuint iMyTextureLegs;
GLuint iMyTextureBody;



unsigned char* pHighMap;
int iHighMapWidth;
int iHighMapHeight;


unsigned char* ReadBmpFromFile(char* szFileName, int &riWidth, int &riHeight)
{
  BITMAPFILEHEADER     bfh;
  BITMAPINFOHEADER     bih;

  int                i, j, h, v, lev, l, ls;
  unsigned char*     buff = NULL;

  unsigned char* p_palette = NULL;
  unsigned short n_colors = 0;

  unsigned char* pRGBBuffer=NULL;

  FILE* hfile;
  fopen_s(&hfile, szFileName, "rb");

  if (hfile != NULL)
  {
    fread(&bfh, sizeof(bfh), 1, hfile);
    if (!(bfh.bfType != 0x4d42 || (bfh.bfOffBits < (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)))))
    {
      fread(&bih, sizeof(bih), 1, hfile);
      v = bih.biWidth;
      h = bih.biHeight;
      lev = bih.biBitCount;

      riWidth = v;
      riHeight = h;
      pRGBBuffer = new unsigned char[riWidth*riHeight * 3]; //Zaalokowanie odpowiedniego buffora obrazu

                                                            //Za³aduj Palete barw jesli jest
      if ((lev == 1) || (lev == 4) || (lev == 8))
      {
        n_colors = 1 << lev;
        p_palette = new unsigned char[4 * n_colors];
        fread(p_palette, 4 * n_colors, 1, hfile);
      }

      fseek(hfile, bfh.bfOffBits, SEEK_SET);

      buff = new unsigned char[v * 4];

      switch (lev)
      {
      case 1:
        //Nie obs³ugiwane
        break;
      case 4:
        //nie Obs³ugiwane
        break;
      case 8: //Skala szaroœci
        ls = (v + 3) & 0xFFFFFFFC;
        for (j = (h - 1); j >= 0; j--)
        {
          fread(buff, ls, 1, hfile);
          for (i = 0, l = 0; i<v; i++)
          {
            pRGBBuffer[((j*riWidth) + i) * 3 + 2] = p_palette[(buff[i] << 2) + 2];//R
            pRGBBuffer[((j*riWidth) + i) * 3 + 1] = p_palette[(buff[i] << 2) + 1];//G
            pRGBBuffer[((j*riWidth) + i) * 3 + 0] = p_palette[(buff[i] << 2) + 0];//B
          }
        };
        break;
      case 24:
        //bitmapa RGB
        ls = (v * 3 + 3) & 0xFFFFFFFC;
        for (j = (h - 1); j >= 0; j--)
        {
          //x_fread(hfile,buff,ls);
          fread(buff, ls, 1, hfile);
          for (i = 0, l = 0; i<v; i++, l += 3)
          {
            pRGBBuffer[((j*riWidth) + i) * 3 + 0] = buff[l + 0];
            pRGBBuffer[((j*riWidth) + i) * 3 + 1] = buff[l + 1];
            pRGBBuffer[((j*riWidth) + i) * 3 + 2] = buff[l + 2];
          };
        };
        break;
      case 32:
        // RGBA bitmap 
        for (j = (h - 1); j >= 0; j--)
        {
          fread(buff, v * 4, 1, hfile);
          for (i = 0, l = 0; i<v; i++, l += 4)
          {
            pRGBBuffer[((j*riWidth) + i) * 3 + 0] = buff[l + 0];
            pRGBBuffer[((j*riWidth) + i) * 3 + 1] = buff[l + 1];
            pRGBBuffer[((j*riWidth) + i) * 3 + 2] = buff[l + 2];
          }
        };
        break;
      };
      delete buff;
      if (p_palette) delete p_palette;

    }
  }
  return pRGBBuffer;
}

void PrepareTextures() {
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &iMyTextureEye);
  glGenTextures(1, &iMyTextureBody);
  glGenTextures(1, &iMyTextureWings);
  glGenTextures(1, &iMyTextureLegs); 

  int iWidth, iHeigt;
  unsigned char* pBMPEye = ReadBmpFromFile("C:\\Users\\student\\Desktop\\Bartosz_Kopras_ME\\ZPM\\mucha_3d\\source\\eye1.bmp", iWidth, iHeigt); //najlepiej potegi dwojki
  glBindTexture(GL_TEXTURE_2D, iMyTextureEye);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeigt, 0, GL_RGBA, GL_UNSIGNED_BYTE, pBMPEye);
}


void PrepareHighMap(){

  pHighMap = ReadBmpFromFile("..\\source\\highmap1.bmp", iHighMapWidth, iHighMapHeight); 


}



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

void Box(float fa = 1.0, float fb = 1.0, float fc = 1.0, float fr=0.5, float fg=0.5, float fb2=0.5) {

  float a = fa / 2.0;
  float b = fb / 2.0;
  float c = fc / 2.0;
  glBegin(GL_TRIANGLES);
  glColor3f(fr, fg, fb);

  glVertex3f(-a, -b, -c);
  glVertex3f(-a, -b, +c);
  glVertex3f(-a, +b, +c);
              
  glVertex3f(-a, -b, -c);
  glVertex3f(-a, +b, -c);
  glVertex3f(-a, +b, +c);
              
  glVertex3f(+a, -b, -c);
  glVertex3f(+a, -b, +c);
  glVertex3f(+a, +b, +c);
             
  glVertex3f(+a, -b, -c);
  glVertex3f(+a, +b, -c);
  glVertex3f(+a, +b, +c);
           
              
  glVertex3f(-a, -b, -c);
  glVertex3f(-a, -b, +c);
  glVertex3f(+a, -b, +c);
            
  glVertex3f(-a, -b, -c);
  glVertex3f(+a, -b, -c);
  glVertex3f(+a, -b, +c);
            
  glVertex3f(-a, +b, -c);
  glVertex3f(-a, +b, +c);
  glVertex3f(+a, +b, +c);
           
  glVertex3f(-a, +b, -c);
  glVertex3f(+a, +b, -c);
  glVertex3f(+a, +b, +c);
          

  glVertex3f(-a, -b, -c);
  glVertex3f(-a, +b, -c);
  glVertex3f(+a, +b, -c);
             
  glVertex3f(-a, -b, -c);
  glVertex3f(+a, -b, -c);
  glVertex3f(+a, +b, -c);
             
  glVertex3f(-a, -b, +c);
  glVertex3f(-a, +b, +c);
  glVertex3f(+a, +b, +c);
            
  glVertex3f(-a, -b, +c);
  glVertex3f(+a, -b, +c);
  glVertex3f(+a, +b, +c);

  glEnd();

}

void Box2(float fa = 1.0, float fb = 1.0, float fc = 1.0) {

  float a = fa / 2.0;
  float b = fb / 2.0;
  float c = fc / 2.0;
  glBegin(GL_TRIANGLES);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-a, -b, +c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-a, +b, -c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(-a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(+a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(+a, -b, +c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(+a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(+a, +b, -c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-a, -b, +c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, -b, +c);


  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(+a, -b, -c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, -b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, +b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-a, +b, +c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, +b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(+a, +b, -c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-a, +b, -c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, -c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, -c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(+a, -b, -c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, -c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, +c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-a, +b, +c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, +c);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-a, -b, +c);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(+a, -b, +c);
  glTexCoord2f(1.0, 1.0);
  glVertex3f(+a, +b, +c);

  glEnd();

}


void DrawFly(float fSize=10.0) {
  glPushMatrix();
  glScalef(fSize, fSize, fSize);
  glPushMatrix();
  Box(1.5, 1.0, 2.0);//body
  

  glTranslatef(-1.5 / 2 + 1.5 / 3/2,//legs
              -1.0 / 2 - 1.0 / 3/2,
              -2.0 / 2 + 2.0 / 5 /2);
  Box(1.5/3, 1.0/3, 2.0/5, 0.2, 0.2, 0.2);
  glTranslatef(0,
    0,
    + 2* 2.0 / 5);
  Box(1.5 / 3, 1.0 / 3, 2.0 / 5, 0.2, 0.2, 0.2);
  glTranslatef(0,
    0,
    +2 * 2.0 / 5);
  Box(1.5 / 3, 1.0 / 3, 2.0 / 5, 0.2, 0.2, 0.2);

  glTranslatef(2* 1.5 / 3,
    0,
    0);
  Box(1.5 / 3, 1.0 / 3, 2.0 / 5, 0.2, 0.2, 0.2);
  glTranslatef(0,
    0,
    -2 * 2.0 / 5);
  Box(1.5 / 3, 1.0 / 3, 2.0 / 5, 0.2, 0.2, 0.2);
  glTranslatef(0,
    0,
   -2 * 2.0 / 5);
  Box(1.5 / 3, 1.0 / 3, 2.0 / 5, 0.2, 0.2, 0.2);

  glPopMatrix();
  glPushMatrix();
  
  //glAct();
 // glBindTexture(GL_TEXTURE_2D, iMyTextureEye);

  glTranslatef(-1.5 / 2 ,//eyes
    +1.0 / 2 + 1.0/2,
    -2.0 / 2 /2);
  Box(1.0 , 1.0, 1.0, 0.5, 0.2, 0.2);
 // Box2(1.0, 1.0, 1.0);

  glTranslatef( 1.5 ,//eyes
    0,
    0);
  Box(1.0, 1.0, 1.0, 0.5, 0.2, 0.2);

  float fWingAngle = 0.0;
  fWingAngle = 12 + 10 * sin((GetTickCount() - iStartTime) * 2 * 3.1416 / 1000);

  glPopMatrix(); //wings
  glPushMatrix();
  glTranslatef(-1.5/2,
    +1.0/2,
    0
  );
  glRotatef(-30.0, 0, 1.0, 0);
  glRotatef(-fWingAngle, 1.0, 0, 0);

  glTranslatef(0,
    0,
    +2.0/2.5);
  Box(1.4, 0.2, 2.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(+1.5 / 2,
    +1.0 / 2,
    0
  );
  glRotatef(+30.0, 0, 1.0, 0);
  glRotatef(-fWingAngle, 1.0, 0, 0);

  glTranslatef(0,
    0,
    +2.0 / 2.5);
  Box(1.4, 0.2, 2.5);
  glPopMatrix();

  glPopMatrix();
}

void DrawHighMap(float fSize) {

  glPushMatrix();

  glScalef(fSize, fSize, fSize);

  glBegin(GL_QUADS);
   glColor3f(0.02, 0.05, 0.02);
    for (int y = 0; y < iHighMapHeight - 1; y++) {
      for (int x = 0; x < iHighMapWidth - 1; x++) {

        float xx1 = x+1-x;  //wyliczanie wektorow
        float yy1 = y-y;
        float zz1 = pHighMap[(y    *iHighMapWidth + x + 1) * 3 + 0] / 2.0 - pHighMap[(y    *iHighMapWidth + x) * 3 + 0] / 2.0;

        float xx2 = x-x;
        float yy2 = y+1-y;
        float zz2 = pHighMap[((y + 1)*iHighMapWidth + x) * 3 + 0] / 2.0 - 2.0 - pHighMap[(y    *iHighMapWidth + x) * 3 + 0] / 2.0;

        float xx3 = yy1*zz2 - zz1*yy2;//normalny wektor
        float yy3 = xx1*zz2 - zz1*xx2;
        float zz3 = xx1*yy2 - yy1*xx2;

        float d = sqrt(xx3*xx3 + yy3*yy3 + zz3*zz3); //normalizacja
        glNormal3f(xx3/d, yy3/d,  zz3/d);     


        glVertex3f(x  , pHighMap[(y    *iHighMapWidth +x  ) * 3 + 0] / 2.0, y   );
        glVertex3f(x+1, pHighMap[(y    *iHighMapWidth +x+1) * 3 + 0] / 2.0, y   );
        glVertex3f(x+1, pHighMap[((y+1)*iHighMapWidth +x+1) * 3 + 0] / 2.0, y+1);
        glVertex3f(x  , pHighMap[((y+1)*iHighMapWidth +x  ) * 3 + 0] / 2.0, y+1);
       /* glVertex3f(x, y, pHighMap[(y    *iHighMapWidth + x) * 3 + 0] / 2.0);
        glVertex3f(x + 1, y, pHighMap[(y    *iHighMapWidth + x + 1) * 3 + 0] / 2.0);
        glVertex3f(x + 1, y + 1, pHighMap[((y + 1)*iHighMapWidth + x + 1) * 3 + 0] / 2.0);
        glVertex3f(x, y + 1, pHighMap[((y + 1)*iHighMapWidth + x) * 3 + 0] / 2.0);*/

      }

    }
    glEnd();
    glPopMatrix();

}


void DrawScene() {
  glClearColor(1.0,0.9,0.8,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  GLfloat fLightPosition[] = { 5.0,15.0,5.0,0.0 };
  

  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);

  glEnable(GL_LIGHT0);

  glLoadIdentity();
  glTranslatef(-1.0,-5.0,-20.0);

  glLightfv(GL_LIGHT0, GL_POSITION, fLightPosition);
 
  Axis(50.0);


  static float fangle = 0.0;
 // fangle += 0.01;
  //glRotatef(fangle, 0, 1, 1);
  fangle += 0.05;
  glRotatef(fangle, 0, 1, 0);
  Axis(50.0);

  glPushMatrix();
  glTranslatef(-iHighMapWidth / 2 * 0.1,-5, -iHighMapHeight / 2 * 0.1);
  DrawHighMap(0.1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, +8, 0);
  DrawFly(2.0);
  
  glPopMatrix();
/*
  
  
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
  */
  
  
}








int WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
  iStartTime = GetTickCount();
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
  //PrepareTextures();
  PrepareHighMap();
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