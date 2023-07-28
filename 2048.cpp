#include <bits/stdc++.h>

using namespace std;
int board[4][4];
int dirline[]={1,0,-1,0};
int dircol[]={0,1,0,-1};
pair<int,int>generateUnoccupiedPosition()
{
    int occupied=1;int line;int coloumn;
    while(occupied)
    {
         line=rand()%4;
         coloumn=rand()%4;
        if(board[line][coloumn]==0)
        occupied=0;
    }
    return {line,coloumn};
}
void addPiece()
{
    pair<int,int>pos=generateUnoccupiedPosition();
    board[pos.first][pos.second]=2;
}
void newgame()
{
    for(int i=0;i<4;++i)
         for(int j=0;j<4;++j)
            board[i][j]=0;
    addPiece();
}
void printUI()
{   
    system("cls");
    for(int i=0;i<4;++i)
    {   for(int j=0;j<4;++j)
            if(board[i][j]==0)
            cout<<setw(4)<<".";
            else
            cout<<setw(4)<<board[i][j];
            cout<<endl;
    }
    cout<<"n:new game, w:up, s:down, d:right, a:left, q:quit"<<endl;
}


bool canDoMove(int line,int col,int nextline,int nextcol)
{
    if(nextline<0 || nextcol<0 || nextline>=4 || nextcol>=4
     || board[line][col]!=board[nextline][nextcol] && board[nextline][nextcol]!=0 )
    return false;
    return true;
}   

void applyMove(int direction)
{
    int startline=0,startcol=0,linestep=1,colstep=1;
    if(direction==0)
    {
        startline=3;
        linestep=-1;
    }
    if(direction==1)
    {
        startcol=3;
        colstep=-1;
    }
    int movePossible=0,canAddPiece=0,rowcnt=0,colcnt=0;
    do{
        movePossible=0;
        
    for(int i=startline;i>=0 && i<4;i+=linestep)
         for(int j=startcol;j>=0 && j<4;j+=colstep)
         {
            int nextI=i+dirline[direction];
            int nextJ=j+dircol[direction];
           if(board[i][j] && canDoMove(i,j,nextI,nextJ))
           {
             
            //  if((direction==0 || direction==2) && rowcnt==0 )
            //  {  board[nextI][j]+=board[i][j];
            //     rowcnt=1;
            //     board[i][j]=0;
            //  }  
            //  if((direction==1 || direction==3) && colcnt==0)
            //  {board[i][nextJ]+=board[i][j];
            //  colcnt=1;
            //  board[i][j]=0;
            //  }
             board[nextI][nextJ]+=board[i][j];

             board[i][j]=0;
             movePossible=canAddPiece=1;
           }
         }
        // printUI();
    }while(movePossible);
     if(canAddPiece==1)
     addPiece();    
}
int main(){
    srand(time(0));
    unordered_map<char,int>commandtodir;
    commandtodir['s']=0;
    commandtodir['d']=1;
    commandtodir['w']=2;
    commandtodir['a']=3;
    newgame();
while(true)
{   printUI();
    char command;
    cin>>command;
    if(command=='n')
    newgame();
    else if(command=='q')
    break;
    else
    {
        int currentdirection=commandtodir[command];
        applyMove(currentdirection);
    }
}
return 0;
}