//Header Files
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<ctype.h>
#include<time.h>
#include"DrawRect.h"
#include"Format.h"
#include"Position.h"

#include<cstdlib>
#include<process.h>
#include<string.h>

#define _WIN32_WINNT 0x0500

using namespace std;

//Function Prototype
void Movepos(void*);
void Menu();

//Global variables
int MouseMode=0;
int TextMode=0;

struct MousePo
{
	int x;
	int y;
}Mouse;

//Function To Get Character(Replacement for in-built getch())
CHAR GetCh (VOID) 
{
   HANDLE hStdin = GetStdHandle (STD_INPUT_HANDLE);
   INPUT_RECORD irInputRecord;
   DWORD dwEventsRead;
   CHAR cChar;
   while(ReadConsoleInputA (hStdin, &irInputRecord, 1, &dwEventsRead)) /* Read key press */ 
   if (irInputRecord.EventType == KEY_EVENT &&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT &&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_MENU &&irInputRecord.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
   {
    cChar = irInputRecord.Event.KeyEvent.uChar.AsciiChar; ReadConsoleInputA (hStdin, &irInputRecord , 1, &dwEventsRead); /* Read key release */
		 return cChar; 
   } 
   return EOF; 
}
//Main Class
class Editor
{
	protected:
		
		char txt[300][65];				//2-D Character Array
		char cpytxt[500];				//Copied Text Buffer				
		int  x,y;						//Array Co-ordinates
		int  ch;						
		int  CursX,CursY;				//Cursor Positions
		int  StartX,StartY;
		int  MinY;						//Position of page in array
		char T;							//Input Character
		bool Move;
		int  thrd;
		int sel_x;
		int sel_y;
		int end_x;
		int end_y;
		int cpylen;
		
		bool shiftpause;
		bool ctrlpause;
		bool sleepMode;
		ofstream B;	
		fstream  C;
		ifstream Dic;
	
		
	public:
		
		Editor()									
		{
			StartX=0;
			StartY=10;
			thrd=0;
			CursX=0;
			CursY=10;
			x=0;
			y=0;
			MinY=0;
			
			cpylen=0;
			shiftpause=false;
			ctrlpause=false;
			sleepMode=false;
			for(int i=0;i<30;i++)
				for(int j=0;j<65;j++)
					txt[i][j]==' ';
			T=' ';
			Move=false;
			Dic.open("Dict.txt");
		}	
		
		void Scroll(int Dir)										//Function to scroll
		{
			if(Dir==1)
			{
				MinY++;
			}
			else if(Dir==-1)
			{
				MinY--;
			}
		}
		
		void MoveCurs()												//Function to move cursor position
		{
			while(1)
			{
						
			if(sleepMode==true)
				{
					Sleep(5);
					continue;
				}
			
			if(GetKeyState(VK_RIGHT) & 0x8000)
				{
					if(CursX==64)
						{
							if((y-MinY)==29)
							{
								Scroll(1);
								y++;
								x=0;
								CursX=0;
							}							
							
							else
							{
								CursY++;
								CursX=0;
								x=0;
								y++;
							}
						}
					else
						{
							CursX++;
							x++;
						}
								
				}
			
			else if(GetKeyState(VK_SHIFT) & 0x8000)
				{
					sel_x=x;
					sel_y=y;
					
					while((GetKeyState(VK_SHIFT) & 0x8000)) 
					{
						shiftpause=true;
						if(GetKeyState(VK_RIGHT) & 0x8000)
						{
							if(x==64 && y==299)
							{
								continue;
							}
							gotoxy(CursX,CursY);
							BColor(159);
							cout<<txt[y][x];
							//BColor(241);
							if(CursX==64)
							{
								CursY++;
								CursX=0;
								x=0;
								y++;
								
							}
							
							else
							{
								x++;
								CursX++;
								
							}
							Sleep(50);
						}
						
						else if(GetKeyState(VK_DOWN) & 0x8000)
						{
													
						}
						shiftpause=false;
					
						
					}
					Sleep(100);
					end_x=x;
					end_y=y;
				}
			else if(GetKeyState(VK_CONTROL) & 0x8000)
				{
					
					
					while(GetKeyState(VK_CONTROL) & 0x8000)
					{
						ctrlpause=true;
						if(GetKeyState(0x4B) & 0x8000)							//0x4B->'K'
						{		
							for(int i=0;i<500;i++)
							{
								cpytxt[i]=NULL;
							}
							int cpypos=0;
							for(int a=sel_y;a<=y;a++)
							{
								if(a != end_y && a != sel_y)
								{
									for(int b=0;b<64;b++)
									{
										cpytxt[cpypos]=txt[a][b];
										cpypos++;
									}
								}
								
								else if(a==end_y)
								{
									for(int b=0;b<=end_x;b++)
									{
										cpytxt[cpypos]=txt[a][b];
										cpypos++;
									}
								}
								
								else if(a==sel_y)
								{
									for(int b=sel_x;b<=64;b++)
									{
										cpytxt[cpypos]=txt[a][b];
										cpypos++;
									}
								}
							}
							cpylen=(cpypos-1);
							break;
													
						}
						
						else if(GetKeyState(0x50) & 0x8000)					//0x50->P
						{
							for(int i=cpylen-1;i>=0;i--)
							{
								for(int a=299;a>y;a--)
								{
									
									for(int b=64;b>=0;b--)
									{
										if(b==0)
										{
											txt[a][b]=txt[a-1][64];
										}
										else
										{
											txt[a][b]=txt[a][b-1];
										}
									}
								}
								for(int j=64;j>=x;j--)
								{
									txt[y][j]=txt[y][j-1];
								}
								txt[y][x]=cpytxt[i];
							}
							Sleep(30);
							break;
						}
						
					}
					ctrlpause=false;
					
				}	
			else if(GetKeyState(VK_DOWN) & 0x8000)
				{
												
					if(y==299)
					{
						continue;
					}
					else if((y-MinY)==29)
					{
						Scroll(1);
						y++;
					}
					
					else
					{
						CursY++;
						y++;
				 	
					}	
				}
			
			else if(GetKeyState(VK_LEFT) & 0x8000)
				{
					if(CursX==0)
						{
							if(CursY=10)
							{
							
							if(y==0)
							{
								continue;	
							}
							
							else if(y<=29){
							
							CursX=64;
							x=64;
							y--;}
							
							else
							{
							Scroll(-1);
							CursX=64;
							x=64;
							y--;
							}
							}
							else
							{
								CursY--;
								y--;
								x=64;
								CursX=64;
							}
						}
					else
						{
						
							CursX--;
							x--;
							
						}							
					
				}
			
			else if(GetKeyState(VK_UP) & 0x8000)
				{
							
					if(y==0)
					{
						continue;
					}
					else if(CursY==10 && y>0)
					{
						Scroll(-1);
						y--;
					}
					else
					{
					
						CursY--; 
						y--;	
					}
				}
			
			else if(GetKeyState(VK_RETURN) & 0x8000)
				{
					
					if(y==299)
					{
						continue;
					}

					else if((y-MinY)==29)
					{
						Scroll(1);
						x=0;
						y++;
					}
					
					else
					{
						CursX=0;
						CursY++;
						x=0;
						y++;	
					}
				}
			else if(GetKeyState(VK_DELETE) & 0x8000)
			{
				for(int i=x;i<65;i++)
				{
					txt[y][i]=txt[y][i+1];
				}
				for(int j=y+1;j<300;j++)
				{
					txt[j-1][64]=txt[j][0];
					
					for(int i=0;i<65;i++)
					{
						txt[j][i]=txt[j][i+1];
					}
				}
			}	
			else if(GetKeyState(VK_BACK) & 0x8000)		
				{
					if(x==0 && y!=0)
						{
							txt[y][x]=' ';
							if(CursY=10)
							{
								CursX=64;
								y--;
								x=64;
							}
							else
							{
								CursY--;
								CursX=64;
								x=64;
								y--;
							}
							cout<<" ";
							gotoxy(CursX,CursY);
														
						}
					else if(y==0 && x!=0)
						{
							gotoxy(CursX,CursY);
							cout<<" ";
							CursX--;
							x--;
							txt[y][x]=' ';
						}
					else if(y==0 && x==0)
						{
							continue;
						}		
					else
						{
							
							gotoxy(CursX,CursY);
							cout<<" ";
							CursX--;
							x--;
							txt[y][x]=' ';
																			
						}
					
					for(int i=x;i<65;i++)
					{
						txt[y][i]=txt[y][i+1];
					}
					for(int j=y+1;j<300;j++)
					{
						txt[j-1][64]=txt[j][0];
						
						for(int i=0;i<65;i++)
						{
							txt[j][i]=txt[j][i+1];
						}
					}
						
				}
			else if(GetKeyState(VK_TAB) & 0x8000)
				{
					if(CursX==59)
						{
							CursY++;
							CursX=0;
							x=0;
							y++;
						}
					else
						{
							CursX+=5;
							x+=5;
						}
					gotoxy(CursX,CursY);
				}
			else if(GetKeyState(VK_HOME) & 0x8000)		
				{
					CursX=0;
					x=0;
					gotoxy(CursX,CursY);
				}
			
			Sleep(50);
			}
			_endthread;
		}
		
		void Write()															//Function where text is written
		{
			_beginthread(Movepos,0,this);
			
			if(TextMode==1/*||TextMode==2*/)
			{
				y=0;CursY=10;
				x=0;CursX=0;
			}	
			else if(TextMode==2)
			{
				y=MinY; CursY=10;
				x=0;CursX=0;
			}
						
			while(true)
			{
			/////////////////////////////////
			gotoxy(1,43);
			cout<<"Line no:";
			DrawRect(10,42,5,2);
			gotoxy(12,43);
			cout<<"   ";
			gotoxy(12,43);
			cout<<(y+1);			
			////////////////////////////////
			gotoxy(StartX,StartY);
						
			for(int i=MinY;i<(MinY+30);i++)
			{
				for(int j=0;j<65;j++)
				{
					if(txt[i][j]==NULL)
						cout<<" ";
					else	
						cout<<txt[i][j];
				}
				cout<<endl;
			}
			sleepMode=false;
			CursX=x;
			CursY=(y-MinY)+10;
			gotoxy(CursX,CursY);

			while(shiftpause==true || ctrlpause==true)
			{
				Sleep(1000);
			}
			
			/////////////////////////////////////////////////////////////////////
			T=GetCh();
			/////////////////////////////////////////////////////////////////////
			
			sleepMode=true;
			BColor(241);
			int A=T;
		
			if((A>0 && A<32) || A==255)
			{
				continue;
			}
			else if(A==0)
			{
				continue;
			}
			if ( txt[y][x] != ' ')
			{
				
				for(int a=299;a>=y;a--)
				{
					if(a>(y)){
									
					for(int b=64;b>=0;b--)
						{
							if(b==0)
								{
									txt[a][b]=txt[a-1][64];
								}
							else
								{
									txt[a][b]=txt[a][b-1];
								}
						}
					}
					else
					{
						for(int b=64;b>=x;b--)
						{
							txt[a][b]=txt[a][b-1];
						}
					}
				}
							
				txt[y][x]=T;
			}
			else
				txt[y][x]=T;
			
			CheckI();
			CheckFullStop();
			CheckCaps();
			if(T=' ')
			{
				CheckWord();
			}
			
			if(CursX==64 && x==64)
			{
				CursY++;
				CursX=0;
				x=0;
				y++;
			}
			else
			{
				
				x++;CursX++;
			}
			
			}
			
		}
		
		void CheckWord()
		{
			char temp[65];
			char test[30];
			for(int i=0;i<65;i++)
			{
				temp[i]=txt[y][i];
			}
			string check(temp);
			bool error=true;
			while(Dic)
			{
				Dic>>test;
				size_t found= check.find(test);
				if ( found==string::npos )
				{
					error=false;
					break;
				}

			}
			
			if(error==true)
			{
				cout<<error;
				Sleep(50);
			}
			
		}
		void CheckI()
		{
			if(txt[y][x-1]=='i' && txt[y][x-2]==' ' && txt[y][x]==' ')
			{
				txt[y][x-1]=toupper(txt[y][x-1]);
			}
			
		}
		
		void CheckFullStop()
		{
			if(txt[y][x]==' ' && txt[y][x-1]==' ')
			{
				txt[y][x-1]='.';
				x--;
				CursX--;
			}
		}
		
		void CheckCaps()
		{
			if (txt[y][x-2]=='.' || txt[y][x-2]=='!' || txt[y][x-2]=='?' && islower(txt[y][x-1]))
			{
				txt[y][x-1]=toupper(txt[y][x-1]);
				
			}
			else if(x==0 && y==0)
			{
				txt[y][x]=toupper(txt[y][x]);
			}
			else if(x==0 && txt[y-1][64]=='.')
			{
				txt[y][x]=toupper(txt[y][x]);
			}
		}	
		
		void ChangePos(int a,int b)
		{
			CursX=a;
			x=a;
			CursY=b;
			y=b-10+MinY;
		}
		
		
};

//Class of which Objects represent  File
class File:public Editor										
{
	private:
		
		int SaveOrUpdate;
	
	protected:
		
		int Found;	
		
	public:
		
		File()
		{
			SaveOrUpdate=0;
			Found=0;
		}
		
		void New()
		{
			char FileName[32];
			gotoxy(10,20);
			cout<<"Enter name of file[max 32 char(with ext)]:";
			cout<<endl<<"\t\t";
			gets(FileName);
			B.open(FileName);
			char Add[16];
			strcpy(Add," - TextMate");
			char Name[26];
			strcpy(Name,(strcat(FileName,Add)));
			SetConsoleTitle(TEXT(Name));
			system("cls");
			Menu();
			Write();
			
		}
		
		void Open()
		{
			char FileNameAndPath[32];
			gotoxy(10,10);
			cout<<"Enter complete file path:";
			gotoxy(10,11);
			gets(FileNameAndPath);
			C.open(FileNameAndPath);
			
			if(C.is_open())
			{
				Sleep(50);
				int n;
				n=-1;
				char c;
				for(int i=0;i<300;i++)
				{
					if(C.eof())
					{
						break;
					}
					
					if(n>=19435)
					{
						break;
					}
					
					for(int j=0;j<66;j++)
					{
						
						if(n>=19435)
						{
							break;
						}
						n++;
						C.seekg(n);
						C.get(c);
						if(c=='\n')
							break;
						if(c==' ')
							c=NULL;
						txt[i][j]=c;
					
						if(C.eof())
						{
							if(i<270)
								MinY=i;
							else
								MinY=270;	
							break;
						}
					}
					
					
				}
				C.close();
				C.open(FileNameAndPath,ios::out);
				C.seekp(0);
				char Add[16];
				strcpy(Add," - TextMate");
				char Name[50];
				strcpy(Name,(strcat(FileNameAndPath,Add)));
				SetConsoleTitle(TEXT(Name));
				system("cls");
				Menu();
				Write();
			}
			
			else
			{
				cout<<"\n\t  "<<"Error Loading Document...\n\t  Creating New Document...";
				New();
			}
			
		}
		
		static void SavGIF(void*)
		{
			ShellExecute(NULL,"open","Save.exe",NULL,NULL,SW_SHOWNORMAL);
			_endthread();
		}
		
		void Save()
		{
			_beginthread(SavGIF,0,this);
			if(TextMode==1)
			{
				
				if(SaveOrUpdate!=0)
				{
					int n=B.tellp();
					n-=19500;
					B.seekp(n);
				}
				
				for(int i=0;i<300;i++)
				{
					for(int j=0;j<65;j++)
					{
						
						char c=txt[i][j];
						B.put(c);	
					}
					B.put('\n');
					
				}
				SaveOrUpdate=1;
			}
			else if(TextMode==2)
			{
				if(SaveOrUpdate!=0)
				{
					int n=B.tellp();
					n-=19500;
					B.seekp(n);
				}
				for(int i=0;i<300;i++)
				{
					for(int j=0;j<65;j++)
					{
						C<<txt[i][j];
					}
					C<<endl;
				}
				SaveOrUpdate=1;
			}
		Sleep(10);	
		}
		
		void Find()
		{
			Found=0;
			ShellExecute(NULL,"open","Find.exe",NULL,NULL,SW_SHOWNORMAL);
			for(int i=0;i<80;i++)
			{
				gotoxy(CursX,CursY);
				if(i%2==0)
				{
					for(int j=0;j<3;j++)
					{
						cout<<".";
						Sleep(30);
					}
				}
				else
				{
					for(int k=0;k<3;k++)
					{
						cout<<" ";
						Sleep(30);
					}
				}
			}
			gotoxy(CursX,CursY);
			ifstream fin;
			fin.open("search.txt");
			char word[20];
			fin.seekg(0);
			fin>>word;
			fin.close();
			int n=0;
			for(int a=0;a<20;a++)
			{
				if(word[a]!=NULL)
					n++;
				else
					break;	
			}
			int i=0,k=0;
			
			while(i<300)
			{
				int j=0;
				while(j<65)
				{
					if (word[k]==txt[i][j])
					{
						j++;
						k++;
						if(k==n)
						{
							Found++;
							k=0;
							continue;
						}
						
					}
					else if(txt[i][j]==NULL)
						break;
					else
					{
						k=0;
						j++;
						continue;
					}	
				}
				i++;
			}
			ofstream fout;
			fout.open("search.txt");
			fout<<Found;
			fout.close();		
			ShellExecute(NULL,"open","Found.exe",NULL,NULL,SW_SHOWNORMAL);
			Sleep(50);
			gotoxy(CursX,CursY);
		}
		
		void ClearAll()
		{
			for(int i=0;i<300;i++)
			{
				for(int j=0;j<65;j++)
				{
					txt[i][j]=' ';
				}
			}
		}
		
		void Exit()
		{
			Save();
			exit(0);
		}
		
}F;
	
void Movepos(void*)
{
	F.MoveCurs();
	
}	

//MOUSE HANDLING
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class MouseInputHandler
{
      //mouse input handler callback function pointer
      typedef void (*MIHCB)(int,int,void*);
      
      public:
      MouseInputHandler(){}
      ~MouseInputHandler(){}
      
      void init();
      
      inline void start_polling()
      {
             _beginthread(polling_function,0,this);
             polling=true;
      }
      
      inline void stop_polling()
      {
             input.quit=true;
             while (polling);
      }
      
      int getx();
      int gety();
      void getxy(int & x, int & y);
      
      //setting the callbacks
      inline void set_lbdcb(MIHCB f){lbdcb=f;}
      inline void set_lbucb(MIHCB f){lbucb=f;}
      inline void set_lbccb(MIHCB f){lbccb=f;}
      inline void set_rbdcb(MIHCB f){}
      inline void set_rbucb(MIHCB f){}
      inline void set_rbccb(MIHCB f){}
      
      //setting the params for the callbacks
      inline void set_lbdcbp(void*p){lbdcbp=p;}
      inline void set_lbucbp(void*p){lbucbp=p;}
      inline void set_lbccbp(void*p){lbccbp=p;}
      inline void set_rbdcbp(void*p){}
      inline void set_rbucbp(void*p){}
      inline void set_rbccbp(void*p){}
      
      public:
      struct MouseInput
      {
             //current and previous mouse button status
             bool cleft, pleft;
             bool cright, pright;
             
             bool quit;
             int x,y;
                          
      } input;
      
      bool polling;
      
      static void polling_function(void*);
      static inline bool is_pressed(int key)
      {
             return (GetAsyncKeyState(key)>>15);
      }
      
      MIHCB lbdcb;
      MIHCB lbucb;
      MIHCB lbccb;
      MIHCB rbdcb;
      MIHCB rbucb;
      MIHCB rbccb;
      
      void* lbdcbp;
      void* lbucbp;
      void* lbccbp;
      void* rbdcbp;
      void* rbucbp;
      void* rbccbp;
  
};

void MouseInputHandler::polling_function(void*p)
{
     MouseInputHandler * m=(MouseInputHandler*)p;
     
     m->input.quit=false;
     
     HWND window=GetConsoleWindow();
     RECT wpos;
     POINT cpos;
     
     
     m->input.cleft=m->input.pleft=m->input.cright=m->input.pright=false;
     int x,y;
     
     
          
     while (!m->input.quit)
     {
           GetWindowRect(window,&wpos);
           GetCursorPos(&cpos);
           
           cpos.x-=wpos.left;
           cpos.y-=wpos.top;
           
           //transform screen to console coords
           x=(cpos.x-5)/8;           
           y=(cpos.y-25)/12;
           
           m->input.cleft=is_pressed(VK_LBUTTON);
           m->input.cright=is_pressed(VK_RBUTTON);
           
           //mouse up event: it was down and now is up
           if (!m->input.cleft && m->input.pleft)
           {
              m->lbucb(x,y,m->lbucbp);
           }
           
           //...more stuff here
           
           m->input.pleft=m->input.cleft;
           //m->input.pright=m->input.cright;
     
           Sleep(10);
     }
     m->polling=false;
}

void left_up(int x, int y, void*p)
{
     //intf("left button up at (%d,%d)\n",x,y);
     Mouse.x=x;
     Mouse.y=y;
	 if(MouseMode==1)
	 {
	 	if(x>=10 && x<=16 && y>=1 && y<=3)
     	{
     		F.Save();
     	
	    }
     	else if(x>=0 && x<=8 && y>=1 && y<=3)
    	{
     		F.Exit();
 	    }
    	 else if(x>=0 && x<65 && y>=10 && y<40)
		{
    	 	F.ChangePos(x,y);
	    }
     	else if(x>18 && x<=25 && y>=1 && y<=3)	
   	  	{
     		F.Find();
     	}
     	else if(x>27 && x<=36 && y>=1 && y<=3)
     	{
     		F.ClearAll();
     	}
 	 }
 	 else
 	 {
 	 	if(x>=32 && x<=46 && y>=20 && y<=23)
		{
			TextMode=1;
		}
		else if(x>=32 && x<=46 && y>=25 && y<=28)
		{
			TextMode=2;
		}  
		else if(x>=10 && x<=16 && y>=1 && y<=3)
     	{
     		gotoxy(35,32);
     		cout<<"Invalid";
     		Sleep(100);
     		gotoxy(35,32);
			cout<<"       ";
     	
	    }
		else if(x>=0 && x<=8 && y>=1 && y<=3)
    	{
     		F.Exit();
 	    }
 	    
		else if(x>18 && x<=25 && y>=1 && y<=3)	
   	  	{
     		gotoxy(35,32);
     		cout<<"Invalid";
     		Sleep(100);
     		gotoxy(35,32);
     		cout<<"       ";
     	
    	}
    	
    	else if(x>27 && x<=36 && y>=1 && y<=3)
   	  	{
     		gotoxy(35,32);
     		cout<<"Invalid";
     		Sleep(100);
     		gotoxy(35,32);
     		cout<<"       ";
     	
    	}
 	 }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Function to draw the Menu Bar
void Menu()
{
	DrawRect(0,0,7,3,0,0);
	BColor(252);cout<<endl;
	gotoxy(2,2);
	cout<<"Exit";
	gotoxy(11,2);
	cout<<"Save";
	BColor(241);cout<<endl;
	DrawRect(9,0,7,3,0,0);
	DrawRect(18,0,7,3,0,0);
	BColor(252);cout<<endl;
	gotoxy(20,2);
	cout<<"Find";
	BColor(241);cout<<endl;
	DrawRect(27,0,8,3,0,0);
	BColor(252);cout<<endl;
	gotoxy(29,2);
	cout<<"Clear";
	BColor(241);
	cout<<endl<<endl<<endl;Line();cout<<endl<<endl;
}

int main()
{

	WindowSize(50,50,700,600);
	BColor(241);
	cout<<endl;
	SetConsoleTitle(TEXT("TextMate"));
	COORD bufferSize = {80, 50};
	system("cls");
	Font(8,12);

	Menu();	
	
	gotoxy(15,15);
	
	MouseInputHandler mouse;
    mouse.set_lbucb(left_up);
        
    mouse.start_polling();
	
	
	DrawRect(32,20,14,3);
	BColor(252);
	cout<<endl;
	gotoxy(38,22);
	cout<<"New";
	BColor(241);
	cout<<endl;
	DrawRect(32,25,14,3);
	BColor(252);
	cout<<endl;
	gotoxy(38,27);
	cout<<"Open";
	BColor(241);
	cout<<endl;
	TextMode=0;
	
	while(TextMode==0)
	{
		Sleep(100);
	}
	
	MouseMode=1;
	
	if (TextMode==1)
	{
		system("cls");
		Menu();
		F.New();
	}
	else if(TextMode==2)
	{
		system("cls");
		Menu();
		F.Open();
	}
	else
	{
		cout<<"Impossible Situation!!Please Report If This Message Is Displayed";
	}
		
	mouse.stop_polling();
	return (0);
}
