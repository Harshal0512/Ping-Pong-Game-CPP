/******************************

         Ping-Pong Game
    Author: Harshal Kulkarni

******************************/

/************Header Files************/
#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<stdio.h>
#include<dos.h>
#include<time.h>
/************************************/

/************Definitions************/
#define ROW 20
#define COL 39
#define NE 45   
#define SE 135
#define NW 315
#define SW 225
#define P1 1
#define P2 2
/***********************************/

/**************Structure**************/
typedef struct Ball{
    int x;
    int y;
    int dir;
};

Ball ball;
/*************************************/

/************Function Prototypes************/
void projectileCalculator();
void printBoard(int LPlayer[3], int RPlayer[3]);
/*******************************************/

/************Global Variables************/
int score1, score2;
char LDir, RDir;
int LTemp, RTemp;
/****************************************/

void projectileCalculator(){
    int flag1=0, flag2=0, flag3=0, flag4=0;
    if(ball.x<=1 || ball.x>=ROW-1){
        if(ball.dir==NE)
            ball.dir=SE;
        else if(ball.dir==SE)
            ball.dir=NE;
        else if(ball.dir==NW)
            ball.dir=SW;
        else if(ball.dir==SW)
            ball.dir=NW;
    }
    
    /*To make the path a little random*/
    if(rand()%73==0)
        flag1=1;
    if(rand()%117==0)
        flag2=1;
    if(rand()%259==0)
        flag3=1;
    if(rand()%193==0)
        flag4=1;
    /**********************************/

    if(ball.dir==NE){
        if(flag1==0 && ball.x>1)
        ball.x--;
        if(flag3==0)
        ball.y++;
    }else if(ball.dir==SE){
        if(flag2==0 && ball.x<ROW-1)
        ball.x++;
        if(flag1==0)
        ball.y++;
    }else if(ball.dir==NW){
        if(flag4==0 && ball.x>1)
        ball.x--;
        if(flag3==0)
        ball.y--;
    }else if(ball.dir==SW){
        if(flag2==0 && ball.x<ROW-1)
        ball.x++;
        if(flag4==0)
        ball.y--;
    }
    //delay(50);
}

void printBoard(int LPlayer[3], int RPlayer[3]){
    clrscr();
    int i, j, board[ROW][COL]={0};
    /***Plot players on board***/
    for(i=0; i<3; i++){
        board[ LPlayer[i] ][1]=P1;
    }
    for(i=0; i<3; i++){
        board[ RPlayer[i] ][COL-2]=P2;
    }
    board[ball.x][ball.y]=3;
    /****Print board****/
    cout<<"\t\t     Player 1 Score:"<<score1<<"     Player 2 Score:"<<score2<<"\n";
    for(i=0; i<ROW; i++){
        if(i==0)
            cout<<"________________________________________________________________________________|";
        else
            cout<<"|"; //to leave one margin gap on left side
        for(j=0; j<COL; j++){
            if(board[i][j]==P1 || board[i][j]==P2){
                cout<<"||";
            }else if(board[i][j]==3){
                cout<<"O ";
            }else{
                if(j==COL-1)
                    cout<<" |";
                else
                    cout<<"  "; //to leave one margin gap in between as well as on right side
            }
        }
        cout<<"\n";
    }
    cout<<"________________________________________________________________________________";
    delay(50);
}

void main(){
    srand(time(NULL));
    ball.dir=SW;
    label:
    int LPlayer[3] = {8, 9, 10}, RPlayer[3] = {8, 9, 10};
    LDir=RDir='N';
    ball.x=9;
    ball.y=19;
    /*
    Left Player:- W & S
    Right Player:- I & J
    U-up
    D-down
    dir:
        NE-45
        SE-135
        NW-315
        SW-225
    */
    while(1){
        if(kbhit()){ //if key pressed
            char ch;
            ch=getch();
            cout<<ch;
            if(int(ch)=='w' || int(ch)=='w'){
                LDir='U';
            }
            else if(int(ch)=='s' || int(ch)=='S'){
                LDir='D';
            }
            if(int(ch)=='i' || int(ch)=='I'){
                RDir='U';
            }
            else if(int(ch)=='j' || int(ch)=='J'){
                RDir='D';
            }
            if(int(ch)=='q' || int(ch)=='Q')
                exit(0);

            if(LDir == 'U' && LPlayer[0]>0){
                int i, x1, temp1=LPlayer[0];
                for(i=1; i<3; i++){ //every other part follows the direction of head
                    x1=LPlayer[i]; //if going up, top part will move first hence i<3
                    LPlayer[i]=temp1;
                    temp1=x1;
                }
                LPlayer[0]--;
                LTemp='U';
                LDir='N'; //this is important because when any key is pressed the left or right one was moving regardless of which key is pressed
            }else if(LDir == 'D' && LPlayer[2]<19){
                int j, x1, temp1=LPlayer[2];
                for(j=1; j>=0; j--){ //if going down, bottom part will move first hence j>=0
                    x1=LPlayer[j];
                    LPlayer[j]=temp1;
                    temp1=x1;
                }
                LPlayer[2]++;
                LTemp='D';
                LDir='N';
            }
            if(RDir == 'U' && RPlayer[0]>0){
                int k, x1, temp1=RPlayer[0];
                for(k=1; k<3; k++){
                    x1=RPlayer[k];
                    RPlayer[k]=temp1;
                    temp1=x1;
                }
                RPlayer[0]--;
                RTemp='U';
                RDir='N';
            }else if(RDir == 'D' && RPlayer[2]<19){
                int l, x1, temp1=RPlayer[2];
                for(l=1; l>=0; l--){
                    x1=RPlayer[l];
                    RPlayer[l]=temp1;
                    temp1=x1;
                }
                RPlayer[2]++;
                RTemp='D';
                RDir='N';
            }
        }
        if(ball.y==2 || ball.y==COL-3){
            if( (ball.x==LPlayer[0] || ball.x==LPlayer[1] || ball.x==LPlayer[2]) && ball.y==2){ //ball collides with left
                if(LTemp=='U'){
                    ball.dir=NE;
                }else if(LTemp=='D'){
                    ball.dir=SE;
                }
            }else if( (ball.x==RPlayer[0] || ball.x==RPlayer[1] || ball.x==RPlayer[2]) && ball.y==COL-3){ //ball collides with right
                if(RTemp=='U'){
                    ball.dir=NW;
                }else if(RTemp=='D'){
                    ball.dir=SW;
                }
            }else{
                /**************Game-Over Condition**************/
                if(ball.y==2){
                    cout<<"\n\t\t\t       Player 2 Score +1";
                    delay(1000);
                    score2++;
                    ball.dir=SE;
                    goto label;
                }
                if(ball.y==COL-3){
                    cout<<"\n\t\t\t       Player 1 Score +1";
                    delay(1000);
                    score1++;
                    ball.dir=SW;
                    goto label;
                }
            }
            /***************************************************/
        }
        projectileCalculator();
        printBoard(LPlayer, RPlayer);
    }
}