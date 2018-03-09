#include <Windows.h>
#include <stdio.h>



  int WINAPI WinMain(HINSTANCE histance, HINSTANCE hPrevinstance, PSTR szCmdLine, int iCmdShow)
  {
    char buffer[50];



    int t = 1, iRetKey;
    int n, x = 1, y = 1000;

    while (t) {
      n = sprintf_s(buffer, "> %d ?", (x + y) / 2);
      iRetKey = MessageBox(0, buffer, "Aplikacja", MB_YESNO);
      if (iRetKey == IDYES) {
        x = (x + y) / 2 + 1;
      }
      else {
        y = (x + y) / 2;
      }
      if (x == y) {
        t = 0;
      }
    }
    sprintf_s(buffer, "Twoja liczba to %d", x);
    MessageBox(0, buffer, "Aplikacja", MB_OK);

    return 0;
  }

