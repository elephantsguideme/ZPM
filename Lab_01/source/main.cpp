#include <Windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
{
  char buffer[50];
  
  /*
  int iRetKey = MessageBox(0, ">20", "Aplikacja", MB_YESNO);
  if (iRetKey == IDYES) {
    iRetKey = MessageBox(0, ">30", "Aplikacja", MB_YESNO);
    if (iRetKey == IDYES) {
      iRetKey = MessageBox(0, ">35", "Aplikacja", MB_YESNO);
      if (iRetKey == IDYES) {
        iRetKey = MessageBox(0, ">38", "Aplikacja", MB_YESNO);
        if (iRetKey == IDYES) {
          iRetKey = MessageBox(0, ">39", "Aplikacja", MB_YESNO);
          if (iRetKey == IDYES) {
            MessageBox(0, "40", "Aplikacja", MB_OK);
          }
          else
          {
            MessageBox(0, "39", "Aplikacja", MB_OK);

          }
          }
      }
    }
  }
  else
  {
    
  }*/
  
  int t = 1;
  int n, x = 20;
  n = sprintf_s(buffer, "> %d ?", x);
  while (t) {
    n = sprintf_s(buffer, "> %d ?", x);
    int iRetKey =MessageBox(0, buffer, "Aplikacja", MB_YESNO);
    if (iRetKey == IDYES) {
      x = (x + 40) / 2;
    }
    else {
      x = x / 2;
    }

  }

  return 0;
}