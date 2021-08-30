#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<cmath>
#include<cstring>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<vector>
#include<unistd.h>
#include<iomanip>
#include<windows.h>
#include<cwchar>
#include<direct.h>
#include<io.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<direct.h>
#include<shlobj.h>
#include"wtypes.h"

#pragma comment(lib, "user32")

#ifndef _WIN32_WINNT 
  #define _WIN32_WINNT 0x0601
  #include<wincon.h>
  #include<string>

  //#endif  // user 1 

typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
}CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif

#endif // user 2

#ifndef UNICODE  
  typedef std::string String; 
#else
  typedef std::wstring String; 
#endif

using namespace std;
/********GLOBAL FUNCTIONS**********/

string DesktopPath,command;
char DesktopPathArray[MAX_PATH];

/**********************************/

/********GLOBAL FUNCTIONS *********/
int dirExists(const char *path)
{
    struct stat info;

    if(stat( path, &info ) != 0)
        return 0;
    else if(info.st_mode & S_IFDIR)
        return 1;
    else
        return 0;
}

void getDesktopPath()
{
    TCHAR appData[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPath(NULL,CSIDL_DESKTOPDIRECTORY | CSIDL_FLAG_CREATE,NULL,SHGFP_TYPE_CURRENT,appData)));

    //wcout<<appData<<endl;

    DesktopPath = appData;
    //string DesktopPath2;

    //DesktopPath2 = DesktopPath; //backup directory if needed
   
    DesktopPath = DesktopPath + "\\" + "Endecter";
    //cout<<"Main"<<DesktopPath<<"Back up"<<DesktopPath2<<endl;
    
    int i;
    for(i=0;i<DesktopPath.length();i++)
    {
     DesktopPathArray[i] = DesktopPath[i];
    }
    DesktopPathArray[i] = '\0';

    //printf("\n after array : %s",DesktopPathArray);

    const char *path = DesktopPathArray;  

    
    int check = dirExists(path);

    //cout<<check<<endl;

    if(!check)
    {  
       command="mkdir "+DesktopPath;
       //cout<<"commad 1 for creating directory "<<command<<endl;
       system(command.c_str()); 
    }
     
     
    //cout<<ch<<endl;
    //? testing command = "echo.successful > " + DesktopPath + "\\harshil_success.txt";
    //cout<<"commad 2 for creating a file "<<command<<endl;
    //system(command.c_str()); 
    
    
    DesktopPath = DesktopPath + "\\" ;

    for(i=0;i<DesktopPath.length();i++)
    {
     DesktopPathArray[i] = DesktopPath[i];
    }
    DesktopPathArray[i] = '\0';

    //printf("\n after array 2 : %s",DesktopPathArray);

    

    // * DesktopPath & DesktopPathArray can be use for creting any file in Endecter folder

}

int GetDesktopResolution()
{ 
    int size=22;
    RECT desktop; // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow(); // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop); 
    // The top left corner will have coordinates (0,0) 
    // and the bottom right corner will have coordinates 
    // (horizontal, vertical) 
    int horizontal = desktop.right; 
    int vertical = desktop.bottom;

    if(horizontal<=600){size=24;}
    else if(horizontal<=800){size=25;}
    else if(horizontal<=1000){size=26;}
    else if(horizontal<=1400){size=28;}
    else if(horizontal <=1900){size=33;}
    else if(horizontal <=2500){size=38;}
    else if(horizontal <=3200){size=40;}
    else if(horizontal <=4000){size=42;}
    else if(horizontal <=4800){size=44;}
    
    return(size);
 } 

void SetColor(int ForgC)
{
 WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
      //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void setConsoleSize()
{
  CONSOLE_FONT_INFOEX cfi;
  cfi.cbSize = sizeof(cfi);
  cfi.nFont = 0;
  cfi.dwFontSize.X = 0;                   // Width of each character in the font
  cfi.dwFontSize.Y = GetDesktopResolution();                  // Height
  cfi.FontFamily = FF_DONTCARE;
  cfi.FontWeight = FW_NORMAL;
  std::wcscpy(cfi.FaceName, L"JetBrains Mono"); // Choose your font
  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}
void gotoxy(int x, int y=0)
{
  for(;x>0;x--)   //vertical
  cout<<"\n";

  while(y!=0) //horizontal
  {
    printf(" ");
    y--;
  }
}

void EXIT_PROGRAM(int status=0,int v=0,int h=0)
{
  gotoxy(v,h);  
  SetColor(2);  
  cout<<"\t\t\t\t   PRESS ANY KEY TO EXIT   "<<endl;
  getch();
  exit(status);
}
/********************/

class ENCRYPTION
{

  /*****static data members*******/
  public:

  static int CHOICE_OPERATION;
  static int MESSAGE_MODE;

  private:

  //static int choice;
  static float choice_;

  /******************/

                    //* Data Member's *//

  /*******FILE********/
  
  private:

  string fileName;  
  char fileNameCopy[256]; // copy for file handling
  int flag_for_file_err;  // file checking error // ? flag 1= file name not okay , 2= missing file extention, 3= file not exist 

  public:

  /*******************/

  /*******CUSTOM-MSG********/
   
  private:
  vector<char> message;
  
  public:

  /******************/

  /********GENERAL*********/
   
   private:

   char read_file_ch;
   char medium;
   char c; // *  custom message ni methods  Msgtofile & showMsg + general methods send_encrypt_decrypt_to_file bne ma commaly use kri shkay che
   int i; // * custom ni getMsg + File ni ConverttoString + file ni checkfilename bne use kre che + used in getFileMsg_for_Decryption + used in getFileMsg_for_Encryption;
   
   vector<char> message_encrypt;

   public:
   
  /*****************/

                    //* Methods *//
    
/********FILE********/
    private:
    void convertStringtoArray(string arg,char* argcopy)
    {

      int i;
      for(i=0;i<arg.length();i++)
      {
       *(argcopy+i) = arg[i];
      }
      *(argcopy+i)='\0';

    }
    int doubleEncryption()
    {
        i = fileName.find_last_of(46) + 1;
        if(fileName[i] == '8')
        {
            return 1;
        }
        return 0;
    }
    int checkFileName() 
    {  
      i=0;
      int FlagA=0,FlagB=1; // A e space mate B a dot. mate // ? 0= okay , 1 = error

      /* space find krva */
      for(i=0;i<fileName.size();i++)
      { 
         if(fileName[i] == 32)
         {   
             FlagA=1;
             break;
         }
      } 
      /* dot(.) find krva */
      for(i=0;i<fileName.size();i++)
      {
         if(fileName[i] == 46)
         {    
             FlagB=0;
             break;
         }
      }
      if(FlagA==1)
      {
         flag_for_file_err=1; // eror 1 apvi filename barabr nthi km k space sathe nakhu che
         return(0); 
      }
      else if(FlagB==1)
      {
          flag_for_file_err=2; // error 2 apvi km k . j nthi atle extention missing che
          return(0);
      }
      else
      {
        return(1); // all stages passed of error checking
      }
    }
    int checkFileExists() 
    {
        int return_status=99; 
        ifstream fcheck;
        
        command = DesktopPath + fileNameCopy;
        convertStringtoArray(command,DesktopPathArray);
        //printf("\n DesktopPatharray  checkFileExists: %s ",DesktopPathArray);
        fcheck.open(DesktopPathArray, ios::in);
        if(fcheck)
        {
          return_status=1;
        } 
        else
        {
          flag_for_file_err=3;
          return_status=0;
        }
            
        fcheck.close();
        return (return_status);         
    }

    public:

    void askFileName() 
    {  
        top:
        flag_for_file_err=0; //error avse 1 st time check file check ma to bdhu reset krvu pde atle
        gotoxy(1,20);
        SetColor(14);
        cout<<"FILE MUST BE IN THE DESKTOP->Endecter FOLDER."<<endl;
        SetColor(10);
        cout<<"\n\nEnter The Name Of File That Contains The Message : ";
        SetColor(15);
        getline(cin,fileName);  //updated string data type with white space input
          
        
        convertStringtoArray(fileName,fileNameCopy);
        int check=checkFileName();  /// 0 hoy to error and 1 hoy to okay
        if(check==0)
        {
            if(flag_for_file_err==1)
            {   
                scrClr(0);
                SetColor(4);
                cout<<"\n\t File name is incorrect or may contain the whitespace ! please Re-enter it correctly."<<endl;
                scrClr(2);
                goto top;
            }
            else if(flag_for_file_err==2)
            {  
                scrClr(0);
                SetColor(4);
                cout<<"\n\t\t\t File Extention is Missing ! please Re-enter it correctly."<<endl;
                scrClr(2);
                goto top;
            }
 
        }
         check=0; // re-used
         check = checkFileExists(); // 0 hoy to error and 1 hoy to okay
         if(check==0)
         {
           if(flag_for_file_err==3)
           { 
             scrClr(0);
             SetColor(4);
             cout<<"\n\t   FILE NOT EXIST IN DESKTOP->Endecter FOLDER ! PLEASE RE-ENTER CORRECT FILE. "<<endl;
             scrClr(2);
             goto top;
           }
         }

         check = doubleEncryption();
         if(check == 1 && CHOICE_OPERATION == 1)
         {
            SetColor(4);
            cout<<"\n\n\t\t\t\t"<<fileNameCopy<<" IS ALREADY ENCRYPTED\n\n";
            EXIT_PROGRAM(0,15);
         }
         else if(check == 0 &&  CHOICE_OPERATION == 2)
         {
            SetColor(4);
            cout<<"\n\n\t\t\t"<<fileNameCopy<<" IS NOT ENCRYPTED YET ! FIRST ENCRYPT IT\n\n";
            EXIT_PROGRAM(0,15);
         }

        if(CHOICE_OPERATION==1)
        {getFileMsg_for_Encryption();}
        else
        {getFileMsg_for_Decryption();}
        
        send_encrypt_decrypt_to_file();
        //getch();
        if(CHOICE_OPERATION==1){finalMsg();}
        else{finalMsg2();}
        
    }

/**************************/

/********CUSTOM-MSG********/

public:

void getMsg()
{  
    i=0; // re used

    char message_array[100000]; // ? large space container we will try to make it short
    SetColor(10);
    cout<<endl<<"Enter The Message You Want to Send : ";
    SetColor(15);
    cin.getline(message_array,100000);  
    while(message_array[i]!='\0')
    {
      message.push_back(message_array[i]);
      i++;
    }

   MsgToFile();
   getFileMsg_for_Encryption();
   send_encrypt_decrypt_to_file();
   //getch();
   finalMsg();
}

private:

void MsgToFile()
{
    c=0; // re used

  
    int st=1;
    char checkFile1[256];
    string s1_new,s2_new,sh_new,Tem_str="Emessage";
    ifstream s1new,s2new;
    while(1)
    {
        s1_new = "";
        s2_new = "";
        sh_new = "";
        sh_new = Tem_str + to_string(st);
         ++st;
        s1_new = sh_new + ".8txt";
        s2_new = sh_new + ".txt";
        checkFile1[0] = '\0';
        for(i=0;i<s1_new.size();i++)
        {
            checkFile1[i]=s1_new[i];
        }
        checkFile1[i] = '\0';

        command = DesktopPath + checkFile1;
        convertStringtoArray(command,DesktopPathArray);
        
        //printf("\n DesktopPatharray  MsgtTofile: %s ",DesktopPathArray);
        s1new.open(DesktopPathArray,ios::in);
        

        checkFile1[0] = '\0';
        for(i=0;i<s2_new.size();i++)
        {
            checkFile1[i]=s2_new[i];
        }
        checkFile1[i] = '\0';

        command = DesktopPath + checkFile1;
        convertStringtoArray(command,DesktopPathArray);
        //printf("\n DesktopPatharray  MsgtoFile 2: %s ",DesktopPathArray);
        s2new.open(DesktopPathArray,ios::in);
        
        if((!s1new.is_open()) && (!s2new.is_open()))
        {
          break;
        }
        s1new.close();
        s2new.close();
    }
    fileName = s2_new;
  
    
    convertStringtoArray(fileName,fileNameCopy);
    ofstream fout;

    command = DesktopPath + fileNameCopy;
    convertStringtoArray(command,DesktopPathArray);
    //printf("\n DesktopPatharray  MsgtoFile 3: %s ",DesktopPathArray);
    fout.open(DesktopPathArray,ios::out);
    

    for(auto c=message.begin();c!=message.end();c++)
    {
      fout<<*c;
    }
    fout.close();
}

void showMsg()  // just for maintainence
{
    c=0; // re used

    for(auto c=message.begin(); c!=message.end(); c++)
    {
      cout<<*c;
    }
}


/********************/

/***************** GENERAL FUNCTIONS *******************/
public:

ENCRYPTION()
{
  flag_for_file_err=read_file_ch=medium=c=i=0;
}

private:

inline void projectName(){SetColor(10);cout<<endl<<endl<<setw(58)<<" E N D E C T E R\t\t\t\t\t"<<endl<<endl;}
//todo:
inline void finalMsg(){scrClr(0.0);gotoxy(8,12);SetColor(10);cout<<"1 ENCRYPTED FILE HAS BEEN GENERATED IN THE DESKTOP->Endecter FOLDER "<<"\n\t\t\t     PLEASE SEND IT TO THE RECEPIENT."<<"\n\n\t\t\t\t     ";

SetColor(15);
cout<<" \" "<<fileNameCopy<<" \""<<endl;}

void getFileMsg_for_Encryption() 
{   
    //file handling for reading the msg file
      ifstream fin;

      command = DesktopPath + fileNameCopy;
      convertStringtoArray(command,DesktopPathArray);

      //printf("\n DesktopPatharray  getfileMsg_for_Encryption: %s ",DesktopPathArray);
      fin.open(DesktopPathArray,ios::in  | ios::binary);


      read_file_ch = fin.get();
      
      while(fin)
      {  
          read_file_ch = read_file_ch + 12;
          message_encrypt.push_back(read_file_ch); 
          read_file_ch = fin.get();
      }
      fin.close();

      command = DesktopPath + fileNameCopy;
      convertStringtoArray(command,DesktopPathArray);
      //printf("\n DesktopPatharray  Remove  : %s ",DesktopPathArray);
      remove(DesktopPathArray);
      

      i = fileName.find_last_of(46) + 1;
      fileName.insert(i,"8");
       
      convertStringtoArray(fileName,fileNameCopy);// ? for used in Decrytion

    //cout<<"\n\n\t\tFILE '"<<fileNameCopy<<"' ENCRYPTION DONE SUCEESFULLY!";
}

void send_encrypt_decrypt_to_file()
{
  char read_only[256]; // re -used
  c=0;
  string Tem;
  ofstream medium_file;

  command = DesktopPath + fileNameCopy;
  convertStringtoArray(command,DesktopPathArray);
  //printf("\n DesktopPatharray  send_encrypt_decrypt_to_file : %s ",DesktopPathArray);
  
  medium_file.open(DesktopPathArray,ios::out | ios::binary);

  for(auto c=message_encrypt.begin(); c!=message_encrypt.end(); c++)
  {
    medium_file<<*c;
  }
  medium_file.close();

  if(ENCRYPTION::CHOICE_OPERATION == 1)
  {

        command = DesktopPath + fileName;
        convertStringtoArray(command,DesktopPathArray);
        //printf("\n DesktopPatharray  reda only  : %s ",DesktopPathArray);
        Tem = "attrib +R ";
        Tem = Tem + DesktopPathArray;
        for(i=0;i<Tem.size();i++)
        {
            read_only[i]=Tem[i];
        }
        read_only[i] = '\0';
        system(read_only); 
  }
}
public:

void pre_warning_for_Encryption()
{ 
  gotoxy(3,2);
  SetColor(14);
  cout<<"WARNING : ORIGINAL FILE WILL BE ENCRYPTED SO TAKE A BACK COPY OF ORIGINAL FILE."<<endl;
  projectName();
}

void scrClr(float i) const
{
  sleep(i);
  system("cls");
}

int ASK_OPERATION();
int ASK_MSG_MODE();

~ENCRYPTION()
{
  //EMPTY DESTRUCTOR
}
/**********************************/

/***********DECRYPTION-CLASS *************/

private:

inline void finalMsg2(){
scrClr(0.0);
gotoxy(8,12); //TODO:
SetColor(10);
cout<<"1 DECRYPTED FILE HAS BEEN GENERATED IN THE DESKTOP->Endecter FOLDER ."<<endl;
SetColor(15);
gotoxy(2,35);
cout<<"    \" "<<fileNameCopy<<" \""<<endl;
}

public:

void getFileMsg_for_Decryption()
{
    char read_only[256]; 
    string Tem;          

    command = DesktopPath + fileName;
    convertStringtoArray(command,DesktopPathArray);
    //printf("\n DesktopPatharray  read only  : %s ",DesktopPathArray);
    Tem = "attrib -R ";
    Tem = Tem + DesktopPathArray;
    for(i=0;i<Tem.size();i++)
    {
        read_only[i]=Tem[i];
    }
    read_only[i] = '\0';
    system(read_only); 
   
    ifstream fin;

    command = DesktopPath + fileNameCopy;
    convertStringtoArray(command,DesktopPathArray);
    //printf("\n DesktopPatharray  getfilemsgForDecryption 679 : %s ",DesktopPathArray);
    fin.open(DesktopPathArray,ios::in  | ios::binary); 
    read_file_ch = fin.get();
 
    while(fin)
    {  
        read_file_ch = read_file_ch - 12;
        message_encrypt.push_back(read_file_ch); 
        read_file_ch = fin.get();
    }
  
    fin.close();
    //cout<<"\n\n\t\tFILE '"<<fileNameCopy<<"' DECRYPTION DONE SUCCESSFULLY!";

    command = DesktopPath + fileNameCopy;
    convertStringtoArray(command,DesktopPathArray);
    //printf("\n DesktopPatharray  getfilemsgForDecryption 696 : %s ",DesktopPathArray);
    remove(DesktopPathArray);
    i = fileName.find_last_of(46) + 1;
    fileName.erase(i, 1);
    convertStringtoArray(fileName,fileNameCopy);
    
}

/**************************************************************/

};

//*!!!!!!!!!!!!!!!! CLASS END HERE !!!!!!!!!!!!!!!!!!!!!!!!!!*//

/*****STATIC DEFINATION******/

int ENCRYPTION:: CHOICE_OPERATION=0;
int ENCRYPTION:: MESSAGE_MODE=0;
//int ENCRYPTION:: choice=0;
float ENCRYPTION:: choice_=0.0f;

/******OUTSIDE DEFINATION*****/

int ENCRYPTION::ASK_OPERATION()
{   
    
    // choice=0;   // re used 
    choice_=0.0f; // re used


    bool match=false;

    re_ask:
    SetColor(10);
    cout<<"\n  WHAT  DO YOU WANT ?\n"<<endl;
    cout<<"\n  1) ENCRYPTION"<<endl<<endl;
    cout<<"  2) DECRYPTION"<<endl;
    
  do
  {
    SetColor(10);
    cout<<endl<<endl<<setw(49)<<"CHOICE: ";
    SetColor(15);
    cin>>choice_;
     
    if (!cin)
    {
        cin.clear();
        cin.ignore(80,'\n');
    }
    else if(choice_>=101&&choice_<=110)
    {
        match=true;
    }

    if(choice_<1||choice_>2)
    {        
       SetColor(4);
       gotoxy(1,35);
       cout<<"Invalid Choice Entered !"<<endl;
       gotoxy(1,28);
       cout<<"Please re-Enter Your Choice Correctly.\n"<<endl;
       scrClr(1);
       goto re_ask;
    }
    choice_ =(int)floor(choice_);  // * for stop looping error float
    if(choice_==1||choice_==2)
    {break;}

  }while(match!=true);

    scrClr(0.5);

    fflush(stdin);

   

    return(choice_);
}

int ENCRYPTION::ASK_MSG_MODE()
{
  
    
    //choice=0;   // re used 
    choice_=0.0f; // re used

    bool match=false;
    
    re_ask:
    SetColor(10);
    cout<<"\n\n  FROM WHICH METHOD DO YOU WANT TO SEND A MESSAGE ?"<<endl<<endl<<endl;
    cout<<"\n  1)CUSTOM MESSAGE"<<endl<<endl;
    cout<<"  2)SELECTING A FILE"<<endl<<endl;
 
 
    do{
  
       SetColor(10);
       cout<<endl<<endl<<setw(49)<<"CHOICE: ";
       SetColor(15);
       cin>>choice_;


       if (!cin)
       {
           cin.clear();
           cin.ignore(80,'\n');
       }
       else if(choice_>=101&&choice_<=110)
       {
           match=true;
       }

        if(choice_<1||choice_>2)
       {
         SetColor(4);
         gotoxy(1,35);
         cout<<"Invalid Choice Entered !"<<endl;
         gotoxy(1,28);
         cout<<"Please re-Enter Your Choice Correctly.\n"<<endl;
         scrClr(1);
         goto re_ask;
       }
      choice_ =(int)floor(choice_); // * for stop looping error float
      if(choice_==1||choice_==2)
      {break;}

     }while(match!=true);
    
    scrClr(0.5);
    
    fflush(stdin);

    

  
    return(choice_);      
}

/*******************/

int main(void)
{       
        // get handle to the console window
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

        // retrieve screen buffer info
        CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
        GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

        // current window size
        short winWidth = scrBufferInfo.srWindow.Right - scrBufferInfo.srWindow.Left + 1;
        short winHeight = scrBufferInfo.srWindow.Bottom - scrBufferInfo.srWindow.Top + 1;

        // current screen buffer size
        short scrBufferWidth = scrBufferInfo.dwSize.X;
        short scrBufferHeight = scrBufferInfo.dwSize.Y;        

        // to remove the scrollbar, make sure the window height matches the screen buffer height
        COORD newSize;
        newSize.X = scrBufferWidth;
        newSize.Y = winHeight;

        // set the new screen buffer dimensions
        SetConsoleScreenBufferSize(hOut, newSize);

        ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
      
        setConsoleSize();
        system("color a");
        getDesktopPath();

        ENCRYPTION OBJECT;
        
        OBJECT.pre_warning_for_Encryption();

        ENCRYPTION::CHOICE_OPERATION = OBJECT.ASK_OPERATION(); // ? MODE ENCRYPT

        if(ENCRYPTION::CHOICE_OPERATION == 1)
        {
              ENCRYPTION::MESSAGE_MODE = OBJECT.ASK_MSG_MODE();
              if(ENCRYPTION::MESSAGE_MODE==1) //custom msg
              {
                  OBJECT.getMsg();                 
              }
              else if(ENCRYPTION::MESSAGE_MODE==2) //file method
              {
                    OBJECT.askFileName();
              }
        }
        else if(ENCRYPTION::CHOICE_OPERATION == 2)   // ? MODE DECRYPTION
        {
              OBJECT.askFileName();
        }

        EXIT_PROGRAM(0,10);
        return(0);
}
