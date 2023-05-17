#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include <dos.h>
#include <conio.h>
#include<unistd.h>
#include <string>



#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define MINX 2
#define MINY 2
#define MAXX 49
#define MAXY 19


using namespace std;

unsigned int ball_posx=SCREEN_HEIGHT/2; //yükseklik
unsigned int ball_posy=SCREEN_WIDTH/2; // geniþlik
unsigned int b1_ymove=1;
unsigned int b1_xmove=0;
unsigned int paddle_x = 22;
unsigned int paddle_y = SCREEN_WIDTH/2-3;
unsigned int r1_move = 1;

int isgamewin=0;
int isgamestart=0;
int isendgame=0;
int heal=5;
int score=0;
void playGame();
void start_game();
void endgame();


HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

void gotoxy(int x, int y)
{

    CursorPosition.X=x;
    CursorPosition.Y=y;
    SetConsoleCursorPosition(console,CursorPosition);
}


void resetgame(){
ball_posx=SCREEN_HEIGHT/2; //yükseklik
ball_posy=SCREEN_WIDTH/2; // geniþlik
b1_ymove=1;
b1_xmove=0;
paddle_x = 22;
paddle_y = SCREEN_WIDTH/2-3;
r1_move = 1;

int isgamewin=0;
int isgamestart=0;
int isendgame=0;
int heal=5;
int score=0;
}

void setcursor(bool visible, DWORD size) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
    if(size == 0)
    {
        size = 20;	// default cursor size Changing to numbers from 1 to 20, decreases cursor width
    }
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console,&lpCursor);
}


int init_board[25][80];
int bricks[25][80];

void initboard()
{

    for (int i=0; i<25; i++)
    {
        for (int j=0; j<80; j++)
        {

            if((i>2 && i<8) && (j>10 && j<70) )
            {


                if(i==5)
                {
                    continue;
                }
                for(int k=0; k<2; k++)
                {

                    for(int m=0; m<6; m++)
                    {
                        bricks[i][j]=1;
                        init_board[i][j]=1;
                        j++;
                    }
                    j=j+4;


                }

            }
            else
            {
                init_board[i][j]=0;
                bricks[i][j]=0;

                if(i==0 || i==24)
                {
                    init_board[i][j]=2;
                    bricks[i][j]=2;
                }

                if(j==0 || j==79)
                {
                    init_board[i][j]=2;
                    bricks[i][j]=2;

                }
            }
        }
    }
}


void draw_gameborder()
{
    for(int i=0; i<SCREEN_WIDTH; i++)
    {
        gotoxy(i,0);
        cout<<"%";
        gotoxy(i,SCREEN_HEIGHT-1);
        cout<<"%";
    }

    for(int i=0; i<SCREEN_HEIGHT; i++)
    {
        gotoxy(0,i);
        cout<<"%";
        gotoxy(SCREEN_WIDTH,i);
        cout<<"%";
    }
}


void draw_initboard()
{


    for (int i=0; i<SCREEN_HEIGHT; i++)
    {

        for (int j=0; j<SCREEN_WIDTH; j++)
        {

            if(bricks[i][j]==1)
            {
                gotoxy(j,i);
                cout <<"#" ;
            }
            if(init_board[i][j]==0)
            {
                gotoxy(j,i);
                cout <<" ";
            }


        }
    }
}


void draw_strxy(string str, int x,  int y)
{
    gotoxy(y,x);
    cout << str;
}


void draw_paddle()
{
    string paddle = "=========";

    draw_strxy(paddle,paddle_x,paddle_y);
}

void clear_paddle()
{
    string clearpaddle = "         ";
    draw_strxy(clearpaddle,paddle_x,paddle_y);
}

void draw_ball()
{

    string ball = "O";
    draw_strxy(ball,ball_posx,ball_posy);
}

void clear_ball()
{
    string clearball = " ";
    draw_strxy(clearball,ball_posx,ball_posy);
}

void move_paddle_right()
{

    clear_paddle();
    if(paddle_y<69)
    {
        paddle_y = paddle_y+2;
        draw_paddle();
    }


}

void move_paddle_left()
{

    clear_paddle();
    if(paddle_y>1)
    {
        paddle_y = paddle_y-2;
        draw_paddle();
    }


}

void Check_collision(int ballx,int bally)
{

    int a = 0;
    int b = 0;


    while(init_board[ballx][bally+a]!=0)
    {

        bricks[ballx][bally+a]=0;
        a = a + 1;
    }


    while(init_board[ballx][bally-b]!=0)
    {

        bricks[ballx][bally-b]=0;
        b = b + 1;
    }





    system("cls");
    draw_paddle();
    draw_gameborder();
    draw_initboard();


}

void start_game(){
    resetgame();
    heal=5;
    score=0;
 setcursor(0,0);
    system("cls");


            draw_strxy(" _____     _     _      _____             _                                ",2,20);
            draw_strxy("| __  |___|_|___| |_   | __  |___ ___ ___| |_ ___ ___    ___ ___ _____ ___  ",3,20);
            draw_strxy("| __ -|  _| |  _| '_|  | __ -|  _| -_| .'| '_| -_|  _|  | . | .'|     | -_| ",4,20);
            draw_strxy("|_____|_| |_|___|_,_|  |_____|_| |___|__,|_,_|___|_|    |_  |__,|_|_|_|___| ",5,20);


        draw_strxy("Ana Menu " ,1,40);

         draw_strxy("OYUNA BASLAMAK ICIN SPACE BASINIZ" ,10,20);

	char op = _getche();

            int i = 5;

		if( op==32) {
		    int i =5;
		    for(i=5;i>0;i--){
                std::string strsayac = std::to_string(i);
                draw_strxy("OYUN BASLAMASINA "+ strsayac + " SANIYE KALDI" ,15,20);
                Sleep(1000);
                 }

            system("cls");
            isgamestart=1;
             setcursor(0,0);
            initboard();
            draw_gameborder();
            draw_initboard();
            playGame();

		   }

}

void playGame()
{

    while(1)
    {
    if(isgamestart==0){
    break;
    }
else{
        Sleep(150);
        std::string strheal = std::to_string(heal);
        std::string strscore = std::to_string(score);

        draw_strxy("Heal : "+ strheal,1,60);
         draw_strxy("Score : "+ strscore,1,10);

        draw_paddle();
        clear_ball();
        ball_posx = ball_posx + b1_ymove;
        ball_posy = ball_posy - b1_xmove;
        draw_ball();

        int i = ball_posx;
        int j = ball_posy;
        if( bricks[i][j]==1)
        {
            b1_ymove=-b1_ymove;
            Check_collision(i,j);
            score=score+10;

            if(score==120){
                system("cls");
                isgamewin=1;
                isgamestart=0;
                isendgame=1;
                endgame();
            }



        }

        // === === ===

        if(ball_posx+1==paddle_x)
        {
            if(ball_posy==paddle_y+0)
            {

                b1_ymove=-b1_ymove;
                b1_xmove=1;

            }

             if(ball_posy==paddle_y+1)
            {

                b1_ymove=-b1_ymove;
                b1_xmove=1;

            }
             if(ball_posy==paddle_y+2)
            {

                b1_ymove=-b1_ymove;
                b1_xmove=1;

            }



            if((ball_posy==paddle_y+3)|| (ball_posy==paddle_y+4)|| (ball_posy==paddle_y+5))
            {

                b1_ymove=-b1_ymove;
                b1_xmove=0;

            }



            if((ball_posy==paddle_y+6)|| (ball_posy==paddle_y+7)|| (ball_posy==paddle_y+8))
            {

                b1_ymove=-b1_ymove;
                b1_xmove=-1;

            }
        }

        if(ball_posx==1)
        {

            b1_ymove=-b1_ymove;
            b1_xmove=b1_xmove;
        }

        if(ball_posy<2 ||ball_posy>78)
        {
            b1_ymove=b1_ymove;
            b1_xmove=-b1_xmove;
        }

        if(ball_posx==SCREEN_HEIGHT-2 )
        {
            if(heal==1){
                isgamewin=0;
                isgamestart=0;
                isendgame=1;
                endgame();


            }
            else{
                heal--;

            clear_ball();
            clear_paddle();
            ball_posx=SCREEN_HEIGHT/2; //yükseklik
            ball_posy=SCREEN_WIDTH/2; // geniþlik
            b1_ymove=1;
            b1_xmove=0;
            paddle_x = 22;
            paddle_y = SCREEN_WIDTH/2-3;
            r1_move = 1;
            }
        }

        if(_kbhit())
        {

            char ch = _getch();
            if( ch=='d'||ch=='D')
            {

                clear_paddle();
                move_paddle_right();
                draw_paddle();


            }
           else if( ch=='a'||ch=='A')
            {

                if(paddle_y != 1)
                {

                    clear_paddle();
                    move_paddle_left();
                    draw_paddle();
                }



            }


        }
    }
}}

void endgame(){

    setcursor(0,0);
    system("cls");


            draw_strxy(" _____     _     _      _____             _                                ",2,20);
            draw_strxy("| __  |___|_|___| |_   | __  |___ ___ ___| |_ ___ ___    ___ ___ _____ ___  ",3,20);
            draw_strxy("| __ -|  _| |  _| '_|  | __ -|  _| -_| .'| '_| -_|  _|  | . | .'|     | -_| ",4,20);
            draw_strxy("|_____|_| |_|___|_,_|  |_____|_| |___|__,|_,_|___|_|    |_  |__,|_|_|_|___| ",5,20);
            draw_strxy("                                                        |___|               ",6,20);


    if(isgamewin==1){
    draw_strxy("TEBRIKLER OYUNU KAZANDINIZ ",15,20);
}
else{

    draw_strxy("UZGUNUM OYUNU KAYBETTINIZ ",15,20);

}

 draw_strxy(" ANA MENUYE DONMEK ICIN SPACE BASINIZ",20,20);
while(1){

    if(isendgame==0){
        system("cls");
        break;
    }

    if(_kbhit())
        {

            char ch = _getch();
            if( ch==32)
            {

               isendgame=0;

            }

    }


}
start_game();
}

int main()
{

    start_game();
}




